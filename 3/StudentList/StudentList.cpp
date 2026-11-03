//
// Created by Velin Poznakov on 10/29/2026.
//

#include "StudentList.h"
#include <iostream>
#include <stdexcept>

StudentList::StudentList(int capacity) {
    if (capacity <= 0)
        throw std::invalid_argument("Capacity must be positive");

    this->capacity = capacity;
    this->students = new Student[capacity];
}

StudentList::~StudentList() {
    delete[] students;
}

void StudentList::grow() {
    Student *bigger = new Student[capacity * 2];

    for (int i = 0; i < size; i++)
        bigger[i] = students[i];

    delete[] students;
    students = bigger;
    capacity *= 2;
}

void StudentList::add(const Student &s) {
    if (size == capacity)
        grow();

    students[size++] = s;
}

Student &StudentList::getBest() {
    if (size == 0)
        throw std::underflow_error("Student list is empty");

    int best = 0;

    for (int i = 1; i < size; i++) {
        if (students[i].getGrade() > students[best].getGrade())
            best = i;
    }

    return students[best];
}

const Student &StudentList::getByIndex(int i) const {
    if (i < 0 || i >= size)
        throw std::out_of_range("Student index out of range");

    return students[i];
}

void StudentList::swapStudents(int i, int j) {
    if (i < 0 || i >= size || j < 0 || j >= size)
        throw std::out_of_range("Student index out of range");

    Student &first = students[i];
    Student &second = students[j];

    Student temp = first;
    first = second;
    second = temp;
}

void StudentList::print() const {
    for (int i = 0; i < size; i++) {
        std::cout << i << ". ";
        students[i].print();
    }
}
