//talgov44@gmail.com
#include "PriorityQueue.hpp"

namespace graph {

    PriorityQueue::PriorityQueue(int maxSize) : maxSize(maxSize), size(0)
    {
        vertices = new int[maxSize];
        weights = new int[maxSize];
    }

    PriorityQueue::~PriorityQueue() {
        delete[] vertices;
        delete[] weights;
    }

    void PriorityQueue::push(int vertex, int weight) {
        if (size >= maxSize) {return;}

        vertices[size] = vertex;
        weights[size] = weight;
        size++;
    }

    int PriorityQueue::pop() {
        if (isEmpty())
        {
            return -1;
        }

        int minIndex = 0;
        for (int i = 1; i < size; ++i) {
            if (weights[i] < weights[minIndex]) {
                minIndex = i;
            }
        }

        int vertex = vertices[minIndex];

        for (int i = minIndex; i < size - 1; ++i)
        {
            vertices[i] = vertices[i + 1];
            weights[i] = weights[i + 1];
        }

        size--;
        return vertex;
    }

    bool PriorityQueue::isEmpty() const {
        return size == 0;
    }
}