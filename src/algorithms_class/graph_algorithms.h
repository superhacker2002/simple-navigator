#ifndef SRC_GRAPH_ALGORITHMS_H_
#define SRC_GRAPH_ALGORITHMS_H_

#include "../main_class/graph.h"
#include "../main_class/iterators/row_graph_iterator.h"
#include <vector>
#include <map>
#include <algorithm>

namespace s21 {
  class GraphAlgorithms {
    public:
      GraphAlgorithms();
      ~GraphAlgorithms();
      static std::vector<int> depthFirstSearch(Graph &graph, int start_vertex);
      static std::vector<int> breadthFirstSearch(Graph& graph, int start_vertex);
      static int getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);

    private:
      template <class Container>
      static std::vector<int> searchAlgorithm_(Graph& graph, int start_vertex, Container not_visited_vertices);
      static std::vector<int> getHeirsIndexes_(Graph& graph, int start_vertex);
  };
}

#endif  // SRC_GRAPH_ALGORITHMS_H_