
#include "../src/main_class/graph.h"

#include <gtest/gtest.h>
#include <vector>
#include <iostream>

const std::vector<int> answer = {0, 12, 0, 0, 0,
                                 0, 0, 0, 20, 8, 
                                 11, 0, 0, 17, 0, 
                                 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0};

TEST(graph_tests, iterator_operator_plus) {
  s21::Graph graph;
  graph.loadGraphFromFile("../datasets/sample2.txt");
  auto answer_it = answer.begin();
  for (auto it = graph.begin(); it != graph.end(); ++it) {
    EXPECT_EQ(*it, *answer_it);
    answer_it++;
  }
}

TEST(graph_tests, iterator_operator_minus) {
  s21::Graph graph;
  graph.loadGraphFromFile("../datasets/sample2.txt");
  auto answer_it = answer.end();
  answer_it--;
  for (auto it = graph.end(); it != graph.begin(); --it) {
    EXPECT_EQ(*it, *answer_it);
    answer_it--;
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
