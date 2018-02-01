#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include "../TSPData.h"
#include "tsp_path_solution.h"
#include "tsp_population.h"


const int POPULATION_SIZE = 1000;
const int GENERATIONS = 300;
const double SURVIVAL_RATIO = 0.1;
const double MUTATION_CHANCE = 0.1;
const int RESTARTS = 5;


int main (int argc, char const *argv[]) {
	// reading data from input file
	if (argc < 2)
	    throw std::runtime_error("usage: ./main filename.dat");
	TSPData data;
	data.read(argv[1]);
	
	// setting random seed (different every second)
	srand(time(0));

	tsp_path_solution best(data.size());
	std::cout << "********** START **********" << std::endl;
	for (int r = 0; r < RESTARTS; r++) {
		std::cout << "Restart n. " << r << std::endl;

		// creating first gen random population
		tsp_population pop(data.size(), POPULATION_SIZE);
		
		//evaluate population
		pop.evaluate(data.costs());
		// double last = pop[0].fitness();
		
		// new generations
		for (int i = 0; i < GENERATIONS; i++) {
		    pop.new_generation(SURVIVAL_RATIO, MUTATION_CHANCE);
		    pop.evaluate(data.costs());
		    // if (pop[0].fitness() < last) {
		    	// std::cout << "Gen " << i + 1 << ": " << pop[0] << std::endl;
		    	// last = pop[0].fitness();
			// }
		}

		if (pop[0].fitness() < best.fitness())
			best = pop[0];
		std::cout << "Best solution found: " << std::endl;
		std::cout << pop[0] << std::endl << std::endl;
	}
	std::cout << "*********** END ***********" << std::endl;
	std::cout << std::endl << "Best overall solution:" << std::endl << best << std::endl;
}
