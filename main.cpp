//talgov44@gmail.com
#include <iostream>
#include "Graph/graph.hpp"
#include "Algorithms/Algorithms.hpp"

using namespace graph;

int main() {
    try{
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

        kruskalTree.removeEdge(0,2);

        kruskalTree.print_graph();

        int numV = kruskalTree.getNumVertices();
        std::cout << "The number of vertices in the graph: " << numV<< std::endl;

        int wEdge = kruskalTree.getEdgeWeight(1,3);
        std::cout << "The weight between vertex 1 and vertex 3: " << wEdge<< std::endl;

        int numEdges = 0;
        Edge* edges = primTree.getEdges(&numEdges);

        std::cout << "Number of edges: " << numEdges << std::endl;
        for (int i = 0; i < numEdges; ++i) {
            std::cout << "Edge from " << edges[i].src << " to " << edges[i].dest
                      << " with weight: " << edges[i].weight << std::endl;
        }


    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid argument error: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Out of range error: " << e.what() << std::endl;
    }catch (const std::runtime_error& e) {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }

    return 0;
}