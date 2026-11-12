//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef COURSEPROJECT_VEHICLE_H
#define COURSEPROJECT_VEHICLE_H

#include "../SpotSize/SpotSize.h"
#include <ostream>
#include <string>

class Vehicle {
    std::string licensePlate;
    std::string ownerName;

public:
    Vehicle(const std::string &licensePlate, const std::string &ownerName);
    virtual ~Vehicle() = default;

    static std::string normalizePlate(const std::string &plate);

    const std::string &getLicensePlate() const {return licensePlate;}
    const std::string &getOwnerName() const {return ownerName;}

    virtual std::string getType() const = 0;
    virtual SpotSize getSpotSize() const = 0;
    virtual double getHourlyRate() const = 0;
    virtual double calculateFee(int hours) const;
};

std::ostream &operator<<(std::ostream &out, const Vehicle &vehicle);


#endif //COURSEPROJECT_VEHICLE_H
