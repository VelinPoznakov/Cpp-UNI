//
// Created by Velin Poznakov on 11/12/2026.
//

#include "Vehicle.h"
#include <iostream>
#include <stdexcept>

Vehicle::Vehicle(int numWheels, int range) {
    setNumWheels(numWheels);
    setRange(range);
}

void Vehicle::setNumWheels(int numWheels) {
    if (numWheels <= 0)
        throw std::invalid_argument("Number of wheels must be positive");

    this->numWheels = numWheels;
}

void Vehicle::setRange(int range) {
    if (range <= 0)
        throw std::invalid_argument("Range must be positive");

    this->range = range;
}

void Vehicle::showv() const {
    std::cout << "Wheels: " << numWheels << '\n';
    std::cout << "Range: " << range << '\n';
}
