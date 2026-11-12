//
// Created by Velin Poznakov on 11/12/2026.
//

#include "SpotSize.h"
#include <stdexcept>

std::string sizeName(SpotSize size) {
    if (size == SMALL)
        return "SMALL";
    if (size == MEDIUM)
        return "MEDIUM";
    return "LARGE";
}

SpotSize sizeFromName(const std::string &name) {
    if (name == "SMALL")
        return SMALL;
    if (name == "MEDIUM")
        return MEDIUM;
    if (name == "LARGE")
        return LARGE;

    throw std::invalid_argument("Unknown spot size: " + name);
}
