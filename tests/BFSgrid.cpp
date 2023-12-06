#include "BFSgrid.h"

#include <limits>
#include <algorithm>
#include <sstream>

#include "../lib/cs225/HSLAPixel.h"

using namespace std;

BFSgrid::BFSgrid() {
    columns_  = 0;
    rows_ = 0;
}

void BFSgrid::readFromFile(const string& filename, int wallValue) {
    wallValue_ = wallValue;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    string line;
    while (std::getline(file, line)) {
        std::stringstream str(line);
        int value;
        vector<int> row;
        while (str >> value) {
            row.push_back(value);
        }

        maze_.push_back(row);
        columns_ = row.size(); 
        ++rows_;
    }
}

void BFSgrid::readFromCSV(const string& filename, int wallValue) {
    // read 0s and 1s from csv file
    wallValue_ = wallValue;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    string line;
    while (std::getline(file, line)) {
        std::stringstream str(line);
        int value;
        vector<int> row;
        while (str >> value) {
            row.push_back(value);
            str.ignore(1, ',');
        }
        maze_.push_back(row);
        columns_ = row.size(); 
        ++rows_;
    }
}

void BFSgrid::createPointMaze() {
    pointmaze_.resize(rows_, vector<Point>(columns_));
    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < columns_; c++) {
            pointmaze_[r][c] = Point(r, c, maze_[r][c], 0);
        }
    }
}

vector<std::pair<int,int>> BFSgrid::solveMaze(Point start, Point goal) {
    
    // BFS search algorithm
    // Derived from pseudocode found at 
    // https://en.wikipedia.org/wiki/Breadth-first_search#Pseudocode

    queue<Point*> q;
    q.push(&start);
    start.searched = true;

    while (!q.empty()) {
        // This operation can occur in O(Log(N)) time if openSet is a min-heap or a priority queue
        Point* current = q.front(); // the node in openSet having the lowest f value
        q.pop();
        if (current->positionEquals(goal)) {
            return reconstruct_path(current); 
        }

        vector<Point*> neighbors = getNeighbors(current);

        for (Point*& neighbor : neighbors) { // the 4 directions besides the one it came from
            if (!neighbor->searched) {
                neighbor->setCameFrom(current);
                neighbor->searched = true;
                q.push(neighbor);
            }
        }
    }
    // Queue is empty but goal was never reached
    return vector<pair<int, int>>();
}

vector<pair<int, int>> BFSgrid::reconstruct_path(Point* current) {
    vector<pair<int, int>> total_path;
    total_path.push_back(current->getXY());
    while (current->getCameFrom() != nullptr) {
        current = current->getCameFrom();
        total_path.push_back(current->getXY());
    }
    std::reverse(total_path.begin(), total_path.end());
    return total_path;
}

vector<Point*> BFSgrid::getNeighbors(Point* current) { 
    vector<Point*> neighbors;
    std::pair<int, int> directions[] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},  // Horizontal and vertical neighbors
    };

    std::pair<int, int> currentXY = current->getXY();
    for (const auto& dir : directions) {
        int newX = currentXY.first + dir.first;
        int newY = currentXY.second + dir.second;

        // Check if the new position is within the maze bounds
        if (newX >= 0 && newX < rows_ && newY >= 0 && newY < columns_) {
            Point* cameFrom = current->getCameFrom();
            if (cameFrom != nullptr && newX == cameFrom->getXY().first && newY == cameFrom->getXY().second) {
                continue; // Don't go back to the node we came from
            }
            if (maze_[newX][newY] == wallValue_) {
                continue; // Don't go to a wall
            }
            neighbors.push_back(&pointmaze_[newX][newY]);
        }
    }
    return neighbors;
} 

cs225::PNG BFSgrid::createPicture() {
    picture_ = cs225::PNG(columns_, rows_);
    cs225::HSLAPixel white(0, 0, 1, 1);
    cs225::HSLAPixel black(0, 0, 0, 1);
    for (int row = 0; row < rows_; row++) {
        for (int col = 0; col < columns_; col++) {
            if (maze_[row][col] == wallValue_) {
                picture_.getPixel(col, row) = black;
            } else {
                picture_.getPixel(col, row) = white;
            }
        }
    }
    return picture_;
}


cs225::PNG BFSgrid::drawPath(const vector<pair<int,int>>& solutionPath) {
    cs225::PNG copy = picture_;
    cs225::HSLAPixel red(0, 1, 0.5, 1);
    for (const pair<int,int>& tile : solutionPath) {
        copy.getPixel(tile.second, tile.first) = red;
    }
    return copy;
}