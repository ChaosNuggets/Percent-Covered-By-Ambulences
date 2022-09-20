#ifndef GET_TEST_BOUNDS_H
#define GET_TEST_BOUNDS_H

#include <utility>

std::pair<std::pair<int, int>, std::pair<int, int>> getTestIndexBounds(const std::pair<double, double>& stationCoordinate, const double radiusOfCircles);

#endif