//
// Created by Velin Poznakov on 9/29/2026.
//

#include "Employee.h"
#include <string>

Employee::Employee(std::string name, int age, std::string currentPosition, double* salaries, int count) {
    setName(name);
    setAge(age);
    setCurrentPosition(currentPosition);

    for (int i = 0; i < count; i++)
        setSalary(salaries[i]);
}

void Employee::setAge(int age) {
    this->age = age;
}

void Employee::setCurrentPosition(std::string currentPosition) {
    this->currentPosition = currentPosition;
}

void Employee::setSocialNumber(int socialNumber) {
    this->socialNumber = socialNumber;
}

void Employee::setName(std::string name) {
    this->name = name;
}

void Employee::setYearsOfExperience(int yearsOfExperience) {
    this->yearsOfExperience = yearsOfExperience;
}

void Employee::setSalary(double salary) {
    if (salaryCount < MAX_SALARIES)
        this->salaries[salaryCount++] = salary;
}

int Employee::getAverageSalary() {
    double sum = 0;

    if (salaryCount == 0)
        return 0;

    for (int i = 0; i < salaryCount; i++) {
        sum += this->salaries[i];
    }

    return sum / salaryCount;
}

int Employee::getMinimalSalary() {
    double min = this->salaries[0];

    for (int i = 1; i < salaryCount; i++) {
        if (this->salaries[i] < min) {
            min = this->salaries[i];
        }
    }

    return min;
}

std::string Employee::getSalaries() {
    std::string salariesString = "";

    for (int i = 0; i < salaryCount; i++) {
        salariesString += std::to_string(this->salaries[i]) + " ";
    }

    return salariesString;
}


