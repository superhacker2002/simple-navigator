#ifndef BRUTE_FORCE_H_
#define BRUTE_FORCE_H_

#include "../../../s21_graph.h"
#include "../../../helpers/includes.h"
#include "../solver_interface.h"

#include <vector>

class BruteForce : public ISalesmanSolver {
 public:
    BruteForce(const s21::Graph& graph);
    s21::TsmResult findBestPath() override;

    BruteForce(const BruteForce&) = delete;
    BruteForce &operator=(const BruteForce&) = delete;

private:
    static constexpr double kMaxDistance = s21::INF;
    s21::GraphData::MatrixType source_matrix_;
    s21::VerticesList final_solution_;
    double best_length_;
    double cost_(const s21::VerticesList& solution);
    void makeStep_(s21::VerticesList path, int vertices_number);
    void evaluateSolution_(const s21::VerticesList& solution);
};

#endif  // BRUTE_FORCE_H_