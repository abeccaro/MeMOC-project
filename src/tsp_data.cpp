/**
 * @file tsp_data.cpp
 * @brief TSP data implementation
 */
 
#include "tsp_data.h"
#include <fstream>
#include <cmath>

const double tsp_data::INFINITE = 1e10;

tsp_data::tsp_data() : n(0), opt(0) {};

void tsp_data::read(const char* filename) {
    std::ifstream in(filename);

    // read size
    in >> n;
    in >> opt;

    // read costs
    c.reserve(n);
    for (int i = 0; i < n; i++) {
        c.push_back(std::vector<double>(n));
        for (int j = 0; j < n; j++) {
            double cost;
            in >> cost;
            c[i][j] = cost;
        }
    }

    in.close();
}

int tsp_data::size() const {
    return n;
}

std::vector<std::vector<double> > tsp_data::costs() const {
    return c;
}
