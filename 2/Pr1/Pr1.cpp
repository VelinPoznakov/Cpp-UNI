//
// Created by Velin Poznakov on 10/15/2026.
//

#include "Pr1.h"
#include "../Pr2/Pr2.h"

Pr1::Pr1() {
    printing = 0;
}

void Pr1::set_print(int status) {
    this->printing = status;
}

bool inuse(Pr1 p1, Pr2 p2) {
    return p1.printing != 0 || p2.printing != 0;
}
