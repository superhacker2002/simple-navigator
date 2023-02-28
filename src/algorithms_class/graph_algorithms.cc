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

std::vector<int> s21::GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {
    std::map<int, bool> visited_vertices;
    std::vector<int> D(graph.m_data_.matrix.GetCols(), std::numeric_limits<int>::infinity());
    D[vertex1] = 0;
    int w = vertex1;
    // пока не посетили все точки
    while (visited_vertices.size() != graph.m_data_.matrix.GetCols()) {
        // ищем доступные вершины из текущей точки w
        auto heirs_indexes = getHeirsIndexes(graph, w);
        std::vector<int> not_visited_vertices;
        // из всех доступных вершин из текущей точки
        for (auto heir : heirs_indexes) {
            // если вершину еще не посещали
            if (visited_vertices.find(w) == visited_vertices.end()) {
                // обновляем вес каждой непосещенной точки:
                // вес невыделенной вершины есть минимальное число из старого веса данной вершины,
                // суммы веса текущей вершины и веса ребра, соединяющего текущую вершину с невыделенной
                not_visited_vertices.push_back(heir);
                D[heir] = std::min(D[heir], D[w] + graph.m_data_.matrix.at(w, heir));
            }
            w = *(std::min_element(not_visited_vertices.begin(), not_visited_vertices.end()));
        }
    }
}

std::vector<int> s21::GraphAlgorithms::getHeirsIndexes(const Graph& graph, int start_index) {
    std::vector<int> heirs_indexes;

    for (int j = 0; j < graph.m_data_.matrix.GetCols(); ++j)
        if (graph.m_data_.matrix.at(start_index, j) != 0)
            heirs_indexes.push_back(j);
    
    return heirs_indexes;
}