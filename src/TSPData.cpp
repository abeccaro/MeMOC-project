/**
 * @file TSPData.cpp
 * @brief TSP data implementation
 */
 
#include "TSPData.h"
#include <iostream>
#include <cmath>

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

// EUC_2D format reader
/*void TSPData::read(const char* filename) {
    std::ifstream in(filename);

    // read size
    in >> n;
    in >> opt;

    std::vector<std::pair<double, double> > coords(n);
    for (int i = 0; i < n; i++) {
        double x, y;
        in >> x;
        in >> y;
        coords[i] = std::pair<double, double>(x, y);
    }

    // read costs
    c.reserve(n);
    for (int i = 0; i < n; i++) {
        c.push_back(std::vector<double>(n));
        for (int j = 0; j < n; j++) {
            double xd = coords[i].first - coords[j].first;
            double yd = coords[i].second - coords[j].second;
            c[i][j] = (int) (std::sqrt(xd*xd + yd*yd) + 0.5);
        }
    }

     for (int i = 0; i < n; i++) {
         for (int j = 0; j < n; j++)
             std::cout << c[i][j] << " ";
         std::cout << std::endl;
     }

    in.close();
}*/

// ATT format reader
/*void TSPData::read(const char* filename) {
    std::ifstream in(filename);

    // read size
    in >> n;
    in >> opt;

    std::vector<std::pair<double, double> > coords(n);
    for (int i = 0; i < n; i++) {
        double x, y;
        in >> x;
        in >> y;
        coords[i] = std::pair<double, double>(x, y);
    }

    // read costs
    c.reserve(n);
    for (int i = 0; i < n; i++) {
        c.push_back(std::vector<double>(n));
        for (int j = 0; j < n; j++) {
            double xd = coords[i].first - coords[j].first;
            double yd = coords[i].second - coords[j].second;
            double rij = std::sqrt( (xd*xd + yd*yd) / 10.0 );
            double tij = (int) (0.5 + rij);
            if (tij < rij)
                c[i][j] = tij + 1;
            else
                c[i][j] = tij;
        }
    }

     for (int i = 0; i < n; i++) {
         for (int j = 0; j < n; j++)
             std::cout << c[i][j] << " ";
         std::cout << std::endl;
     }

    in.close();
}*/

// UPPER_ROW format reader
/*void TSPData::read(const char* filename) {
    std::ifstream in(filename);

    // read size
    in >> n;
    in >> opt;

    // read costs
    c.reserve(n);
    for (int i = 0; i < n; i++)
        c.push_back(std::vector<double>(n));

    for (int i = 0; i < n; i++) {
        c[i][i] = 0;
        for (int j = i + 1; j < n; j++) {
            double cost;
            in >> cost;
            c[i][j] = cost;
            c[j][i] = cost;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            std::cout << c[i][j] << " ";
        std::cout << std::endl;
    }

    in.close();
}*/

// LOWER_DIAGONAL_ROW format reader
/*void TSPData::read(const char* filename) {
    std::ifstream in(filename);

    // read size
    in >> n;
    in >> opt;

    // read costs
    c.reserve(n);
    for (int i = 0; i < n; i++) {
        c.push_back(std::vector<double>(n));
        for (int j = 0; j <= i; j++) {
            double cost;
            in >> cost;
            c[i][j] = cost;
            c[j][i] = cost;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            std::cout << c[i][j] << " ";
        std::cout << std::endl;
    }

    in.close();
}*/

int TSPData::size() const {
    return n;
}

std::vector<std::vector<double> > TSPData::costs() const {
    return c;
}

double TSPData::cost(int i, int j) const {
    return c[i][j];
}
