#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include "../hepers/includes.h"
#include "../file_handler/file_handler.h"

namespace s21 {
  class Graph {
    public:
      Graph();
      ~Graph();
      GraphData loadGraphFromFile(const std::string& filename);
      void exportGraphToDot(const std::string& filename);

    private:
      FileHandler m_file_hndlr_;
      GraphData m_data_;

  };
}

#endif  // SRC_GRAPH_H_