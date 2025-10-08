// wedForecast.cpp
// Uses nlohmann/json (header-only)
// CIT-66 – Fresno City College
// Professor Dennis Mohle – Oct 8, 2025

// 🧭 Instructions:
// 1. Adjust your CMakeLists.txt to include your project's include folder:
//        include_directories("C:/2025_Fall/cppCIT66/wedWarmUpCode/include")
// 2. Then go to CLion → File → Reload CMake Project
// 3. Finally, click the white hammer (Build) next to the green Run button.

#include <iostream>
#include <windows.h>   // for SetConsoleOutputCP
#include "include/json.hpp"    // from include folder

using namespace std;
using json = nlohmann::json;

int main() {
    // Enable UTF-8 output in Windows console
    SetConsoleOutputCP(CP_UTF8);

    cout << "\n🧠 JSON DEMO — Local Weather Example\n\n";

    json weather = {
        {"city", "Fresno"},
        {"state", "California"},
        {"forecast", {
                {"temperature", 88},
                {"unit", "F"},
                {"condition", "Sunny"}
        }},
        {"recommendation", "No — it’s warm enough today."}
    };

    cout << "Weather object:\n" << weather.dump(4) << "\n\n";
    cout << "Temperature: " << weather["forecast"]["temperature"]
         << "°" << weather["forecast"]["unit"] << "\n";

    cout << "\n✅ Program complete.\n";
    return 0;
}