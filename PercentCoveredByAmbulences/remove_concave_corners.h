#ifndef REMOVE_CONCAVE_CORNERS_H
#define REMOVE_CONCAVE_CORNERS_H

#include "polygon.h"

void removeConcaveCorners(Polygon& polygon);
void removeConcaveCorners(std::vector<Polygon>& polygons);

#endif