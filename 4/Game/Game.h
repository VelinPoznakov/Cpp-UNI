//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef INC_4_GAME_H
#define INC_4_GAME_H

#include "../Item/Item.h"


class Game : public Item {
    int difficultyLevel = 1;
    std::string mfg;    // manufacturer of the equipment the game runs on, e.g. "Sony PlayStation"

    void setDifficultyLevel(int difficultyLevel);
    void setMfg(const std::string &mfg);

public:
    Game(const std::string &title, double price, int itemID, const std::string &mediaFormat,
         const std::string &datePurchased, int difficultyLevel, const std::string &mfg);

    int getDifficultyLevel() const {return difficultyLevel;}
    std::string getEquipment() const {return mfg;}

    void playOnCD() const;
    void playOnVideo() const;

    std::string toString() const;
};


#endif //INC_4_GAME_H
