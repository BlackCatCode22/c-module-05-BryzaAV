#include <iostream>
using std::string;
using namespace std;

class abstractEmployee {
    virtual void askForPromotion()=0;
};

class employee:abstractEmployee {
private:
    string name;
    string company;
    int age;

public:
    void setName(string name) {
        name = name;
    }
    string getName() {
        return name;
    }
    void setCompany(string company) {
        company = company;
    }
    string getCompany() {
        return company;
    }
    void setAge(int age) {
        if (age>= 18) {
            age = age;
        }
        else {
            cout << "\n Age must be 18 or older. Setting age to 18." << endl;
            age = 18;
        }
    }
    int getAge() {
        return age;
    }

    void introduceYourself() {
        std::cout << "Name - " << name << std::endl;
        std::cout << "Company - " << company << std::endl;
        std::cout << "Age - " << age << std::endl;
    }
public:
    employee(string name, string company, int age) {
        name = name;
        company = company;
        age = age;
    }
    void askForPromotion() {
        if (age >30)
            std::cout << name << " got promoted! " << std::endl;
        else
            std::cout << name << " ,sorry not promoted! " << std::endl;
    }
};
class developer:public
employee {
    public:

    string favProgramingLanguage;
    developer(string name, string company, int age, string favProgramingLanguage)
        : employee(name, company, age) {
        favProgramingLanguage = favProgramingLanguage;
    }
    void fixBug() {
        std::cout << name << "fixed bug using " << favProgramingLanguage << std::endl;
    }
};

int main() {
    employee employee1 = employee("Bryza", "Apple", 19);
    employee employee2 = employee("John", "Amazon", 30);

   developer d=developer( "Bryza", "Apple", 19, "C++");
    d.fixBug();
    d.fixBug();
    d.fixBug ();
    d.askForPromotion();


    return 0;
}