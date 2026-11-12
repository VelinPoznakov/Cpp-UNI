//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef COURSEPROJECT_VEHICLEFACTORY_H
#define COURSEPROJECT_VEHICLEFACTORY_H

#include "../Vehicle/Vehicle.h"
#include <memory>
#include <string>

class VehicleFactory {
public:
    static std::unique_ptr<Vehicle> create(const std::string &type, const std::string &licensePlate,
                                           const std::string &ownerName);
};


#endif //COURSEPROJECT_VEHICLEFACTORY_H
