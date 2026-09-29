#include "Line.h"
#include <iostream>
#include <stdexcept>
#include <string>

Line::Line(int length) : Len(length) {
    if (Len <= 0)
        throw std::invalid_argument("Line length must be positive");
    draw();
}

void Line::draw() const {
    std::cout << std::string(Len, '*') << std::flush;
}

void Line::erase() const {
    std::cout << '\r' << std::string(Len, ' ') << '\r' << std::flush;
}