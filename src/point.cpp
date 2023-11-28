#include "point.h"

Point::Point() {}

Point::Point(int weight, double h) : weight_(weight), h_(h) {}

void Point::setG(double g) {
    g_ = g;
    f_ = g_ + h_;
}

double Point::getF() {
    return f_;
}

double Point::getG() {
    return g_;
}

double Point::getH() {
    return h_;
}