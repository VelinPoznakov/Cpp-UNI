//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef INC_4_ITEM_H
#define INC_4_ITEM_H

#include <set>
#include <string>


class Item {
    // IDs of all items that currently exist, so a new item can't take one that is already used
    static std::set<int> usedIds;

protected:
    std::string contentType;
    std::string datePurchased;
    int itemID = 0;
    std::string mediaFormat;
    static int numberOfItems;
    double price = 0;
    std::string title;

    // Protected, because Item is only a base - you create a Movie, a Game or a Music,
    // and each of them passes its own content type here
    Item(const std::string &contentType, const std::string &title, double price, int itemID,
         const std::string &mediaFormat, const std::string &datePurchased);

    void setTitle(const std::string &title);
    void setPrice(double price);
    void setMediaFormat(const std::string &mediaFormat);
    void setDatePurchased(const std::string &datePurchased);

public:
    ~Item();

    // Every item has a unique ID, so a copy would be a second item with the same ID
    Item(const Item &) = delete;
    Item &operator=(const Item &) = delete;

    void setItemId(int itemID);

    std::string getContentType() const {return contentType;}
    std::string getDatePurchased() const {return datePurchased;}
    int getItemId() const {return itemID;}
    std::string getMediaFormat() const {return mediaFormat;}
    double getPrice() const {return price;}
    std::string getTitle() const {return title;}

    static int getNumberOfItems() {return numberOfItems;}

    std::string toString() const;
};


#endif //INC_4_ITEM_H
