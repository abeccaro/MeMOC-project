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

std::ostream& operator<<(std::ostream& os, const tsp_solution& sol) {
    os << "[ ";
    for (int i = 0; i < sol.sequence.size(); i++)
        os << sol.sequence[i] << " ";
	return os << "] fit = " << sol.fit;
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
    fit = rhs.fit;
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

tsp_solution tsp_solution::crossover() const {
    tsp_solution child = *this;
    
    // starting index and length of reverse
    int k = (double) rand() / RAND_MAX * (child.sequence.size() - 1);
    int l = (double) rand() / RAND_MAX * (child.sequence.size() - k) + 1;
    
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

void tsp_solution::mutate() {
    // indices in range [1, |nodes| - 1]
    int i = 1 + rand() % (sequence.size() - 2); // random sequence index
    int j;
    
    do {
       j = 1 + rand() % (sequence.size() - 2);
    } while (j == i);

    iter_swap(sequence.begin() + i, sequence.begin() + j);
}

