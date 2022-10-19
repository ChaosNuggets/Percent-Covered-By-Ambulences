#ifndef GET_TEST_BOUNDS_H
#define GET_TEST_BOUNDS_H

#include <utility>
#include "point.h"

double calcCoordLong(const Point& coordinate, const double distance);
constexpr double calcCoordLat(const Point& coordinate, const double distance);
std::pair<std::pair<int, int>, std::pair<int, int>> getTestIndexBounds(const Point& stationCoordinate, const double boxRadius);

#endif