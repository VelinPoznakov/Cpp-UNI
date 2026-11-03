//
// Created by Velin Poznakov on 10/29/2026.
//

#ifndef INC_3_ARRAY_H
#define INC_3_ARRAY_H


class Array {
    int size;
    char *p;

public:
    Array(int size);
    ~Array();

    // The class owns p, so copying would make two objects delete the same memory
    Array(const Array &) = delete;
    Array &operator=(const Array &) = delete;

    char &put(int i);
    char get(int i) const;

    int getSize() const {return size;}
};


#endif //INC_3_ARRAY_H
