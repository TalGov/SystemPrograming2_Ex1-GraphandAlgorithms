//talgov44@gmail.com
#include <iostream>
#include "Graph/graph.hpp"
#include "Algorithms/Algorithms.hpp"

using namespace graph;

int main() {

        Graph g(6);

        g.addEdge(0, 1, 4);
        g.addEdge(0, 2, 3);
        g.addEdge(1, 2, 1);
        g.addEdge(1, 3, 2);
        g.addEdge(2, 3, 4);
        g.addEdge(3, 4, 2);
        g.addEdge(4, 5, 6);

        g.print_graph();

        std::cout << "\n ---BFS---\n";
        Graph bfsTree = Algorithms::bfs(g, 0);
        bfsTree.print_graph();

        std::cout << "\n---DFS---\n";
        Graph dfsTree = Algorithms::dfs(g, 0);
        dfsTree.print_graph();

        std::cout << "\n---Dijkstra---\n";
        Graph dijkstraTree = Algorithms::dijkstra(g, 0);
        dijkstraTree.print_graph();

        std::cout << "\n---Prim---\n";
        Graph primTree = Algorithms::prim(g);
        primTree.print_graph();

        std::cout << "\n---Kruskal---\n";
        Graph kruskalTree = Algorithms::kruskal(g);
        kruskalTree.print_graph();

    return 0;
}