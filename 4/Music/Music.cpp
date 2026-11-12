//
// Created by Velin Poznakov on 11/12/2026.
//

#include "Music.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

Music::Music(const std::string &title, double price, int itemID, const std::string &datePurchased,
             const std::string &bandOrArtist)
    : Item("Music", title, price, itemID, "CD", datePurchased) {
    setBandOrArtist(bandOrArtist);
}

void Music::setBandOrArtist(const std::string &bandOrArtist) {
    if (bandOrArtist.empty())
        throw std::invalid_argument("Band or artist must not be empty");

    this->bandOrArtist = bandOrArtist;
}

void Music::playOnCD() const {
    std::cout << "Playing \"" << title << "\" by " << bandOrArtist << " on a CD player\n";
}

std::string Music::toString() const {
    std::ostringstream out;

    out << Item::toString() << " Performed by: " << bandOrArtist << '.';

    return out.str();
}
