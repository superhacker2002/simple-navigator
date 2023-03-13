#include "interface.h"

static bool m_shutdown_ = false;

void s21::Interface::exitFromInterface() { exit(EXIT_SUCCESS); }

s21::Interface::Interface() { signal(SIGINT, s21::Interface::sighandler); }

s21::Interface &s21::Interface::getIfaceInstance() {
  static s21::Interface instance;
  return instance;
}

void s21::Interface::showIfaceOptionsMsg() { std::cout << IFACE_OPTIONS_MSG; }

void s21::Interface::sighandler(int /*sig*/) {
  exit(EXIT_SUCCESS);
}

void s21::Interface::start() {
  size_t function_num;
  std::cout << START_MSG;
  while (true) {
    if (m_shutdown_) {
      break;
    }
    showIfaceOptionsMsg();
    std::cin >> function_num;
    if (function_num < m_functions_.size()) {
      auto function = m_functions_[function_num];
      if (function_num == LOAD_GRAPH_FROM_FILE || function_num == EXIT ||
          !m_graph_.isEmpty()) {
        function(*this);
      } else {
        std::cout << "\u001b[31mError : graph is empty! Chose option 1 to load "
                     "graph.\e[0m\n";
      }
    } else {
      std::cout << "\u001b[31mWrong input!\e[0m\n";
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
  if (file_path[0] != '0') {
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
  if (file_path[0] != '0') {
    try {
      m_graph_.exportGraphToDot(file_path);
      std::cout << "\u001b[32mGraph is successfully exported to .dot file. ";
    } catch (const std::exception &err) {
      std::cout << "\u001b[31m" << err.what() << "\e[0m\n";
    }
  }
}

void s21::Interface::breadthSearch() {
  std::cout << MENU_MSGS[BREADTH_SEARCH];
  while (1) {
    int start_vertex;
    std::cout << "\u001b[32mType in index of start vertex.\e[0m\n";
    std::cin >> start_vertex;
    if (start_vertex == GraphFunctions::EXIT) {
      break;
    } else if (checkVertex(start_vertex)) {
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
  std::cout << MENU_MSGS[DEPTH_SEARCH];
  while (1) {
    int start_vertex;
    std::cout << "\u001b[32mType in index of start vertex.\e[0m\n";
    std::cin >> start_vertex;
    if (start_vertex == GraphFunctions::EXIT) {
      break;
    } else if (checkVertex(start_vertex)) {
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
  std::cout << MENU_MSGS[DEPTH_SEARCH];
  bool finded_res = false;
  while (!finded_res) {
    int first_vertex;
    std::cout << "\u001b[32mType in index of start vertex.\e[0m\n";
    std::cin >> first_vertex;
    if (first_vertex == GraphFunctions::EXIT) {
      break;
    } else if (checkVertex(first_vertex)) {
      while (!finded_res) {
        int second_vertex;
        std::cout << "\n\u001b[32mType in index of second vertex.\e[0m\n";
        std::cin >> second_vertex;
        if (second_vertex == GraphFunctions::EXIT) {
          break;
        } else if (checkVertex(second_vertex)) {
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
  std::cout << "Result : \n";
  res.OutputMatrix();
}

void s21::Interface::minimalSpanningTreeSearch() {
  std::cout << MENU_MSGS[MINIMAL_SPANNING_TREE_SEARCH];
  auto res = s21::GraphAlgorithms::getLeastSpanningTree(m_graph_);
  std::cout << "Result : \n";
  res.OutputMatrix();
}

void s21::Interface::salesmanProblemSolve() {
  std::cout << MENU_MSGS[SALESMAN_PROBLEM_SOLVE];
  try {
    auto res = s21::GraphAlgorithms::solveTravelingSalesmanProblem(m_graph_);
    std::cout << "\u001b[35mThe most profitable route passing " <<
                "through all the vertices of the graph:\e[0m\n";
    for (auto it : res.vertices) {
      std::cout << it << " ";
    }
    std::cout << "\n\u001b[35mLength of this route is:\e[0m\n" << res.distance << "\n";
  } catch (const std::exception& err) {
    std::cout << "\u001b[31m" << err.what() << "\e[0m\n";
  }
}

bool s21::Interface::checkVertex(int start_vertex) {
  int vertices_num = m_graph_.getVerticesCount();
  bool is_correct = true;
  if (start_vertex <= 0) {
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
        auto res = s21::GraphAlgorithms::getShortestPathBetweenVertices(
        m_graph_, first_vertex, second_vertex);
        std::cout << "\n\u001b[35mShortest path between " << first_vertex
                << " and " << second_vertex << " vertices: \e[0m\n";
        std::cout << res << "\n";
    } catch (const std::exception& err) {
        std::cout << "\u001b[31m" << err.what() << "\e[0m\n";
    }
}
