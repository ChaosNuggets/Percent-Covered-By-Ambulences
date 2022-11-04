#include "remove_inside_corners.h"
#include "check_if_inside.h"
#include <cmath>

static const double PI = 3.1415926535897932384626;

static constexpr double calculateDistance(Point a, Point b)
{
	return hypot(a.lat - b.lat, a.lon - b.lon);
}

static double calculateAngle(Point a, Point b, Point c)
{
	// Use dot product
	a = 
}

struct VertexData
{
	int direction;
	int angle;
	int distance; // The distance from polygon[i] to polygon[j]

	void calculateData(const Point& insidePoint, const Point vertexA, const Point vertexB)
	{
		this->direction = calculateDirection(insidePoint, vertexA, vertexB);
		this->angle = calculateAngle(insidePoint, vertexA, vertexB);
		this->distance = calculateDistance(vertexA, vertexB);
	}
};

static constexpr int nextIndex(int index, int size)
{
	return (index + 1) % size;
}

int findBiggestAngleIndex(const Polygon& polygon, const Point& insidePoint, const int i)
{
	// i is the vertex we are keeping constant
	// j is the vertex we are incrementing
	int j = nextIndex(i, polygon.size()); // The index of the second vertex to test

	VertexData current;
	current.calculateData(insidePoint, polygon[i], polygon[j]);

	VertexData prev;

	int insideDistance = calculateDistance(insidePoint, polygon[i]); // The distance from the inside point to polygon[i]
	int biggestAngle = current.angle;
	int biggestAngleIndex = j;

	do
	{
		j = nextIndex(j, polygon.size());

		prev = current;
		current.calculateData(insidePoint, polygon[i], polygon[j]);

		if (current.angle > biggestAngle)
		{
			biggestAngle = current.angle;
			biggestAngleIndex = j;
		}
	} while (
		prev.direction != current.direction &&
		prev.distance > insideDistance && current.distance > insideDistance &&
		prev.angle < PI / 2 && current.angle < PI / 2
		);

	return biggestAngleIndex;
}

static void removeInsideCorners(Polygon& polygon, const int start, const int end)
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

static void removeInsideCorners(Polygon& polygon, const Point& insidePoint)
{
	// If the polygon has less than 4 vertexes then it already has all the inside corners removed
	if (polygon.size() < 4)
	{
		return;
	}
	for (int i = 0; i < polygon.size(); i++)
	{
		int startRemovingIndex = nextIndex(i, polygon.size());
		int stopRemovingIndex = findBiggestAngleIndex(polygon, insidePoint, i);

		// Remove all the points between i and biggestAngleIndex (not inclusive)
		removeInsideCorners(polygon, startRemovingIndex, stopRemovingIndex);
	}
}