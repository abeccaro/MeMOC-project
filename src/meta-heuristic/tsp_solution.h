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
    
public:
    /** Constructor 
     * build a random feasible solution
     * @param data instance data
     */
    tsp_solution(const TSPData& data);
    
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
};

#endif
