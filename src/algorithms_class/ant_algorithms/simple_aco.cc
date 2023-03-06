#include "simple_aco.h"
#include <iostream>
// TODO: add path from last city to the first

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
			ant.tabu.push_back(0);
			ant.path.push_back(kUndefined);
		}
		ant.path_index = 1;
		ant.path[0] = ant.cur_city;
		ant.next_city = kUndefined;
		ant.tour_length = 0;
        ants.push_back(ant);
		ants[ant_num].tabu[ants[ant_num].cur_city] = 1;
	}
    return ants;
}

void SimpleACO::restartAnts_() {
	for (int ant = 0; ant < ants_number_; ant++) {
		if (ants_[ant].tour_length < best_path_length_) {
			best_path_length_ = ants_[ant].tour_length;
			best_path_ = ants_[ant].path;
		}
	}
	ants_ = createAnts_();
}

double SimpleACO::antProduct_(int from, int to) {
	return pow(pheromones_(from, to), kAlpha) * pow(1.0 / distances_(from, to), kBetha);
}

int SimpleACO::selectNextCity_(int ant) {
	double max_probability = 0.0;
	int from = ants_[ant].cur_city;
    int to = 0;
	for (; to < cities_number_; to++) {
		if (ants_[ant].tabu[to] == 0) {
			max_probability += antProduct_(from, to);
		}
	}
	assert(max_probability != 0.0);
	std::uniform_real_distribution<double> dis(0.0, max_probability);

	while (1) {
		to++;
		if (to >= cities_number_) {
			to = 0;
        }
		if (ants_[ant].tabu[to] == 0) {
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
	for (int ant = 0; ant < ants_number_; ant++) {
		if (ants_[ant].path_index < cities_number_) {
			int next_city = selectNextCity_(ant);
			ants_[ant].next_city = next_city;
			ants_[ant].tabu[next_city] = 1;
			ants_[ant].path[ants_[ant].path_index++] = ants_[ant].next_city;
			ants_[ant].tour_length += distances_(ants_[ant].cur_city, next_city);
			if (ants_[ant].path_index == cities_number_) {
				ants_[ant].tour_length += distances_(ants_[ant].path[cities_number_ - 1], 
                                                     ants_[ant].path[0]);
			}	
			ants_[ant].cur_city = next_city;
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
				pheromones_(from, to) *=  1.0 - kEvaporationRate;
				if (pheromones_(from, to) < 0.0) {
					pheromones_(from, to) = init_pheromone_;
				}
			}
		}
	}
}

void SimpleACO::addPheromones_() {
    for (int ant = 0; ant < ants_number_; ant++) {
		for (int city = 0; city < cities_number_; city++) {	
            int from, to;
			if (city < cities_number_ - 1) {
				from = ants_[ant].path[city];
				to = ants_[ant].path[city + 1];
			} else {
				from = ants_[ant].path[city];
				to = ants_[ant].path[0];
			}	
			pheromones_(from, to) += (kConstQValue / ants_[ant].tour_length);
			pheromones_(to, from) = pheromones_(from, to);
		}
	}
}

TsmResult SimpleACO::findBestPath() {
	int curr_time = 0;
	int max_time = kMaxTours * cities_number_;
	while (curr_time++ < max_time) {
		if (simulateAnts_() == 0) {
			updateTrails_();
			if (curr_time != max_time) {
				restartAnts_();
			}
		}
	}
	for (int i = 0; i < ants_number_; i++) {
		best_path_[i] += 1;
	}
	return TsmResult{best_path_, best_path_length_};
}

void SimpleACO::logging_() {
	for (int ant = 0; ant < ants_number_; ant++) {
		printf("ant: %d, path: ", ant);
		for (int j = 0; j < cities_number_; j++) {
			printf("%d ", ants_[ant].path[j] + 1);
		}
		printf("\n");
		printf("tour length: %f\n", ants_[ant].tour_length);
	}
	printf("\n");
}
