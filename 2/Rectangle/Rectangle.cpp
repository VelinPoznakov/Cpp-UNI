//
// Created by Velin Poznakov on 10/15/2026.
//

#include "Rectangle.h"
#include <iostream>
#include <stdexcept>

Rectangle::Rectangle(double width, double height) {
    setWidth(width);
    setHeight(height);
}

Rectangle::~Rectangle() {
    std::cout << "Destructing object rectangle!\n";
}

void Rectangle::setWidth(double width) {
    if (width <= 0)
        throw std::invalid_argument("Width must be positive");

    this->width = width;
}

void Rectangle::setHeight(double height) {
    if (height <= 0)
        throw std::invalid_argument("Height must be positive");

    this->height = height;
}

double Rectangle::face() const {
    return width * height;
}

double Rectangle::face(double *perimeter) const {
    *perimeter = 2 * (width + height);

    return face();
}

void Rectangle::show(const std::string &name) const {
    std::cout << "Sides of the rectangle " << name << ": "
              << "a=" << width << ", b=" << height << '\n';
}
