#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <string>
#include "../includes/includes.h"

namespace s21 {
  class Graph {
    public:
      GraphData loadGraphFromFile(const std::string& filename);
      void exportGraphToDot(const std::string& filename);

  };
}

#endif  // SRC_GRAPH_H_