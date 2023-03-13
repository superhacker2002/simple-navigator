#include "interface.h"

static bool m_shutdown_ = false;

void s21::Interface::exitFromInterface() {
    exit(EXIT_SUCCESS);
}

s21::Interface::Interface() {
    signal(SIGINT, s21::Interface::sighandler);
}

s21::Interface& s21::Interface::getIfaceInstance() {
    static s21::Interface instance;
    return instance;
}

void s21::Interface::showIfaceOptionsMsg() {
    std::cout << IFACE_OPTIONS_MSG;

}

void s21::Interface::sighandler(int /*sig*/) {
    // instance->exitFromInterface();
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
            if (function_num == LOAD_GRAPH_FROM_FILE || function_num == EXIT || !m_graph_.isEmpty()) {
                function(*this);
            } else {
                std::cout << "\u001b[31mError: graph is empty! Chose option 1 to load graph.\e[0m\n";
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
    std::cout << "\u001b[32mType in file name.\e[0m\n";
    std::cin >> file_path;
    if (file_path[0] != '0') {
        try {
            m_graph_.loadGraphFromFile(file_path);
            std::cout << "\u001b[32mGraph is successfully loaded. ";
        } catch (const std::exception& err) {
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
        } catch (const std::exception& err) {
            std::cout << "\u001b[31m" << err.what() << "\e[0m\n";
        }
    }
}

void s21::Interface::breadthSearch() {
    int startVertex = 1;
    std::cout << MENU_MSGS[BREADTH_SEARCH] << LEAVE_MSG;
    std::cout << "\u001b[32mType in index of start vertex.\e[0m\n";
    std::cin >> startVertex;
    if (startVertex != 0) {
        auto res = s21::GraphAlgorithms::breadthFirstSearch(m_graph_, startVertex);
        std::cout << "\nResult of the braedth search: \n";
        for (auto it : res) {
            std::cout << it << " ";
        }
        std::cout << '\n';
    }
}

void s21::Interface::depthSearch() {
    int startVertex = 1;
    std::cout << MENU_MSGS[DEPTH_SEARCH] << LEAVE_MSG;
    std::cout << "Type in index of start vertex\n";
    std::cin >> startVertex;
    if (startVertex != 0) {
        auto res = s21::GraphAlgorithms::depthFirstSearch(m_graph_, startVertex);
        std::cout << "Result : \n";
        for (auto it : res) {
            std::cout << it << " ";
        }
    }
}

void s21::Interface::shortestPathBetweenTwo() {
    int firstVertex, secondVertex = 1;
    std::cout << MENU_MSGS[SHORTEST_PATH_BETWEEN_TWO] << LEAVE_MSG;
    std::cout << "Type in index of first vertex\n";
    std::cin >> firstVertex;
    if (firstVertex == 0) {
        return;
    }
    std::cout << "\nType in index of second vertex\n";
    std::cin >> secondVertex;
    auto res =
        s21::GraphAlgorithms::getShortestPathBetweenVertices(m_graph_, firstVertex, secondVertex);
    std::cout << "Result : \n";
    std::cout << res;
}

void s21::Interface::shortestPathBetweenAllPairs() {
    std::cout << MENU_MSGS[SHORTEST_PATH_BETWEEN_ALL_PAIRS];
    auto res =
        s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(m_graph_);
    std::cout << "Result : \n";
    res.OutputMatrix();
}

void s21::Interface::minimalSpanningTreeSearch() {
    std::cout << MENU_MSGS[MINIMAL_SPANNING_TREE_SEARCH];
    auto res =
        s21::GraphAlgorithms::getLeastSpanningTree(m_graph_);
    std::cout << "Result : \n";
    res.OutputMatrix();
}

void s21::Interface::salesmanProblemSolve() {
    std::cout << MENU_MSGS[SALESMAN_PROBLEM_SOLVE];
    auto res = s21::GraphAlgorithms::solveTravelingSalesmanProblem(m_graph_);
    std::cout << "Result : \n";
    for (auto it : res.vertices) {
        std::cout << it << " ";
    }
    std::cout << "Distance of this route is " << res.distance;
}
