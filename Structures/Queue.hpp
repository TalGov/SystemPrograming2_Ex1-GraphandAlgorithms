//talgov44@gmail.com
#ifndef QUEUE_H
#define QUEUE_H
#include "..//Graph/Node.hpp"

namespace graph {

    class Queue {
    private:
        NodeQueue* head;
        NodeQueue* tail;

    public:
        Queue() : head(nullptr), tail(nullptr) {}

        void enqueue(int value);
        int dequeue();
        bool isEmpty() const;

    };

}
#endif
