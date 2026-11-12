//
// Created by Velin Poznakov on 11/12/2026.
//

#include "VehicleFactory.h"
#include "../Car/Car.h"
#include "../Motorcycle/Motorcycle.h"
#include "../Truck/Truck.h"
#include <stdexcept>

std::unique_ptr<Vehicle> VehicleFactory::create(const std::string &type, const std::string &licensePlate,
                                                const std::string &ownerName) {
    if (type == "Car")
        return std::make_unique<Car>(licensePlate, ownerName);
    if (type == "Motorcycle")
        return std::make_unique<Motorcycle>(licensePlate, ownerName);
    if (type == "Truck")
        return std::make_unique<Truck>(licensePlate, ownerName);

    throw std::invalid_argument("Unknown vehicle type: " + type);
}
