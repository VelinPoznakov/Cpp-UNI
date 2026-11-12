//
// Created by Velin Poznakov on 11/12/2026.
//

#include "Car.h"
#include <iostream>
#include <stdexcept>

// The wheels and the range belong to Vehicle, so they are passed on to its constructor
Car::Car(int passengers, int numWheels, int range) : Vehicle(numWheels, range) {
    setPassengers(passengers);
}

void Car::setPassengers(int passengers) {
    if (passengers <= 0)
        throw std::invalid_argument("Passengers must be positive");

    this->passengers = passengers;
}

void Car::show() const {
    showv();
    std::cout << "Passengers: " << passengers << '\n';
}
