#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <sys/time.h>
#include <thread>
#include <future>
#include "../TSPData.h"
#include "tsp_path_solution.h"
#include "tsp_population.h"


const int POPULATION_SIZE = 1000;
const int GENERATIONS = 500;
const double SURVIVAL_RATIO = 0.1;
const double MUTATION_CHANCE = 0.1;
const int POPULATIONS = 5;


/**
 * Creates a new population, creates specified amount of generation and returns the best solution found
 */
tsp_path_solution evaluate_random_population(const TSPData& data) {
	// creating first gen random population
	tsp_population pop(data.size(), POPULATION_SIZE);
	
	//evaluate population
	pop.evaluate(data.costs());
	
	// new generations
	for (int i = 0; i < GENERATIONS; i++) {
	    pop.new_generation(SURVIVAL_RATIO, MUTATION_CHANCE);
	    pop.evaluate(data.costs());
	}

	// returning best solution
	return pop[0];
}


int main (int argc, char const *argv[]) {
	// reading data from input file
	if (argc < 2)
	    throw std::runtime_error("usage: ./main data_filename.dat");

	TSPData data;
	data.read(argv[1]);
	
	// setting random seed (different every second)
	srand(time(0));

    // start timer
    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);

	// setting best cost to INFINITE with random solution (will be overriden)
	tsp_path_solution best(data.size());
	
	// starting 'POPULATIONS' random populations evaluation
	std::future<tsp_path_solution> bests[POPULATIONS];
	std::cout << "********** START **********" << std::endl << std::endl;
	for (int i = 0; i < POPULATIONS; i++)
		 bests[i] = std::async(std::launch::async, evaluate_random_population, data);

	// getting best solution from each population and storing the best found
	for (int i = 0; i < POPULATIONS; i++) {
		tsp_path_solution best_sol = bests[i].get();

		if (best_sol.fitness() < best.fitness())
			best = best_sol;

		std::cout << "Best solution found in population n. " << i + 1 << ": " << std::endl;
		std::cout << best_sol << std::endl << std::endl;
	}
	std::cout << "*********** END ***********" << std::endl;

	// stop timer
    gettimeofday(&tv2, NULL);
    double time = (double)(tv2.tv_sec+tv2.tv_usec*1e-6 - (tv1.tv_sec+tv1.tv_usec*1e-6));

    // print results
	std::cout << std::endl << "Best solution found:" << std::endl << best << std::endl;
	std::cout << "Optimal value: " << data.optimum() << ", found: " << best.fitness();
	if (data.optimum() == best.fitness())
		std::cout << " (optimal solution)";
	else
		std::cout << " (" << 100 * (1 - data.optimum() / best.fitness()) << "% off optimal)";
		std::cout << std::endl;
    std::cout << "Calculation took " << time << " seconds" << std::endl << std::endl;
}
