#ifndef SRC_GRAPH_ALGORITHMS_H_
#define SRC_GRAPH_ALGORITHMS_H_

#include "../main_class/graph.h"
#include <vector>

namespace s21 {
  class GraphAlgorithms {
    public:
      GraphAlgorithms();
      ~GraphAlgorithms();
      std::vector<int> depthFirstSearch(Graph &graph, int startVertex);
  };
}

#endif  // SRC_GRAPH_ALGORITHMS_H_