//
// Created by Velin Poznakov on 11/12/2026.
//

#include "Item.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>

std::set<int> Item::usedIds;
int Item::numberOfItems = 0;

Item::Item(const std::string &contentType, const std::string &title, double price, int itemID,
           const std::string &mediaFormat, const std::string &datePurchased) {
    this->contentType = contentType;
    setTitle(title);
    setPrice(price);
    setMediaFormat(mediaFormat);
    setDatePurchased(datePurchased);

    // Done last, so a failed validation above doesn't leave the ID marked as used
    setItemId(itemID);
    numberOfItems++;
}

Item::~Item() {
    usedIds.erase(itemID);
    numberOfItems--;
}

void Item::setTitle(const std::string &title) {
    if (title.empty())
        throw std::invalid_argument("Title must not be empty");

    this->title = title;
}

void Item::setPrice(double price) {
    if (price < 0)
        throw std::invalid_argument("Price cannot be negative");

    this->price = price;
}

void Item::setMediaFormat(const std::string &mediaFormat) {
    if (mediaFormat != "DVD" && mediaFormat != "CD" && mediaFormat != "Video")
        throw std::invalid_argument("Media format must be DVD, CD or Video");

    this->mediaFormat = mediaFormat;
}

void Item::setDatePurchased(const std::string &datePurchased) {
    if (datePurchased.empty())
        throw std::invalid_argument("Date of purchase must not be empty");

    this->datePurchased = datePurchased;
}

void Item::setItemId(int itemID) {
    if (itemID <= 0)
        throw std::invalid_argument("Item ID must be positive");

    if (itemID == this->itemID)
        return;

    if (usedIds.contains(itemID))
        throw std::invalid_argument("Item ID " + std::to_string(itemID) + " is already used");

    usedIds.erase(this->itemID);
    usedIds.insert(itemID);
    this->itemID = itemID;
}

std::string Item::toString() const {
    std::ostringstream out;

    out << contentType << " on " << mediaFormat << " with title \"" << title
        << "\" was purchased for " << std::fixed << std::setprecision(2) << price
        << " on " << datePurchased << '.';

    return out.str();
}
