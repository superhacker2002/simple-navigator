#include "branch_and_bound.h"

BranchAndBound::BranchAndBound(const s21::Graph& graph)
    : graph_(graph)
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

// function that takes as arguments:
// curr_bound . lower bound of the root node
// curr_weight. stores the weight of the path so far
// level. current level while moving in the search
//         space tree
// curr_path . where the solution is being stored which
//                would later be copied to final_path
void BranchAndBound::TSPRec_(double curr_bound, double curr_weight, int level, std::vector<int>& curr_path) {
    if (level == graph_.getVerticesCount()) {
        if (graph_.getWeight(curr_path[level - 1], curr_path[0]) != 0) {
            double curr_res = curr_weight +
                              graph_.getWeight(curr_path[level - 1], curr_path[0]);
            if (curr_res < final_res_) {
                std::vector<int> final_path;
                for (int v = 0; v < graph_.getVerticesCount(); v++)
                    final_path.push_back(curr_path[v]);
                final_path.push_back(curr_path[0]);
                final_res_ = curr_res;
            }
        }
        return;
    }

    // for any other level iterate for all vertices to
    // build the search space tree recursively
    for (int v = 0; v < graph_.getVerticesCount(); v++) {
        // Consider next vertex if it is not same (diagonal
        // entry in adjacency matrix and not visited
        // already)
        if (graph_.getWeight(curr_path[level - 1], v) != 0 && !visited_[v]) {
            int temp = curr_bound;
            curr_weight += graph_.getWeight(curr_path[level - 1], v);

            // different computation of curr_bound for
            // level 2 from the other levels
            if (level == 1) {
                curr_bound -= ((firstMin_(curr_path[level - 1]) +
                                firstMin_(v)) / 2);
            } else {
                curr_bound -= ((secondMin_(curr_path[level - 1]) +
                                firstMin_(v)) / 2);
            }
            // curr_bound + curr_weight is the actual lower bound
            // for the node that we have arrived on
            // If current lower bound < final_res, we need to explore
            // the node further
            if (curr_bound + curr_weight < final_res_) {
                curr_path[level] = v;
                visited_[v] = true;

                // call TSPRec for the next level
                TSPRec_(curr_bound, curr_weight, level + 1, curr_path);
            }

            // Else we have to prune the node by resetting
            // all changes to curr_weight and curr_bound
            curr_weight -= graph_.getWeight(curr_path[level - 1], v);
            curr_bound = temp;

            // Also reset the visited array
            for (int v = 0; v < graph_.getVerticesCount(); ++v) {
                visited_[v] = false;
            }
            for (int v = 0; v <= level - 1; v++)
                visited_[curr_path[v]] = true;
        }
    }
}

// This function sets up final_path
s21::TsmResult BranchAndBound::getShortestRoute() {
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
    // Compute initial bound
    for (int v = 0; v < graph_.getVerticesCount(); v++) {
        curr_bound += (firstMin_(v) + secondMin_(v));
    }

    curr_bound /= 2;

    // We start at vertex 1 so the first vertex
    // in curr_path[] is 0
    visited_[start] = true;
    curr_path[0] = start;

    // Call to TSPRec for curr_weight equal to
    // 0 and level 1
    TSPRec_(curr_bound, 0, 1, curr_path);
    for (int v = 0; v < graph_.getVerticesCount() + 1; ++v) {
        curr_path[v] += 1;
    }

    return s21::TsmResult{curr_path, final_res_};
}