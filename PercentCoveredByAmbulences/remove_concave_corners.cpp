#include "remove_concave_corners.h"
#include "check_if_inside.h"

#include <iostream>

static constexpr int prevIndex(const int index, const int size)
{
	return index - 1 >= 0 ? index - 1 : size - 1;
}

static constexpr int nextIndex(const int index, const int size)
{
	return (index + 1) % size;
}

static int calculateDirection(const Polygon& polygon)
{
	double sum = 0;
	for (int i = 0; i < polygon.size(); i++)
	{
		const int nextInd = nextIndex(i, polygon.size());
		sum += (polygon[nextInd].lon - polygon[i].lon) * (polygon[nextInd].lat + polygon[i].lat);
	}
	if (sum == 0) return 0; // Colinear
	if (sum < 0) return 2; // CCW
	return 1; // CW
}


static void removeIndexes(Polygon& polygon, const int start, const int end)
{
	if (start < end)
	{
		polygon.erase(polygon.begin() + start, polygon.begin() + end);
	}
	else
	{
		polygon.erase(polygon.begin() + start, polygon.end());
		polygon.erase(polygon.begin(), polygon.begin() + end);
	}
}

void removeConcaveCorners(Polygon& polygon)
{
	// If the polygon has less than 4 vertexes then it already has all the inside corners removed
	if (polygon.size() < 4)
	{
		return;
	}

	int polygonDirection = calculateDirection(polygon);
	if (polygonDirection == 0)
	{
		throw std::runtime_error("The polygon is colinear????");
	}
	for (int i = 0; i < polygon.size(); i++)
	{
		int startInd = prevIndex(i, polygon.size()); // The index of the point before i
		int middleInd = i; // The index of the point at i
		int endInd = nextIndex(i, polygon.size()); // The index of the point after i
		int pointDirection = calculateDirection(polygon[startInd], polygon[middleInd], polygon[endInd]);
		while (pointDirection != polygonDirection)
		{
			startInd = prevIndex(startInd, polygon.size());
			middleInd = prevIndex(middleInd, polygon.size());
			pointDirection = calculateDirection(polygon[startInd], polygon[middleInd], polygon[endInd]);
		}
		int startRemove = middleInd;

		startInd = prevIndex(i, polygon.size()); // The index of the point before i
		middleInd = i; // The index of the point at i
		endInd = nextIndex(i, polygon.size()); // The index of the point after i
		pointDirection = calculateDirection(polygon[startInd], polygon[middleInd], polygon[endInd]);
		while (pointDirection != polygonDirection)
		{
			middleInd = nextIndex(middleInd, polygon.size());
			endInd = nextIndex(endInd, polygon.size());
			pointDirection = calculateDirection(polygon[startInd], polygon[middleInd], polygon[endInd]);
		}
		int endRemove = endInd;

		removeIndexes(polygon, startRemove, endRemove);
	}
}

void removeConcaveCorners(std::vector<Polygon>& polygons)
{
	for (Polygon& polygon : polygons)
	{
		removeConcaveCorners(polygon);
	}
}