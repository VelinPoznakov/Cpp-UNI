//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef INC_4_TRUCK_H
#define INC_4_TRUCK_H

#include "../Vehicle/Vehicle.h"


class Truck : public Vehicle {
    int loadLimit = 0;

public:
    Truck(int loadLimit, int numWheels, int range);

    void setLoadLimit(int loadLimit);

    int getLoadLimit() const {return loadLimit;}

    void show() const;
};


#endif //INC_4_TRUCK_H
