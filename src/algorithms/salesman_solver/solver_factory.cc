#include "solver_factory.h"

#include "ant_algorithm/simple_aco.h"
#include "branch_and_bound_algorithm/branch_and_bound.h"

namespace SalesmanSolverFactory {
    std::unique_ptr<ISalesmanSolver> getSalesmanSolver(SolverAlgorithm type, const s21::Graph& graph) {
        switch (type) {
            case SolverAlgorithm::ANT_COLONY_OPTIMIZATION: {
                return std::make_unique<SimpleACO>(graph);
            }
            case SolverAlgorithm::BRANCH_AND_BOUND: {
                return std::make_unique<BranchAndBound>(graph);
            }
        }
    }
}