#ifndef SRC_GRAPH_ALGORITHMS_H_
#define SRC_GRAPH_ALGORITHMS_H_

#include <algorithm>
#include <map>
#include <vector>

#include "../main_class/graph.h"
#include "../main_class/iterators/row_graph_iterator.h"

namespace s21 {
  struct TsmResult {
    int* vertices;
    double distance;
  };

class GraphAlgorithms {
 public:
  GraphAlgorithms();
  ~GraphAlgorithms();
  static std::vector<int> depthFirstSearch(Graph& graph, int start_vertex);
  static std::vector<int> breadthFirstSearch(Graph& graph, int start_vertex);
  static int getShortestPathBetweenVertices(Graph& graph, int vertex1,
                                            int vertex2);
  static s21::Matrix<int> getShortestPathsBetweenAllVertices(Graph& graph);
  //static TsmResult solveTravelingSalesmanProblem(Graph &graph);

 private:
  template <class Container>
  static std::vector<int> searchAlgorithm_(Graph& graph, int start_vertex,
                                           Container& not_visited_vertices);
  static std::vector<int> getHeirsIndexes_(Graph& graph, int start_vertex);
  static void prepareGraphForFloydWarshallAlgo_(Graph& graph);
  static int isPath_(int tag);
};
}  // namespace s21

#endif  // SRC_GRAPH_ALGORITHMS_H_