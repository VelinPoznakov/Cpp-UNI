//
// Created by Velin Poznakov on 9/29/2026.
//

#ifndef INC_1_TIME_H
#define INC_1_TIME_H
#include <string>


class Time {

    int seconds{};
    int minutes{};
    int hours{};
public:

    Time(int seconds, int minutes, int hours);

    void setSeconds(int seconds);
    void setMinutes(int minutes);
    void setHours(int hours);

    int getSeconds() const {return seconds;}
    int getMinutes() const {return minutes;}
    int getHours() const {return hours;}

    std::string getTime();


};


#endif //INC_1_TIME_H
