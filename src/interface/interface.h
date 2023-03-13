#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "../s21_graph.h"
#include "../s21_graph_algorithms.h"
#include <chrono>
#include <functional>
#include <map>
#include <signal.h>
#include <string_view>
#include <thread>

const static std::string_view IFACE_OPTIONS_MSG =
    "\n\u001b[32mChoose option:\e[0m\n\
    \u001b[33;1m1\e[0m - load the original graph from a file\n\
    \u001b[33;1m2\e[0m - load current graph to .dot file\n\
    \u001b[33;1m3\e[0m - traverse graph in breadth\n\
    \u001b[33;1m4\e[0m - traverse graph in depth\n\
    \u001b[33;1m5\e[0m - search for the shortest path between two vertices\n\
    \u001b[33;1m6\e[0m - search for the shortest paths between all pairs of vertices in the graph\n\
    \u001b[33;1m7\e[0m - search for the minimal spanning tree in the graph\n\
    \u001b[33;1m8\e[0m - solve the salesman problem using ant algorithm\n\
    \u001b[33;1m9\e[0m - output current graph\n\
    \u001b[33;1m0\e[0m - exit (CTRL + C)\n\n\
";

const static std::vector<std::string_view> MENU_MSGS = {
    "\n\u001b[34mExit from app.\e[0m\n\n",
    "\n\u001b[34mLoad graph from file.\e[0m\n\n",
    "\n\u001b[34mExport graph to dot.\e[0m\n\n",
    "\n\u001b[34mBreadth search.\e[0m\n\n",
    "\n\u001b[34mDepth search.\e[0m\n\n",
    "\n\u001b[34mShortest path between two vertices.\e[0m\n\n",
    "\n\u001b[34mShortest path between all pairs of vertices.\e[0m\n\n",
    "\n\u001b[34mMinimal spanning tree search.\e[0m\n\n",
    "\n\u001b[34mSalesman problem solve.\e[0m\n\n",
    "\n\u001b[34mOutput current graph.\e[0m\n\n"};

const static std::string_view LEAVE_MSG = "If you want to go back type 0.\n\n";

const static std::string_view START_MSG =
    "\n\u001b[32;1mConsole application for checking the operability of the "
    "implemented libraries s21_graph.h and s21_graph_algorithms.h\e[0m\n";

namespace s21 {
enum GraphFunctions {
  EXIT,
  LOAD_GRAPH_FROM_FILE,
  EXPORT_GRAPH_TO_DOT,
  BREADTH_SEARCH,
  DEPTH_SEARCH,
  SHORTEST_PATH_BETWEEN_TWO,
  SHORTEST_PATH_BETWEEN_ALL_PAIRS,
  MINIMAL_SPANNING_TREE_SEARCH,
  SALESMAN_PROBLEM_SOLVE,
  OUTPUT_GRAPH
};

class Interface {
  using function_type = std::function<void(Interface &)>;
  // using function_type = std::function<void()>;

public:
  static Interface &getIfaceInstance();
  ~Interface() {}
  void start();

private:
  static void sighandler(int sig);
  void exitFromInterface();
  void showIfaceOptionsMsg();
  void loadGraphFromFile();
  void exportGraphToDot();
  void breadthSearch();
  void depthSearch();
  void shortestPathBetweenTwo();
  void shortestPathBetweenAllPairs();
  void minimalSpanningTreeSearch();
  void salesmanProblemSolve();
  void outputGraph();

  Interface();
  Interface(const Interface &other);
  Interface(Interface &&other);
  Interface &operator=(const Interface &other);
  Interface &operator=(Interface &&other);

  s21::Graph m_graph_;
  std::vector<function_type> m_functions_ = {
    &s21::Interface::exitFromInterface,
    &s21::Interface::loadGraphFromFile,
    &s21::Interface::exportGraphToDot,
    &s21::Interface::breadthSearch,
    &s21::Interface::depthSearch,
    &s21::Interface::shortestPathBetweenTwo,
    &s21::Interface::shortestPathBetweenAllPairs,
    &s21::Interface::minimalSpanningTreeSearch,
    &s21::Interface::salesmanProblemSolve,
    &s21::Interface::outputGraph};
}; // class Interface
} // namespace s21

#endif // INTERFACE_H_
