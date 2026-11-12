//
// Created by Velin Poznakov on 11/12/2026.
//

#include "Truck.h"

Truck::Truck(const std::string &licensePlate, const std::string &ownerName)
    : Vehicle(licensePlate, ownerName) {
}

double Truck::calculateFee(int hours) const {
    return Vehicle::calculateFee(hours) + ENTRY_FEE;
}
