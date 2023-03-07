#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include "../helpers/includes.h"
#include "file_handler/file_handler.h"
#include "iterators/col_graph_iterator.h"
#include "iterators/graph_iterator.h"
#include "iterators/row_graph_iterator.h"

namespace s21 {
class Graph {
 public:
  using iterator = s21::GraphIterator<double>;
  using rowIterator = s21::RowGraphIterator<double>;
  using colIterator = s21::ColGraphIterator<double>;
  using constIterator = s21::ConstGraphIterator<double>;
  using constRowIterator = s21::ConstRowGraphIterator<double>;
  using constColIterator = s21::ConstColGraphIterator<double>;

  Graph();
  Graph(const Graph& other);
  Graph(int n);
  Graph& operator=(const Graph& other);
  ~Graph();

  void loadGraphFromFile(const std::string& filename);
  void exportGraphToDot(const std::string& filename);
  double& getWeigth(int i, int j);
  double getWeight(int i, int j) const;
  int getVerticesCount() const;
  iterator begin();
  iterator end();
  rowIterator rowBegin(int row);
  rowIterator rowEnd(int row);
  colIterator colBegin(int col);
  colIterator colEnd(int col);

  constIterator cBegin() const;
  constIterator cEnd() const;
  constRowIterator cRowBegin(int row) const;
  constRowIterator cRowEnd(int row) const;
  constColIterator cColBegin(int col) const;
  constColIterator cColEnd(int col) const;

  s21::GraphData::MatrixType graphToMatrix() const;
  void matrixToGraph(const s21::GraphData::MatrixType& other);

 private:
  FileHandler m_file_hndlr_;
  GraphData m_data_;
};
}  // namespace s21

#endif  // SRC_GRAPH_H_