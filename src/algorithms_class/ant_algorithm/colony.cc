#include "colony.h"

Colony::Colony(Graph& graph) 
    : distances_(graph),
      pheromones_(s21::Graph(graph.getVerticesCount())),
      rand_direction_(),
      random_engine_(rand_direction_())
{}

void Colony::createAnts_() {
    int size = distances_.getVerticesCount();
    ants_.resize(size);
    for (int i = 0; i < size; ++i) {
        ants_[i] = std::make_unique<Ant>(random_engine_, size, false);
    }
}

void Colony::findBestPath() {
    double best_path_length = INFINITY;
    auto continue_available = kRunsWithoutImprovement;
    while (continue_available > 0) {
        createAnts_();
        for (auto& ant : ants_) {
            while (ant->canContinue()) {
                ant->makeChoice(pheromones_, distances_, kAlpha, kBeta);
            }
            auto current_path = ant->getPath();
            if (best_path_length > current_path->getDistance()) {
                best_path_length = current_path->getDistance();
                continue_available = kRunsWithoutImprovement;
            }
        }
    }

}

