/**
* @file tsp_solution.h
* @brief TSP solution definition
*/

#ifndef TSPSOLUTION_H
#define TSPSOLUTION_H

#include <vector>
#include "../TSPData.h"

/**
* TSP Solution representation: ordered sequence of nodes (path representation)
*/
class tsp_solution {
private:
    std::vector<int> sequence;
    double fit;
    
public:
    /** Constructor 
     * build a random feasible solution
     * @param data instance data
     */
    tsp_solution(int size);
    
    /** 
     * Copy constructor
     * @param sol Tsp solution to copy
     */
    tsp_solution(const tsp_solution& sol);
    
    /**
     * Prints solution
     */
    void print() const;
    
    /**
     * Returns solution size
     */
    unsigned long size() const;
    
    /** 
     * Assignment operator
     * @param rhs The solution to assign
     */
    tsp_solution& operator=(const tsp_solution& rhs);
    
    /** 
     * Output stream operator
     * @param sol The solution to output
     */
    friend std::ostream& operator<<(std::ostream& os, const tsp_solution& sol);

	/**
	 * Evaluate this solution fitness and updates value
	 */
	void evaluate(const std::vector<std::vector<double> >& costs);

	/**
	 * Gets this solution fitness
	 * @return The fitness
	 */
	double fitness() const;
	
	/**
	 * Creates a child from this solution reversing a substring
	 */
	tsp_solution crossover() const;
};

#endif
