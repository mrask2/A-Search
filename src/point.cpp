#include "point.h"

Point::Point() {}

Point::Point(int x, int y, int weight, int h) : x_(x), y_(y), weight_(weight), h_(h) {}

void Point::setG(int g) {
    g_ = g;
    f_ = g_ + h_;
}