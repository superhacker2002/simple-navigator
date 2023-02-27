#ifndef SRC_GRAPH_ALGORITHMS_H_
#define SRC_GRAPH_ALGORITHMS_H_

#include "../main_class/graph.h"
#include "../helpers/containers/s21_queue.h"
#include <vector>
#include <map>

namespace s21 {
  class GraphAlgorithms {
    public:
      GraphAlgorithms();
      ~GraphAlgorithms();
      static std::vector<int> depthFirstSearch(Graph &graph, int startVertex);
      static std::vector<int> breadthFirstSearch(const Graph& graph, int startVertex);


    private:
      static std::vector<int> getHeirsIndexes(const Graph& graph, int startVertex);
  };
}

#endif  // SRC_GRAPH_ALGORITHMS_H_