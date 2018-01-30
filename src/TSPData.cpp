/**
 * @file TSP.cpp
 * @brief TSP data implementation
 */
 
#include "TSPData.h"

const double TSPData::INFINITE = 1e10;

TSPData::TSPData() : n(0) {};

void TSPData::read(const char* filename) {
    std::ifstream in(filename);
    // read size
    in >> n;
    // read costs
    c.reserve(n);
    for (int i = 0; i < n; i++) {
        c.reserve(n);
        for (int j = 0; j < n; j++) {
            double cost;
            in >> cost;
            c[i].push_back(cost);
        }
    }
    in.close();
}

int TSPData::size() const {
    return n;
}

std::vector<std::vector<double> > TSPData::costs() const {
    return c;
}

double TSPData::cost(int i, int j) const {
    return c[i][j];
}
