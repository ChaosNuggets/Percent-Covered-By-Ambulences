#ifndef GET_TEST_BOUNDS_H
#define GET_TEST_BOUNDS_H

#include <utility>

double calcCoordLong(const std::pair<double, double>& coordinate, const double distance);
constexpr double calcCoordLat(const std::pair<double, double>& coordinate, const double distance);
std::pair<std::pair<int, int>, std::pair<int, int>> getTestIndexBounds(const std::pair<double, double>& stationCoordinate, const double boxRadius);

#endif