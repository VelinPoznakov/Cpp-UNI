#include "Menu/Menu.h"
#include "ParkingLot/ParkingLot.h"
#include "PostgresStorage/PostgresStorage.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

std::string readConnectionSettings() {
    std::ifstream file(std::string(PROJECT_DIR) + "/db.conf");

    std::string settings;
    if (!std::getline(file, settings))
        throw std::runtime_error("Copy db.conf.example to db.conf and write your database password in it");

    return settings;
}

int main() {
    try {
        PostgresStorage storage(readConnectionSettings());
        ParkingLot lot(storage);

        if (lot.getSpots().empty()) {
            lot.addSpots(SMALL, 4);
            lot.addSpots(MEDIUM, 10);
            lot.addSpots(LARGE, 3);
        }

        Menu menu(lot, storage);
        menu.run();
    } catch (const std::exception &error) {
        std::cout << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
