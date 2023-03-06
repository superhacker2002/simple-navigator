#include "simple_aco.h"

int main() {
    s21::Graph graph;
    graph.loadGraphFromFile("datasets/sample8.txt");
    SimpleACO path(graph);
    auto result = path.findBestPath();
}