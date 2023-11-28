#pragma once

#include "Grid.h"

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



// A* finds a path from start to goal.
// h is the heuristic function. h(n) estimates the cost to reach goal from node n.
vector<std::pair<int,int>> solveMaze(Point start, Point goal, std::vector<std::vector<Point>> maze){

    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
    // This is usually implemented as a min-heap or priority queue rather than a hash-set.
    openSet := {start}

    // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from the start
    // to n currently known.
    cameFrom := an empty map

    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    gScore := map with default value of Infinity
    gScore[start] := 0

    // For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how cheap a path could be from start to finish if it goes through n.
    fScore := map with default value of Infinity
    fScore[start] := h(start)

    while openSet is not empty
        // This operation can occur in O(Log(N)) time if openSet is a min-heap or a priority queue
        current := the node in openSet having the lowest fScore[] value
        if current = goal
            return reconstruct_path(cameFrom, current)

        openSet.Remove(current)
        for each neighbor of current
            // d(current,neighbor) is the weight of the edge from current to neighbor
            // tentative_gScore is the distance from start to the neighbor through current
            tentative_gScore := gScore[current] + d(current, neighbor)
            if tentative_gScore < gScore[neighbor]
                // This path to neighbor is better than any previous one. Record it!
                cameFrom[neighbor] := current
                gScore[neighbor] := tentative_gScore
                fScore[neighbor] := tentative_gScore + h(neighbor)
                if neighbor not in openSet
                    openSet.add(neighbor)

    // Open set is empty but goal was never reached
    return failure
}