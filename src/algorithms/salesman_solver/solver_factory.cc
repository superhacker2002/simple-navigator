#include "solver_factory.h"

#include "ant_algorithm/simple_aco.h"
#include "branch_and_bound_algorithm/branch_and_bound.h"
#include "brute_force_algorithm/brute_force.h"

namespace SalesmanSolverFactory {
std::unique_ptr<ISalesmanSolver> getSalesmanSolver(SolverAlgorithm type,
                                                   const s21::Graph &graph) {
  std::unique_ptr<ISalesmanSolver> solver;
  switch (type) {
  case SolverAlgorithm::ANT_COLONY_OPTIMIZATION: {
    solver = std::make_unique<SimpleACO>(graph);
    break;
  }
  case SolverAlgorithm::BRANCH_AND_BOUND: {
    solver = std::make_unique<BranchAndBound>(graph);
    break;
  }
  case SolverAlgorithm::BRUTE_FORCE: {
    solver = std::make_unique<BruteForce>(graph);
    break;
  }
  default:
    throw std::invalid_argument("No such salesman solver.");
  }
  return solver;
}
} // namespace SalesmanSolverFactory