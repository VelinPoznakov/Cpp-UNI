//
// Created by Velin Poznakov on 10/15/2026.
//

#ifndef INC_2_CAR_H
#define INC_2_CAR_H

class Truck;


class Car {
    int passengers{};
    int speed{};

public:
    Car(int passengers, int speed);

    void setPassengers(int passengers);
    void setSpeed(int speed);

    int sp_greater(Truck t);

    friend int sp_greater(Car c, Truck t);
    friend double travelTime(Car c, double km);
};


#endif //INC_2_CAR_H
