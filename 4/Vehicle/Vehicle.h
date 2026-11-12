//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef INC_4_VEHICLE_H
#define INC_4_VEHICLE_H


class Vehicle {
    int numWheels = 0;
    int range = 0;

public:
    Vehicle(int numWheels, int range);

    void setNumWheels(int numWheels);
    void setRange(int range);

    int getNumWheels() const {return numWheels;}
    int getRange() const {return range;}

    void showv() const;
};


#endif //INC_4_VEHICLE_H
