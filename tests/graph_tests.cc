
#include "../src/main_class/graph.h"

#include <gtest/gtest.h>
#include <vector>

const std::vector<int> answer = {0, 29, 20, 21, 16, 31, 100, 12, 4, 31, 18};

TEST(graph_tests, iterator) {
  s21::Graph graph;
  graph.loadGraphFromFile("datasets/sample1.txt");
  for (auto it = graph.begin(); it != graph.end(); ++it) {
    
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
