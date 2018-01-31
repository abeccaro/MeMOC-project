/**
* @file tsp_path_solution.h
* @brief TSP solution implementation
*/

#include <algorithm>
#include <iostream>
#include "tsp_path_solution.h"

tsp_path_solution::tsp_path_solution(int size) : fit(TSPData::INFINITE) {
    sequence.reserve(size + 1);

    sequence.push_back(0);
    for (int i = 1; i < size; i++)
        sequence.push_back(i);
    std::random_shuffle(sequence.begin() + 1, sequence.end());
}

tsp_path_solution::tsp_path_solution(const tsp_path_solution& sol) : sequence(sol.sequence), fit(sol.fit) {}

std::ostream& operator<<(std::ostream& os, const tsp_path_solution& sol) {
    os << "[ ";
    for (int i = 0; i < sol.sequence.size(); i++)
        os << sol.sequence[i] << " ";
	return os << "] fit = " << sol.fit;
}

unsigned long tsp_path_solution::size() const {
    return sequence.size();
}

tsp_path_solution& tsp_path_solution::operator=(const tsp_path_solution& rhs) {
    // Handle self-assignment:
    if (this == &rhs)
    	return *this;
    
    sequence = rhs.sequence;
    fit = rhs.fit;

    return *this;
}

void tsp_path_solution::evaluate(const std::vector<std::vector<double> >& costs) {
	fit = 0;
	
	for (int i = 0; i < sequence.size() - 1; i++)
		fit += costs[sequence[i]][sequence[i+1]];
    fit += costs[sequence.back()][sequence.front()];
}

double tsp_path_solution::fitness() const {
	return fit;
}

tsp_path_solution tsp_path_solution::crossover() const {
    tsp_path_solution child(*this);
    
    // generating 2 random indices
    int i = 1 + rand() % (child.sequence.size() - 1);
    int j = 1 + rand() % (child.sequence.size() - 1);
    if (j < i)
        std::swap(i, j);
    
    std::reverse(child.sequence.begin() + i, child.sequence.begin() + j);
    return child;
}

void tsp_path_solution::mutate() {
    int i = 1 + rand() % (sequence.size() - 1); // random sequence index
    int j;
    
    do {
       j = 1 + rand() % (sequence.size() - 1);
    } while (j == i);

    iter_swap(sequence.begin() + i, sequence.begin() + j);
}
