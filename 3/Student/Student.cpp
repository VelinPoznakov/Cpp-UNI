//
// Created by Velin Poznakov on 10/29/2026.
//

#include "Student.h"
#include <cstring>
#include <iostream>
#include <stdexcept>

Student::Student() {
    setName("");
}

Student::Student(const char *name, int facultyNumber, double grade) {
    setName(name);
    setFacultyNumber(facultyNumber);
    setGrade(grade);
}

Student::~Student() {
    delete[] name;
}

Student::Student(const Student &other) {
    setName(other.name);
    this->facultyNumber = other.facultyNumber;
    this->grade = other.grade;
}

Student &Student::operator=(const Student &other) {
    if (this != &other) {
        setName(other.name);
        this->facultyNumber = other.facultyNumber;
        this->grade = other.grade;
    }

    return *this;
}

void Student::setName(const char *name) {
    if (name == nullptr)
        throw std::invalid_argument("Name must not be null");

    char *copy = new char[std::strlen(name) + 1];
    std::strcpy(copy, name);

    delete[] this->name;
    this->name = copy;
}

void Student::setFacultyNumber(int facultyNumber) {
    if (facultyNumber <= 0)
        throw std::invalid_argument("Faculty number must be positive");

    this->facultyNumber = facultyNumber;
}

void Student::setGrade(double grade) {
    if (grade < 2 || grade > 6)
        throw std::invalid_argument("Grade must be between 2 and 6");

    this->grade = grade;
}

void Student::print() const {
    std::cout << name << " (" << facultyNumber << "), grade: " << grade << '\n';
}
