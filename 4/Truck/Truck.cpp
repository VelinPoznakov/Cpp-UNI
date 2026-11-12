//
// Created by Velin Poznakov on 11/12/2026.
//

#include "Truck.h"
#include <iostream>
#include <stdexcept>

Truck::Truck(int loadLimit, int numWheels, int range) : Vehicle(numWheels, range) {
    setLoadLimit(loadLimit);
}

void Truck::setLoadLimit(int loadLimit) {
    if (loadLimit <= 0)
        throw std::invalid_argument("Load limit must be positive");

    this->loadLimit = loadLimit;
}

void Truck::show() const {
    showv();
    std::cout << "Load limit: " << loadLimit << '\n';
}
