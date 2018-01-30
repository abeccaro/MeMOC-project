#include <iostream>
#include <vector>
#include <cstdlib>
#include "../TSPData.h"
#include "tsp_solution.h"
#include "tsp_population.h"

int main (int argc, char const *argv[]) {
	// reading data from input file
	if (argc < 2)
	    throw std::runtime_error("usage: ./main filename.dat");
	TSPData data;
	data.read(argv[1]);
	
	// setting random seed
	srand(time(0));

	// creating first gen random population
	tsp_population pop(data, 10);
	
	std::cout << pop.size() << std::endl;
	for (int i = 0; i < pop.size(); i++)
		pop[i].print();
		
}
