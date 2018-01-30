/**
 * @file TSP.h
 * @brief TSP data definition
 */

#ifndef TSP_H
#define TSP_H

#include <fstream>
#include <vector>

/**
 * Class that describes a TSP instance (a cost matrix, nodes are identified by integer 0 ... n-1)
 */
class TSPData {
private:
    int n; //number of nodes
    double infinite; // infinite value (an upper bound on the value of any feasible solution)
    std::vector< std::vector<double> > costs;

public:
    /**
     * Default constructor
     */
    TSPData();
    
    /**
     * Reads data from specified file.
     * File should contain the number of nodes, followed by the matrix of costs.
     */
    void read(const char* filename);
    
    /**
     * Return nodes count
     */
    int size() const;
    
    /**
     * Return nodes count
     */
    double cost(int i, int j) const;
};

#endif /* TSP_H */
