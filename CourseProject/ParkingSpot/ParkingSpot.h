//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef COURSEPROJECT_PARKINGSPOT_H
#define COURSEPROJECT_PARKINGSPOT_H

#include "../SpotSize/SpotSize.h"
#include "../Vehicle/Vehicle.h"
#include <memory>

class ParkingSpot {
    int number;
    SpotSize size;
    std::unique_ptr<Vehicle> vehicle;

public:
    ParkingSpot(int number, SpotSize size);

    int getNumber() const {return number;}
    SpotSize getSize() const {return size;}
    bool isFree() const {return vehicle == nullptr;}
    const Vehicle *getVehicle() const {return vehicle.get();}

    void park(std::unique_ptr<Vehicle> newVehicle);
    void release();
};


#endif //COURSEPROJECT_PARKINGSPOT_H
