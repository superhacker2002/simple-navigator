#include "simple_aco.h"

SimpleACO::SimpleACO(const s21::Graph& graph)
    : cities_number_(graph.getVerticesCount()),
      ants_number_(graph.getVerticesCount()),
      init_pheromone_(1.0 / cities_number_),
      distances_(graph.graphToMatrix()),
      pheromones_(cities_number_),
      best_path_length_(kMaxDistance),
      ants_(createAnts_()),
      random_generator_(rand_dev_()) {
  pheromones_.FillMatrix(init_pheromone_);
}

std::vector<AntType> SimpleACO::createAnts_() {
  std::vector<AntType> ants;
  int to = 0;
  for (int ant_num = 0; ant_num < ants_number_; ant_num++) {
    if (to == cities_number_) {
      to = 0;
    }
    AntType ant;
    ant.cur_city = to++;
    for (int from = 0; from < cities_number_; from++) {
      ant.tabu.push_back(kUnvisited);
      ant.path.push_back(kUndefined);
    }
    ant.path_index = 1;
    ant.path[0] = ant.cur_city;
    ant.next_city = kUndefined;
    ant.tour_length = 0;
    ants.push_back(ant);
    ants[ant_num].tabu[ants[ant_num].cur_city] = kVisited;
  }
  return ants;
}

void SimpleACO::restartAnts_() {
  for (const AntType& ant : ants_) {
    if (ant.tour_length < best_path_length_) {
      best_path_length_ = ant.tour_length;
      best_path_ = ant.path;
      best_path_.push_back(ant.path[0]);
    }
  }
  ants_ = createAnts_();
}

double SimpleACO::antProduct_(int from, int to) {
  return pow(pheromones_(from, to), kAlpha) *
         pow(1.0 / distances_(from, to), kBetha);
}

int SimpleACO::selectNextCity_(int ant) {
  double max_probability = 0.0;
  int from = ants_[ant].cur_city;
  int to = 0;
  for (; to < cities_number_; to++) {
    if (ants_[ant].tabu[to] == kUnvisited) {
      max_probability += antProduct_(from, to);
    }
  }
  if (max_probability == 0.0 || max_probability == kMaxDistance) {
    throw std::invalid_argument(
        "Impossible to solve salesman problem for this graph.");
  }
  std::uniform_real_distribution<double> dis(0.0, max_probability);
  while (true) {
    to++;
    if (to >= cities_number_) {
      to = 0;
    }
    if (ants_[ant].tabu[to] == kUnvisited) {
      double desire = antProduct_(from, to) / max_probability;
      double choice = dis(random_generator_);
      if (choice < desire) {
        break;
      }
    }
  }
  return to;
}

int SimpleACO::simulateAnts_() {
  int moving = 0;
  for (AntType& ant : ants_) {
    if (ant.path_index < cities_number_) {
      int next_city = selectNextCity_(&ant - &ants_[0]);
      ant.next_city = next_city;
      ant.tabu[next_city] = kVisited;
      ant.path[ant.path_index++] = ant.next_city;
      ant.tour_length += distances_(ant.cur_city, next_city);
      if (ant.path_index == cities_number_) {
        ant.tour_length +=
            distances_(ant.path[cities_number_ - 1], ant.path[0]);
      }
      ant.cur_city = next_city;
      moving++;
    }
  }
  return moving;
}

void SimpleACO::updateTrails_() {
  evaporatePheromones_();
  addPheromones_();

  for (int from = 0; from < cities_number_; from++) {
    for (int to = 0; to < cities_number_; to++) {
      pheromones_(from, to) *= kEvaporationRate;
    }
  }
}

void SimpleACO::evaporatePheromones_() {
  for (int from = 0; from < cities_number_; from++) {
    for (int to = 0; to < cities_number_; to++) {
      if (from != to) {
        pheromones_(from, to) *= 1.0 - kEvaporationRate;
        if (pheromones_(from, to) < 0.0) {
          pheromones_(from, to) = init_pheromone_;
        }
      }
    }
  }
}

void SimpleACO::addPheromones_() {
  for (const AntType& ant : ants_) {
    for (int city = 0; city < cities_number_; city++) {
      int from, to;
      if (city < cities_number_ - 1) {
        from = ant.path[city];
        to = ant.path[city + 1];
      } else {
        from = ant.path[city];
        to = ant.path[0];
      }
      pheromones_(from, to) += (kConstQValue / ant.tour_length);
      pheromones_(to, from) = pheromones_(from, to);
    }
  }
}

s21::TsmResult SimpleACO::findBestPath() {
  int curr_time = 0;
  int max_time = cities_number_ * cities_number_;
  while (curr_time++ < max_time) {
    if (simulateAnts_() == 0) {
      updateTrails_();
      if (curr_time != max_time) {
        restartAnts_();
      }
    }
  }
  for (int city = 0; city < cities_number_ + 1; city++) {
    best_path_[city] += 1;
  }
  return s21::TsmResult{best_path_, best_path_length_};
}
