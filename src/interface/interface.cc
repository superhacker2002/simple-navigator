#include "interface.h"

static s21::Interface* instance = nullptr;
static bool m_shutdown_ = false;

void s21::Interface::exitFromInterface() {
    exit(EXIT_SUCCESS);
}

s21::Interface::Interface() {
    signal(SIGINT, s21::Interface::sighandler);
}

s21::Interface* s21::Interface::getIfaceInstance() {
    if (instance) {
        return instance;
    }
    return new Interface();
}

void s21::Interface::showIfaceOptionsMsg() {
    std::cout << IFACE_OPTIONS_MSG;

}

void s21::Interface::sighandler(int /*sig*/) {
    instance->exitFromInterface();
}

void s21::Interface::start() {
    int function_num;
    while (true) {
        if (m_shutdown_) {
            break;
        }
        showIfaceOptionsMsg();
        std::cin >> function_num;
        auto function = m_functions_.find(static_cast<GraphFunctions>(function_num));
        if (function != m_functions_.end()) {
            (*function).second(*instance);
        } else {
            std::cout << "Wrong input!\n";
        }
    }
}

void s21::Interface::outputGraph() {
    std::cout << MENU_MSGS[EXIT];
    m_graph_.graphToMatrix().OutputMatrix();
}

void s21::Interface::loadGraphFromFile() {
    std::string file_path;
    std::cout << MENU_MSGS[LOAD_GRAPH_FROM_FILE] << LEAVE_MSG;
    std::cout << "Type in file name\n";
    std::cin >> file_path;
    if (file_path[0] != '0') {
        m_graph_.loadGraphFromFile(file_path);
    }
}

void s21::Interface::exportGraphToDot() {
    std::string file_path;
    std::cout << MENU_MSGS[EXPORT_GRAPH_TO_DOT] << LEAVE_MSG;
    std::cout << "Type in file name\n";
    std::cin >> file_path;
    if (file_path[0] != '0') {
        m_graph_.loadGraphFromFile(file_path);
    }
}

void s21::Interface::breadthSearch() {
    int startVertex = 1;
    std::cout << MENU_MSGS[BREADTH_SEARCH] << LEAVE_MSG;
    std::cout << "Type in index of start vertex\n";
    std::cin >> startVertex;
    if (startVertex != 0) {
        auto res = s21::GraphAlgorithms::breadthFirstSearch(m_graph_, startVertex);
        std::cout << "Result : \n";
        for (auto it : res) {
            std::cout << it << " ";
        }
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