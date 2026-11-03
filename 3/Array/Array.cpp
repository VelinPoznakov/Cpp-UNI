//
// Created by Velin Poznakov on 10/29/2026.
//

#include "Array.h"
#include <stdexcept>

Array::Array(int size) {
    if (size <= 0)
        throw std::invalid_argument("Array size must be positive");

    this->size = size;
    this->p = new char[size];
}

Array::~Array() {
    delete[] p;
}

char &Array::put(int i) {
    if (i < 0 || i >= size)
        throw std::out_of_range("Bounds error !!!");

    return p[i];
}

char Array::get(int i) const {
    if (i < 0 || i >= size)
        throw std::out_of_range("Bounds error !!!");

    return p[i];
}
