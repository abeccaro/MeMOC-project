/**
 * @file TSP.h
 * @brief TSP data definition
 */

#ifndef TSPDATA_H
#define TSPDATA_H

#include <fstream>
#include <vector>

/**
 * Class that describes a TSP instance (a cost matrix, nodes are identified by integer 0 ... n-1)
 */
class TSPData {
private:
    int n; //number of nodes
    double opt; // optimal value for objective function
    std::vector<std::vector<double> > c; // costs

public:
    /**
     * Infinite value (an upper bound on the value of any feasible solution)
     */
    static const double INFINITE;
	
	
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
     * Return costs matrix
     */
    std::vector<std::vector<double> > costs() const;

    /**
     * Returns optimal cost sum
     */
    double optimum() const {
        return opt;
    }
    
    /**
     * Return nodes count
     */
    double cost(int i, int j) const;
};

#endif /* TSP_H */
