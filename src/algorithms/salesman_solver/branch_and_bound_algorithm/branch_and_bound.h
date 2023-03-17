#ifndef BRANCH_AND_BOUND_H_
#define BRANCH_AND_BOUND_H_

#include <limits>
#include <vector>

#include "../../../graph/graph.h"
#include "../../../helpers/includes.h"
#include "../solver_interface.h"

class BranchAndBound : public ISalesmanSolver {
public:
  using Edge = std::pair<int, int>;
  using VerticesList = std::vector<int>;
  using PathsList = std::vector<Edge>;
  BranchAndBound(const s21::Graph &graph);
  s21::TsmResult findBestPath() override;
  ~BranchAndBound();

private:
  const double kMaxDistance = std::numeric_limits<double>::infinity();
  s21::GraphData::MatrixType source_matrix_;
  double best_length_;
  PathsList best_path_;
  VerticesList final_solution_;
  PathsList last_step_;

  void pathSearching_(const s21::GraphData::MatrixType &matrix,
                      PathsList &curr_path, double curr_lower_bound);
  void logPath_(const PathsList &path);
  Edge findBestZeroPath_(const s21::GraphData::MatrixType &matrix);

  void compareWithOptimalSolution_(PathsList &curr_path);
  void addInfinity_();
  double matrixReduction_(s21::GraphData::MatrixType &matrix);
  double getCoefficient_(const s21::GraphData::MatrixType &matrix, int from,
                         int to);
  void evaluateSolution_(const PathsList &paths);
  double cost(const PathsList &paths);
  void addInfinity_(s21::GraphData::MatrixType &matrix);
  double summarizeMinCosts_(std::vector<double> &min_row,
                            std::vector<double> &min_col, double lower_bound);
  double getCoefficient_(int r, int c);
};

#endif // BRANCH_AND_BOUND_H_