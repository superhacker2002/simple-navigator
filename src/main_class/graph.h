#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include "../helpers/includes.h"
#include "file_handler/file_handler.h"
#include "iterator/graph_iterator.h"
#include "iterator/col_graph_iterator.h"
#include "iterator/row_graph_iterator.h"

namespace s21 {
  class Graph {
    public:
      using iterator = s21::GraphIterator<int>;
      using row_iterator = s21::RowGraphIterator<int>;
      using col_iterator = s21::ColGraphIterator<int>;
      Graph();
      ~Graph();
      void loadGraphFromFile(const std::string& filename);
      void exportGraphToDot(const std::string& filename);
      iterator begin();
      iterator end();
      row_iterator row_begin(int row);
      row_iterator row_end(int row);
      col_iterator col_begin(int col);
      col_iterator col_end(int col);
    friend class GraphAlgorithms;

    private:
      FileHandler m_file_hndlr_;
      GraphData m_data_;
  };
}

#endif  // SRC_GRAPH_H_