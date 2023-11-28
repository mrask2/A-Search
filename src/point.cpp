#include "point.h"

Point::Point() {}

Point::Point(int x, int y, int weight, double h) : x_(x), y_(y), weight_(weight), h_(h) {}

void Point::setG(double g) {
    g_ = g;
    f_ = g_ + h_;
}