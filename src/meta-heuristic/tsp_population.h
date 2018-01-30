/**
* @file tsp_population.h
* @brief TSP population definition
*/

#ifndef TSPPOPULATION_H
#define TSPPOPULATION_H

#include "tsp_solution.h"

class tsp_population {
private:
	std::vector<tsp_solution> solutions;
	
	/**
	 * Sorts solutions by fitness
	 */
	void sort_solutions();
	
public:
    /**
     * Random population
     */
    tsp_population(int sol_size, int size);
    
    /**
     * Returns population size
     */
    unsigned long size() const;
    
    /**
     * Random access operator redefinitions
     */
    const tsp_solution& operator[](unsigned long index) const;
    tsp_solution& operator[](unsigned long index);
    
    /** 
     * Output stream operator
     * @param pop The population to output
     */
    friend std::ostream& operator<<(std::ostream& os, const tsp_population& pop);
    
    /**
     * Evaluates all the solutions and sorts them
     */
    void evaluate(const std::vector<std::vector<double> >& costs);
    
    /**
     * Selects one random solution with probabilities proportional to fitness
     */
    const tsp_solution& select() const;
    
    /**
     * Advance to next generation by selecting some parents, creating offsprings from them
     * and replacing worst solutions with new ones
     * @param ratio The survival ratio (1 means no new solutions, 0 means replace all)
     * @param mut_chance The chance for a new solution to mutate
     */
    void new_generation(double ratio, double mut_chance);
};

#endif
