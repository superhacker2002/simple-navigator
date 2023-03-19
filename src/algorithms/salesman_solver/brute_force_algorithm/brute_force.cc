#include "brute_force.h"

#include <cfloat>

BruteForce::BruteForce(const s21::Graph &graph)
    : source_matrix_(graph.graphToMatrix()),
      final_solution_(graph.getVerticesCount()),
      best_length_(kMaxDistance) {
  for (int i = 0; i < graph.getVerticesCount(); ++i) {
    final_solution_[i] = i;
  }
  evaluateSolution_(final_solution_);
}

s21::TsmResult BruteForce::findBestPath() {
  makeStep_(final_solution_, 1);
  for (auto &vertice : final_solution_) {
    vertice++;
  }
  int first_vertice = final_solution_.front();
  final_solution_.push_back(first_vertice);
  return s21::TsmResult{final_solution_, best_length_};
}

void BruteForce::makeStep_(s21::VerticesList path, int vertices_number) {
  if (vertices_number > static_cast<int>(path.size())) {
    evaluateSolution_(path);
    return;
  }

  makeStep_(path, vertices_number + 1);
  for (size_t i = vertices_number + 1; i < path.size(); i++) {
    std::swap(path[vertices_number], path[i]);
    makeStep_(path, vertices_number + 1);
    std::swap(path[vertices_number], path[i]);
  }
}

double BruteForce::cost_(const s21::VerticesList &solution) {
  double result = 0;
  for (size_t i = 1; i < solution.size(); ++i) {
    double weight = source_matrix_(solution[i - 1], solution[i]);
    if (weight == 0) {
      throw std::invalid_argument("Impossible to solve salesman problem for this graph.");
    }
    result += weight;
    
  }
  result += source_matrix_(solution.back(), solution.front());
  return result;
}

void BruteForce::evaluateSolution_(const s21::VerticesList &solution) {
  double curr_cost = cost_(solution);
  if (curr_cost >= best_length_) {
    return;
  }
  best_length_ = curr_cost;
  final_solution_ = solution;
}
