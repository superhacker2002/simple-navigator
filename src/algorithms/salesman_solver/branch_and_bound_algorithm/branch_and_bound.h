#ifndef BRANCH_AND_BOUND_H_
#define BRANCH_AND_BOUND_H_

#include <limits>
#include <vector>
#include <algorithm>

#include "../../../helpers/includes.h"
#include "../../../s21_graph.h"
#include "../solver_interface.h"

class BranchAndBound : public ISalesmanSolver {
 public:
  using Edge = std::pair<int, int>;
  using VerticesList = std::vector<int>;
  using PathsList = std::vector<Edge>;

  BranchAndBound(const s21::Graph &graph);
  s21::TsmResult findBestPath() override;

  ~BranchAndBound();
  BranchAndBound(const BranchAndBound &) = delete;
  BranchAndBound &operator=(const BranchAndBound &) = delete;

 private:
  static constexpr double kMaxDistance = s21::INF;
  s21::GraphData::MatrixType source_matrix_;
  double best_length_;
  PathsList best_path_;

  void pathSearching_(const s21::GraphData::MatrixType &matrix,
                      PathsList &curr_path, double curr_lower_bound);
  Edge findBestZeroPath_(const s21::GraphData::MatrixType &matrix);

  void compareWithOptimalSolution_(PathsList &curr_path);
  void addInfinity_();
  double matrixReduction_(s21::GraphData::MatrixType &matrix);
  double getCoefficient_(const s21::GraphData::MatrixType &matrix, int from,
                         int to);
  void evaluateSolution_(const PathsList &paths);
  double cost_(const PathsList &paths);
  void addInfinity_(s21::GraphData::MatrixType &matrix);
  double summarizeMinCosts_(std::vector<double> &min_row,
                            std::vector<double> &min_col, double lower_bound);
};

#endif  // BRANCH_AND_BOUND_H_