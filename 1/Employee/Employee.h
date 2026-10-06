//
// Created by Velin Poznakov on 9/29/2026.
//

#ifndef INC_1_EMPLOYEE_H
#define INC_1_EMPLOYEE_H

#include <string>
using namespace std;


class Employee {
    static constexpr int MAX_SALARIES = 12;

    int socialNumber = 0;
    string name;
    int age;
    int yearsOfExperience = 0;
    string currentPosition;
    double salaries[MAX_SALARIES] = {};
    int salaryCount = 0;

public:
    Employee(std::string name, int age, std::string currentPosition, double salaries[], int count);

    void setSocialNumber(int socialNumber);
    void setName(std::string name);
    void setAge(int age);
    void setYearsOfExperience(int yearsOfExperience);
    void setCurrentPosition(std::string currentPosition);
    void setSalaries(double salary);

    int getSocialNumber() const {return socialNumber;}
    std::string getName() const {return name;}
    int getAge() const {return age;}
    int getYearsOfExperience() const {return yearsOfExperience;}
    std::string getCurrentPosition() const {return currentPosition;}
    std::string getSalaries();

    void setSalary(double salary);

    double getAverageSalary();
    double getMinimalSalary();


};


#endif //INC_1_EMPLOYEE_H
