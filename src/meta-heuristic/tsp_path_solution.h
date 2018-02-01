/**
* @file tsp_path_solution.h
* @brief TSP solution definition
*/

#ifndef TSPPATHSOLUTION_H
#define TSPPATHSOLUTION_H

#include <vector>
#include "../tsp_data.h"

/**
* TSP Solution representation: ordered sequence of nodes (path representation)
*/
class tsp_path_solution {
private:
    // ordered sequence of nodes
    std::vector<int> sequence;
    
    // fitness (= cost)
    double fit;
    
public:
    /**
     * Builds a random feasible solution
     * @param size The solution size
     */
    tsp_path_solution(int size);

    /**
     * Builds a solution from given path
     * @param path The path
     */
    tsp_path_solution(const std::vector<int>& path);
    
    /** 
     * Copy constructor
     * @param sol Tsp solution to copy
     */
    tsp_path_solution(const tsp_path_solution& sol);
    
    /**
     * Returns solution size
     */
    unsigned long size() const;
    
    /** 
     * Assignment operator
     * @param rhs The solution to assign
     */
    tsp_path_solution& operator=(const tsp_path_solution& rhs);
    
    /** 
     * Output stream operator
     * @param sol The solution to output
     */
    friend std::ostream& operator<<(std::ostream& os, const tsp_path_solution& sol);

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
	tsp_path_solution crossover(const tsp_path_solution& p2) const;
	
	/**
	 * Mutates this solution
	 */
	void mutate();
};

#endif
