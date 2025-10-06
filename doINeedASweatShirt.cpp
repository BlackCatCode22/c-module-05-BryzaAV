//doINeedASweatShirt.cpp
//BAV 10/06/2025

#include <iostream>
#include <string>
#include <curl/curl.h>
#include "nlohmann/json.hpp"  // Include the nlohmann/json header

using namespace std;
using json = nlohmann::json;

// Callback function for libcurl to store HTTP response data
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {

    cout << "\n Do I need a sweat shirt \n" << endl;

    const std::string url = "https://api.weather.gov/gridpoints/HNX/60,100/forecast";
    std::string response;

    // Initialize CURL
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize libcurl.\n";
        return 1;
    }

    // Set options
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // NWS requires a User-Agent header
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "User-Agent: FresnoWeatherStudentApp (student@fresnocitycollege.edu)");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Perform the GET request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "CURL error: " << curl_easy_strerror(res) << "\n";
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        return 1;
    }

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    try {
        // Parse the JSON response
        json data = json::parse(response);

        auto periods = data["properties"]["periods"];
        if (periods.empty()) {
            std::cerr << "No forecast data found.\n";
            return 1;
        }

        // Find "Today" forecast (first period)
        auto today = periods[0];
        int temp = today["temperature"];
        std::string unit = today["temperatureUnit"];
        std::string forecast = today["shortForecast"];

        std::cout << "Today's forecast for Fresno, CA:\n";
        std::cout << "Temperature: " << temp << " " << unit << "\n";
        std::cout << "Conditions: " << forecast << "\n\n";

        // Decide if sweatshirt is needed
        int thresholdF = 60; // You can adjust this comfort threshold
        if (temp <= thresholdF) {
            std::cout << "🧥 Yes, you should wear a sweatshirt today.\n";
        } else if (temp <= thresholdF + 8) {
            std::cout << "😐 Maybe — a light hoodie or sweatshirt would be nice.\n";
        } else {
            std::cout << "☀️ No, it's warm enough — no sweatshirt needed.\n";
        }

    } catch (std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
        return 1;
    }

    return 0;
}