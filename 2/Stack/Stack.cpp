//
// Created by Velin Poznakov on 10/15/2026.
//

#include "Stack.h"
#include <stdexcept>

void Stack::push(char item) {
    if (isFull())
        throw std::overflow_error("Stack is full");

    this->items[top++] = item;
}

char Stack::pop() {
    if (isEmpty())
        throw std::underflow_error("Stack is empty");

    return this->items[--top];
}

Stack loadstack() {
    return loadstack(0);
}

Stack loadstack(int upper) {
    Stack stack;
    char first = (upper == 1) ? 'A' : 'a';

    for (char letter = first; letter < first + 26; letter++)
        stack.push(letter);

    return stack;
}
