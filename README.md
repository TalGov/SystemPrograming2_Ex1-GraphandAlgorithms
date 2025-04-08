# SystemPrograming2_Ex1-Graph&Algorithms
## Project Description
The project includes two main classes:

### Algorithms:
The class includes the most common algorithms for working with undirected graphs (Algorithms.hpp):

- **Prim** – Algorithm for finding the Minimum Spanning Tree (MST) in an undirected graph.
- **Kruskal** – Another algorithm for finding the Minimum Spanning Tree (MST) in an undirected graph.
- **Dijkstra** – Algorithm for finding the shortest path between vertices in a weighted graph.
- **BFS** - Breadth-First Search : level by level, visiting all neighbors before moving to the next level.
- **DFS** - Depth-First Search : by going as deep as possible along each branch before backtracking.

### Graph:
The class contains the implementation of the undirected graph itself using an adjacency list (graph.hpp). 
Each graph is represented by a list of vertices. 
The class also includes structs for nodes (Node.hpp) and edges (Edge.hpp), allowing flexible and efficient management and operations on the graph.


## Data Structures:
In this project, I did not use the standard libraries for data structures, so I implemented three  data structures:

1. **Priority Queue:** implementation of a priority queue that stores vertices with associated weights and allows for retrieval of the vertex with the smallest weight (PriorityQueue.hpp).
2. **Queue:** A basic queue implementation for handling elements in a first-in, first-out (FIFO) manner (Queue.hpp).
3. **Union-Find:** A data structure used for managing and merging disjoinsets sets (UnionFind.hpp).
