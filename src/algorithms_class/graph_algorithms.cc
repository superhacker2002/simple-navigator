#include "graph_algorithms.h"

#include "../helpers/containers/s21_queue.h"
#include "../helpers/containers/s21_stack.h"

std::vector<int> s21::GraphAlgorithms::depthFirstSearch(Graph& graph,
                                                        int start_vertex) {
  s21::Stack<int> not_visited_verticles;
  return searchAlgorithm_<s21::Stack<int>>(graph, start_vertex,
                                           not_visited_verticles);
}

std::vector<int> s21::GraphAlgorithms::breadthFirstSearch(Graph& graph,
                                                          int start_vertex) {
  s21::Queue<int> not_visited_verticles;
  return searchAlgorithm_<s21::Queue<int>>(graph, start_vertex,
                                           not_visited_verticles);
}

int s21::GraphAlgorithms::getShortestPathBetweenVertices(Graph& graph,
                                                         int vertex1,
                                                         int vertex2) {
  vertex1 -= 1;
  std::map<int, bool> visited_vertices;
  s21::Queue<int> not_visited_vertices = {vertex1};

  int vertices_number = graph.getVerticesCount();

  std::vector<int> tags(vertices_number, std::numeric_limits<int>::max());
  tags[vertex1] = 0;

  while ((int)visited_vertices.size() != vertices_number &&
         !not_visited_vertices.empty()) {
    for (auto heir : getHeirsIndexes_(graph, vertex1)) {
      if (!visited_vertices.count(vertex1)) {
        not_visited_vertices.push(heir);
        int weight = *(graph.rowBegin(vertex1) + heir);
        tags[heir] = std::min(tags[heir], tags[vertex1] + weight);
      }
    }
    not_visited_vertices.pop();
    visited_vertices[vertex1] = true;
    vertex1 = not_visited_vertices.peek();
  }
  return tags[vertex2 - 1];
}

s21::Matrix<int> s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(Graph& graph) {
    std::vector<Graph> graphs(graph.getVerticesCount() + 1, s21::Graph(graph.getVerticesCount()));
    prepareGraphForFloydWarshallAlgo_(graph);
    graphs.at(0) = graph;
    for (int k = 1; k <= graph.getVerticesCount(); ++k) {
        for (int i = 0; i < graph.getVerticesCount(); ++i) {
            for (int j = 0; j < graph.getVerticesCount(); ++j) {
                Graph& prev_graph = graphs.at(k - 1);
                graphs.at(k).getWeigth(i, j) =
                    std::min(
                        prev_graph.getWeigth(i, j),
                        prev_graph.getWeigth(i, k-1) + prev_graph.getWeigth(k-1, j));
            }
        }
    }
    return graphs.at(graph.getVerticesCount()).graphToMatrix();
}

template <class Container>
std::vector<int> s21::GraphAlgorithms::searchAlgorithm_(
    Graph& graph, int start_vertex, Container not_visited_vertices) {
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

std::vector<int> s21::GraphAlgorithms::getHeirsIndexes_(Graph& graph,
                                                        int start_index) {
  std::vector<int> heirs_indexes;
  for (auto it = graph.rowBegin(start_index); it != graph.rowEnd(start_index);
       ++it) {
    if (*it != 0) {
      heirs_indexes.push_back(it.get_curr_col());
    }
  }
  return heirs_indexes;
}

void s21::GraphAlgorithms::prepareGraphForFloydWarshallAlgo_(Graph& graph) {
    for (int i = 0; i < graph.getVerticesCount(); i++) {
        for (int j = 0; j < graph.getVerticesCount(); j++) {
            if (i == j) {
                graph.getWeigth(i, j) = 0;
            } else {
                if (graph.getWeigth(i, j) == 0) {
                    graph.getWeigth(i, j) = 1000;
                }
            }
        }
    }
}   

