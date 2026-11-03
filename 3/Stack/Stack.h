//
// Created by Velin Poznakov on 10/29/2026.
//

#ifndef INC_3_STACK_H
#define INC_3_STACK_H

#define MAX_STACK_SIZE 26

class Stack {

    char items[MAX_STACK_SIZE] = {};
    int top = 0;

public:
    void push(char item);
    char pop();

    bool isEmpty() const {return top == 0;}
    bool isFull() const {return top == MAX_STACK_SIZE;}
    int getSize() const {return top;}
};

Stack loadstack();
Stack loadstack(int upper);


#endif //INC_3_STACK_H
