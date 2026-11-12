//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef COURSEPROJECT_SPOTSIZE_H
#define COURSEPROJECT_SPOTSIZE_H

#include <string>

enum SpotSize {
    SMALL = 1,
    MEDIUM = 2,
    LARGE = 3
};

std::string sizeName(SpotSize size);
SpotSize sizeFromName(const std::string &name);


#endif //COURSEPROJECT_SPOTSIZE_H
