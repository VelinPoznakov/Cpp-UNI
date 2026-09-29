//
// Created by Velin Poznakov on 9/29/2026.
//

#include "Employee.h"
#include <string>

Employee::Employee(std::string name, int age, std::string currentPosition, double salaries[]) {
    setName(name);
    setAge(age);
    setCurrentPosition(currentPosition);

    for (int i = 0; i < sizeof(salaries) / sizeof(salaries[0]); i++)
        setSalaries(salaries[i]);
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
    int length = std::size(this->salaries);

    this->salaries[length] = salary;
}

int Employee::getAverageSalary() {
    double sum = 0;

    int length = std::size(this->salaries);

    for (double salary: this->salaries) {
        sum += salary;
    }

    return sum / length;
}

int Employee::getMinimalSalary() {
    double min = this->salaries[0];

    for (double salary: this->salaries) {
        if (salary < min) {
            min = salary;
        }
    }

    return min;
}

std::string Employee::getSalaries() {
    std::string salariesString = "";

    for (double salary: this->salaries) {
        salariesString += std::to_string(salary) + " ";
    }

    return salariesString;
}


