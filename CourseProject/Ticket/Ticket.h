//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef COURSEPROJECT_TICKET_H
#define COURSEPROJECT_TICKET_H

#include <ctime>
#include <ostream>
#include <string>

class Ticket {
    int id;
    std::string licensePlate;
    std::string vehicleType;
    std::string ownerName;
    int spotNumber;
    std::time_t entryTime;
    std::time_t exitTime = 0;
    double fee = 0;

public:
    Ticket(int id, const std::string &licensePlate, const std::string &vehicleType,
           const std::string &ownerName, int spotNumber, std::time_t entryTime);

    void close(std::time_t exitTime, double fee);
    int hoursUntil(std::time_t time) const;

    int getId() const {return id;}
    const std::string &getLicensePlate() const {return licensePlate;}
    const std::string &getVehicleType() const {return vehicleType;}
    const std::string &getOwnerName() const {return ownerName;}
    int getSpotNumber() const {return spotNumber;}
    std::time_t getEntryTime() const {return entryTime;}
    std::time_t getExitTime() const {return exitTime;}
    double getFee() const {return fee;}
    bool isClosed() const {return exitTime != 0;}

    static std::string formatTime(std::time_t time);
    static std::string formatMoney(double amount);
};

std::ostream &operator<<(std::ostream &out, const Ticket &ticket);


#endif //COURSEPROJECT_TICKET_H
