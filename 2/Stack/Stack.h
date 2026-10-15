//
// Created by Velin Poznakov on 10/15/2026.
//

#ifndef INC_2_STACK_H
#define INC_2_STACK_H


class Stack {
    static constexpr int MAX_SIZE = 26;

    char items[MAX_SIZE] = {};
    int top = 0;

public:
    void push(char item);
    char pop();

    bool isEmpty() const {return top == 0;}
    bool isFull() const {return top == MAX_SIZE;}
    int getSize() const {return top;}
};

Stack loadstack();
Stack loadstack(int upper);


#endif //INC_2_STACK_H
