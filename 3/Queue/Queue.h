//
// Created by Velin Poznakov on 10/29/2026.
//

#ifndef INC_3_QUEUE_H
#define INC_3_QUEUE_H


class Queue {
    int *items;
    int capacity;
    int head = 0;
    int count = 0;

public:
    Queue(int capacity);
    ~Queue();

    // The class owns items, so copying would make two objects delete the same memory
    Queue(const Queue &) = delete;
    Queue &operator=(const Queue &) = delete;

    int &enqueue(int value);
    int dequeue();
    const int &front() const;

    bool isEmpty() const {return count == 0;}
    bool isFull() const {return count == capacity;}
    int getSize() const {return count;}

    void print() const;

    friend void mergeQueues(const Queue &q1, const Queue &q2, Queue &result);
};

void mergeQueues(const Queue &q1, const Queue &q2, Queue &result);


#endif //INC_3_QUEUE_H
