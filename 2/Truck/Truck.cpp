//
// Created by Velin Poznakov on 10/15/2026.
//

#include "Truck.h"
#include <stdexcept>

Truck::Truck(int weight, int speed) {
    setWeight(weight);
    setSpeed(speed);
}

void Truck::setWeight(int weight) {
    if (weight <= 0)
        throw std::invalid_argument("Weight must be positive");

    this->weight = weight;
}

void Truck::setSpeed(int speed) {
    if (speed <= 0)
        throw std::invalid_argument("Speed must be positive");

    this->speed = speed;
}

double travelTime(Truck t, double km) {
    if (km < 0)
        throw std::invalid_argument("Distance cannot be negative");

    return km / t.speed;
}
