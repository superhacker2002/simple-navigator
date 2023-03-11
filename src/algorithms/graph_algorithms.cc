#include "graph_algorithms.h"

#include <queue>

#include "../helpers/containers/s21_queue.h"
#include "../helpers/containers/s21_stack.h"

/**
 * Method for traversing graph data structure.
 * The algorithm starts at the root node (selecting some arbitrary node
 * as the root node in the case of a graph) and explores as far as possible
 * along each branch before backtracking.
 * @returns vector containing the traversed vertices in the order
 * of their traversal
 */
std::vector<int> s21::GraphAlgorithms::depthFirstSearch(const Graph& graph,
                                                        int start_vertex) {
  s21::Stack<int> not_visited_verticles;
  return searchAlgorithm_<s21::Stack<int>>(graph, start_vertex,
                                           not_visited_verticles);
}
/**
 * Method for traversing graph data structure.
 * The algorithm starts at the tree’s root or graph and searches/visits
 * all nodes at the current depth level before moving on to the nodes at
 * the next depth level.
 * @returns vector containing the traversed vertices in the order
 * of their traversal
 */
std::vector<int> s21::GraphAlgorithms::breadthFirstSearch(const Graph& graph,
                                                          int start_vertex) {
  s21::Queue<int> not_visited_verticles;
  return searchAlgorithm_<s21::Queue<int>>(graph, start_vertex,
                                           not_visited_verticles);
}

/**
 * Method for finding the shortest path between vertex1
 * and vertex2 in a weighted graph using Dijkstra's algorithm.
 * @returns numerical result equal to the smallest distance
 */
int s21::GraphAlgorithms::getShortestPathBetweenVertices(const Graph& graph,
                                                         int vertex1,
                                                         int vertex2) {
  vertex1 -= 1;
  std::map<int, bool> visited_vertices;
  s21::Queue<int> not_visited_vertices = {vertex1};

  int vertices_number = graph.getVerticesCount();
  std::vector<double> tags(vertices_number, INF);
  tags[vertex1] = 0;

  while ((int)visited_vertices.size() != vertices_number &&
         !not_visited_vertices.empty()) {
    for (auto heir : getHeirsIndexes_(graph, vertex1)) {
      if (!visited_vertices.count(vertex1)) {
        not_visited_vertices.push(heir);
        double weight = graph.getWeight(vertex1, heir);
        tags[heir] = std::min(tags[heir], tags[vertex1] + weight);
      }
    }
    not_visited_vertices.pop();
    visited_vertices[vertex1] = true;
    vertex1 = not_visited_vertices.peek();
  }
  printf("%f\n", tags[vertex2 - 1]);
  return isPath_(tags[vertex2 - 1]);
}

/**
 * Method for finding shortest paths between all pairs of
 * vertices in a directed weighted graph using Floyd–Warshall algorithm.
 * @returns matrix of shortest paths between all vertices of the graph.
 */
s21::GraphData::MatrixType
s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(const Graph& graph) {
  std::vector<Graph> graphs(graph.getVerticesCount() + 1,
                            s21::Graph(graph.getVerticesCount()));
  s21::Graph prepared_graph = prepareGraphForFloydWarshallAlgo_(graph);
  graphs.at(0) = prepared_graph;
  for (int k = 1; k <= prepared_graph.getVerticesCount(); ++k) {
    for (int i = 0; i < prepared_graph.getVerticesCount(); ++i) {
      for (int j = 0; j < prepared_graph.getVerticesCount(); ++j) {
        Graph& prev_graph = graphs.at(k - 1);
        graphs.at(k).getWeigth(i, j) = std::min(
            prev_graph.getWeigth(i, j),
            prev_graph.getWeigth(i, k - 1) + prev_graph.getWeigth(k - 1, j));
      }
    }
  }
  return graphs.at(prepared_graph.getVerticesCount()).graphToMatrix();
}

/**
 * Method that solves the traveling salesman problem using an ant algorithm.
 * Finds the most advantageous (shortest) route passing through all the
 * vertices of the graph at least once, followed by a return to the original
 * vertex.
 * @returns struct that contains array with the desired route
 * (with the order of traversing the vertices) and the length of this route.
 */
TsmResult s21::GraphAlgorithms::solveTravelingSalesmanProblem(
    const Graph& graph) {
  SimpleACO colony(graph);
  return colony.findBestPath();
}

/**
 * 
*/
s21::GraphData::MatrixType s21::GraphAlgorithms::getLeastSpanningTree(
    const Graph& graph) {
  int vertices_number = graph.getVerticesCount();
  std::vector<bool> visited_vertices(vertices_number, false);
  visited_vertices[0] = true;
  s21::GraphData::MatrixType spanning_tree(vertices_number);
  spanning_tree.FillMatrix(0.0);
  int current_edge = 0;

  while (current_edge < vertices_number - 1) {
    double min_dist = INF;
    int from = 0, to = 0;
    for (int i = 0; i < vertices_number; i++) {
      if (visited_vertices[i]) {
        for (int j = 0; j < vertices_number; j++) {
          double distance = graph.getWeight(i, j);
          if (!visited_vertices[j] && distance && distance < min_dist) {
            min_dist = distance;
            from = i;
            to = j;
          }
        }
      }
    }
    spanning_tree(from, to) = graph.getWeight(from, to);
    visited_vertices[to] = true;
    current_edge++;
  }
  spanning_tree.OutputMatrix();
  return spanning_tree;
}

int s21::GraphAlgorithms::isPath_(double tag) {
  if (tag == INF) {
    throw std::invalid_argument("No path between these two vertices.");
  }
  return tag;
}

template <class Container>
std::vector<int> s21::GraphAlgorithms::searchAlgorithm_(
    const Graph& graph, int start_vertex, Container& not_visited_vertices) {
  start_vertex -= 1;
  not_visited_vertices.push(start_vertex);
  std::map<int, bool> visited_vertices{{start_vertex, true}};
  std::vector<int> vertices_sequence;

  while (!not_visited_vertices.empty()) {
    int curr_vertex = not_visited_vertices.peek();
    not_visited_vertices.pop();
    visited_vertices[curr_vertex] = true;
    vertices_sequence.push_back(curr_vertex + 1);
    for (int& heir : getHeirsIndexes_(graph, curr_vertex)) {
      if (!visited_vertices[heir]) {
        not_visited_vertices.push(heir);
        visited_vertices[heir] = true;
      }
    }
  }
  return vertices_sequence;
}

std::vector<int> s21::GraphAlgorithms::getHeirsIndexes_(const Graph& graph,
                                                        int start_index) {
  std::vector<int> heirs_indexes;
  for (auto it = graph.cRowBegin(start_index); it != graph.cRowEnd(start_index);
       ++it) {
    if (*it != 0) {
      heirs_indexes.push_back(it.get_curr_col());
    }
  }
  return heirs_indexes;
}

s21::Graph s21::GraphAlgorithms::prepareGraphForFloydWarshallAlgo_(
    const Graph& graph) {
  s21::Graph prepared_graph(graph);
  for (int i = 0; i < prepared_graph.getVerticesCount(); i++) {
    for (int j = 0; j < prepared_graph.getVerticesCount(); j++) {
      if (i == j) {
        prepared_graph.getWeigth(i, j) = 0;
      } else {
        if (prepared_graph.getWeigth(i, j) == 0) {
          prepared_graph.getWeigth(i, j) = INF;
        }
      }
    }
  }
  return prepared_graph;
}
