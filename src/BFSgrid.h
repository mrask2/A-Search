#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_map>

#include "point.h"

using namespace std;

class BFSgrid {
    public:
        BFSgrid(); // empty constructor
        void readFromFile(const string& filename); // constructs 2d array from file
        void createPointMaze();

        int getHeuristic(int x, int y, int goalX, int goalY);
        vector<pair<int,int>> solveMaze(Point start, Point goal);

        Point& operator()(int x, int y) { return pointmaze_[x][y]; }

    private:
        vector<pair<int, int>> reconstruct_path(Point* current); 
        vector<Point> getNeighbors(Point current);

        vector<vector<int>> maze_;
        vector<vector<Point>> pointmaze_;
        int rows_;
        int columns_;

        vector<pair<int, int>> path_;
};