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
    
    sequence.push_back(sequence.front());
}

tsp_path_solution::tsp_path_solution(const tsp_path_solution& sol) : fit(sol.fit) {
    sequence.reserve(sol.size());
    for (int i = 0; i < sol.sequence.size(); i++)
        sequence.push_back(sol.sequence[i]);
}

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
    
    for (int i = 0; i < sequence.size(); i++)
        sequence[i] = rhs.sequence[i];
    fit = rhs.fit;
    return *this;
}

void tsp_path_solution::evaluate(const std::vector<std::vector<double> >& costs) {
	fit = 0;
	
	for (int i = 0; i < sequence.size() - 1; i++)
		fit += costs[sequence[i]][sequence[i+1]];
}

double tsp_path_solution::fitness() const {
	return fit;
}

tsp_path_solution tsp_path_solution::crossover() const {
    tsp_path_solution child = *this;
    
    // starting index and length of reverse
    int k = 1 + rand() % (child.sequence.size() - 2);
    int l = 1 + rand() % (child.sequence.size() - k - 1);
    
    std::reverse(child.sequence.begin() + k, child.sequence.begin() + k + l);
    
    // solution may be unfeasible, forcing them to be feasible
    if (child.sequence.front() != child.sequence.back()) {
        if (k == 0) // first node changed but not last
            child.sequence.back() = child.sequence.front();
        else // last node changed but not first
            child.sequence.front() = child.sequence.back();
    }
    
    return child;
}

void tsp_path_solution::mutate() {
    int i = 1 + rand() % (sequence.size() - 2); // random sequence index
    int j;
    
    do {
       j = 1 + rand() % (sequence.size() - 2);
    } while (j == i);

    iter_swap(sequence.begin() + i, sequence.begin() + j);
}
