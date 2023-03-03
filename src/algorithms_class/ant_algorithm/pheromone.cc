#include "pheromone.h"

void Pheromone::lay(s21::Graph& pheromones, const Path& path, double pheromone_per_ant) {
    int steps = path.getNumberOfSteps();
    double pheromone_to_lay = pheromone_per_ant / steps;
    for (int i = 1, n = steps; i < n; ++i) {

    }
}