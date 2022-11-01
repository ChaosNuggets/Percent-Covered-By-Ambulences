#ifndef EXTRACT_POLYGONS_H
#define EXTRACT_POLYGONS_H

#include <vector>
#include "point.h"

typedef std::vector<Point> Polygon;
extern std::vector<Polygon> isochrones;
void extractPolygons();

#endif