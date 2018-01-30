/**
* @file tsp_population.cpp
* @brief TSP population implementation
*/

#include "tsp_population.h"
#include <algorithm>


void tsp_population::sort_solutions() {
    std::sort(solutions.begin(), solutions.end());
}


tsp_population::tsp_population(int sol_size, int size) {
	solutions.reserve(size);
	
	for (int i = 0; i < size; i++)
		solutions.push_back(tsp_solution(sol_size));
}

unsigned long tsp_population::size() const {
	return solutions.size();
}

const tsp_solution& tsp_population::operator[](unsigned long index) const {
    return solutions[index];
}
tsp_solution& tsp_population::operator[](unsigned long index) {
    return solutions[index];
}

std::ostream& operator<<(std::ostream& os, const tsp_population& pop) {
    for (int i = 0; i < pop.size(); i++)
        os << pop[i] << std::endl;
    return os;
}

void tsp_population::evaluate(const std::vector<std::vector<double> >& costs) {
	for (int i = 0; i < solutions.size(); i++)
		solutions[i].evaluate(costs);
	
	sort_solutions();
}
