//
// Created by Velin Poznakov on 11/12/2026.
//

#include "Game.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

Game::Game(const std::string &title, double price, int itemID, const std::string &mediaFormat,
           const std::string &datePurchased, int difficultyLevel, const std::string &mfg)
    : Item("Game", title, price, itemID, mediaFormat, datePurchased) {
    if (this->mediaFormat != "CD" && this->mediaFormat != "Video")
        throw std::invalid_argument("A game can only be on CD or Video");

    setDifficultyLevel(difficultyLevel);
    setMfg(mfg);
}

void Game::setDifficultyLevel(int difficultyLevel) {
    if (difficultyLevel < 1 || difficultyLevel > 10)
        throw std::invalid_argument("Difficulty level must be between 1 and 10");

    this->difficultyLevel = difficultyLevel;
}

void Game::setMfg(const std::string &mfg) {
    if (mfg.empty())
        throw std::invalid_argument("Equipment must not be empty");

    this->mfg = mfg;
}

void Game::playOnCD() const {
    if (mediaFormat != "CD")
        throw std::logic_error("\"" + title + "\" is not on CD");

    std::cout << "Playing the game \"" << title << "\" from CD on " << mfg << '\n';
}

void Game::playOnVideo() const {
    if (mediaFormat != "Video")
        throw std::logic_error("\"" + title + "\" is not on Video");

    std::cout << "Playing the game \"" << title << "\" from video on " << mfg << '\n';
}

std::string Game::toString() const {
    std::ostringstream out;

    out << Item::toString() << " Difficulty: " << difficultyLevel << "/10, equipment: " << mfg << '.';

    return out.str();
}
