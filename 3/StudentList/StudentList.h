//
// Created by Velin Poznakov on 10/29/2026.
//

#ifndef INC_3_STUDENTLIST_H
#define INC_3_STUDENTLIST_H

#include "../Student/Student.h"


class StudentList {
    Student *students;
    int capacity;
    int size = 0;

    void grow();

public:
    StudentList(int capacity);
    ~StudentList();

    // The class owns students, so copying would make two objects delete the same memory
    StudentList(const StudentList &) = delete;
    StudentList &operator=(const StudentList &) = delete;

    void add(const Student &s);
    Student &getBest();
    const Student &getByIndex(int i) const;
    void swapStudents(int i, int j);

    int getSize() const {return size;}

    void print() const;
};


#endif //INC_3_STUDENTLIST_H
