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

s21::Graph::iterator s21::Graph::begin(int vertice) {
  return iterator(vertice);
}

s21::Graph::iterator s21::Graph::end(int vertice) {
  int last_neighbour = m_data_.matrix.GetCols();
  return iterator(m_data_.matrix(vertice, last_neighbour));
}
