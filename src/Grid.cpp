#include "Grid.h"

Grid::Grid() {
    columns  = 0;
    rows = 0;
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
        columns = row.size(); 
        ++rows;
    }
}

void


