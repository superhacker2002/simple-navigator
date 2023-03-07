#include <gtest/gtest.h>

#include "../src/algorithms_class/graph_algorithms.h"
#include "../src/main_class/graph.h"

const std::vector<int> bfs_1_answer = {1, 2, 3, 5, 4, 6, 7};
const std::vector<int> dfs_1_answer = {1, 3, 6, 7, 4, 2, 5};

struct SearchAlgorithmsTest : public testing::Test {
 protected:
  s21::Graph graph;
  void SetUp() { graph.loadGraphFromFile("../datasets/sample5.txt"); }
  void TearDown() {}
};

TEST_F(SearchAlgorithmsTest, dfs_1) {
  std::vector<int> result = s21::GraphAlgorithms::depthFirstSearch(graph, 1);
  auto answer_it = dfs_1_answer.begin();
  for (auto& heir : result) {
    EXPECT_EQ(*answer_it, heir);
    answer_it++;
  }
}

TEST_F(SearchAlgorithmsTest, bfs_1) {
  std::vector<int> result = s21::GraphAlgorithms::breadthFirstSearch(graph, 1);
  auto answer_it = bfs_1_answer.begin();
  for (auto& heir : result) {
    EXPECT_EQ(*answer_it, heir);
    answer_it++;
  }
}

struct PathAlgorithmsTest : public testing::Test {
 protected:
  s21::Graph graph;
  void SetUp() { graph.loadGraphFromFile("../datasets/sample6.txt"); }
  void TearDown() {}
};

TEST_F(PathAlgorithmsTest, get_shortest_path_between_two_1) {
  int result =
      s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 2);
  EXPECT_EQ(result, 10);
}

TEST_F(PathAlgorithmsTest, get_shortest_path_between_two_2) {
  int result =
      s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 1, 7);
  EXPECT_EQ(result, 30);
}

TEST_F(PathAlgorithmsTest, get_shortest_path_between_two_3) {
  int result =
      s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 6, 4);
  EXPECT_EQ(result, 12);
}


TEST_F(PathAlgorithmsTest, get_shortest_path_between_two_4) {
  EXPECT_ANY_THROW(s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 2, 3));
  EXPECT_ANY_THROW(s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 3, 1));
  EXPECT_ANY_THROW(s21::GraphAlgorithms::getShortestPathBetweenVertices(graph, 7, 3));
}

struct AllAlgorithmsTest : public testing::Test {
 protected:
  s21::Graph graph;
  void SetUp() {}
  void TearDown() {}
};

TEST_F(AllAlgorithmsTest, simple_ant_algorithm) {
  graph.loadGraphFromFile("../datasets/sample9.txt");
  std::vector<int> answer = {1, 2, 3, 4};
  auto answer_it = answer.begin();
  TsmResult result = s21::GraphAlgorithms::solveTravelingSalesmanProblem(graph);
  for (auto& vertice : result.vertices) {
    EXPECT_EQ(*answer_it, vertice);
    answer_it++;
  }
  EXPECT_EQ(result.distance, 97.0);
}

TEST_F(AllAlgorithmsTest, simple_ant_algorithm_fail) {
  graph.loadGraphFromFile("../datasets/sample8.txt");
  EXPECT_ANY_THROW(s21::GraphAlgorithms::solveTravelingSalesmanProblem(graph));
}

TEST_F(AllAlgorithmsTest, spanning_tree_search) {
  graph.loadGraphFromFile("../datasets/sample9.txt");
  s21::GraphAlgorithms::getLeastSpanningTree(graph);
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
