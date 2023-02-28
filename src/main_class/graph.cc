#include "graph.h"

s21::Graph::Graph() {}

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

s21::Graph::iterator s21::Graph::begin() {
  return iterator(&m_data_.matrix, 0, 0);
}

s21::Graph::iterator s21::Graph::end() {
  int rows = m_data_.matrix.GetRows();
  int cols = m_data_.matrix.GetCols();
  return iterator(&m_data_.matrix, rows - 1, cols);
}
