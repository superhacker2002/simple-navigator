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

int s21::GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {
    std::map<int, bool> visited_vertices;
    s21::Queue<int> not_visited_vertices = {vertex1};

    vertex1 -= 1;
    int vertices_number = graph.getVerticesNumber();

    std::vector<int> tags(vertices_number, std::numeric_limits<int>::max());
    tags[vertex1] = 0;

    while ((int)visited_vertices.size() != vertices_number) {
        for (auto heir : getHeirsIndexes_(graph, vertex1)) {
            if (!visited_vertices.count(vertex1)) {
                not_visited_vertices.push(heir);  
                int weight = *(graph.row_begin(vertex1) + heir);
                tags[heir] = std::min(tags[heir], tags[vertex1] + weight);
            }
        }
        not_visited_vertices.pop();
        visited_vertices[vertex1] = true;
        vertex1 = not_visited_vertices.peek();

    }
    return tags[vertex2 - 1];
}

template <class Container>
std::vector<int> s21::GraphAlgorithms::searchAlgorithm_(Graph& graph, int start_vertex, Container not_visited_vertices) {
    start_vertex -= 1;
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
    for (auto it = graph.row_begin(start_index); it != graph.row_end(start_index); ++it) {
        if (*it != 0) {
            heirs_indexes.push_back(it.get_curr_col());
        }
    }
    return heirs_indexes;
}
