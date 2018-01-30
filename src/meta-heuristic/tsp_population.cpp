/**
* @file tsp_population.cpp
* @brief TSP population implementation
*/

#include "tsp_population.h"

tsp_population::tsp_population(const TSPData& data, int size) {
	solutions.reserve(size);
	
	for (int i = 0; i < size; i++)
		solutions.push_back(tsp_solution(data));
}

unsigned long tsp_population::size() const {
	return solutions.size();
}

tsp_solution& tsp_population::operator[](unsigned long index) {
        return solutions[index];
    }
