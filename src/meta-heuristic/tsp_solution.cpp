/**
* @file tsp_solution.h
* @brief TSP solution implementation
*/

#include <algorithm>
#include <iostream>
#include "tsp_solution.h"

tsp_solution::tsp_solution(int size) : fit(TSPData::INFINITE) {
    sequence.reserve(size + 1);

    for (int i = 0; i < size; i++)
        sequence.push_back(i);
    std::random_shuffle(sequence.begin(), sequence.end());
    
    sequence.push_back(sequence.front());
}

tsp_solution::tsp_solution(const tsp_solution& sol) : fit(sol.fit) {
    sequence.reserve(sol.size());
    for (int i = 0; i < sol.sequence.size(); i++)
        sequence.push_back(sol.sequence[i]);
}

void tsp_solution::print() const {
    for (int i = 0; i < sequence.size(); i++)
        std::cout << sequence[i] << " ";
	std::cout << std::endl;
}

unsigned long tsp_solution::size() const {
    return sequence.size();
}

tsp_solution& tsp_solution::operator=(const tsp_solution& rhs) {
    // Handle self-assignment:
    if (this == &rhs)
    	return *this;
    
    for (int i = 0; i < sequence.size(); i++)
        sequence[i] = rhs.sequence[i];
    return *this;
}

void tsp_solution::evaluate(const std::vector<std::vector<double> >& costs) {
	fit = 0;
	
	for (int i = 0; i < sequence.size() - 1; i++)
		fit += costs[sequence[i]][sequence[i+1]];
}

double tsp_solution::fitness() const {
	return fit;
}
