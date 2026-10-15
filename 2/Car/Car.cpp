//
// Created by Velin Poznakov on 10/15/2026.
//

#include "Car.h"
#include "../Truck/Truck.h"
#include <stdexcept>

Car::Car(int passengers, int speed) {
    setPassengers(passengers);
    setSpeed(speed);
}

void Car::setPassengers(int passengers) {
    if (passengers < 0)
        throw std::invalid_argument("Passengers cannot be negative");

    this->passengers = passengers;
}

void Car::setSpeed(int speed) {
    if (speed <= 0)
        throw std::invalid_argument("Speed must be positive");

    this->speed = speed;
}

int Car::sp_greater(Truck t) {
    return speed - t.speed;
}

int sp_greater(Car c, Truck t) {
    return c.speed - t.speed;
}

double travelTime(Car c, double km) {
    if (km < 0)
        throw std::invalid_argument("Distance cannot be negative");

    return km / c.speed;
}
