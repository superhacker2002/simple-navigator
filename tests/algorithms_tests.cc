#include <gtest/gtest.h>
#include "../src/main_class/graph.h"
#include "../src/algorithms_class/graph_algorithms.h"

const std::vector<int> dfs_answer = {1, 2, 3, 5, 4};



TEST(search_tests, DFS) {
  s21::Graph graph;
  graph.loadGraphFromFile("datasets/sample4.txt");
  s21::GraphAlgorithms algorithm;
  std::vector<int> result = algorithm.depthFirstSearch(graph, 1);
  auto start = dfs_answer.begin();
  for (auto &node : result) {
    EXPECT_EQ(node, start++);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
