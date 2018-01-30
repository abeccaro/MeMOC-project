/**
 * @file TSP.cpp
 * @brief TSP data implementation
 */
 
#include "TSPData.h"

TSPData::TSPData() : n(0) , infinite(1e10) {};

void TSPData::read(const char* filename) {
    std::ifstream in(filename);
    // read size
    in >> n;
    // read costs
    costs.reserve(n);
    for (int i = 0; i < n; i++) {
        costs.reserve(n);
        for (int j = 0; j < n; j++) {
            double c;
            in >> c;
            costs[i].push_back(c);
        }
    }
    in.close();
}

int TSPData::size() const {
    return n;
}

double TSPData::cost(int i, int j) const {
    return costs[i][j];
}
