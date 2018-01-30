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
     * Random access operator redefinition
     */
    tsp_solution& operator[](unsigned long index);
    
    /**
     * Evaluates all the solutions
     */
    void evaluate(const std::vector<std::vector<double> >& costs);
};

#endif
