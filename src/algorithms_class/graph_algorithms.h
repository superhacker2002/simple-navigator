#ifndef SRC_GRAPH_ALGORITHMS_H_
#define SRC_GRAPH_ALGORITHMS_H_

#include <algorithm>
#include <map>
#include <vector>

#include "../main_class/graph.h"
#include "../main_class/iterators/row_graph_iterator.h"
#include "ant_algorithm/simple_aco.h"

namespace s21 {
class GraphAlgorithms {
 public:
  GraphAlgorithms();
  ~GraphAlgorithms();
  static std::vector<int> depthFirstSearch(const Graph& graph, int start_vertex);
  static std::vector<int> breadthFirstSearch(const Graph& graph, int start_vertex);
  static int getShortestPathBetweenVertices(const Graph& graph, int vertex1,
                                            int vertex2);  // double path
  static GraphData::MatrixType getShortestPathsBetweenAllVertices(const Graph& graph);  // double
  static TsmResult solveTravelingSalesmanProblem(const Graph &graph);
  static GraphData::MatrixType getLeastSpanningTree(const Graph &graph);

 private:
  static constexpr double INF = std::numeric_limits<double>::infinity();
  template <class Container>
  static std::vector<int> searchAlgorithm_(const Graph& graph, int start_vertex,
                                           Container& not_visited_vertices);
  static std::vector<int> getHeirsIndexes_(const Graph& graph, int start_vertex);
  static void prepareGraphForFloydWarshallAlgo_(Graph& graph);
  static int isPath_(int tag);
};
}  // namespace s21

#endif  // SRC_GRAPH_ALGORITHMS_H_