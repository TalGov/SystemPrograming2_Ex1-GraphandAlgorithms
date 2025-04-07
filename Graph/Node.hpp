//talgov44@gmail.com
#ifndef NODE_HPP
#define NODE_HPP


namespace graph {

    struct Node {
        int vertex;
        int weight;
        Node* next;

        Node(int v, int w) : vertex(v), weight(w), next(nullptr) {}
    };

    struct NodeQueue {
        int info;
        NodeQueue* next;

        NodeQueue(int info) : info(info), next(nullptr) {}
    };
}
#endif
