#include "graph.h"
#include <cassert>

s21::Graph::Graph() {}

s21::Graph::Graph(const Graph& other) {
  m_data_ = other.m_data_;
}

s21::Graph& s21::Graph::operator=(const Graph& other) {
  m_data_ = other.m_data_;
  return *this;
}

s21::Matrix<int> s21::Graph::graph_to_matrix() {
  return s21::Matrix<int>(m_data_.matrix);
}

void s21::Graph::matrix_to_graph(const s21::Matrix<int>& other) {
  m_data_.matrix = other;
}

s21::Graph::~Graph() {}

void s21::Graph::loadGraphFromFile(const std::string& filepath) {
  try {
    m_data_ = m_file_hndlr_.parseFile(filepath);
  } catch (const std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

void s21::Graph::exportGraphToDot(const std::string& filepath) {
  try {
    m_file_hndlr_.writeToFile(filepath, m_data_);
  } catch (const std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

int& s21::Graph::getWeigth(int i, int j) {
  return m_data_.matrix(i, j);
}

s21::Graph::iterator s21::Graph::begin() {
  return iterator(&m_data_.matrix, 0, 0);
}

s21::Graph::iterator s21::Graph::end() {
  int rows = m_data_.matrix.GetRows();
  int cols = m_data_.matrix.GetCols();
  return iterator(&m_data_.matrix, rows - 1, cols);
}

s21::Graph::row_iterator s21::Graph::row_begin(int row) {
  assert(row < m_data_.matrix.GetRows());
  return row_iterator(&m_data_.matrix, row, 0);
}

s21::Graph::row_iterator s21::Graph::row_end(int row) {
  assert(row < m_data_.matrix.GetRows());
  int cols = m_data_.matrix.GetCols();
  return row_iterator(&m_data_.matrix, row, cols);
}

s21::Graph::col_iterator s21::Graph::col_begin(int col) {
  assert(col < m_data_.matrix.GetCols());
  return col_iterator(&m_data_.matrix, 0, col);
}

s21::Graph::col_iterator s21::Graph::col_end(int col) {
  assert(col < m_data_.matrix.GetCols());
  int rows = m_data_.matrix.GetRows();
  return col_iterator(&m_data_.matrix, rows, col);
}


