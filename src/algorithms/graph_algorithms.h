#ifndef GRAPH_ALGORITHMS_H_
#define GRAPH_ALGORITHMS_H_

#include <algorithm>
#include <vector>

#include "../graph/graph.h"

namespace s21 {
class GraphAlgorithms {
 public:
  GraphAlgorithms() = delete;
  ~GraphAlgorithms() = delete;
  static std::vector<int> depthFirstSearch(const Graph& graph,
                                           int start_vertex);
  static std::vector<int> breadthFirstSearch(const Graph& graph,
                                             int start_vertex);
  static double getShortestPathBetweenVertices(const Graph& graph, int vertex1,
                                            int vertex2);
  static GraphData::MatrixType getShortestPathsBetweenAllVertices(
      const Graph& graph);
  static GraphData::MatrixType getLeastSpanningTree(const Graph& graph);
  static TsmResult solveTravelingSalesmanProblem(const Graph& graph);
  static TsmResult solveTravelingSalesmanProblemBB(const Graph& graph);

 private:
  static constexpr double INF = std::numeric_limits<double>::infinity();
  template <class Container>
  static std::vector<int> searchAlgorithm_(const Graph& graph, int start_vertex,
                                           Container& not_visited_vertices);
  static std::vector<int> getHeirsIndexes_(const Graph& graph,
                                           int start_vertex);
  static Graph prepareGraphForFloydWarshallAlgo_(const Graph& graph);
  static int isPath_(double tag);
};
}  // namespace s21

#endif  // GRAPH_ALGORITHMS_H_