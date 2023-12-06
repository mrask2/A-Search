#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_map>

#include "point.h"
#include "PNG.h"

using namespace std;

class Grid {
    public:
        Grid(); // empty constructor
        void readFromFile(const string& filename, int wallValue); // constructs 2d array from file
        void readFromCSV(const string& filename, int wallValue);
        void createPointMaze(int goalX, int goalY);

        int getHeuristic(int x, int y, int goalX, int goalY);
        vector<pair<int,int>> solveMaze(Point start, Point goal);

        Point& operator()(int x, int y) { return pointmaze_[x][y]; }

        cs225::PNG createPicture();
        cs225::PNG drawPath(const vector<pair<int,int>>& solutionPath);

    private:
        vector<pair<int, int>> reconstruct_path(Point* current); 
        vector<Point*> getNeighbors(Point* current);

        vector<vector<int>> maze_;
        vector<vector<Point>> pointmaze_;
        int rows_;
        int columns_;
        int wallValue_;

        vector<pair<int, int>> path_;
        cs225::PNG picture_;
};