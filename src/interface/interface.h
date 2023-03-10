#ifndef INTERFACE_
#define INTERFACE_

#include "../main_class/graph.h"
#include "../algorithms_class/graph_algorithms.h"
#include <string_view>
#include <signal.h>
#include <map>
#include <functional>
#include <thread>
#include <chrono>

const static std::string_view IFACE_OPTIONS_MSG = 
"\
    1 - loading the original graph from a file\n\
    2 - loading current graph to .dot file\n\
    3 - graph traversal in breadth with output of the result to the console\n\
    4 - graph traversal in depth with output of the result to the console\n\
    5 - searching for the shortest path between any two vertices and displaying the result to the console\n\
    6 - searching for the shortest paths between all pairs of vertices in the graph with the output of the resulting matrix to the console\n\
    7 - searching for the minimal spanning tree in the graph with the output of the resulting adjacency matrix to the console\n\
    8 - solving the salesman problem with the output of the resulting route and its length to the console\n\
    9 - output graph\n\
    0 - exit (CTRL + C)\n\
    Type in the following number to start function\n\
";

const static std::vector<std::string_view> MENU_MSGS = {
    "\nExit from app\n", "\nLoad graph from file\n", "\nExport graph to dot\n", "\nBreadth search\n",
    "\nDepth search\n", "\nShortest path between two vertices\n", "\nShortest path between all pairs of vertices\n",
    "\nMinimal spanning tree search\n", "\nSalesman problem solve\n", "\nOutput current graph\n"
};

const static std::string_view LEAVE_MSG = "If you want to go back type 0\n";
constexpr int OP_NUM = 9;

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
    using function_type = std::function<void()>;

    Interface(const Interface& other) = delete;
    Interface(Interface&& other) = delete;
    Interface& operator=(const Interface& other) = delete;
    Interface& operator=(Interface&& other) = delete;

    public:
        using instance = Interface&;
        static instance getIfaceInstance();
        ~Interface() {}
        void start();

    private:
        void sighandler(int sig);
        Interface();
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
            &s21::Interface::outputGraph
        };

};  // class Interface
}  // namespace s21


#endif  // INTERFACE_