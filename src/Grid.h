#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "point.h"

class Grid {
    public:
    Grid(); // empty constructor
    void readFromFile(const std::string& filename); // constructs 2d array from file
    void createPointMaze();

    double getHeuristic(int x, int y, int goalX, int goalY);
   

    private:
        std::vector<std::vector<int>> maze_;
        std::vector<std::vector<Point>> pointmaze_;
        size_t rows_;
        size_t columns_;
        
};