//talgov44@gmail.com
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

    bool Graph::addEdge(int src, int dest, int weight) {
        if (src == dest) {
            throw std::invalid_argument("Can't add an edge from a vertex to itself");

        }

        if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
            throw std::out_of_range("Vertex index out of range");
        }
        if(weight == 0){
            throw std::invalid_argument("Weight cannot be zero");
        }

        // Check if edge already exists
        Node* temp = adjList[src];
        while (temp) {
            if (temp->vertex == dest) {
                std::cout << "The edge already exists from vertex " << src << " to vertex " << dest << std::endl;
                return false;
            }
            temp = temp->next;
        }

        //Add to src the new dest in adjList.
        Node* newNode = new Node(dest, weight);
        newNode->next = adjList[src];
        adjList[src] = newNode;

        //Add to dest the new src (undirected edge)
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
            throw std::invalid_argument("Can't add an edge from a vertex to itself");
        }
        if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices)
        {
            throw std::out_of_range("Vertex index out of range");
        }

        //remove src->dest
        bool removed = removeEdgeFromList(src, dest);
        if (!removed) {
            throw std::invalid_argument("Edge does not exist");
        }

        //remove dest->src
        removed = removeEdgeFromList(dest, src);
        if(!removed)
        {
            throw std::invalid_argument("Edge does not exist");
        }

        return true;
    }

    void Graph::print_graph() const {
        if (numVertices == 0) {
            throw std::invalid_argument("The graph is empty");
        }

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
            throw std::out_of_range("Vertex index out of range");
        }

        Node* temp = adjList[src];
        while (temp) {
            if (temp->vertex == dest)
            {
                return temp->weight;
            }
            temp = temp->next;
        }

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
        int numE;
        Graph visitedGraph = Algorithms::dfs(*this, 0);
        Edge* edges = visitedGraph.getEdges(&numE);

        if(numE >= visitedGraph.getNumVertices()-1)
        {
            delete[] edges;
            return true;
        }
        delete[] edges;
        return false;

    }
}