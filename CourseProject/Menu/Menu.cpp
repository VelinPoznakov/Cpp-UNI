//
// Created by Velin Poznakov on 11/12/2026.
//

#include "Menu.h"
#include "../VehicleFactory/VehicleFactory.h"
#include <format>
#include <iostream>
#include <stdexcept>

Menu::Menu(ParkingLot &lot, PostgresStorage &storage) : lot(lot), storage(storage) {
}

std::string Menu::readLine(const std::string &prompt) {
    std::cout << prompt;

    std::string line;
    if (!std::getline(std::cin, line))
        throw std::runtime_error("No more input");

    return line;
}

int Menu::readNumber(const std::string &prompt, int min, int max) {
    while (true) {
        std::string line = readLine(prompt);

        bool onlyDigits = !line.empty() && line.find_first_not_of("0123456789") == std::string::npos;
        if (onlyDigits) {
            int number = std::stoi(line);
            if (number >= min && number <= max)
                return number;
        }

        std::cout << "Please enter a number from " << min << " to " << max << ".\n";
    }
}

void Menu::run() {
    std::cout << "===== Parking Lot Manager =====\n";

    while (std::cin) {
        std::cout << "\nFree spots: small " << lot.countSpots(SMALL, true) << '/' << lot.countSpots(SMALL, false)
                  << ", medium " << lot.countSpots(MEDIUM, true) << '/' << lot.countSpots(MEDIUM, false)
                  << ", large " << lot.countSpots(LARGE, true) << '/' << lot.countSpots(LARGE, false) << '\n'
                  << "1. Parking map\n"
                  << "2. Park a vehicle\n"
                  << "3. Vehicle leaves (pay)\n"
                  << "4. Find a vehicle\n"
                  << "5. Parked vehicles\n"
                  << "6. Ticket history\n"
                  << "7. Revenue report\n"
                  << "8. Add parking spots\n"
                  << "0. Exit\n";

        try {
            int choice = readNumber("Choice: ", 0, 8);
            std::cout << '\n';

            switch (choice) {
                case 0:
                    std::cout << "Goodbye!\n";
                    return;
                case 1: showMap(); break;
                case 2: parkVehicle(); break;
                case 3: vehicleLeaves(); break;
                case 4: findVehicle(); break;
                case 5: showParked(); break;
                case 6: showHistory(); break;
                case 7: showRevenue(); break;
                case 8: addSpots(); break;
            }
        } catch (const std::exception &error) {
            std::cout << "Error: " << error.what() << '\n';
        }
    }
}

void Menu::showMap() const {
    std::cout << "S = small (motorcycles), M = medium (cars), L = large (trucks)\n";

    int count = 0;
    for (const ParkingSpot &spot : lot.getSpots()) {
        std::string vehicle = spot.isFree() ? "free" : spot.getVehicle()->getLicensePlate();
        std::cout << std::format("[{:2} {} {:<10}] ", spot.getNumber(), sizeName(spot.getSize())[0], vehicle);

        count++;
        if (count % 4 == 0)
            std::cout << '\n';
    }
    std::cout << '\n';
}

void Menu::parkVehicle() {
    std::string plate = Vehicle::normalizePlate(readLine("License plate: "));
    if (lot.findTicket(plate) != nullptr) {
        std::cout << plate << " is already parked here.\n";
        return;
    }

    std::unique_ptr<Vehicle> vehicle = storage.loadVehicle(plate);
    if (vehicle != nullptr) {
        std::cout << "Welcome back: " << *vehicle << '\n';
    } else {
        const std::string types[] = {"Car", "Motorcycle", "Truck"};
        std::cout << "1. Car\n2. Motorcycle\n3. Truck\n";
        int type = readNumber("Vehicle type: ", 1, 3);
        std::string owner = readLine("Owner name: ");
        vehicle = VehicleFactory::create(types[type - 1], plate, owner);
    }

    const Ticket &ticket = lot.park(std::move(vehicle));
    std::cout << "Parked on spot " << ticket.getSpotNumber() << ". Ticket #" << ticket.getId()
              << ", entered at " << Ticket::formatTime(ticket.getEntryTime()) << ".\n";
}

void Menu::vehicleLeaves() {
    Ticket ticket = lot.leave(readLine("License plate: "));
    int hours = ticket.hoursUntil(ticket.getExitTime());

    std::cout << "Ticket #" << ticket.getId() << "  " << ticket.getVehicleType() << ' ' << ticket.getLicensePlate()
              << " (" << ticket.getOwnerName() << "), spot " << ticket.getSpotNumber() << '\n'
              << "  In:     " << Ticket::formatTime(ticket.getEntryTime()) << '\n'
              << "  Out:    " << Ticket::formatTime(ticket.getExitTime()) << '\n'
              << "  To pay: " << hours << " h = " << Ticket::formatMoney(ticket.getFee()) << '\n';
}

void Menu::findVehicle() const {
    std::string plate = Vehicle::normalizePlate(readLine("License plate: "));
    const Ticket *ticket = lot.findTicket(plate);

    if (ticket == nullptr)
        std::cout << plate << " is not in the parking lot.\n";
    else
        std::cout << *ticket << "\nIf it leaves now: " << Ticket::formatMoney(lot.currentFee(*ticket)) << '\n';
}

void Menu::showParked() const {
    std::vector<Ticket> parked = lot.getParkedTickets();
    if (parked.empty())
        std::cout << "The parking lot is empty.\n";

    for (const Ticket &ticket : parked)
        std::cout << ticket << "  (" << ticket.getOwnerName() << ", so far "
                  << Ticket::formatMoney(lot.currentFee(ticket)) << ")\n";
}

void Menu::showHistory() const {
    std::vector<Ticket> history = storage.loadHistory(20);
    if (history.empty())
        std::cout << "No vehicle has left yet.\n";

    for (const Ticket &ticket : history)
        std::cout << ticket << '\n';
}

void Menu::showRevenue() const {
    std::cout << std::format("{:<12}{:>8}{:>14}\n", "Type", "Visits", "Revenue");

    int visits = 0;
    double total = 0;
    for (const RevenueRow &row : storage.loadRevenue()) {
        std::cout << std::format("{:<12}{:>8}{:>14}\n", row.vehicleType, row.visits, Ticket::formatMoney(row.total));
        visits += row.visits;
        total += row.total;
    }

    std::cout << std::format("{:<12}{:>8}{:>14}\n", "Total", visits, Ticket::formatMoney(total));
}

void Menu::addSpots() {
    std::cout << "1. SMALL\n2. MEDIUM\n3. LARGE\n";
    SpotSize size = static_cast<SpotSize>(readNumber("Spot size: ", 1, 3));
    int count = readNumber("How many: ", 1, 100);

    lot.addSpots(size, count);
    std::cout << "Added " << count << ' ' << sizeName(size) << " spot(s).\n";
}
