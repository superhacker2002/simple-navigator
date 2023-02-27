#include "graph_algorithms.h"

std::vector<int> s21::GraphAlgorithms::breadthFirstSearch(const Graph &graph, int start_vertex) {
    start_vertex--;
    s21::Queue<int> vertices_queue = {start_vertex};
    std::map<int, bool> visited_vertices{{start_vertex, true}};
    std::vector<int> vertices_sequence;
    while (!vertices_queue.empty()) {
        int curr_vertex = vertices_queue.front();
        vertices_queue.pop();
        visited_vertices[curr_vertex] =  true;
        vertices_sequence.push_back(curr_vertex + 1);
        for (int& heir : getHeirsIndexes(graph, curr_vertex)) {
            if (!visited_vertices[heir]) {
                vertices_queue.push(heir);
                visited_vertices[heir] = true;
            }
        }
    }
    return vertices_sequence;
}

std::vector<int> s21::GraphAlgorithms::getHeirsIndexes(const Graph& graph, int start_index) {
    std::vector<int> heirs_indexes;

    for (int j = 0; j < graph.m_data_.matrix.GetCols(); ++j)
        if (graph.m_data_.matrix.at(start_index, j) != 0)
            heirs_indexes.push_back(j);
    
    return heirs_indexes;
}