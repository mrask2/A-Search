#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Grid {
    public:
    Grid(); // empty constructor
    void readFromFile(const std::string& filename); // constructs 2d array from file
    
    private:
        std::vector<std::vector<int>> maze_;
        size_t rows;
        size_t columns;
        
};