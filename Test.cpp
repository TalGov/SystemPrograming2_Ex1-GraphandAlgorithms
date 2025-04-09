// talgov44@gmail.com
#include "Doctest/doctest.hpp"
#include "Graph/graph.hpp"
#include "Algorithms/Algorithms.hpp"
#include "Structures/Queue.hpp"
#include "Structures/UnionFind.hpp"
#include "Structures/PriorityQueue.hpp"

using namespace std;
using namespace doctest;
using namespace graph;

TEST_CASE("Adding edges and edge list") {
    Graph g(5);
    g.addEdge(0, 1, 7);
    g.addEdge(0, 2, 12);
    g.addEdge(1, 3, 8);
    g.addEdge(3, 4, 4);


    CHECK(g.getEdgeWeight(1, 0) == 7); //check undirected
    CHECK(g.getEdgeWeight(0, 2) == 12);

    int numEdgeG = 0;
    Edge* edges = g.getEdges(&numEdgeG);
    CHECK(numEdgeG == 4); //num of edges
    CHECK(g.getEdgeWeight(0, 4) == 0); //get that not found edge 0-4
    CHECK_THROWS_AS( g.addEdge(0,3,0), invalid_argument); //check no edge
    CHECK_THROWS_AS( g.addEdge(7,2,6), out_of_range);

    delete[] edges;
}

TEST_CASE("Graph constructor and getNumV") {
    Graph g(10);
    CHECK(g.getNumVertices() == 10);
}

TEST_CASE("Adding existing edges and invalid edges") {
    Graph g(3);
    CHECK( g.addEdge(0, 1, 5) == true);

    CHECK(g.addEdge(0, 1, 5) == false); //check already exist

    CHECK(g.getEdgeWeight(0, 1) == 5);

    CHECK_THROWS_AS(g.addEdge(0, 3, 10),out_of_range); //out of bound- vertex 3

    CHECK_THROWS_AS(g.addEdge(0, 0, 5),invalid_argument); //edge from src=dest
}

TEST_CASE("Removing edges") {
    Graph g(4);
    g.addEdge(0, 1, 8);
    g.addEdge(1, 2, 5);
    g.addEdge(2, 3, 11);


    CHECK(g.removeEdge(1, 2) == true); // remove edge
    CHECK(g.getEdgeWeight(1, 2) == 0); // the edge removed

    CHECK_THROWS_AS(g.removeEdge(0, 3), invalid_argument); // edge doesn't exist
}

TEST_CASE("Testing Dijkstra with negative weights") {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, -5);   // negative edge
    g.addEdge(2, 3, 1);


    CHECK_THROWS_AS(Algorithms::dijkstra(g, 0), invalid_argument); //Does not support negative weight
}

TEST_CASE("Testing Prim's algorithm with disconnected graph") {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 5);

    CHECK_THROWS_AS(Algorithms::prim(g), runtime_error); //Doesn't support unconnected graph
}


TEST_CASE("Testing Kruskal's algorithm with disconnected graph") {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 5);

    CHECK_THROWS_AS(Algorithms::kruskal(g), runtime_error); //Doesn't support unconnected graph
}

TEST_CASE("Testing DFS and BFS with invalid input") {
    Graph g(3);

    CHECK_THROWS_AS(Algorithms::dfs(g, 5), out_of_range);  // No such vertex exists
    CHECK_THROWS_AS(Algorithms::bfs(g, 6), out_of_range);  //No such vertex exists.
}

TEST_CASE("Testing Prim's algorithm for connected graph") {
    Graph g(4);
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 2);

    CHECK_NOTHROW(Algorithms::prim(g)); //Checks that there is no exception that it is not connected
}

TEST_CASE("Testing Kruskal's algorithm for connected graph") {
    Graph g(4);
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 2);

    CHECK_NOTHROW(Algorithms::kruskal(g)); //Checks that there is no exception that it is not connected
}

TEST_CASE("Testing DFS Algorithm") {

    int numE;
    Graph g(7);

    g.addEdge(0, 1, 8);
    g.addEdge(0, 2, 15);
    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 11);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 5);
    g.addEdge(4, 6, 3);

    Graph dfsT = Algorithms::dfs(g, 4);
    Edge* edges = dfsT.getEdges(&numE);

    CHECK(numE == 6);
    CHECK(dfsT.getEdgeWeight(4, 5) == 5);
    CHECK(dfsT.getEdgeWeight(4, 6) == 3);
    CHECK(dfsT.getEdgeWeight(5, 3) == 6);
    CHECK(dfsT.getEdgeWeight(3, 1) == 7);
    CHECK(dfsT.getEdgeWeight(1, 0) == 8);
    CHECK(dfsT.getEdgeWeight(0, 2) == 15);

    delete[] edges;

    CHECK_NOTHROW(Algorithms::dfs(g, 0));
}

TEST_CASE("Testing BFS Algorithm") {
    int numE;
    Graph g(7);

    g.addEdge(0, 1, 8);
    g.addEdge(0, 2, 15);
    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 11);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 5);
    g.addEdge(4, 6, 3);

    Graph bfsT = Algorithms::bfs(g, 4);
    Edge* edges = bfsT.getEdges(&numE);

    CHECK(numE == 6);
    CHECK(bfsT.getEdgeWeight(4, 5) == 5);
    CHECK(bfsT.getEdgeWeight(4, 6) == 3);
    CHECK(bfsT.getEdgeWeight(4, 2) == 11);
    CHECK(bfsT.getEdgeWeight(2, 1) == 4);
    CHECK(bfsT.getEdgeWeight(2, 0) == 15);
    CHECK(bfsT.getEdgeWeight(5, 3) == 6);

    delete[] edges;

    CHECK_NOTHROW(Algorithms::bfs(g, 2));
}

TEST_CASE("Testing Dijkstra's Algorithm (positive weights)") {
    int numE;
    Graph g(7);

    g.addEdge(0, 1, 8);
    g.addEdge(0, 2, 15);
    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 11);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 5);
    g.addEdge(4, 6, 3);

    Graph dijkstraT = Algorithms::dijkstra(g, 3);
    Edge* edges = dijkstraT.getEdges(&numE);

    CHECK(numE == 6);
    CHECK(dijkstraT.getEdgeWeight(3, 5) == 6);
    CHECK(dijkstraT.getEdgeWeight(5, 4) == 5);
    CHECK(dijkstraT.getEdgeWeight(4, 6) == 3);
    CHECK(dijkstraT.getEdgeWeight(3, 1) == 7);
    CHECK(dijkstraT.getEdgeWeight(1, 2) == 4);
    CHECK(dijkstraT.getEdgeWeight(1, 0) == 8);

    delete[] edges;

    CHECK_NOTHROW(Algorithms::dijkstra(g, 4));
}

TEST_CASE("Testing Prim's Algorithm") {
    int numE;
    Graph g(7);

    g.addEdge(0, 1, 8);
    g.addEdge(0, 2, 15);
    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 11);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 5);
    g.addEdge(4, 6, 3);

    Graph primT = Algorithms::prim(g);
    Edge* edges = primT.getEdges(&numE);

    CHECK(numE == 6);
    CHECK(primT.getEdgeWeight(0, 1) == 8);
    CHECK(primT.getEdgeWeight(1, 2) == 4);
    CHECK(primT.getEdgeWeight(1, 3) == 7);
    CHECK(primT.getEdgeWeight(3, 5) == 6);
    CHECK(primT.getEdgeWeight(5, 4) == 5);
    CHECK(primT.getEdgeWeight(4, 6) == 3);

    delete[] edges;
    CHECK_NOTHROW(Algorithms::prim(g));
}

TEST_CASE("Testing Kruskal's Algorithm") {
    int numE;
    Graph g(7);

    g.addEdge(0, 1, 8);
    g.addEdge(0, 2, 15);
    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 11);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 5);
    g.addEdge(4, 6, 3);

    Graph kruskalT = Algorithms::kruskal(g);
    Edge* edges = kruskalT.getEdges(&numE);

    CHECK(numE == 6);
    CHECK(kruskalT.getEdgeWeight(4, 6) == 3);
    CHECK(kruskalT.getEdgeWeight(4, 5) == 5);
    CHECK(kruskalT.getEdgeWeight(3, 5) == 6);
    CHECK(kruskalT.getEdgeWeight(1, 3) == 7);
    CHECK(kruskalT.getEdgeWeight(0, 1) == 8);
    CHECK(kruskalT.getEdgeWeight(1, 2) == 4);

    delete[] edges;

    CHECK_NOTHROW(Algorithms::kruskal(g));
}


////////////////////////////////////////////////////////////////////////////////////////////////////////


TEST_CASE("Testing PriorityQueue constructor and isEmpty") {
    PriorityQueue pq(5);
    CHECK(pq.isEmpty() == true);  //empty
    pq.push(1, 10);
    CHECK(pq.isEmpty() == false); //not empty
}

TEST_CASE("Testing PriorityQueue push and pop") {
    PriorityQueue pq(5);
    pq.push(0, 10);
    pq.push(1, 5);
    pq.push(2, 20);

    CHECK(pq.pop() == 1); //lowest weight
    CHECK(pq.pop() == 0);
    CHECK(pq.pop() == 2);
    CHECK(pq.pop() == -1); //No vertices
}


TEST_CASE("Testing PriorityQueue decreaseKey") {
    PriorityQueue pq(5);
    pq.push(0, 10);
    pq.push(1, 5);
    pq.push(2, 20);

    pq.decreaseKey(2, 3); //decrease key of 2
    CHECK(pq.pop() == 2);
    CHECK(pq.pop() == 1);
    CHECK(pq.pop() == 0);
}

TEST_CASE("Testing Queue constructor and isEmpty") {
    Queue q;
    CHECK(q.isEmpty() == true);  //is empty
    q.enqueue(5);
    CHECK(q.isEmpty() == false); //not empty
}

TEST_CASE("Testing Queue enqueue and dequeue") {
    Queue q;
    q.enqueue(5);
    q.enqueue(10);
    q.enqueue(15);

    CHECK(q.dequeue() == 5);
    CHECK(q.dequeue() == 10);
    CHECK(q.dequeue() == 15);
    CHECK(q.dequeue() == -1); //no values
}


TEST_CASE("Testing UnionFind constructor and find") {
    UnionFind uf(5);

    //Vertices point to themselves
    CHECK(uf.find(0) == 0);
    CHECK(uf.find(1) == 1);
    CHECK(uf.find(2) == 2);
}

TEST_CASE("Testing UnionFind unionSets") {
    UnionFind uf(5);

    uf.unionSets(0, 1);
    uf.unionSets(2, 3);
    uf.unionSets(1, 2);

    CHECK(uf.find(0) == uf.find(2)); //in the same group
}

