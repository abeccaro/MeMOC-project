/**
 * @file TSPData.cpp
 * @brief TSP data implementation
 */
 
#include "TSPData.h"
#include <iostream>

const double TSPData::INFINITE = 1e10;

TSPData::TSPData() : n(0) {};

void TSPData::read(const char* filename) {
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

// // UPPER_ROW reader
// void TSPData::read(const char* filename) {
//     std::ifstream in(filename);

//     // read size
//     in >> n;

//     // read costs
//     c.reserve(n);
//     for (int i = 0; i < n; i++)
//         c.push_back(std::vector<double>(n));

//     for (int i = 0; i < n; i++) {
//         c[i][i] = 0;
//         for (int j = i + 1; j < n; j++) {
//             double cost;
//             in >> cost;
//             c[i][j] = cost;
//             c[j][i] = cost;
//         }
//     }

//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++)
//             std::cout << c[i][j] << " ";
//         std::cout << std::endl;
//     }

//     in.close();
// }

int TSPData::size() const {
    return n;
}

std::vector<std::vector<double> > TSPData::costs() const {
    return c;
}

double TSPData::cost(int i, int j) const {
    return c[i][j];
}
