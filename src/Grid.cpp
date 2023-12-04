#include "Grid.h"

#include <limits>
#include <algorithm>
#include <sstream>

using namespace std;

Grid::Grid() {
    columns_  = 0;
    rows_ = 0;
}

void Grid::readFromFile(const string& filename, int rows, int columns) {
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
        if ((int) row.size() != columns) {
            std::cerr << "Error: row size does not match columns" << std::endl;
            return;
        }
        maze_.push_back(row);
        columns_ = row.size(); 
        ++rows_;
    }
    if (rows_ != rows) {
        std::cerr << "Error: number of rows does not match rows" << std::endl;
        return;
    }
}

void Grid::createPointMaze() {
    pointmaze_.resize(rows_, vector<Point>(columns_));
    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < columns_; c++) {
            // If destination is not bottom right, needs to be changed
            pointmaze_[r][c] = Point(r, c, maze_[r][c], getHeuristic(r,c, rows_ - 1, columns_ - 1)); 
        }
    }
}


int Grid::getHeuristic(int x, int y, int goalX, int goalY) {
    return std::abs(goalX - x + goalY - y);
}


// A* finds a path from start to goal.
// h is the heuristic function. h(n) estimates the cost to reach goal from node n.
vector<std::pair<int,int>> Grid::solveMaze(Point start, Point goal) {
    // Derived from pseudocode found at
    // https://en.wikipedia.org/wiki/A*_search_algorithm#Pseudocode

    // The set of discovered nodes that may need to be (re-)expanded.
    priority_queue<Point*, vector<Point*>, greater<Point*>> openSet;
    openSet.push(&start);

    // For node n, n.getCameFrom() is the Point* immediately preceding 
    // it on the cheapest path from the start to n currently known.

    // For node n, n.setG() is the cost of the cheapest path from start to n currently known.
    start.setG(0);

    // For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how cheap a path could be from start to finish if it goes through n.
    // Set automatically in Point::setG()

    while (!openSet.empty()) {
        // This operation can occur in O(Log(N)) time if openSet is a min-heap or a priority queue
        Point* current = openSet.top(); // the node in openSet having the lowest f value
        if (current->searched) {
            continue;
        }
        if (current->positionEquals(goal)) {
            return reconstruct_path(current); 
        }

        current->searched = true;
        openSet.pop();

        vector<Point*> neighbors = getNeighbors(current);

        for (auto& neighbor : neighbors) { // the seven directions besides the one it came from
            // tentative_gScore is the distance from start to the neighbor through current
            double tentative_gScore = current->getG() + neighbor->getWeight();
            if (tentative_gScore < neighbor->getG()) {
                // This path to neighbor is better than any previous one. Record it!
                // std::cout << "Setting cameFrom for point " << neighbor->getXY().first << ", " << neighbor->getXY().second << " to " << current->getXY().first << ", " << current->getXY().second << std::endl;
                neighbor->setCameFrom(current); 
                neighbor->setG(tentative_gScore);
                if (!neighbor->searched) {
                    openSet.push(neighbor);
                }
            }
        }
    }
    // Open set is empty but goal was never reached
    return vector<pair<int, int>>();
}

vector<pair<int, int>> Grid::reconstruct_path(Point* current) {
    vector<pair<int, int>> total_path;

    total_path.push_back(current->getXY());
    
    while (current->getCameFrom() != nullptr) {
        current = current->getCameFrom();
        total_path.push_back(current->getXY());
    }
    std::reverse(total_path.begin(), total_path.end());
    return total_path;
}

vector<Point*> Grid::getNeighbors(Point* current) { 
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
            if (maze_[newX][newY] != 1) {
                continue; // Don't go to a wall
            }
            // if (cameFrom != nullptr) {
            //     std::cout << "NewXY: \t" << newX << ", " << newY << std::endl;
            //     std::cout << "CamFrm \t" << cameFrom->getXY().first << ", " << cameFrom->getXY().second << std::endl;
            //     std::cout << "Curnt \t" << current->getXY().first << ", " << current->getXY().second << std::endl;
            // }
            neighbors.push_back(&pointmaze_[newX][newY]);
        }
    }
    return neighbors;
} 