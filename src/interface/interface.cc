#include "interface.h"

#include <chrono>

void s21::Interface::exitFromInterface() { exit(EXIT_SUCCESS); }

s21::Interface::Interface() { signal(SIGINT, s21::Interface::sighandler); }

s21::Interface &s21::Interface::getIfaceInstance() {
  static s21::Interface instance;
  return instance;
}

void s21::Interface::showIfaceOptionsMsg() { std::cout << IFACE_OPTIONS_MSG; }

void s21::Interface::sighandler(int /*sig*/) { exit(EXIT_SUCCESS); }

void s21::Interface::start() {
  std::cout << START_MSG;
  while (true) {
    showIfaceOptionsMsg();
    std::string function_str;
    std::cin >> function_str;
    int function_num = NA;
    int is_number = checkInput(function_str, function_num);
    if (is_number != NA && function_num >= GraphFunctions::EXIT &&
        function_num < static_cast<int>(m_functions_.size())) {
      auto function = m_functions_[function_num];
      if (function_num == LOAD_GRAPH_FROM_FILE || function_num == EXIT ||
          !m_graph_.isEmpty()) {
        function(*this);
      } else {
        std::cout << "\u001b[31mError : graph is empty! Chose option 1 to load "
                     "graph.\e[0m\n";
      }
    }
  }
}

void s21::Interface::outputGraph() {
  std::cout << MENU_MSGS[OUTPUT_GRAPH];
  m_graph_.graphToMatrix().OutputMatrix();
}

void s21::Interface::loadGraphFromFile() {
  std::string file_path;
  std::cout << MENU_MSGS[LOAD_GRAPH_FROM_FILE] << LEAVE_MSG;
  std::cout << "\u001b[32mType in relative path to the file.\e[0m\n";
  std::cin >> file_path;
  if (!checkBackInput(file_path)) {
    try {
      m_graph_.loadGraphFromFile(file_path);
      std::cout << "\u001b[32mGraph is successfully loaded.\n";
    } catch (const std::exception &err) {
      std::cout << "\u001b[31m" << err.what() << "\e[0m\n";
    }
  }
}

void s21::Interface::exportGraphToDot() {
  std::string file_path;
  std::cout << MENU_MSGS[EXPORT_GRAPH_TO_DOT] << LEAVE_MSG;
  std::cout << "\u001b[32Type in file name.\e[0m\n";
  std::cin >> file_path;
  if (!checkBackInput(file_path)) {
    try {
      m_graph_.exportGraphToDot(file_path);
      std::cout << "\u001b[32mGraph is successfully exported to .dot file. ";
    } catch (const std::exception &err) {
      std::cout << "\u001b[31m" << err.what() << "\e[0m\n";
    }
  }
}

void s21::Interface::breadthSearch() {
  std::cout << MENU_MSGS[BREADTH_SEARCH] << LEAVE_MSG;
  while (1) {
    std::cout << "\u001b[32mType in index of start vertex.\e[0m\n";
    std::string start_vertex_str;
    std::cin >> start_vertex_str;
    if (checkBackInput(start_vertex_str)) {
      break;
    }
    int start_vertex = NA;
    int is_number = checkInput(start_vertex_str, start_vertex);
    if (is_number != NA && checkVertex(start_vertex)) {
      auto res =
          s21::GraphAlgorithms::breadthFirstSearch(m_graph_, start_vertex);
      std::cout << "\n\u001b[35mResult of the breadth search:\e[0m\n";
      for (auto it : res) {
        std::cout << it << " ";
      }
      std::cout << '\n';
      break;
    }
  }
}

void s21::Interface::depthSearch() {
  std::cout << MENU_MSGS[DEPTH_SEARCH] << LEAVE_MSG;
  while (1) {
    std::cout << "\u001b[32mType in index of start vertex.\e[0m\n";
    std::string start_vertex_str;
    std::cin >> start_vertex_str;
    if (checkBackInput(start_vertex_str)) {
      break;
    }
    int start_vertex = NA;
    int is_number = checkInput(start_vertex_str, start_vertex);
    if (is_number != NA && checkVertex(start_vertex)) {
      auto res = s21::GraphAlgorithms::depthFirstSearch(m_graph_, start_vertex);
      std::cout << "\n\u001b[35mResult of the depth search:\e[0m\n";
      for (auto it : res) {
        std::cout << it << " ";
      }
      std::cout << '\n';
      break;
    }
  }
}

void s21::Interface::shortestPathBetweenTwo() {
  std::cout << MENU_MSGS[DEPTH_SEARCH] << LEAVE_MSG;
  bool finded_res = false;
  while (!finded_res) {
    std::cout << "\u001b[32mType in index of start vertex.\e[0m\n";
    std::string first_vertex_str;
    std::cin >> first_vertex_str;
    if (checkBackInput(first_vertex_str)) {
      break;
    }
    int first_vertex = NA;
    int is_number = checkInput(first_vertex_str, first_vertex);
    if (is_number != NA && checkVertex(first_vertex)) {
      while (!finded_res) {
        std::cout << "\u001b[32mType in index of second vertex.\e[0m\n";
        std::string second_vertex_str;
        std::cin >> second_vertex_str;
        if (checkBackInput(first_vertex_str)) {
          break;
        }
        int second_vertex = NA;
        int is_number = checkInput(second_vertex_str, second_vertex);
        if (is_number != NA && checkVertex(second_vertex)) {
          checkPath(first_vertex, second_vertex);
          finded_res = true;
        }
      }
    }
  }
}

void s21::Interface::shortestPathBetweenAllPairs() {
  std::cout << MENU_MSGS[SHORTEST_PATH_BETWEEN_ALL_PAIRS];
  auto res = s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(m_graph_);
  std::cout
      << "\u001b[35mMatrix of the shortest paths between all vertices:\e[0m\n";
  res.OutputMatrix();
}

void s21::Interface::minimalSpanningTreeSearch() {
  std::cout << MENU_MSGS[MINIMAL_SPANNING_TREE_SEARCH];
  auto res = s21::GraphAlgorithms::getLeastSpanningTree(m_graph_);
  std::cout << "\u001b[35mAdjacency matrix of the minimal spanning tree for "
               "this graph:\e[0m\n";
  res.OutputMatrix();
}

void s21::Interface::salesmanProblemSolve() {
  std::cout << MENU_MSGS[SALESMAN_PROBLEM_SOLVE];
  try {
    auto res = s21::GraphAlgorithms::solveTravelingSalesmanProblem(m_graph_);
    std::cout << "\u001b[35mThe most profitable route passing "
                 "through all the vertices of the graph:\e[0m\n";
    for (auto it : res.vertices) {
      std::cout << it << " ";
    }
    std::cout << "\n\u001b[35mLength of this route is:\e[0m\n"
              << res.distance << "\n";
  } catch (const std::exception &err) {
    std::cout << "\u001b[31m" << err.what() << "\e[0m\n";
  }
}

void s21::Interface::salesmanAlgorithmsComparison() {
  std::cout << MENU_MSGS[SALESMAN_ALGROTHMS_DIFF] << LEAVE_MSG;
  try {
    s21::GraphAlgorithms::solveTravelingSalesmanProblem(m_graph_);
  } catch (const std::exception &err) {
    std::cout << "\u001b[31m" << err.what() << "\e[0m\n";
    return;
  }
  while (1) {
    std::cout
        << "\u001b[32mType in number of repetitions of the solution.\e[0m\n";
    std::string iterations_str;
    std::cin >> iterations_str;
    if (checkBackInput(iterations_str)) {
      break;
    }
    int iterations_num = NA;
    int is_number = checkInput(iterations_str, iterations_num);
    if (is_number != NA) {
      std::cout << "\u001b[35mTime of execution for ant colony optimization "
                   "algorithm:\e[0m\n";
      measureSalesmanSolverSpeed(
          iterations_num, &s21::GraphAlgorithms::solveTravelingSalesmanProblem);
      std::cout << "\u001b[35mTime of execution for branch and bound "
                   "algorithm:\e[0m\n";
      measureSalesmanSolverSpeed(
          iterations_num,
          &s21::GraphAlgorithms::solveTravelingSalesmanProblemBB);
      std::cout
          << "\u001b[35mTime of execution for brute force algorithm:\e[0m\n";
      measureSalesmanSolverSpeed(
          iterations_num,
          &s21::GraphAlgorithms::solveTravelingSalesmanProblemBF);
      break;
    }
  }
}

void s21::Interface::measureSalesmanSolverSpeed(
  int iterations_number,
  std::function<s21::TsmResult(const s21::Graph &graph)> salesman_solver) {
  auto begin = std::chrono::steady_clock::now();
  for (int i = 0; i < iterations_number; i++) {
    salesman_solver(m_graph_);
  }
  auto end = std::chrono::steady_clock::now();

  auto elapsed_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
  std::cout << elapsed_ms.count() << " ms\n";
}

bool s21::Interface::checkVertex(int start_vertex) {
  int vertices_num = m_graph_.getVerticesCount();
  bool is_correct = true;
  if (start_vertex < 0) {
    std::cout << WRONG_SIZE[0];
    is_correct = false;
  } else if (start_vertex > vertices_num) {
    std::cout << WRONG_SIZE[1];
    is_correct = false;
  }
  return is_correct;
}

void s21::Interface::checkPath(int first_vertex, int second_vertex) {
  try {
    double res = s21::GraphAlgorithms::getShortestPathBetweenVertices(
        m_graph_, first_vertex, second_vertex);
    std::cout << "\n\u001b[35mShortest path between " << first_vertex << " and "
              << second_vertex << " vertices: \e[0m\n";
    std::cout << res << "\n";
  } catch (const std::exception &err) {
    std::cout << "\u001b[31m" << err.what() << "\e[0m\n";
  }
}

int s21::Interface::checkInput(std::string input, int &result) {
  try {
    result = std::stoi(input);
    return 1;
  } catch (...) {
    std::cout << "\n\u001b[31mError : Not numeric input.\e[0m\n\n";
    return -1;
  }
}

bool s21::Interface::checkBackInput(std::string input) {
  return input.size() == 1 && input[0] == 'b';
}
