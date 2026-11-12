//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef INC_4_MOVIE_H
#define INC_4_MOVIE_H

#include "../Item/Item.h"


class Movie : public Item {
    double rating = 0;

    void setRating(double rating);

public:
    Movie(const std::string &title, double price, int itemID, const std::string &mediaFormat,
          const std::string &datePurchased, double rating);

    double getRating() const {return rating;}

    void playOnDVD() const;
    void playOnVideo() const;

    std::string toString() const;
};


#endif //INC_4_MOVIE_H
