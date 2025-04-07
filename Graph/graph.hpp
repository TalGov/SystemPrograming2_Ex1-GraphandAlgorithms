//talgov44@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include "node.hpp"
#include "edge.hpp"

namespace graph {

    class Graph {

    private:
        int numVertices;
        Node** adjList;

        bool removeEdgeFromList(int vertex, int target);

    public:

        Graph(int vertices);
        ~Graph();

        bool addEdge(int src, int dest, int weight= 1);
        bool removeEdge(int src, int dest);
        void print_graph() const;

        bool isConnected() const;

        int getNumVertices() const {return numVertices;};
        int getEdgeWeight(int src, int dest) const;
        Edge* getEdges(int* numOfEdge) const;
    };

}

#endif
