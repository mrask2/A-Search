#include <catch2/catch_test_macros.hpp>
#include "Grid.h"
#include "BFSgrid.h"

#include <chrono>

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

TEST_CASE("3x3 Correct Shortest Path using BFS", "[weight=10][valgrind][3x3]") {
    // 3x3 maze is the grid of nodes created from the 3x3.txt dataset, where each number 1-9 represents a passable node with weight and each 0 represents the start and end
    // findPath will return a vector of nodes that represent the shortest path from pointA to pointB
    // 3x3shortestPath will be a vector of points that correspond to the shortest path from the top left most points (0,0) to the bottom left most point (5,0)
    Grid threeGrid;
    threeGrid.readFromFile("../data/3x3.txt", 0);
    threeGrid.createPointMaze(2,2);
    Point start = threeGrid(0,0);
    Point end = threeGrid(2,2);

    BFSgrid bfs;
    bfs.readFromFile("../data/3x3.txt" , 0);
    bfs.createPointMaze();

    vector<pair<int,int>> solution = bfs.solveMaze(start, end);
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
    Grid aSearch;
    aSearch.readFromFile("../data/5x5.txt", 0);
    aSearch.createPointMaze(4,4);
    Point start = aSearch(0,0);
    Point end = aSearch(4,4);

    vector<pair<int,int>> solution = {{0,0}, {0,1}, {1,1}, {1,2}, {2,2}, {2,3}, {3,3}, {3,4}, {4,4}};
    vector<pair<int,int>> shortestPath = aSearch.solveMaze(start, end);
    REQUIRE(solution.size() == shortestPath.size());
}


TEST_CASE("10x10 Correct Shortest Path from top left to bottom right", "[weight=10][valgrind][3x3]") {
    // 3x3 maze is the grid of nodes created from the 3x3.txt dataset, where each number 1-9 represents a passable node with weight and each 0 represents the start and end
    // findPath will return a vector of nodes that represent the shortest path from pointA to pointB
    // 3x3shortestPath will be a vector of points that correspond to the shortest path from the top left most points (0,0) to the bottom left most point (5,0)
    Grid aSearch;
    aSearch.readFromFile("../data/10x10.txt", 0);
    aSearch.createPointMaze(9,9);
    Point start = aSearch(0,0);
    Point end = aSearch(9,9);


    BFSgrid bfs;
    bfs.readFromFile("../data/10x10.txt", 0);
    bfs.createPointMaze();
    
    auto t1 = std::chrono::high_resolution_clock::now();
    vector<pair<int,int>> solution = bfs.solveMaze(start, end);
    auto t2 = std::chrono::high_resolution_clock::now();
    vector<pair<int,int>> shortestPath = aSearch.solveMaze(start, end);
    auto t3 = std::chrono::high_resolution_clock::now();


    auto ms_bfs = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    auto ms_astar = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2);
    std::cout << "BFS 10x10 "<< ms_bfs.count() << " ms\n";
    std::cout << "A* 10x10 "<< ms_astar.count() << " ms\n";


    REQUIRE(solution.size() == shortestPath.size());
}


TEST_CASE("100x100 Correct Shortest Path from top left to bottom right", "[weight=10][valgrind][3x3]") {
    // 3x3 maze is the grid of nodes created from the 3x3.txt dataset, where each number 1-9 represents a passable node with weight and each 0 represents the start and end
    // findPath will return a vector of nodes that represent the shortest path from pointA to pointB
    // 3x3shortestPath will be a vector of points that correspond to the shortest path from the top left most points (0,0) to the bottom left most point (5,0)
    Grid aSearch;
    aSearch.readFromFile("../data/100x100.txt", 0);
    aSearch.createPointMaze(99,99);
    Point start = aSearch(0,0);
    Point end = aSearch(99,99);


    BFSgrid bfs;
    bfs.readFromFile("../data/100x100.txt" , 0);
    bfs.createPointMaze();
    
    auto t1 = std::chrono::high_resolution_clock::now();
    vector<pair<int,int>> solution = bfs.solveMaze(start, end);
    auto t2 = std::chrono::high_resolution_clock::now();
    vector<pair<int,int>> shortestPath = aSearch.solveMaze(start, end);
    auto t3 = std::chrono::high_resolution_clock::now();

    auto ms_bfs = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    auto ms_astar = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2);
    std::cout << "BFS 100x100 "<< ms_bfs.count() << " ms\n";
    std::cout << "A* 100x100 "<< ms_astar.count() << " ms\n";


    REQUIRE(solution.size() == shortestPath.size());
    for (size_t i = 0; i < solution.size(); i++) {
        REQUIRE(solution[i].first == shortestPath[i].first);
        REQUIRE(solution[i].second == shortestPath[i].second);
    }
}


TEST_CASE("Sydney CSV to PNG", "[weight=10][valgrind][3x3]") {
    Grid aSearch;
    aSearch.readFromCSV("../data/Sydney_0_1024.csv", 1);
    cs225::PNG pic = aSearch.createPicture();
    pic.writeToFile("SydneyTemp.png");
}


TEST_CASE("Sydney Correct Shortest Path from top left to bottom right", "[weight=10][valgrind][3x3]") {
    // 3x3 maze is the grid of nodes created from the 3x3.txt dataset, where each number 1-9 represents a passable node with weight and each 0 represents the start and end
    // findPath will return a vector of nodes that represent the shortest path from pointA to pointB
    // 3x3shortestPath will be a vector of points that correspond to the shortest path from the top left most points (0,0) to the bottom left most point (5,0)
    Grid aSearch;
    aSearch.readFromCSV("../data/Sydney_0_1024.csv", 1);
    aSearch.createPointMaze(1023,1023);
    Point start = aSearch(0,0);
    Point end = aSearch(1023,1023);


    BFSgrid bfs;
    bfs.readFromCSV("../data/Sydney_0_1024.csv", 1);
    bfs.createPointMaze();

    auto t1 = std::chrono::high_resolution_clock::now();
    vector<pair<int,int>> solution = bfs.solveMaze(start, end);
    auto t2 = std::chrono::high_resolution_clock::now();
    vector<pair<int,int>> shortestPath = aSearch.solveMaze(start, end);
    auto t3 = std::chrono::high_resolution_clock::now();

    auto ms_bfs = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    auto ms_astar = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2);
    std::cout << "BFS Sydney took "<< ms_bfs.count() << " ms\n";
    std::cout << "A* Sydney took "<< ms_astar.count() << " ms\n";

    REQUIRE(solution.size() == shortestPath.size());
}


TEST_CASE("New York Correct Shortest Path from top left to bottom right", "[weight=10][valgrind][3x3]") {
    // 3x3 maze is the grid of nodes created from the 3x3.txt dataset, where each number 1-9 represents a passable node with weight and each 0 represents the start and end
    // findPath will return a vector of nodes that represent the shortest path from pointA to pointB
    // 3x3shortestPath will be a vector of points that correspond to the shortest path from the top left most points (0,0) to the bottom left most point (5,0)
    Grid aSearch;
    aSearch.readFromCSV("../data/NewYork_1_256.csv", 1);
    aSearch.createPointMaze(255,255);
    Point start = aSearch(0,0);
    Point end = aSearch(255,255);


    BFSgrid bfs;
    bfs.readFromCSV("../data/NewYork_1_256.csv", 1);
    bfs.createPointMaze();
    
    auto t1 = std::chrono::high_resolution_clock::now();
    vector<pair<int,int>> solution = bfs.solveMaze(start, end);
    auto t2 = std::chrono::high_resolution_clock::now();
    vector<pair<int,int>> shortestPath = aSearch.solveMaze(start, end);
    auto t3 = std::chrono::high_resolution_clock::now();

    auto ms_bfs = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    auto ms_astar = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2);
    std::cout << "BFS New York took "<< ms_bfs.count() << " ms\n";
    std::cout << "A* New York took "<< ms_astar.count() << " ms\n";

    cs225::PNG aPic = aSearch.createPicture();
    cs225::PNG bfsPic = bfs.createPicture();


    // aPic.writeToFile("AShaghaiTemp.png");
    // bfsPic.writeToFile("BFShangaiTemp.png");
    
    cs225::PNG bfsPath = bfs.drawPath(solution);
    cs225::PNG aPath = aSearch.drawPath(shortestPath);

    aPath.writeToFile("ASnewYork.png");
    bfsPath.writeToFile("BFSnewYork.png");

    REQUIRE(solution.size() == shortestPath.size());    
}

TEST_CASE("500x500 Timer", "[weight=10][valgrind][3x3]") {
    // 3x3 maze is the grid of nodes created from the 3x3.txt dataset, where each number 1-9 represents a passable node with weight and each 0 represents the start and end
    // findPath will return a vector of nodes that represent the shortest path from pointA to pointB
    // 3x3shortestPath will be a vector of points that correspond to the shortest path from the top left most points (0,0) to the bottom left most point (5,0)
    Grid aSearch;
    aSearch.readFromFile("../data/500x500.txt", 0);
    aSearch.createPointMaze(499,499);
    Point start = aSearch(0,0);
    Point end = aSearch(499,499);


    BFSgrid bfs;
    bfs.readFromFile("../data/500x500.txt", 0);
    bfs.createPointMaze();
    
    auto t1 = std::chrono::high_resolution_clock::now();
    vector<pair<int,int>> solution = bfs.solveMaze(start, end);
    auto t2 = std::chrono::high_resolution_clock::now();
    vector<pair<int,int>> shortestPath = aSearch.solveMaze(start, end);
    auto t3 = std::chrono::high_resolution_clock::now();


    auto ms_bfs = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    auto ms_astar = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2);
    std::cout << "BFS 500x500 "<< ms_bfs.count() << " ms\n";
    std::cout << "A* 500x500 "<< ms_astar.count() << " ms\n";


    REQUIRE(solution.size() == shortestPath.size());
}

TEST_CASE("5000x5000 Timer", "[weight=10][valgrind][3x3]") {
    // 3x3 maze is the grid of nodes created from the 3x3.txt dataset, where each number 1-9 represents a passable node with weight and each 0 represents the start and end
    // findPath will return a vector of nodes that represent the shortest path from pointA to pointB
    // 3x3shortestPath will be a vector of points that correspond to the shortest path from the top left most points (0,0) to the bottom left most point (5,0)
    Grid aSearch;
    aSearch.readFromFile("../data/5000x5000.txt", 0);
    aSearch.createPointMaze(4999,4999);
    Point start = aSearch(0,0);
    Point end = aSearch(4999,4999);


    BFSgrid bfs;
    bfs.readFromFile("../data/5000x5000.txt", 0);
    bfs.createPointMaze();
    
    auto t1 = std::chrono::high_resolution_clock::now();
    vector<pair<int,int>> solution = bfs.solveMaze(start, end);
    auto t2 = std::chrono::high_resolution_clock::now();
    vector<pair<int,int>> shortestPath = aSearch.solveMaze(start, end);
    auto t3 = std::chrono::high_resolution_clock::now();


    auto ms_bfs = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    auto ms_astar = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2);
    std::cout << "BFS 5000x5000 "<< ms_bfs.count() << " ms\n";
    std::cout << "A* 5000x5000 "<< ms_astar.count() << " ms\n";


    REQUIRE(solution.size() == shortestPath.size());
}