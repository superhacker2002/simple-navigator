#include "interface.h"

static s21::Interface* instance = nullptr;
static bool m_shutdown_ = false;

void s21::Interface::exit() {
    m_shutdown_ = true;
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
    instance->exit();
}

void s21::Interface::start() {
    showIfaceOptionsMsg();
    int function_num;
    while (true) {
        if (m_shutdown_) {
            break;
        }
        std::cin >> function_num;
        auto function = m_functions_.find(static_cast<GraphFunctions>(function_num));
        if (function != m_functions_.end()) {
            (*function).second(*instance);
        } else {
            std::cout << "Wrong input!\n";
            showIfaceOptionsMsg();
        }
    }
}

void s21::Interface::outputGraph() {
    instance->m_graph_.graphToMatrix().OutputMatrix();
}

void s21::Interface::loadGraphFromFile() {
    std::string file_path;
    std::cout << "Type in file path";
    std::cin >> file_path;
    instance->m_graph_.loadGraphFromFile(file_path);
}

void s21::Interface::exportGraphToDot() {

}

void s21::Interface::breadthSearch() {

}

void s21::Interface::depthSearch() {

}

void s21::Interface::shortestPathBetweenTwo() {

}

void s21::Interface::shortestPathBetweenAllPairs() {

}

void s21::Interface::minimalSpanningTreeSearch() {

}

void s21::Interface::salesmanProblemSolve() {

}