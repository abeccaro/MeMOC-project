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
    tsp_population(const TSPData& data, int size);
    
    /**
     * Returns population size
     */
    unsigned long size() const;
    
    /**
     * Random access operator redefinition
     */
    tsp_solution& operator[](unsigned long index);
};

#endif
