#pragma once

#include "Grid.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>

Grid::Grid() {
    columns_  = 0;
    rows_ = 0;
}

void Grid::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    int value;
    while (file >> value) {
        std::vector<int> row;
        row.push_back(value);

        while (file.peek() == ' ') {
            file.ignore();
            file >> value;
            row.push_back(value);
        }
        maze_.push_back(row);
        columns_ = row.size(); 
        ++rows_;
    }
}

void Grid::createPointMaze() {
    pointmaze_.resize(rows_, std::vector<Point>(columns_));
    for (unsigned r = 0; r < rows_; r++) {
        for (unsigned c = 0; c < columns_; c++) {
            pointmaze_[r][c] = Point(maze_[r][c], getHeuristic(r,c, rows_ - 1, columns_ - 1));
        }
    }
}


 double Grid::getHeuristic(int x, int y, int goalX, int goalY) {
    return std::sqrt(std::pow((goalX - x), 2) + std::pow((goalY - y), 2));
 }

