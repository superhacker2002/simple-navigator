#ifndef ANT_ALGORITHM_PHEROMONE_H_
#define ANT_ALGORITHM_PHEROMONE_H_

#include "../../main_class/graph.h"
#include "path.h"

namespace Pheromone {
    void lay(s21::Graph& pheromones, const Path& path, double pheromone_per_ant);
    void evaporate(s21::Graph& pheromones, double pheromone_per_ant);
}
#endif  // ANT_ALGORITHM_PHEROMONE_H_