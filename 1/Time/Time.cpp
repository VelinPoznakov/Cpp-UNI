//
// Created by Velin Poznakov on 9/29/2026.
//

#include "../Time.h"
#include <iostream>

Time::Time(int seconds, int minutes, int hours) {
    this->setSeconds(seconds);
    this->setMinutes(minutes);
    this->setHours(hours);
}

void Time::setSeconds(int seconds) {
    if (seconds < 0 || seconds > 59)
        throw std::invalid_argument("Seconds must be between 0 and 59");

    this->seconds = seconds;
}

void Time::setMinutes(int minutes) {
    if (minutes < 0 || minutes > 59)
        throw std::invalid_argument("Minutes must be between 0 and 59");

    this->minutes = minutes;
}

void Time::setHours(int hours) {
    if (hours < 0 || hours > 23)
        throw std::invalid_argument("Hours must be between 0 and 23");

    this->hours = hours;
}

std::string Time::getTime() {
    return std::to_string(this->getHours()) + ":"
         + std::to_string(this->getMinutes()) + ":"
         + std::to_string(this->getSeconds())
         + (this->getHours() > 11 ? " PM" : " AM");
}
