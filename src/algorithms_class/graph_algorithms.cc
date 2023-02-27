#include "graph_algorithms.h"

std::vector<int> s21::GraphAlgorithms::breadthFirstSearch(const Graph &graph, int startVertex) {
    startVertex--;
    s21::Queue<int> verticesQueue = {startVertex};
    std::map<int, bool> visitedVertices;
    visitedVertices[startVertex] = true;
    std::vector<int> verticesSequence;
    while (!verticesQueue.empty()) {
        int currVertex = verticesQueue.front();
        verticesQueue.pop();
        visitedVertices[currVertex] =  true;
        verticesSequence.push_back(currVertex + 1);
        for (int& heir : getHeirsIndexes(graph, currVertex)) {
            if (!visitedVertices[heir]) {
                verticesQueue.push(heir);
                visitedVertices[heir] = true;
            }
        }
    }
    return verticesSequence;
}

std::vector<int> s21::GraphAlgorithms::getHeirsIndexes(const Graph& graph, int startIndex) {
    std::vector<int> heirsIndexes;

    for (int j = 0; j < graph.m_data_.matrix.GetCols(); ++j)
        if (graph.m_data_.matrix.at(startIndex, j) != 0)
            heirsIndexes.push_back(j);
    
    return heirsIndexes;
}