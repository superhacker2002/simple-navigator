#include <iostream>
#include <fstream>
#include "main_class/graph.h"
#include "algorithms_class/graph_algorithms.h"
#include "interface/interface.h"

int main() {
  // for (int i = 0; i < 12; ++i) {
  //   std::cout << char('A' + (i > 25 ? i % 26 : i)) + std::to_string(i/26) << " ";
  // }
  // s21::Graph graph;
  // graph.loadGraphFromFile("../datasets/sample1.txt");
  // s21::Matrix<int> mtrx = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
  // mtrx.OutputMatrix();
  s21::Interface* iface = s21::Interface::getIfaceInstance();
  iface->start();
}