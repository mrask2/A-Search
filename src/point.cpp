#include "point.h"

Point::Point() {}

Point::Point(int weight, double h) : weight_(weight), h_(h) {}

void Point::setG(double g) {
    g_ = g;
    f_ = g_ + h_;
}