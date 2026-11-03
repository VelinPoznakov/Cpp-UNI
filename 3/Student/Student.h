//
// Created by Velin Poznakov on 10/29/2026.
//

#ifndef INC_3_STUDENT_H
#define INC_3_STUDENT_H


class Student {
    char *name = nullptr;
    int facultyNumber = 0;
    double grade = 2;

public:
    Student();
    Student(const char *name, int facultyNumber, double grade);
    ~Student();

    // name is a char*, so copies need their own memory for it
    Student(const Student &other);
    Student &operator=(const Student &other);

    void setName(const char *name);
    void setFacultyNumber(int facultyNumber);
    void setGrade(double grade);

    const char *getName() const {return name;}
    int getFacultyNumber() const {return facultyNumber;}
    double getGrade() const {return grade;}

    void print() const;
};


#endif //INC_3_STUDENT_H
