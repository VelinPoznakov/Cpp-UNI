//
// Created by Velin Poznakov on 11/12/2026.
//

#include "Ticket.h"
#include <format>

Ticket::Ticket(int id, const std::string &licensePlate, const std::string &vehicleType,
               const std::string &ownerName, int spotNumber, std::time_t entryTime)
    : id(id), licensePlate(licensePlate), vehicleType(vehicleType), ownerName(ownerName),
      spotNumber(spotNumber), entryTime(entryTime) {
}

void Ticket::close(std::time_t exitTime, double fee) {
    this->exitTime = exitTime;
    this->fee = fee;
}

int Ticket::hoursUntil(std::time_t time) const {
    long long seconds = time - entryTime;
    long long hours = (seconds + 3599) / 3600;

    if (hours < 1)
        return 1;
    return static_cast<int>(hours);
}

std::string Ticket::formatTime(std::time_t time) {
    char text[20];
    std::strftime(text, sizeof(text), "%d.%m.%Y %H:%M", std::localtime(&time));
    return text;
}

std::string Ticket::formatMoney(double amount) {
    return std::format("{:.2f} EUR", amount);
}

std::ostream &operator<<(std::ostream &out, const Ticket &ticket) {
    out << std::format("#{:<4} {:<10} {:<11} spot {:<3} {} -> ", ticket.getId(), ticket.getLicensePlate(),
                       ticket.getVehicleType(), ticket.getSpotNumber(), Ticket::formatTime(ticket.getEntryTime()));

    if (ticket.isClosed())
        out << std::format("{}  {:>2} h  {:>10}", Ticket::formatTime(ticket.getExitTime()),
                           ticket.hoursUntil(ticket.getExitTime()), Ticket::formatMoney(ticket.getFee()));
    else
        out << "still inside";

    return out;
}
