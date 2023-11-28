#include "Grid.h"

#include <limits>

using namespace std;

Grid::Grid() {
    columns_  = 0;
    rows_ = 0;
}

void Grid::readFromFile(const string& filename) {
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

void Grid::createPointMaze() {
    pointmaze_.resize(rows_, vector<Point>(columns_));
    for (unsigned r = 0; r < rows_; r++) {
        for (unsigned c = 0; c < columns_; c++) {
            pointmaze_[r][c] = Point(r, c, maze_[r][c], getHeuristic(r,c, rows_ - 1, columns_ - 1));
        }
    }
}


double Grid::getHeuristic(int x, int y, int goalX, int goalY) {
    return std::sqrt(std::pow((goalX - x), 2) + std::pow((goalY - y), 2));
}


// A* finds a path from start to goal.
// h is the heuristic function. h(n) estimates the cost to reach goal from node n.
vector<std::pair<int,int>> Grid::solveMaze(Point start, Point goal) {

    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
    // This is usually implemented as a min-heap or priority queue rather than a hash-set.
    priority_queue<Point, vector<Point>, greater<Point>> openSet;
    openSet.push(start);

    // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from the start
    // to n currently known.
    // unordered_map<Point, Point> cameFrom = {{start, start}};
    // cameFrom ==== POINT.get/setCameFrom(POINT*);

    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    //map with default value of Infinity
    start.setG(0);

    // For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how cheap a path could be from start to finish if it goes through n.
    // Set automatically in Point::setG()

    while (!openSet.empty()) {
        // This operation can occur in O(Log(N)) time if openSet is a min-heap or a priority queue
        Point current = openSet.top(); // the node in openSet having the lowest fScore[] value
        if (current.positionEquals(goal)) {
            return reconstruct_path(&current); /// TODO: this function
        }
        current.in_open_set = false;
        openSet.pop();

        vector<Point> neighbors = getNeighbors(current);

        for (auto& neighbor : neighbors) { // the seven directions besides the one it came from
            // d(current,neighbor) is the weight of the edge from current to neighbor
            // tentative_gScore is the distance from start to the neighbor through current
            double tentative_gScore = current.getG() + neighbor.getWeight();
            if (tentative_gScore < neighbor.getG()) {
                // This path to neighbor is better than any previous one. Record it!
                neighbor.setCameFrom(&current);
                neighbor.setG(tentative_gScore);
                // auto:: fScore[neighbor] = tentative_gScore + neighbor.getH();
                if (!neighbor.in_open_set) {
                    openSet.push(neighbor);
                    neighbor.in_open_set = true;
                }
            }
        }
    }
    // Open set is empty but goal was never reached // should never happen...
    throw std::runtime_error("No path found");
}

vector<pair<int, int>> Grid::reconstruct_path(Point* current) {
    vector<pair<int, int>> total_path;
    total_path.push_back(current->getXY());
    while (current->getCameFrom() != nullptr) {
        current = current->getCameFrom();
        total_path.push_back(current->getXY());
    }
    return total_path;
}

vector<Point> Grid::getNeighbors(Point current) { 
    vector<Point> neighbors;
    std::pair<int, int> directions[] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},  // Horizontal and vertical neighbors
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1} // Diagonal neighbors
    };

    std::pair<int, int> currentXY = current.getXY();
    for (const auto& dir : directions) {
        int newX = currentXY.first + dir.first;
        int newY = currentXY.second + dir.second;

        // Check if the new position is within the maze bounds
        if (newX >= 0 && newX < rows_ && newY >= 0 && newY < columns_) {
            if (current.getCameFrom() != nullptr && newX == current.getCameFrom()->getXY().first && newY == current.getCameFrom()->getXY().second) {
                continue; // Don't go back to the node we came from
            }
            neighbors.push_back(pointmaze_[newX][newY]);
        }
    }
    return neighbors;
} 