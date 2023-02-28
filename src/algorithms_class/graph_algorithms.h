#ifndef SRC_GRAPH_ALGORITHMS_H_
#define SRC_GRAPH_ALGORITHMS_H_

#include "../main_class/graph.h"
#include <vector>
#include <map>
#include <algorithm>

namespace s21 {
  class GraphAlgorithms {
    public:
      GraphAlgorithms();
      ~GraphAlgorithms();
      static std::vector<int> depthFirstSearch(Graph &graph, int start_vertex);
      static std::vector<int> breadthFirstSearch(const Graph& graph, int start_vertex);
      
      
      static std::vector<int> getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);

    private:
      static std::vector<int> getHeirsIndexes(const Graph& graph, int start_vertex);
  };
}

#endif  // SRC_GRAPH_ALGORITHMS_H_