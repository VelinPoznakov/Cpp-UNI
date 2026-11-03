//
// Created by Velin Poznakov on 10/29/2026.
//

#include "Queue.h"
#include <iostream>
#include <stdexcept>

Queue::Queue(int capacity) {
    if (capacity <= 0)
        throw std::invalid_argument("Queue capacity must be positive");

    this->capacity = capacity;
    this->items = new int[capacity];
}

Queue::~Queue() {
    delete[] items;
}

int &Queue::enqueue(int value) {
    if (isFull())
        throw std::overflow_error("Queue is full");

    // The queue is circular: after the last cell it continues from index 0
    int tail = (head + count) % capacity;
    items[tail] = value;
    count++;

    return items[tail];
}

int Queue::dequeue() {
    if (isEmpty())
        throw std::underflow_error("Queue is empty");

    int value = items[head];
    head = (head + 1) % capacity;
    count--;

    return value;
}

const int &Queue::front() const {
    if (isEmpty())
        throw std::underflow_error("Queue is empty");

    return items[head];
}

void Queue::print() const {
    for (int i = 0; i < count; i++)
        std::cout << items[(head + i) % capacity] << ' ';
}

void mergeQueues(const Queue &q1, const Queue &q2, Queue &result) {
    int longest = (q1.count > q2.count) ? q1.count : q2.count;

    for (int i = 0; i < longest; i++) {
        if (i < q1.count)
            result.enqueue(q1.items[(q1.head + i) % q1.capacity]);

        if (i < q2.count)
            result.enqueue(q2.items[(q2.head + i) % q2.capacity]);
    }
}
