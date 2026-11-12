//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef COURSEPROJECT_TRUCK_H
#define COURSEPROJECT_TRUCK_H

#include "../Vehicle/Vehicle.h"

class Truck : public Vehicle {
public:
    static constexpr double ENTRY_FEE = 5.0;

    Truck(const std::string &licensePlate, const std::string &ownerName);

    std::string getType() const override {return "Truck";}
    SpotSize getSpotSize() const override {return LARGE;}
    double getHourlyRate() const override {return 4.0;}
    double calculateFee(int hours) const override;
};


#endif //COURSEPROJECT_TRUCK_H
