#pragma once

#include <cmath>

class Point {
    public:
        Point(); 
        Point(int weight, double h); 
        void setG(double g); 
        int getWeight() const { return weight_; }
        double getF() const { return f_; }
        double getG() const { return g_; }
        double getH() const { return h_; }
    private:
        int weight_ = 0; // weight of the node
        double f_ = 0; // total cost
        double g_ = 0; // cost to get to this point
        double h_ = 0; // heuristic value
};

