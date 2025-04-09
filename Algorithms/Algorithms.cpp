//talgov44@gmail.com
#include "Algorithms.hpp"
#include <climits>

namespace graph {

    Graph Algorithms::bfs(const Graph &g, int start) {
        Queue q;
        int numVer = g.getNumVertices();

        Graph bfsT(numVer);

        if (numVer == 0) {
            throw std::invalid_argument("The graph is empty");
        }

        if (start < 0 || start >= g.getNumVertices()) {
            throw std::out_of_range("Vertex index out of range");

        }

        bool *visited = new bool[numVer]();
        visited[start] = true;
        q.enqueue(start);

        for (int i = 0; i < numVer; ++i) {
            visited[i] = false;
        }

        while (!q.isEmpty()) {
            int current = q.dequeue();
            for (int v = 0; v < numVer; v++) {
                int weight = g.getEdgeWeight(current, v);
                if (weight != 0 && !visited[v]) {
                    visited[v] = true;
                    bfsT.addEdge(current, v, weight);
                    q.enqueue(v);
                }
            }
        }

        delete[] visited;
        return bfsT;
    }


    void Algorithms::dfsHelper(const Graph& g, Graph& dfsT, bool* visited, int current)
    {
        visited[current] = true;
        int numVertices = g.getNumVertices();

        for (int v = 0; v < numVertices; ++v)
        {
            int weight = g.getEdgeWeight(current, v);
            if (weight != 0 && !visited[v])
            {
                dfsT.addEdge(current, v, weight);
                dfsHelper(g, dfsT, visited, v);
            }
        }
    }

    Graph Algorithms::dfs(const Graph& g, int start)
    {
        int numVertices = g.getNumVertices();
        Graph dfsT(numVertices);

        if (numVertices == 0) {
            throw std::invalid_argument("The graph is empty");
        }

        if (start < 0 || start >= numVertices) {
            throw std::out_of_range("Vertex index out of range");
        }

        bool* visited = new bool[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            visited[i] = false;
        }

        dfsHelper(g ,dfsT,visited,start);

        delete[] visited;
        return dfsT;
    }


    Graph Algorithms::dijkstra(const Graph &g, int src) {
        int numVertices = g.getNumVertices();
        Graph shortestPathTree(numVertices);

        if (numVertices == 0) {
            throw std::invalid_argument("The graph is empty");
        }

        if (src < 0 || src >= numVertices) {
            throw std::out_of_range("Vertex index out of range");
        }

        int numEdges = 0;
        Edge *edges = g.getEdges(&numEdges);
        for (int i = 0; i < numEdges; ++i) {
            if (edges[i].weight < 0) {
                delete[] edges;
                throw std::invalid_argument("Graph contains negative edge weights");

            }
        }

        int *dist = new int[numVertices];
        int *parent = new int[numVertices];
        bool *visited = new bool[numVertices];

        for (int i = 0; i < numVertices; ++i) {
            dist[i] = INT_MAX;
            parent[i] = -1;
            visited[i] = false;
        }

        dist[src] = 0;

        PriorityQueue pq(numVertices);
        pq.push(src, 0);

        while (!pq.isEmpty()) {
            int u = pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            for (int i = 0; i < numEdges; ++i) {
                if (edges[i].src == u || edges[i].dest == u) {
                    int v = (edges[i].src == u) ? edges[i].dest : edges[i].src;
                    int weight = edges[i].weight;

                    if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        parent[v] = u;
                        pq.push(v, dist[v]);
                    }
                }
            }
        }

        for (int i = 0; i < numVertices; ++i) {
            if (parent[i] != -1) {
                int w = dist[i] - dist[parent[i]];
                shortestPathTree.addEdge(parent[i], i, w);
            }
        }

        delete[] dist;
        delete[] parent;
        delete[] visited;
        delete[] edges;

        return shortestPathTree;
    }

    Graph Algorithms::prim(const Graph &g) {
        int numVertices = g.getNumVertices();
        Graph mst(numVertices);

        if (numVertices == 0) {
            throw std::invalid_argument("The graph is empty");
        }

        if (!g.isConnected()) {
            throw std::runtime_error("Graph is disconnected");
        }

        int *minWeight = new int[numVertices];
        int *parent = new int[numVertices];

        for (int i = 0; i < numVertices; ++i) {
            minWeight[i] = INT_MAX;
            parent[i] = -1;
        }

        minWeight[0] = 0;

        PriorityQueue pq(numVertices);
        for (int i = 0; i < numVertices; ++i) {
            pq.push(i, minWeight[i]);
        }

        while (!pq.isEmpty()) {
            int u = pq.pop();

            int numEdges = 0;
            Edge *edges = g.getEdges(&numEdges);

            for (int i = 0; i < numEdges; ++i) {
                int src = edges[i].src;
                int dest = edges[i].dest;
                int weight = edges[i].weight;

                if (src == u && pq.contains(dest) && weight < minWeight[dest]) {
                    minWeight[dest] = weight;
                    parent[dest] = u;
                    pq.decreaseKey(dest, weight);
                } else if (dest == u && pq.contains(src) && weight < minWeight[src]) {
                    minWeight[src] = weight;
                    parent[src] = u;
                    pq.decreaseKey(src, weight);
                }
            }

            delete[] edges;
        }

        for (int i = 1; i < numVertices; ++i) {
            if (parent[i] != -1) {
                mst.addEdge(parent[i], i, minWeight[i]);
            }
        }

        delete[] minWeight;
        delete[] parent;

        return mst;
    }

    Graph Algorithms::kruskal(const Graph &g) {
        int numVertices = g.getNumVertices();
        int numEdges = 0;
        Graph mst(numVertices);

        if (numVertices == 0) {
            throw std::invalid_argument("The graph is empty");
        }

        if (!g.isConnected()) {
            throw std::runtime_error("Graph is disconnected");
        }

        Edge *edges = g.getEdges(&numEdges);

        if (numEdges == 0) {
            throw std::invalid_argument("Graph has no edges");
        }

        //sort- bubble
        for (int i = 0; i < numEdges - 1; ++i) {
            for (int j = 0; j < numEdges - i - 1; ++j) {
                if (edges[j].weight > edges[j + 1].weight) {
                    Edge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }

        UnionFind UF(numVertices);

        for (int i = 0; i < numEdges; ++i) {
            int u = edges[i].src;
            int v = edges[i].dest;

            if (UF.find(u) != UF.find(v)) {
                mst.addEdge(u, v, edges[i].weight);
                UF.unionSets(u, v);
            }
        }

        delete[] edges;
        return mst;
    }

}