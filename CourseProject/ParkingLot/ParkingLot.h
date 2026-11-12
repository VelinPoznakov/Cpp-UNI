//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef COURSEPROJECT_PARKINGLOT_H
#define COURSEPROJECT_PARKINGLOT_H

#include "../ParkingSpot/ParkingSpot.h"
#include "../PostgresStorage/PostgresStorage.h"
#include "../Ticket/Ticket.h"
#include "../Vehicle/Vehicle.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

class ParkingLot {
    PostgresStorage &storage;
    std::vector<ParkingSpot> spots;
    std::map<std::string, Ticket> openTickets;

    ParkingSpot *findFreeSpot(SpotSize neededSize);

public:
    explicit ParkingLot(PostgresStorage &storage);

    void addSpots(SpotSize size, int count);
    const Ticket &park(std::unique_ptr<Vehicle> vehicle);
    Ticket leave(const std::string &licensePlate);

    const std::vector<ParkingSpot> &getSpots() const {return spots;}
    int countSpots(SpotSize size, bool onlyFree) const;
    const Ticket *findTicket(const std::string &licensePlate) const;
    double currentFee(const Ticket &ticket) const;
    std::vector<Ticket> getParkedTickets() const;
};


#endif //COURSEPROJECT_PARKINGLOT_H
