#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_map>

#include "point.h"

class Grid {
    public:
        Grid(); // empty constructor
        void readFromFile(const std::string& filename); // constructs 2d array from file
        void createPointMaze();

        double getHeuristic(int x, int y, int goalX, int goalY);
        vector<std::pair<int,int>> solveMaze(Point start, Point goal, std::vector<std::vector<Point>> maze);
        vector<std::pair<int,int>> Grid::solveMaze(Point start, Point goal);

    private:
        vector<pair<int, int>> Grid::reconstruct_path(Point* current); 
        vector<Point> Grid::getNeighbors(Point current);

        std::vector<std::vector<int>> maze_;
        std::vector<std::vector<Point>> pointmaze_;
        size_t rows_;
        size_t columns_;
};