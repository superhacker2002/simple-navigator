#ifndef INTERFACE_
#define INTERFACE_

#include "../main_class/graph.h"
#include <string_view>
#include <signal.h>
#include <map>
#include <functional>

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
    using function_type = std::function<void(Interface&)>;
    // using function_type = std::function<void()>;

    Interface(const Interface& other) = delete;
    Interface(Interface&& other) = delete;
    Interface& operator=(const Interface& other) = delete;
    Interface& operator=(Interface&& other) = delete;

    public:
        static Interface*  getIfaceInstance();
        ~Interface() {}
        void start();



    private:
        static void sighandler(int sig);
        Interface();
        void exit();
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
        std::map<int, function_type> m_functions_ = {
            {static_cast<int>(EXIT),                            &s21::Interface::exit},
            {static_cast<int>(LOAD_GRAPH_FROM_FILE),            &s21::Interface::loadGraphFromFile},
            {static_cast<int>(EXPORT_GRAPH_TO_DOT),             &s21::Interface::exportGraphToDot},
            {static_cast<int>(BREADTH_SEARCH),                  &s21::Interface::breadthSearch},
            {static_cast<int>(DEPTH_SEARCH),                    &s21::Interface::depthSearch},
            {static_cast<int>(SHORTEST_PATH_BETWEEN_TWO),       &s21::Interface::shortestPathBetweenTwo},
            {static_cast<int>(SHORTEST_PATH_BETWEEN_ALL_PAIRS), &s21::Interface::shortestPathBetweenAllPairs},
            {static_cast<int>(MINIMAL_SPANNING_TREE_SEARCH),    &s21::Interface::minimalSpanningTreeSearch},
            {static_cast<int>(SALESMAN_PROBLEM_SOLVE),          &s21::Interface::salesmanProblemSolve},
            {static_cast<int>(OUTPUT_GRAPH),                    &s21::Interface::outputGraph}
        };

            
            


};  // class Interface
}  // namespace s21


#endif  // INTERFACE_