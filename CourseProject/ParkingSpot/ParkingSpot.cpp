//
// Created by Velin Poznakov on 11/12/2026.
//

#include "ParkingSpot.h"

ParkingSpot::ParkingSpot(int number, SpotSize size) : number(number), size(size) {
}

void ParkingSpot::park(std::unique_ptr<Vehicle> newVehicle) {
    vehicle = std::move(newVehicle);
}

void ParkingSpot::release() {
    vehicle = nullptr;
}
