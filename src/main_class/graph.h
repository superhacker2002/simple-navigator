#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include "../helpers/includes.h"
#include "file_handler/file_handler.h"
#include "iterator/graph_iterator.h"

namespace s21 {
  class Graph {
    public:
      using iterator = s21::GraphIterator<int>;
      Graph();
      ~Graph();
      void loadGraphFromFile(const std::string& filename);
      void exportGraphToDot(const std::string& filename);
      iterator begin();
      iterator end();
    friend class GraphAlgorithms;

    private:
      FileHandler m_file_hndlr_;
      GraphData m_data_;

  };
}

#endif  // SRC_GRAPH_H_