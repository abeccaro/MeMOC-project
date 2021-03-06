/**
* @file tsp_population.cpp
* @brief TSP population implementation
*/

#include "tsp_population.h"
#include <algorithm>
#include <cmath>

// solution comparer, used to sort solution by fitness (desc)
struct solution_comparer {
    bool operator ()(const tsp_path_solution& a, const tsp_path_solution& b) const {
        return a.fitness() < b.fitness();
    }
};


tsp_population::tsp_population(int sol_size, int size) {
	solutions.reserve(size);
	
	for (int i = 0; i < size; i++)
		solutions.push_back(tsp_path_solution(sol_size));
}

unsigned long tsp_population::size() const {
	return solutions.size();
}

const tsp_path_solution& tsp_population::operator[](unsigned long index) const {
    return solutions[index];
}

tsp_path_solution& tsp_population::operator[](unsigned long index) {
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
	
	// sort solutions by fitness
	std::sort(solutions.begin(), solutions.end(), solution_comparer());
}

const tsp_path_solution& tsp_population::select() const {
    double random_double = (double)rand() / RAND_MAX;

    // the higher the exponent the higher the probability of the random index to be low
    int index = (int) std::floor(solutions.size() * (std::pow(random_double, 2)));

    return solutions[index];
}

void tsp_population::new_generation(double ratio, double mut_chance) {
	// n = number of new solutions to generate
    int n = solutions.size() * (1 - ratio);
	
	for (int i = solutions.size() - n; i < solutions.size(); i++) {
		// generate new solution
	    tsp_path_solution sol = select().crossover(select());

	    // mutation chance
	    if ((double)rand() / RAND_MAX < mut_chance)
	        sol.mutate();

	    // replace old solution with new one
	    solutions[i] = sol;
	}
}
