//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef INC_4_MUSIC_H
#define INC_4_MUSIC_H

#include "../Item/Item.h"


class Music : public Item {
    std::string bandOrArtist;

    void setBandOrArtist(const std::string &bandOrArtist);

public:
    // Music can only be played on CD, so the format is always "CD" and isn't a parameter
    Music(const std::string &title, double price, int itemID, const std::string &datePurchased,
          const std::string &bandOrArtist);

    std::string getBandOrArtist() const {return bandOrArtist;}

    void playOnCD() const;

    std::string toString() const;
};


#endif //INC_4_MUSIC_H
