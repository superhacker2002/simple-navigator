#include "simple_aco.h"

int main() {
    s21::Graph graph;
    graph.loadGraphFromFile("../../../datasets/sample9.txt");
    SimpleACO path(graph);
    auto result = path.findBestPath();
}