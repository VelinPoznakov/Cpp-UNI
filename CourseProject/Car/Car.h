//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef COURSEPROJECT_CAR_H
#define COURSEPROJECT_CAR_H

#include "../Vehicle/Vehicle.h"

class Car : public Vehicle {
public:
    Car(const std::string &licensePlate, const std::string &ownerName);

    std::string getType() const override {return "Car";}
    SpotSize getSpotSize() const override {return MEDIUM;}
    double getHourlyRate() const override {return 2.0;}
};


#endif //COURSEPROJECT_CAR_H
