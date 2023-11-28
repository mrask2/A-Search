#pragma once

#include <utility>
#include <limits>

class Point {
    public:
        Point(); 
        Point(int x, int y, int weight, double h); 
        void setG(double g);
        void setXY(int x, int y) { x_ = x; y_ = y; }
        std::pair<int,int> getXY() const { return std::make_pair(x_, y_); }

        void setCameFrom(Point* cameFrom) { cameFrom_ = cameFrom; }
        Point* getCameFrom() const { return cameFrom_; }

        int getWeight() const { return weight_; }
        double getF() const { return f_; }
        double getG() const { return g_; }
        double getH() const { return h_; }

        bool operator<(const Point& rhs) const {
            return f_ < rhs.f_;
        }
        bool operator>(const Point& rhs) const {
            return f_ > rhs.f_;
        }
        bool positionEquals(const Point& rhs) const {
            return x_ == rhs.x_ && y_ == rhs.y_;
        }

        bool in_open_set = false;

    private:
        int x_ = 0;
        int y_ = 0;
        Point* cameFrom_ = nullptr;
        int weight_ = 0; // weight of the node
        double f_ = 0; // total cost
        double g_ = std::numeric_limits<double>::max(); // cost to get to this point
        double h_ = 0; // heuristic value
};

