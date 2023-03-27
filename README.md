
# SimpleNavigator

Implementation of several basic algorithms on graphs. 

## Information

### Representation of the graph

The main ways of representing graphs are:
* *an adjacency matrix* is a square matrix whose dimension is equal to the number of vertices in the graph, and in which $`A_{ij}`$ element of the matrix contains information about an edge from vertex $`i`$ to vertex $`j`$. Possible values that $`A_{ij}`$ can have:
    + for an unweighted undirected graph:
        - 0 - there is no edge between the vertices
        - 1 - there is an edge between the vertices
    + for a weighted undirected graph:
        - 0 - there is no edge between the vertices
        - N - there is an edge between vertices, and its weight is N
    + for an unweighted directed graph:
        - 0 - there is no arc between the vertices
        - 1 - there is an arc (directed edge), which is directed from vertex $`i`$ to vertex $`j`$.
    + for a weighted directed graph:
        - 0 - there is no arc between the vertices
        - N - there is an arc (directed edge), which is directed from vertex $`i`$ to vertex $`j`$, and its weight is N
        
You can find an example of representing a graph with an adjacency matrix in the materials.

## Usage
Install the application with `make interface` in terminal and choose available options:
1. Downloading graph from a file and export it to .dot.
2. Depth- or Breadth-first search graph.
3. Finding the shortest path between two vertices or between all vertices.
4. Finding the minimum spanning tree.
5. Solving travelling salesman problem using different algorithms and comparison of the time of execution.
