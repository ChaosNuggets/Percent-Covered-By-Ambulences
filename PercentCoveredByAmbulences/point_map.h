#ifndef POINTS_H
#define POINTS_H

#include <utility>
#include <vector>
#include "point_struct.h"

typedef double (*funcPtr)(double);

extern std::vector<std::vector<bool>> points;
extern int totalPoints;

std::pair<int, int> coordToIndex(const std::pair<double, double>& coordinate, funcPtr roundFunc = round);
Point indexToCoord(const std::pair<int, int>& index);
void fillPoints(bool countPoints = false);

#endif