#include <iostream>
#include <vector>
#include <cstdlib>
#include "../TSPData.h"
#include "tsp_solution.h"
#include "tsp_population.h"

const int GENERATIONS = 5;
const double SURVIVAL_RATIO = 0.25;

int main (int argc, char const *argv[]) {
	// reading data from input file
	if (argc < 2)
	    throw std::runtime_error("usage: ./main filename.dat");
	TSPData data;
	data.read(argv[1]);
	
	// setting random seed (different every second)
	srand(time(0));

	// creating first gen random population
	tsp_population pop(data.size(), 10);
	
	//evaluate population
	pop.evaluate(data.costs());
	
	std::cout << pop << std::endl;
	
	for (int i = 0; i < GENERATIONS; i++) {
	    int n = pop.size() * (1 - SURVIVAL_RATIO);
	    std::vector<tsp_solution> new_solutions(n, tsp_solution(data.size()));
	    for (int j = 0; j < n; j++) {
	        new_solutions[j] = pop.select().crossover();
	        new_solutions[j].evaluate(data.costs());
	        std::cout << new_solutions[j] << std::endl;
	    }
	}
}
