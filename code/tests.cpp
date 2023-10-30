TEST_CASE("6x3 Correct Shortest Path from top left to bottom left") {
// 6x3maze is the grid of nodes created from the 6x3maze.txt dataset, where each 1 represents a passable node and each 0 represents an obstacle
// findPath will return a vector of nodes that represent the shortest path from pointA to pointB
// 6x3shortestPath will be a vector of points that correspond to the shortest path from the top left most points (0,0) to the bottom left most point (5,0)   
   REQUIRE findPath(6x3maze, pointA, pointB) == 6x3shortestPath;
}

TEST_CASE("3x3 Correct Heuristic Calculations") {

// creating a grid from the 3x3maze.txt image
Grid threeGrid = toGrid(3x3maze.txt); 

Point startPoint;
Point midPoint;
Point endPoint;
startPoint.h_ = val0 //expected h value of startPoint
midPoint.h_  = val1   //expected h value of midPoint
endPoint.h_ = val2 // expected h value of endPoint

// creating a vector of points with known heuristics
vector<Point> knownHeuristics = {startPoint, midPoint, endPoint}; // example known heuristic value for startPoint


// Calculate and compare heuristic values for each point
for (const auto& point: knownHeuristics) {

    double expectedHeuristic = point.h_; //h_ is the heursitic value
    
    double calculatedHeuristic = getHeuristic(testPoint, startPoint, endPoint);
    
    // Check if the calculated heuristic matches the expected value
    REQUIRE(calculatedHeuristic == expectedHeuristic);
}
}


TEST_CASE("Straight Path with No Obstacles") {
    // testing on a straight path with no obstacles
    REQUIRE findPath(emptyMaze, startPoint, endPoint) == straightPath;
}