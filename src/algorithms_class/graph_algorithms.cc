#include "graph_algorithms.h"
#include "../helpers/containers/s21_stack.h"
#include "../helpers/containers/s21_queue.h"


std::vector<int> s21::GraphAlgorithms::depthFirstSearch(Graph &graph, int start_vertex) {
    s21::Stack<int> not_visited_verticles;
    return searchAlgorithm_<s21::Stack<int>>(graph, start_vertex, not_visited_verticles);
}

std::vector<int> s21::GraphAlgorithms::breadthFirstSearch(Graph &graph, int start_vertex) {
    s21::Queue<int> not_visited_verticles;
    return searchAlgorithm_<s21::Queue<int>>(graph, start_vertex, not_visited_verticles);
}

// std::vector<int> s21::GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {
//     std::map<int, bool> visited_vertices;
//     std::vector<int> D(graph.m_data_.matrix.GetCols(), std::numeric_limits<int>::infinity());
//     D[vertex1] = 0;
//     int w = vertex1;
//     // пока не посетили все точки
//     while (visited_vertices.size() != graph.m_data_.matrix.GetCols()) {
//         // ищем доступные вершины из текущей точки w
//         auto heirs_indexes = getHeirsIndexes(graph, w);
//         std::vector<int> not_visited_vertices;
//         // из всех доступных вершин из текущей точки
//         for (auto heir : heirs_indexes) {
//             // если вершину еще не посещали
//             if (visited_vertices.find(w) == visited_vertices.end()) {
//                 // обновляем вес каждой непосещенной точки:
//                 // вес невыделенной вершины есть минимальное число из старого веса данной вершины,
//                 // суммы веса текущей вершины и веса ребра, соединяющего текущую вершину с невыделенной
//                 not_visited_vertices.push_back(heir);
//                 D[heir] = std::min(D[heir], D[w] + graph.m_data_.matrix.at(w, heir));
//             }
//             w = *(std::min_element(not_visited_vertices.begin(), not_visited_vertices.end()));
//         }
//     }
// }

template <class Container>
std::vector<int> s21::GraphAlgorithms::searchAlgorithm_(Graph& graph, int start_vertex, Container not_visited_vertices) {
    start_vertex--;
    not_visited_vertices.push(start_vertex);
    std::map<int, bool> visited_vertices{{start_vertex, true}};
    std::vector<int> vertices_sequence;

    while (!not_visited_vertices.empty()) {
        int curr_vertex = not_visited_vertices.peek();
        not_visited_vertices.pop();
        visited_vertices[curr_vertex] =  true;
        vertices_sequence.push_back(curr_vertex + 1);
        for (int& heir : getHeirsIndexes_(graph, curr_vertex)) {
            if (!visited_vertices[heir]) {
                not_visited_vertices.push(heir);
                visited_vertices[heir] = true;
            }
        }
    }
    return vertices_sequence;
}

std::vector<int> s21::GraphAlgorithms::getHeirsIndexes_(Graph& graph, int start_index) {
    std::vector<int> heirs_indexes;
    for (auto it = graph.row_begin(start_index); it != graph.row_end(start_index); ++it)
        if (*it != 0)
            heirs_indexes.push_back(it.get_curr_col());
    
    return heirs_indexes;
}

void s21::GraphAlgorithms::prepareGraphForFloydWarshallAlgo_(Graph& graph) {
    for (int i = 0; i < graph.getVerticesCount(); i++) {
        for (int j = 0; j < graph.getVerticesCount(); j++) {
            if (i == j) {
                graph.getWeigth(i, j) = 0;
            } else {
                if (graph.getWeigth(i, j) == 0) {
                    graph.getWeigth(i, j) = 1000;
                }
            }
        }
    }
}

s21::Matrix<int> s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(Graph& graph) {
    std::vector<Graph> graphs(graph.getVerticesCount() + 1, s21::Graph(graph.getVerticesCount()));
    prepareGraphForFloydWarshallAlgo_(graph);
    graphs.at(0) = graph;
    for (int k = 1; k <= graph.getVerticesCount(); ++k) {
        for (int i = 0; i < graph.getVerticesCount(); ++i) {
            for (int j = 0; j < graph.getVerticesCount(); ++j) {
                Graph& prev_graph = graphs.at(k - 1);
                graphs.at(k).getWeigth(i, j) =
                    std::min(
                        prev_graph.getWeigth(i, j),
                        prev_graph.getWeigth(i, k-1) + prev_graph.getWeigth(k-1, j));
            }
        }
    }
    return graphs.at(graph.getVerticesCount()).graphToMatrix();
}
