#include "graph.h"

#include <cassert>

s21::Graph::Graph() {}

s21::Graph::Graph(int n) {
  m_data_.matrix = std::make_unique<s21::GraphData::MatrixType>(n, n);
}

s21::Graph::Graph(const Graph &other) { m_data_ = other.m_data_; }

void s21::Graph::loadGraphFromFile(const std::string &filepath) {
  m_data_ = m_file_hndlr_.parseFile(filepath);
}

void s21::Graph::exportGraphToDot(const std::string &filepath) {
  m_file_hndlr_.writeToFile(filepath, m_data_);
}

s21::Graph &s21::Graph::operator=(const Graph &other) {
  m_data_ = other.m_data_;
  return *this;
}

s21::GraphData::MatrixType s21::Graph::graphToMatrix() const {
  return s21::GraphData::MatrixType(*m_data_.matrix);
}

void s21::Graph::matrixToGraph(const s21::GraphData::MatrixType &other) {
  if (m_data_.matrix == nullptr) {
    m_data_.matrix = std::make_unique<s21::GraphData::MatrixType>(1);
  }
  *m_data_.matrix = other;
}

s21::Graph::~Graph() {}

bool s21::Graph::isEmpty() {
  return m_data_.matrix.get() == nullptr ? true : m_data_.matrix->isEmpty();
}

int s21::Graph::getVerticesCount() const { return m_data_.matrix->GetRows(); }

double &s21::Graph::getWeight(int i, int j) { return (*m_data_.matrix)(i, j); }

double s21::Graph::getWeight(int i, int j) const {
  return m_data_.matrix->at(i, j);
}

s21::Graph::iterator s21::Graph::begin() {
  return iterator(m_data_.matrix.get(), 0, 0);
}

s21::Graph::iterator s21::Graph::end() {
  int rows = m_data_.matrix->GetRows();
  int cols = m_data_.matrix->GetCols();
  return iterator(m_data_.matrix.get(), rows - 1, cols);
}

s21::Graph::rowIterator s21::Graph::rowBegin(int row) {
  assert(row < m_data_.matrix->GetRows());
  return rowIterator(m_data_.matrix.get(), row, 0);
}

s21::Graph::rowIterator s21::Graph::rowEnd(int row) {
  assert(row < m_data_.matrix->GetRows());
  int cols = m_data_.matrix->GetCols();
  return rowIterator(m_data_.matrix.get(), row, cols);
}

s21::Graph::colIterator s21::Graph::colBegin(int col) {
  assert(col < m_data_.matrix->GetCols());
  return colIterator(m_data_.matrix.get(), 0, col);
}

s21::Graph::colIterator s21::Graph::colEnd(int col) {
  assert(col < m_data_.matrix->GetCols());
  int rows = m_data_.matrix->GetRows();
  return colIterator(m_data_.matrix.get(), rows, col);
}

s21::Graph::constIterator s21::Graph::cBegin() const {
  return constIterator(m_data_.matrix.get(), 0, 0);
}

s21::Graph::constIterator s21::Graph::cEnd() const {
  int rows = m_data_.matrix->GetRows();
  int cols = m_data_.matrix->GetCols();
  return constIterator(m_data_.matrix.get(), rows - 1, cols);
}

s21::Graph::constRowIterator s21::Graph::cRowBegin(int row) const {
  assert(row < m_data_.matrix->GetRows());
  return constRowIterator(m_data_.matrix.get(), row, 0);
}

s21::Graph::constRowIterator s21::Graph::cRowEnd(int row) const {
  assert(row < m_data_.matrix->GetRows());
  int cols = m_data_.matrix->GetCols();
  return constRowIterator(m_data_.matrix.get(), row, cols);
}

s21::Graph::constColIterator s21::Graph::cColBegin(int col) const {
  assert(col < m_data_.matrix->GetCols());
  return constColIterator(m_data_.matrix.get(), 0, col);
}

s21::Graph::constColIterator s21::Graph::cColEnd(int col) const {
  assert(col < m_data_.matrix->GetCols());
  int rows = m_data_.matrix->GetRows();
  return constColIterator(m_data_.matrix.get(), rows, col);
}