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

tsp_path_solution::tsp_path_solution(const std::vector<int>& path) : sequence(path), fit(TSPData::INFINITE) {}

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

// Implemented with Order Crossover (OX) algorithm
tsp_path_solution tsp_path_solution::crossover(const tsp_path_solution& p2) const {
    // indexes in range [1, |nodes| - 1] for cut point start and end
    int start = 1 + rand() % (sequence.size() - 1);
    int end;
    
    do {
       end = 1 + rand() % (sequence.size() - 1);
    } while (end == start);

    if (start > end)
        std::swap(start, end);

    std::vector<int> child_sequence(size(), -1);

    // copy solution part between cut points
    std::copy(sequence.begin() + start, sequence.begin() + end, child_sequence.begin() + start);

    // getting remaining elements from p2 in order
    int k = end;

    // p2 after end
    for (int i = end; i < p2.size(); i++)
        // if sequence[start - end] doesn't contain p2[i]
        if (std::find(sequence.begin() + start, sequence.begin() + end, p2.sequence[i]) == sequence.begin() + end) {
            child_sequence[k] = p2.sequence[i];
            k++;
        }

    // p2 before start
    for (int i = 0; i < end; i++)
        // if sequence[start - end] doesn't contain p2[i]
        if (std::find(sequence.begin() + start, sequence.begin() + end, p2.sequence[i]) == sequence.begin() + end) {
            k %= child_sequence.size();
            child_sequence[k] = p2.sequence[i];
            k++;
        }

    // child sequence might not have 0 in first place
    // rotate it right until it has
    while (child_sequence.front() != 0)
        std::rotate(child_sequence.rbegin(), child_sequence.rbegin() + 1, child_sequence.rend());

    return tsp_path_solution(child_sequence);
}


// tsp_path_solution tsp_path_solution::crossover() const {
//     tsp_path_solution child(*this);
    
//     // generating 2 random indices
//     int i = 1 + rand() % (child.sequence.size() - 1);
//     int j = 1 + rand() % (child.sequence.size() - 1);
//     if (j < i)
//         std::swap(i, j);
    
//     std::reverse(child.sequence.begin() + i, child.sequence.begin() + j);
//     return child;
// }

// 2-opt mutation
void tsp_path_solution::mutate() {
    // generating 2 random indices
    int i = 1 + rand() % (sequence.size() - 1);
    int j = 1 + rand() % (sequence.size() - 1);
    if (j < i)
        std::swap(i, j);
    
    std::reverse(sequence.begin() + i, sequence.begin() + j);
}

// // swap mutation
// void tsp_path_solution::mutate() {
//     // indexes in range [1, |nodes| - 1]
//     int i = 1 + rand() % (sequence.size() - 1);
//     int j;
    
//     do {
//        j = 1 + rand() % (sequence.size() - 1);
//     } while (j == i);

//     iter_swap(sequence.begin() + i, sequence.begin() + j);
// }
