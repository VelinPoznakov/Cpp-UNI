//
// Created by Velin Poznakov on 10/15/2026.
//

#ifndef INC_2_TRUCK_H
#define INC_2_TRUCK_H

#include "../Car/Car.h"


class Truck {
    int weight{};
    int speed{};

public:
    Truck(int weight, int speed);

    void setWeight(int weight);
    void setSpeed(int speed);

    friend int sp_greater(Car c, Truck t);
    friend int Car::sp_greater(Truck t);
    friend double travelTime(Truck t, double km);
};


#endif //INC_2_TRUCK_H
