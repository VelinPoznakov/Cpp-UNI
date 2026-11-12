//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef COURSEPROJECT_MENU_H
#define COURSEPROJECT_MENU_H

#include "../ParkingLot/ParkingLot.h"
#include "../PostgresStorage/PostgresStorage.h"
#include <string>

class Menu {
    ParkingLot &lot;
    PostgresStorage &storage;

    static std::string readLine(const std::string &prompt);
    static int readNumber(const std::string &prompt, int min, int max);

    void showMap() const;
    void parkVehicle();
    void vehicleLeaves();
    void findVehicle() const;
    void showParked() const;
    void showHistory() const;
    void showRevenue() const;
    void addSpots();

public:
    Menu(ParkingLot &lot, PostgresStorage &storage);

    void run();
};


#endif //COURSEPROJECT_MENU_H
