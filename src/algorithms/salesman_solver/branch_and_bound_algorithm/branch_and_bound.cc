#include "branch_and_bound.h"

BranchAndBound::BranchAndBound(const s21::Graph& graph)
    : graph_(graph),
    final_path_(graph.getVerticesCount() + 1)
{}

BranchAndBound::~BranchAndBound() {}

int BranchAndBound::firstMin_(int from) {
    double min = kMaxDistance;
    for (int to = 0; to < graph_.getVerticesCount(); to++)
        if (graph_.getWeight(from, to) < min && from != to)
            min = graph_.getWeight(from, to);
    return min;
}

int BranchAndBound::secondMin_(int from) {
    double first = kMaxDistance;
    double second = kMaxDistance;
    for (int to = 0; to < graph_.getVerticesCount(); to++) {
        if (from != to) {
            if (graph_.getWeight(from, to) <= first) {
                second = first;
                first = graph_.getWeight(from, to);
            } else if (graph_.getWeight(from, to) <= second &&
                       graph_.getWeight(from, to) != first)
                second = graph_.getWeight(from, to);
        }
    }
    return second;
}

void BranchAndBound::TSPRec_(double curr_bound, double curr_weight, int level, std::vector<int>& curr_path) {
    if (level == graph_.getVerticesCount()) {
        if (graph_.getWeight(curr_path[level - 1], curr_path[0]) != 0) {
            double curr_res = curr_weight +
                              graph_.getWeight(curr_path[level - 1], curr_path[0]);
            if (curr_res < final_res_) {
                for (int v = 0; v < graph_.getVerticesCount(); v++) {
                    final_path_[v] = curr_path[v];
                }
                final_path_[graph_.getVerticesCount()] = curr_path[0];
                final_res_ = curr_res;
            }
        }
        return;
    }

    for (int v = 0; v < graph_.getVerticesCount(); v++) {
        if (graph_.getWeight(curr_path[level - 1], v) != 0 && !visited_[v]) {
            int temp = curr_bound;
            curr_weight += graph_.getWeight(curr_path[level - 1], v);
            if (level == 1) {
                curr_bound -= ((firstMin_(curr_path[level - 1]) +
                                firstMin_(v)) / 2);
            } else {
                curr_bound -= ((secondMin_(curr_path[level - 1]) +
                                firstMin_(v)) / 2);
            }
            if (curr_bound + curr_weight < final_res_) {
                curr_path[level] = v;
                visited_[v] = true;
                TSPRec_(curr_bound, curr_weight, level + 1, curr_path);
            }
            curr_weight -= graph_.getWeight(curr_path[level - 1], v);
            curr_bound = temp;
            for (int v = 0; v < graph_.getVerticesCount(); ++v) {
                visited_[v] = false;
            }
            for (int v = 0; v <= level - 1; v++)
                visited_[curr_path[v]] = true;
        }
    }
}

s21::TsmResult BranchAndBound::findBestPath() {
    final_res_ = kMaxDistance;
    int start = 0;
    for (int v = 0; v < graph_.getVerticesCount(); ++v) {
        visited_.push_back(0);
    }
    std::vector<int> curr_path;
    for (int v = 0; v < graph_.getVerticesCount() + 1; ++v){
        curr_path.push_back(-1);
    }

    double curr_bound = 0;
    for (int v = 0; v < graph_.getVerticesCount(); v++) {
        curr_bound += (firstMin_(v) + secondMin_(v));
    }

    curr_bound /= 2;
    visited_[start] = true;
    curr_path[0] = start;

    TSPRec_(curr_bound, 0, 1, curr_path);
    for (int v = 0; v < graph_.getVerticesCount() + 1; ++v) {
        final_path_[v] += 1;
    }

    return s21::TsmResult{final_path_, final_res_};
}