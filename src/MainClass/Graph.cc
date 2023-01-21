#include "Graph.h"

s21::Graph::Graph() {}

s21::Graph::~Graph() {}

s21::GraphData s21::Graph::loadGraphFromFile(const std::string& filepath) {
  try {
    m_data_ = m_file_hndlr_.parseFile(filepath);
  } catch (const std::exception& exc) {
    std::cout << exc.what() << std::endl;
  }
}

void s21::Graph::exportGraphToDot(const std::string& filepath) {
  m_file_hndlr_.writeToFile(filepath, m_data_);
}