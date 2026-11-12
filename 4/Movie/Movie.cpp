//
// Created by Velin Poznakov on 11/12/2026.
//

#include "Movie.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

// If something here throws, the Item part is already built, so ~Item() still runs and frees the ID
Movie::Movie(const std::string &title, double price, int itemID, const std::string &mediaFormat,
             const std::string &datePurchased, double rating)
    : Item("Movie", title, price, itemID, mediaFormat, datePurchased) {
    if (this->mediaFormat != "DVD" && this->mediaFormat != "Video")
        throw std::invalid_argument("A movie can only be on DVD or Video");

    setRating(rating);
}

void Movie::setRating(double rating) {
    if (rating < 0 || rating > 10)
        throw std::invalid_argument("Rating must be between 0 and 10");

    this->rating = rating;
}

void Movie::playOnDVD() const {
    if (mediaFormat != "DVD")
        throw std::logic_error("\"" + title + "\" is not on DVD");

    std::cout << "Playing the movie \"" << title << "\" on a DVD player\n";
}

void Movie::playOnVideo() const {
    if (mediaFormat != "Video")
        throw std::logic_error("\"" + title + "\" is not on Video");

    std::cout << "Playing the movie \"" << title << "\" on a video player\n";
}

std::string Movie::toString() const {
    std::ostringstream out;

    out << Item::toString() << " Rating: " << rating << "/10.";

    return out.str();
}
