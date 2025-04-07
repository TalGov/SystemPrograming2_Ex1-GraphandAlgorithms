//talgov44@gmail.com
#include "Algorithms.hpp"
#include <climits>

namespace graph {

    Graph Algorithms::bfs(const Graph& g, int start)
    {
        int numVertices = g.getNumVertices();

        if (numVertices == 0) {
            std::cout << "Error: The graph is empty" << std::endl;
            return Graph(0);
        }

        if (start < 0 || start >= numVertices) {
            std::cout << "Error: Start vertex " << start << " is out of bounds" << std::endl;
            return Graph(0);
        }

        Graph bfsT(numVertices);
        bool* visited = new bool[numVertices];

        for (int i = 0; i < numVertices; ++i) {
            visited[i] = false;
        }

        Queue queue;
        visited[start] = true;
        queue.enqueue(start);

        while (!queue.isEmpty()) {
            int current = queue.dequeue();

            for (int v = 0; v < numVertices; ++v) {
                int weight = g.getEdgeWeight(current, v);
                if (weight != 0 && !visited[v]) {
                    visited[v] = true;
                    bfsT.addEdge(current, v, weight);
                    queue.enqueue(v);
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

        if (numVertices == 0) {
            std::cout << "Error: The graph is empty" << std::endl;
            return Graph(0);
        }

        if (start < 0 || start >= numVertices) {
            std::cout << "Error: Start vertex " << start << " is out of bounds" << std::endl;
            return Graph(0);
        }

        Graph dfsT(numVertices);
        bool* visited = new bool[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            visited[i] = false;
        }

        dfsHelper(g ,dfsT,visited,start);

        delete[] visited;
        return dfsT;
    }


    Graph Algorithms::dijkstra(const Graph& g, int src)
    {
        int numVertices = g.getNumVertices();
        Graph shortestPathTree(numVertices);

        if (numVertices == 0) {
            std::cout << "Error: Graph is empty" << std::endl;
            return shortestPathTree;
        }

        if (src < 0 || src >= numVertices) {
            std::cout << "Error: Source vertex is out of bounds" << std::endl;
            return shortestPathTree;
        }

        int numEdges = 0;
        Edge* edges = g.getEdges(&numEdges);
        for (int i = 0; i < numEdges; ++i) {
            if (edges[i].weight < 0) {
                std::cout << "Error: Graph contains negative edge weights" << std::endl;
                delete[] edges;
                return shortestPathTree;
            }
        }

        int* dist = new int[numVertices];
        int* parent = new int[numVertices];
        bool* visited = new bool[numVertices];

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

    Graph Algorithms::prim(const Graph& g)
    {
        int numVertices = g.getNumVertices();

        if (numVertices == 0) {
            std::cout << "Error: Graph is empty" << std::endl;
            return Graph(0);
        }

        if (!g.isConnected()) {
            std::cout << "Error: Graph is not connected" << std::endl;
            return Graph(0);
        }

        Graph mst(numVertices);

        bool* inMST = new bool[numVertices];
        int* minWeight = new int[numVertices];
        int* parent = new int[numVertices];

        for (int i = 0; i < numVertices; ++i) {
            inMST[i] = false;
            minWeight[i] = INT_MAX;
            parent[i] = -1;
        }

        minWeight[0] = 0;

        for (int count = 0; count < numVertices - 1; ++count) {
            int min = INT_MAX;
            int u = -1;

            for (int v = 0; v < numVertices; ++v) {
                if (!inMST[v] && minWeight[v] < min) {
                    min = minWeight[v];
                    u = v;
                }
            }

            if (u == -1)
            {
                break;
            }

            inMST[u] = true;

            int numEdges = 0;
            Edge* edges = g.getEdges(&numEdges);

            for (int i = 0; i < numEdges; ++i) {
                int src = edges[i].src;
                int dest = edges[i].dest;
                int weight = edges[i].weight;

                if (src == u && !inMST[dest] && weight < minWeight[dest]) {
                    minWeight[dest] = weight;
                    parent[dest] = src;
                } else if (dest == u && !inMST[src] && weight < minWeight[src]) {
                    minWeight[src] = weight;
                    parent[src] = dest;
                }
            }

            delete[] edges;
        }

        for (int i = 1; i < numVertices; ++i) {
            if (parent[i] != -1) {
                mst.addEdge(parent[i], i, minWeight[i]);
            }
        }

        delete[] inMST;
        delete[] minWeight;
        delete[] parent;

        return mst;
    }

    Graph Algorithms::kruskal(const Graph& g)
    {
        int numVertices = g.getNumVertices();
        int numEdges = 0;

        if (numVertices == 0) {
            std::cout << "Error: Empty graph\n";
            return Graph(0);
        }

        if (!g.isConnected()) {
            std::cout << "Error: Graph is not connected.MST cannot be formed.\n";
            return Graph(0);
        }

        Edge* edges = g.getEdges(&numEdges);

        if (numEdges == 0) {
            std::cout << "Error: Graph has no edges\n";
            return Graph(0);
        }

        //sort- bubble
        for (int i = 0; i < numEdges - 1; ++i)
        {
            for (int j = 0; j < numEdges - i - 1; ++j)
            {
                if (edges[j].weight > edges[j + 1].weight) {
                    Edge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }

        Graph mst(numVertices);
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
