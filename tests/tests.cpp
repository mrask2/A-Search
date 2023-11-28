#include <catch2/catch_test_macros.hpp>
#include "Grid.h"

TEST_CASE("3x3 Correct Shortest Path from top left to bottom right", "[weight=10][valgrind][3x3]") {
    // 3x3 maze is the grid of nodes created from the 3x3.txt dataset, where each number 1-9 represents a passable node with weight and each 0 represents the start and end
    // findPath will return a vector of nodes that represent the shortest path from pointA to pointB
    // 3x3shortestPath will be a vector of points that correspond to the shortest path from the top left most points (0,0) to the bottom left most point (5,0)
    Grid threeGrid;
    threeGrid.readFromFile("3x3maze.txt");
    threeGrid.createPointMaze();
    Point start = threeGrid(0,0);
    Point end = threeGrid(2,2);

    vector<pair<int,int>> solution = {{0,0}, {0,1}, {0,2}, {1,2}, {2,2}};
    vector<pair<int,int>> threeShortestPath = threeGrid.solveMaze(start, end);
    for (size_t i = 0; i < solution.size(); i++) {
        REQUIRE(solution[i] == threeShortestPath[i]);
    }
}

/*
TEST_CASE("3x3 Correct Heuristic Calculations") {

    // creating a grid from the 3x3maze.txt image
    Grid threeGrid = toGrid("3x3maze.txt"); 
    Point startPoint;
    Point midPoint;
    Point endPoint;
    startPoint.h_ = val0; //expected h value of startPoint
    midPoint.h_  = val1;   //expected h value of midPoint
    endPoint.h_ = val2; // expected h value of endPoint

    // creating a vector of points with known heuristics
    vector<Point> knownHeuristics = {startPoint, midPoint, endPoint}; // example known heuristic value for startPoint

    // Calculate and compare heuristic values for each point
    for (const auto& point: knownHeuristics) {

        double expectedHeuristic = point.h_; //h_ is the heursitic value
        
        double calculatedHeuristic = getHeuristic(startPoint, endPoint);
        
        // Check if the calculated heuristic matches the expected value
        REQUIRE(calculatedHeuristic == expectedHeuristic);
    }
}


TEST_CASE("Straight Path with No Obstacles") {
    // testing on a straight path with no obstacles
    Graph threeGraph = Graph("3x3maze.txt");
    startPoint = threeGraph(0,0);
    endPoint = threeGraph(2,0);
    REQUIRE(findPath(3x3Maze, startPoint, endPoint) == straightPath);
}

TEST_CASE("Diagonal Path with No Obstacles") { 
    Graph threeGraph = Graph("3x3maze.txt");
    startPoint = threeGraph(0,0);
    endPoint = threeGraph(2,2);
    REQUIRE(findPath(3x3Maze, startPoint, endPoint) == diagonalPath);
}

TEST_CASE("Straight Path with Obstacles") {
    Graph threeGraph = Graph("3x3maze.txt");
    startPoint = threeGraph(0,0);
    endPoint = threeGraph(0,2);
    REQUIRE(findPath(3x3Maze, startPoint, endPoint) == straightObstaclePath);
}
*/