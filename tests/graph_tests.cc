
#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "../src/main_class/graph.h"

const std::vector<int> answer = {0,  12, 0, 0, 0, 0, 0, 0, 20, 8, 11, 0, 0,
                                 17, 0,  0, 0, 0, 0, 0, 0, 0,  0, 0,  0};
const std::vector<int> col_answer = {0, 0, 11, 0, 0};

struct GraphTest : public testing::Test {
 protected:
  s21::Graph graph;
  void SetUp() { graph.loadGraphFromFile("../datasets/sample2.txt"); }
  void TearDown() {}
};

TEST_F(GraphTest, iterator_operator_plus) {
  auto answer_it = answer.begin();
  for (auto it = graph.begin(); it != graph.end(); ++it) {
    EXPECT_EQ(*it, *answer_it);
    answer_it++;
  }
}

TEST_F(GraphTest, iterator_operator_minus) {
  auto answer_it = answer.end() - 1;
  for (auto it = graph.end() - 1; it != graph.begin(); --it) {
    EXPECT_EQ(*it, *answer_it);
    answer_it--;
  }
}

TEST_F(GraphTest, row_iterator_operator_plus) {
  auto answer_it = answer.begin();
  for (auto it = graph.rowBegin(0); it != graph.rowEnd(0); ++it) {
    EXPECT_EQ(*it, *answer_it);
    answer_it++;
  }
}

TEST_F(GraphTest, row_iterator_operator_minus) {
  auto answer_it = answer.end() - 1;
  auto it = graph.rowEnd(4) - 1;
  for (; it != graph.rowBegin(4); --it) {
    EXPECT_EQ(*it, *answer_it);
    answer_it--;
  }
  EXPECT_EQ(*it, *answer_it);
}

TEST_F(GraphTest, col_iterator_operator_plus) {
  auto answer_it = col_answer.begin();
  for (auto it = graph.colBegin(0); it != graph.colEnd(0); ++it) {
    EXPECT_EQ(*it, *answer_it);
    answer_it++;
  }
}

TEST_F(GraphTest, col_iterator_operator_minus) {
  auto answer_it = col_answer.end() - 1;
  auto it = graph.colEnd(0) - 1;
  for (; it != graph.colBegin(0); --it) {
    EXPECT_EQ(*it, *answer_it);
    answer_it--;
  }
  EXPECT_EQ(*it, *answer_it);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
