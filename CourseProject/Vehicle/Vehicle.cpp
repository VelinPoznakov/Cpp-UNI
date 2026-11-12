//
// Created by Velin Poznakov on 11/12/2026.
//

#include "Vehicle.h"
#include <cctype>
#include <stdexcept>

Vehicle::Vehicle(const std::string &licensePlate, const std::string &ownerName) {
    if (ownerName.empty())
        throw std::invalid_argument("Owner name must not be empty");

    this->licensePlate = normalizePlate(licensePlate);
    this->ownerName = ownerName;
}

std::string Vehicle::normalizePlate(const std::string &plate) {
    std::string result;
    for (char c : plate) {
        if (c == ' ' || c == '-')
            continue;
        if (!std::isalnum(static_cast<unsigned char>(c)))
            throw std::invalid_argument("License plate can contain only Latin letters and digits");

        result += static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }

    if (result.size() < 2 || result.size() > 10)
        throw std::invalid_argument("License plate must be 2 to 10 characters long");

    return result;
}

double Vehicle::calculateFee(int hours) const {
    return hours * getHourlyRate();
}

std::ostream &operator<<(std::ostream &out, const Vehicle &vehicle) {
    return out << vehicle.getType() << ' ' << vehicle.getLicensePlate() << " (" << vehicle.getOwnerName() << ')';
}
