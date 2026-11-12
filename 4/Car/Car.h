//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef INC_4_CAR_H
#define INC_4_CAR_H

#include "../Vehicle/Vehicle.h"


class Car : public Vehicle {
    int passengers = 0;

public:
    Car(int passengers, int numWheels, int range);

    void setPassengers(int passengers);

    int getPassengers() const {return passengers;}

    void show() const;
};


#endif //INC_4_CAR_H
