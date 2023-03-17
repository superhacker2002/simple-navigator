#include "branch_and_bound.h"

BranchAndBound::BranchAndBound(const s21::Graph &graph)
    : source_matrix_(graph.graphToMatrix()), best_length_(kMaxDistance) {
  for (int i = 0; i < source_matrix_.GetRows(); i++) {
    for (int j = 0; j < source_matrix_.GetCols(); ++j) {
      if (j == i) {
        source_matrix_(i, j) = kMaxDistance;
      } else if (source_matrix_(i, j) == 0) {
        throw std::invalid_argument(
            "Impossible to solve salesman problem for this graph.");
      }
    }
  }
}

BranchAndBound::~BranchAndBound() {}

s21::TsmResult BranchAndBound::findBestPath() {
  PathsList current_path;
  pathSearching_(source_matrix_, current_path, 0);
  VerticesList final_solution;
  final_solution.push_back(0);
  while (!best_path_.empty()) {
    for (auto path = best_path_.begin(); path != best_path_.end();) {
      if (path->first == final_solution.back()) {
        final_solution.push_back(path->second);
        path = best_path_.erase(path);
      } else {
        ++path;
      }
    }
  }
  for (auto &vertice : final_solution) {
    vertice++;
  }
  std::reverse(std::begin(final_solution), std::end(final_solution));
  return s21::TsmResult{final_solution, best_length_};
}

void BranchAndBound::pathSearching_(const s21::GraphData::MatrixType &matrix,
                                    PathsList &curr_path,
                                    double curr_lower_bound) {
  if (matrix.GetRows() == 2) {
    int i = matrix(0, 0) >= kMaxDistance ? 1 : 0;
    PathsList result(curr_path);
    result.emplace_back(matrix.actualRow(0), matrix.actualCol(i));
    result.emplace_back(matrix.actualRow(1), matrix.actualCol(1 - i));
    evaluateSolution_(result);
    return;
  }

  s21::GraphData::MatrixType new_matrix = matrix;
  curr_lower_bound += matrixReduction_(new_matrix);
  if (curr_lower_bound > best_length_) {
    return;
  }

  Edge zero_edge = findBestZeroPath_(new_matrix);

  s21::GraphData::MatrixType curr_matrix = new_matrix;
  curr_matrix.RemoveRowColumn(zero_edge.first, zero_edge.second);

  PathsList new_path(curr_path);
  new_path.emplace_back(new_matrix.actualRow(zero_edge.first),
                        new_matrix.actualCol(zero_edge.second));
  addInfinity_(curr_matrix);
  pathSearching_(curr_matrix, new_path,
                 curr_lower_bound); // searching subset containing zero_edge

  curr_matrix = new_matrix;
  curr_matrix(zero_edge.first, zero_edge.second) = kMaxDistance;
  pathSearching_(curr_matrix, curr_path,
                 curr_lower_bound); // searching subset not containing zero_edge
}

void BranchAndBound::addInfinity_(s21::GraphData::MatrixType &matrix) {
  std::vector<bool> rows_infinity_elements(matrix.GetRows(), false);
  std::vector<bool> cols_inifity_elements(matrix.GetRows(), false);
  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetRows(); j++) {
      if (matrix(i, j) == kMaxDistance) {
        rows_infinity_elements[i] = true;
        cols_inifity_elements[j] = true;
      }
    }
  }
  int no_inf;
  for (size_t i = 0; i < rows_infinity_elements.size(); i++) {
    if (!rows_infinity_elements[i]) {
      no_inf = i;
      break;
    }
  }
  for (size_t j = 0; j < cols_inifity_elements.size(); j++) {
    if (!cols_inifity_elements[j]) {
      matrix(no_inf, j) = kMaxDistance;
      break;
    }
  }
}

BranchAndBound::Edge
BranchAndBound::findBestZeroPath_(const s21::GraphData::MatrixType &matrix) {
  std::vector<BranchAndBound::Edge> zeroes;
  std::vector<double> coefficients;
  double max_coefficient = 0;
  for (int from = 0; from < matrix.GetRows(); ++from) {
    for (int to = 0; to < matrix.GetRows(); ++to) {
      if (matrix(from, to) == 0) {
        zeroes.push_back({from, to});
        double coefficient = getCoefficient_(matrix, from, to);
        coefficients.push_back(coefficient);
        max_coefficient = std::max(max_coefficient, coefficient);
      }
    }
  }
  auto max_it =
      std::find(coefficients.begin(), coefficients.end(), max_coefficient);
  return zeroes[std::distance(coefficients.begin(), max_it)];
}

double BranchAndBound::getCoefficient_(const s21::GraphData::MatrixType &matrix,
                                       int from, int to) {
  double rmin, cmin;
  rmin = cmin = kMaxDistance;
  for (int v = 0; v < matrix.GetRows(); ++v) {
    if (v != from)
      rmin = std::min(rmin, matrix(v, to));
    if (v != to)
      cmin = std::min(cmin, matrix(from, v));
  }

  return rmin + cmin;
}

double BranchAndBound::matrixReduction_(s21::GraphData::MatrixType &matrix) {
  double lower_bound = 0;
  int vertices_number = matrix.GetRows();
  std::vector<double> min_row(vertices_number, kMaxDistance);
  std::vector<double> min_column(vertices_number, kMaxDistance);
  for (int i = 0; i < vertices_number; ++i) {
    for (int j = 0; j < vertices_number; ++j)
      if (matrix(i, j) < min_row[i]) {
        min_row[i] = matrix(i, j);
      }
    for (int j = 0; j < vertices_number; ++j) {
      if (matrix(i, j) != 0) {
        matrix(i, j) -= min_row[i];
      }
      if ((matrix(i, j) < min_column[j]))
        min_column[j] = matrix(i, j);
    }
  }
  for (int j = 0; j < vertices_number; ++j) {
    for (int i = 0; i < vertices_number; ++i) {
      if (matrix(i, j) != 0) {
        matrix(i, j) -= min_column[j];
      }
    }
  }
  return summarizeMinCosts_(min_row, min_column, lower_bound);
}

double BranchAndBound::summarizeMinCosts_(std::vector<double> &min_row,
                                          std::vector<double> &min_col,
                                          double lower_bound) {
  for (auto i : min_row) {
    lower_bound += i;
  }
  for (auto i : min_col) {
    lower_bound += i;
  }
  return lower_bound;
}

void BranchAndBound::evaluateSolution_(const PathsList &paths) {
  double current_cost;
  if (best_length_ < (current_cost = cost(paths))) {
    return;
  }
  best_length_ = current_cost;
  best_path_ = paths;
}

double BranchAndBound::cost(const PathsList &paths) {
  double result = 0;
  for (auto &paths : paths) {
    result += source_matrix_(paths.first, paths.second);
  }
  return result;
}
