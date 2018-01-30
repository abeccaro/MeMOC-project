/**
* @file tsp_solution.h
* @brief TSP solution implementation
*/

#include <algorithm>
#include <iostream>
#include "tsp_solution.h"

tsp_solution::tsp_solution(const TSPData& data) {
    sequence.reserve(data.size() + 1);

    for (int i = 0; i < data.size(); i++)
        sequence.push_back(i);
    std::random_shuffle(sequence.begin(), sequence.end());
    
    sequence.push_back(sequence.front());
}

tsp_solution::tsp_solution(const tsp_solution& sol) {
    sequence.reserve(sol.size());
    for (int i = 0; i < sol.size(); i++)
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
    if(this == &rhs) return *this;
    
    for (int i = 0; i < sequence.size(); i++)
        sequence[i] = rhs.sequence[i];
    return *this;
}
