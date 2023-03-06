#include "simple_aco.h"
#include <iostream>

SimpleACO::SimpleACO(const s21::Graph& graph)
  : cities_number_(graph.getVerticesCount()),
    ants_number_(graph.getVerticesCount()),
    cities_(graph),
    distances_(graph.graphToMatrix()),
    pheromones_(cities_number_),
    best_path_(kMaxDistance),
    ants_(createAnts_()),
    best_index_(0) {
	pheromones_.FillMatrix(kInitPheromone);
}

std::vector<AntType> SimpleACO::createAnts_() {
    int to = 0;
    std::vector<AntType> ants;
	for (int ant_num = 0; ant_num < ants_number_; ant_num++) {
		if (to == cities_number_) {
			to = 0;
        }
        AntType ant;
        ant.cur_city = to++;
		for (int from = 0; from < cities_number_; from++) {
			ant.tabu.push_back(0);
			ant.path.push_back(-1);
		}
		ant.path_index = 1;
		ant.path[0] = ant.cur_city;
		ant.next_city = -1;
		ant.tour_length = 0;
        ants.push_back(ant);
		ants[ant_num].tabu[ants[ant_num].cur_city] = 1;
	}
    return ants;
}

//reinitialize all ants and redistribute them
void SimpleACO::restartAnts_() {
	for (int ant = 0; ant < ants_number_; ant++) {
		if (ants_[ant].tour_length < best_path_) {
			best_path_ = ants_[ant].tour_length;
			best_index_ = ant;
		}
	}
	ants_ = createAnts_();
}

double SimpleACO::antProduct_(int from, int to) {
	return pow(pheromones_(from, to), kAlpha) * pow(distances_(from, to), kBetha);
}

int SimpleACO::selectNextCity_(int ant) {
	double denom = 0.0;
	int from = ants_[ant].cur_city;
    int to = 0;
	for (; to < cities_number_; to++) {
		if (ants_[ant].tabu[to] == 0) {
			denom += antProduct_(from, to);
		}
	}
	assert(denom != 0.0);
	while (1) {
		double p;
		to++;
		if (to >= cities_number_) {
			to = 0;
        }
		if (ants_[ant].tabu[to] == 0) {
			p = antProduct_(from, to) / denom;
			double x = ((double)rand()/RAND_MAX);  // change random 
			if (x < p) {
				break;
			}
		}
    }
	return to;
}

int SimpleACO::simulateAnts_() {
	int moving = 0;
	for (int ant = 0; ant < ants_number_; ant++) {
		// проверяем, может ли муравей пойти еще куда-то
		if (ants_[ant].path_index < cities_number_) {
			// выбираем город
			int next_city = selectNextCity_(ant);
			// printf("ant: %d, cur city: %d, next city: %d \n", ant, ants_[ant].cur_city, next_city);
			ants_[ant].next_city = next_city;
			// отмечаем следующий город как пройденный
			ants_[ant].tabu[next_city] = 1;
			// добавляем в путь муравья следующий город
			ants_[ant].path[ants_[ant].path_index++] = ants_[ant].next_city;
			// прибавляем к длине пути длину из текущего города в следующий
			ants_[ant].tour_length += distances_(ants_[ant].cur_city, next_city);
			// если муравей дошел до конца пути и ему нужно вернуться обратно
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
		for (int to=0; to < cities_number_; to++) {
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
					pheromones_(from, to) = kInitPheromone;
				}
			}
		}
	}
}

void SimpleACO::addPheromones_() {
    for (int ant = 0; ant < cities_number_; ant++) {
		for (int i = 0; i < cities_number_; i++) {	
            int from, to;
			if (i < cities_number_-1 ) {
				from = ants_[ant].path[i];
				to = ants_[ant].path[i + 1];
			} else {
				from = ants_[ant].path[i];
				to = ants_[ant].path[0];
			}	
			pheromones_(from, to) += (kConstQValue / ants_[ant].tour_length);
			pheromones_(to, from) = pheromones_(from, to);
		}
	}
}

TsmResult SimpleACO::findBestPath() {
	int curr_time = 0;
	
	while (curr_time++ < kMaxTime) {
		if (simulateAnts_() == 0) {
			updateTrails_();
			if (curr_time != kMaxTime) {
				restartAnts_();
            }
			std::cout << "\n Time is " << curr_time << "(" << best_path_ << ")";
		}
	}
	
	std::cout << "\nSACO: Best tour = " << best_path_ << std::endl;
	return TsmResult{ants_[0].path, best_path_};
}
