#ifndef POINTS_H
#define POINTS_H

#include <utility>
#include <vector>
#include "point.h"
#include "index.h"

typedef double (*funcPtr)(double);

extern std::vector<std::vector<bool>> points;
extern int totalPoints;

Index coordToIndex(const Point& coordinate, funcPtr roundFunc = round);
Point indexToCoord(const Index& index);
void fillPoints(bool countPoints = false);

#endif