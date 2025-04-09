//talgov44@gmail.com
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "../Graph/graph.hpp"
#include "../Structures/Queue.hpp"
#include "../Structures/UnionFind.hpp"
#include "../Structures/PriorityQueue.hpp"
#include <stdexcept>

namespace graph {

    class Algorithms {

    private:
        static void dfsHelper(const Graph& g ,Graph& dfsT ,bool* visited ,int current);

    public:
        static Graph bfs(const graph::Graph& g, int start);
        static Graph dfs(const graph::Graph& g, int start);
        static Graph dijkstra(const graph::Graph& g, int start);
        static Graph prim(const graph::Graph& g);
        static Graph kruskal(const graph::Graph& g);
    };
}
#endif
