//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef COURSEPROJECT_PARKINGEXCEPTION_H
#define COURSEPROJECT_PARKINGEXCEPTION_H

#include <stdexcept>
#include <string>

class ParkingException : public std::runtime_error {
public:
    explicit ParkingException(const std::string &message) : std::runtime_error(message) {}
};


#endif //COURSEPROJECT_PARKINGEXCEPTION_H
