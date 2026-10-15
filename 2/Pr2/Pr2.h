//
// Created by Velin Poznakov on 10/15/2026.
//

#ifndef INC_2_PR2_H
#define INC_2_PR2_H

class Pr1;


class Pr2 {
    int printing;

public:
    Pr2();

    void set_print(int status);

    friend bool inuse(Pr1 p1, Pr2 p2);
};


#endif //INC_2_PR2_H
