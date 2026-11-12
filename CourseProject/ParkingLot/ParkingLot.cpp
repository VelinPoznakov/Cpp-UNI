//
// Created by Velin Poznakov on 11/12/2026.
//

#include "ParkingLot.h"
#include "../ParkingException/ParkingException.h"
#include "../VehicleFactory/VehicleFactory.h"
#include <ctime>

ParkingLot::ParkingLot(PostgresStorage &storage) : storage(storage) {
    spots = storage.loadSpots();

    for (const Ticket &ticket : storage.loadOpenTickets()) {
        ParkingSpot &spot = spots[ticket.getSpotNumber() - 1];
        spot.park(VehicleFactory::create(ticket.getVehicleType(), ticket.getLicensePlate(), ticket.getOwnerName()));
        openTickets.emplace(ticket.getLicensePlate(), ticket);
    }
}

ParkingSpot *ParkingLot::findFreeSpot(SpotSize neededSize) {
    for (int size = neededSize; size <= LARGE; size++)
        for (ParkingSpot &spot : spots)
            if (spot.isFree() && spot.getSize() == size)
                return &spot;

    return nullptr;
}

void ParkingLot::addSpots(SpotSize size, int count) {
    for (int i = 0; i < count; i++) {
        int number = static_cast<int>(spots.size()) + 1;
        storage.addSpot(number, size);
        spots.emplace_back(number, size);
    }
}

const Ticket &ParkingLot::park(std::unique_ptr<Vehicle> vehicle) {
    std::string plate = vehicle->getLicensePlate();
    if (openTickets.contains(plate))
        throw ParkingException(plate + " is already parked here");

    ParkingSpot *spot = findFreeSpot(vehicle->getSpotSize());
    if (spot == nullptr)
        throw ParkingException("No free spot for a " + vehicle->getType());

    std::time_t now = std::time(nullptr);
    int id = storage.openTicket(*vehicle, spot->getNumber(), now);
    Ticket ticket(id, plate, vehicle->getType(), vehicle->getOwnerName(), spot->getNumber(), now);

    spot->park(std::move(vehicle));
    openTickets.emplace(plate, ticket);
    return openTickets.at(plate);
}

Ticket ParkingLot::leave(const std::string &licensePlate) {
    std::string plate = Vehicle::normalizePlate(licensePlate);
    if (!openTickets.contains(plate))
        throw ParkingException(plate + " is not in the parking lot");

    Ticket ticket = openTickets.at(plate);
    ParkingSpot &spot = spots[ticket.getSpotNumber() - 1];

    std::time_t now = std::time(nullptr);
    int hours = ticket.hoursUntil(now);
    ticket.close(now, spot.getVehicle()->calculateFee(hours));
    storage.closeTicket(ticket);

    spot.release();
    openTickets.erase(plate);
    return ticket;
}

int ParkingLot::countSpots(SpotSize size, bool onlyFree) const {
    int count = 0;
    for (const ParkingSpot &spot : spots)
        if (spot.getSize() == size && (!onlyFree || spot.isFree()))
            count++;

    return count;
}

const Ticket *ParkingLot::findTicket(const std::string &licensePlate) const {
    std::string plate = Vehicle::normalizePlate(licensePlate);
    if (!openTickets.contains(plate))
        return nullptr;

    return &openTickets.at(plate);
}

double ParkingLot::currentFee(const Ticket &ticket) const {
    const Vehicle *vehicle = spots[ticket.getSpotNumber() - 1].getVehicle();
    return vehicle->calculateFee(ticket.hoursUntil(std::time(nullptr)));
}

std::vector<Ticket> ParkingLot::getParkedTickets() const {
    std::vector<Ticket> parked;
    for (const auto &[plate, ticket] : openTickets)
        parked.push_back(ticket);

    return parked;
}
