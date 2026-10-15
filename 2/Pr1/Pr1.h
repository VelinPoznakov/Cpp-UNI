//
// Created by Velin Poznakov on 10/15/2026.
//

#ifndef INC_2_PR1_H
#define INC_2_PR1_H

class Pr2;


class Pr1 {
    int printing;

public:
    Pr1();

    void set_print(int status);

    friend bool inuse(Pr1 p1, Pr2 p2);
};


#endif //INC_2_PR1_H
