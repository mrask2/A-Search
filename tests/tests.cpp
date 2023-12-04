#include <catch2/catch_test_macros.hpp>
#include "Grid.h"
#include "BFSgrid.h"
TEST_CASE("3x3 Correct Shortest Path from top left to bottom right", "[weight=10][valgrind][3x3]") {
    // 3x3 maze is the grid of nodes created from the 3x3.txt dataset, where each number 1-9 represents a passable node with weight and each 0 represents the start and end
    // findPath will return a vector of nodes that represent the shortest path from pointA to pointB
    // 3x3shortestPath will be a vector of points that correspond to the shortest path from the top left most points (0,0) to the bottom left most point (5,0)
    Grid threeGrid;
    threeGrid.readFromFile("../data/3x3.txt", 0);
    threeGrid.createPointMaze(2,2);
    Point start = threeGrid(0,0);
    Point end = threeGrid(2,2);

    vector<pair<int,int>> solution = {{0,0}, {0,1}, {1,1}, {1,2}, {2,2}};
    vector<pair<int,int>> threeShortestPath = threeGrid.solveMaze(start, end);
    for (size_t i = 0; i < solution.size(); i++) {
        REQUIRE(solution[i] == threeShortestPath[i]);
    }
}



TEST_CASE("3x3 Correct Heuristic Calculations") {

    // creating a grid from the 3x3maze.txt image
    Point startPoint(0, 0, 1, 4); //expected h value of startPoint
    Point midPoint(1, 1, 1, 2); //expected h value of midPoint
    Point endPoint(2, 2, 1, 0); // expected h value of endPoint

    Grid threeGrid;
    threeGrid.readFromFile("../data/3x3.txt", 0);
    threeGrid.createPointMaze(2,2);
    Point start = threeGrid(0,0);
    Point end = threeGrid(2,2);
    
    // creating a vector of points with known heuristics
    vector<Point> knownHeuristics = {startPoint, midPoint, endPoint}; // example known heuristic value for startPoint

    // Calculate and compare heuristic values for each point
    for (const auto& point: knownHeuristics) {

        double expectedHeuristic = point.getH(); //h_ is the heursitic value
        
        double calculatedHeuristic = threeGrid(point.getXY().first, point.getXY().second).getH();
        
        // Check if the calculated heuristic matches the expected value
        REQUIRE(calculatedHeuristic == expectedHeuristic);
    }
}

TEST_CASE("3x3 Correct Backwards Heuristic Calculations") {

    // creating a grid from the 3x3maze.txt image
    
    Point startPoint(2, 2, 1, 0); //expected h value of startPoint
    Point midPoint(1, 1, 1, 2); //expected h value of midPoint
    Point endPoint(0, 0, 1, 4); // expected h value of endPoint

    Grid threeGrid;
    threeGrid.readFromFile("../data/3x3.txt",0);
    threeGrid.createPointMaze(2,2);
    Point start = threeGrid(2,2);
    Point end = threeGrid(0,0);
    
    // creating a vector of points with known heuristics
    vector<Point> knownHeuristics = {startPoint, midPoint, endPoint}; // example known heuristic value for startPoint

    // Calculate and compare heuristic values for each point
    for (const auto& point: knownHeuristics) {

        double expectedHeuristic = point.getH(); //h_ is the heursitic value
        
        double calculatedHeuristic = threeGrid(point.getXY().first, point.getXY().second).getH();
        
        // Check if the calculated heuristic matches the expected value
        REQUIRE(calculatedHeuristic == expectedHeuristic);
    }
}


TEST_CASE("5x5 Correct Shortest Path from top left to bottom right", "[weight=10][valgrind][3x3]") {
    // 3x3 maze is the grid of nodes created from the 3x3.txt dataset, where each number 1-9 represents a passable node with weight and each 0 represents the start and end
    // findPath will return a vector of nodes that represent the shortest path from pointA to pointB
    // 3x3shortestPath will be a vector of points that correspond to the shortest path from the top left most points (0,0) to the bottom left most point (5,0)
    Grid fiveGrid;
    fiveGrid.readFromFile("../data/5x5.txt", 0);
    fiveGrid.createPointMaze(4,4);
    Point start = fiveGrid(0,0);
    Point end = fiveGrid(4,4);

    vector<pair<int,int>> solution = {{0,0}, {0,1}, {1,1}, {1,2}, {2,2}, {2,3}, {3,3}, {3,4}, {4,4}};
    vector<pair<int,int>> fiveShortestPath = fiveGrid.solveMaze(start, end);
    for (size_t i = 0; i < solution.size(); i++) {
        REQUIRE(solution[i].first == fiveShortestPath[i].first);
        REQUIRE(solution[i].second == fiveShortestPath[i].second);
    }
}




TEST_CASE("100x100 Correct Shortest Path from top left to bottom right", "[weight=10][valgrind][3x3]") {
    // 3x3 maze is the grid of nodes created from the 3x3.txt dataset, where each number 1-9 represents a passable node with weight and each 0 represents the start and end
    // findPath will return a vector of nodes that represent the shortest path from pointA to pointB
    // 3x3shortestPath will be a vector of points that correspond to the shortest path from the top left most points (0,0) to the bottom left most point (5,0)
    Grid hundredGrid;
    hundredGrid.readFromFile("../data/100x100.txt", 0);
    hundredGrid.createPointMaze(99,99);
    Point start = hundredGrid(0,0);
    Point end = hundredGrid(99,99);


    BFSgrid bfsHundredGrid;
    bfsHundredGrid.readFromFile("../data/100x100.txt" , 0);
    bfsHundredGrid.createPointMaze();
    
    

    vector<pair<int,int>> solution = bfsHundredGrid.solveMaze(start, end);
    vector<pair<int,int>> hundredShortestPath = hundredGrid.solveMaze(start, end);
    for (size_t i = 0; i < solution.size(); i++) {
        REQUIRE(solution[i].first == hundredShortestPath[i].first);
        REQUIRE(solution[i].second == hundredShortestPath[i].second);
    }
}


/*
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