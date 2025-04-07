//talgov44@gmail.com
#include <stdexcept>
#include "graph.hpp"
#include "../Algorithms/Algorithms.hpp"

namespace graph {


    Graph::Graph(int vertices) : numVertices(vertices)
    {
        if (vertices <= 0)
        {
            throw std::invalid_argument("Number of vertices must be positive");
        }

        adjList = new Node*[numVertices];
        for (int i = 0; i < numVertices; ++i)
        {
            adjList[i] = nullptr;
        }
    }

    Graph::~Graph() {
        for (int i = 0; i < numVertices; ++i)
        {
            Node* current = adjList[i];
            while (current)
            {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] adjList;
    }

    bool Graph::addEdge(int src, int dest, int weight)
    {
        if (src == dest)
        {
            std::cout << "Cannot add an edge from a vertex to itself (" << src << ")" << std::endl;
            return false;
        }

        if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices)
        {
            std::cout << "Error: Source or destination vertex is out of range" << std::endl;
            return false;
        }

        //Check if edge already exists
        Node* temp = adjList[src];

        while (temp)
        {
            if (temp->vertex == dest)
            {
                std::cout << "Edge already exists between " << src << " and " << dest << std::endl;
                return false;
            }
            temp = temp->next;
        }

        //Add to src the new dest -in adjList.
        Node* newNode = new Node(dest, weight);
        newNode->next = adjList[src];
        adjList[src] = newNode;

        //Add to dest the src (undirected)
        Node* newNode2 = new Node(src, weight);
        newNode2->next = adjList[dest];
        adjList[dest] = newNode2;

        return true;
    }

    bool Graph::removeEdgeFromList(int vertex, int target)
    {
        Node* prev = nullptr;
        Node* temp = adjList[vertex];

        while (temp)
        {
            if (temp->vertex == target)
            {
                if (prev)
                {
                    prev->next = temp->next;
                } else {
                    adjList[vertex] = temp->next;
                }
                delete temp;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;
    }

    bool Graph::removeEdge(int src, int dest)
    {
        if (src == dest)
        {
            std::cout << "Cannot add an edge from a vertex to itself (" << src << ")" << std::endl;
            return false;
        }
        if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices)
        {
            std::cout << "Error: Source or destination vertex is out of range" << std::endl;
            return false;
        }

        //remove src->dest
        bool removed = removeEdgeFromList(src, dest);
        if (!removed) {
            std::cout << "Error: Edge does not exist between " << src << " and " << dest << "." << std::endl;
            return false;
        }

        //remove dest->src
        removed = removeEdgeFromList(dest, src);
        if(!removed)
        {
            std::cout << "Although the graph is directed, no edge exists between the destination and source." << std::endl;
            return false;
        }

        return true;
    }

    void Graph::print_graph() const {

        std::cout << "Adjacency List of the Graph:" << std::endl;
        for (int i = 0; i < numVertices; ++i) {
            std::cout << i << ": ";
            Node* temp = adjList[i];
            while (temp) {
                std::cout << "(" << temp->vertex << ", w=" << temp->weight << ") ";
                temp = temp->next;
            }
            std::cout << std::endl;
        }
    }


    int Graph::getEdgeWeight(int src, int dest) const {
        if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices)
        {
            std::cout << "Error: Source or destination vertex is out of range" << std::endl;
            return 0;
        }

        Node* temp = adjList[src];
        while (temp) {
            if (temp->vertex == dest)
            {
                return temp->weight;
            }
            temp = temp->next;
        }

        std::cout << "No such edge found" << std::endl;
        return 0;
    }

    Edge* Graph::getEdges(int* numEdges) const
    {
        *numEdges = 0;
        Edge* edgesList = nullptr;

        //First loop to count edges
        for (int i = 0; i < numVertices; i++) {
            Node* temp = adjList[i];
            while (temp) {
                if (i < temp->vertex) //Avoid adding duplicate edges
                {
                    (*numEdges)++;
                }
                temp = temp->next;
            }
        }

        if (*numEdges > 0) {
            edgesList = new Edge[*numEdges];
        }
        else
        {
            return edgesList;
        }

        int index = 0;
        for (int i = 0; i < numVertices; i++) {
            Node* temp = adjList[i];
            while (temp) {
                if (i < temp->vertex)
                {
                    edgesList[index].src = i;
                    edgesList[index].dest = temp->vertex;
                    edgesList[index].weight = temp->weight;
                    index++;
                }
                temp = temp->next;
            }
        }
        return edgesList;
    }


    bool Graph::isConnected() const
    {
        Graph visitedGraph = Algorithms::dfs(*this, 0);

        return visitedGraph.getNumVertices() == numVertices;

    }
}