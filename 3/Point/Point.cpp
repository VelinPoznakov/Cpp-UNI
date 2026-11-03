//
// Created by Velin Poznakov on 10/29/2026.
//

#include "Point.h"
#include <cmath>
#include <iostream>

Point::Point(double x, double y) {
    std::cout << "Creating Point(" << x << "," << y << ")\n";

    this->x = x;
    this->y = y;
}

Point::~Point() {
    std::cout << "Destructing ";
    print();
    std::cout << '\n';
}

void Point::print() const {
    std::cout << "Point(" << x << "," << y << ")";
}

double Point::dist(const Point &p1, const Point &p2) const {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
