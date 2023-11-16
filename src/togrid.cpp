#include "togrid.h"

Grid::Grid() {
    columns  = 0;
    rows = 0;
}

void Grid::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    char digit; //creates 
    bool reachedNewLine = false;
    while (file >> digit) {
        if (digit == '0' || digit == '1') {
            maze_.push_back({digit - '0'});
            if (!reachedNewLine) {
                columns++;
            }
        } else if (digit == '\n') {
            reachedNewLine = true;
            rows++;
        }
    }
}


