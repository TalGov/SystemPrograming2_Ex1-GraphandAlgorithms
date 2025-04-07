//talgov44@gmail.com
#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

namespace graph {
    class PriorityQueue {
    private:
        int maxSize;
        int size;
        int *vertices;
        int *weights;

    public:
        PriorityQueue(int maxSize);

        ~PriorityQueue();

        void push(int vertex, int weight);

        int pop();

        bool isEmpty() const;

    };
}
#endif // PRIORITY_QUEUE_HPP
