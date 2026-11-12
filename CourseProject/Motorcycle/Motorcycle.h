//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef COURSEPROJECT_MOTORCYCLE_H
#define COURSEPROJECT_MOTORCYCLE_H

#include "../Vehicle/Vehicle.h"

class Motorcycle : public Vehicle {
public:
    Motorcycle(const std::string &licensePlate, const std::string &ownerName);

    std::string getType() const override {return "Motorcycle";}
    SpotSize getSpotSize() const override {return SMALL;}
    double getHourlyRate() const override {return 1.0;}
};


#endif //COURSEPROJECT_MOTORCYCLE_H
