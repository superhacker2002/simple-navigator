#include <iostream>
#include <fstream>
#include "main_class/graph.h"

int main() {
  // for (int i = 0; i < 12; ++i) {
  //   std::cout << char('A' + (i > 25 ? i % 26 : i)) + std::to_string(i/26) << " ";
  // }
  s21::Graph graph;
  graph.loadGraphFromFile("testdata/sample1.txt");
  graph.exportGraphToDot("graph.dot");
}