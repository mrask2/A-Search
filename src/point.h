#pragma once

class Point {
    public:
        Point(); 
        Point(int weight_, double h); 
        void setG(double g); 
        double getF();
        double getG();
        double getH();
    private:
        int weight_ = 0; // weight of the node
        double f_ = 0; // total cost
        double g_ = 0; // cost to get to this point
        double h_ = 0; // heuristic value
};