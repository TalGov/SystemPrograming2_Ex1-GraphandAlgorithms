//talgov44@gmail.com
#include <iostream>
#include "Queue.hpp"

namespace graph {
    void Queue::enqueue(int value) {
        NodeQueue *newNode = new NodeQueue(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    int Queue::dequeue() {
        if (!head) {
            std::cout << "The queue is empty!" << std::endl;
            return -1;
        }

        int result = head->info;
        NodeQueue* temp = head;
        head = head->next;

        if (head == nullptr) {
            tail = nullptr;
        }

        delete temp;
        return result;
    }

    bool Queue::isEmpty() const {
        return head == nullptr;
    }
}