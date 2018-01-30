#include <iostream>
#include <vector>
#include <cstdlib>
#include "../TSPData.h"
#include "tsp_solution.h"
#include "tsp_population.h"

const int GENERATIONS = 100;
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
	
	std::cout << "Generation 0:" << std::endl;
	std::cout << pop << std::endl;
	
	for (int i = 0; i < GENERATIONS; i++) {
	    pop.new_generation(SURVIVAL_RATIO);
	    pop.evaluate(data.costs());
	    
	    std::cout << "Generation " << i + 1 << ":" << std::endl;
	    std::cout << pop << std::endl;
	}
}
