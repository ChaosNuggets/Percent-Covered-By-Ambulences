#define _USE_MATH_DEFINES
#include <cmath>
#include "point_map.h"
#include "constants.h"
#include "angle_conversions.h"
#include "get_test_bounds.h"

double calcCoordLong(const Point& coordinate, const double distance)
{
    auto [latitude, longitude] = coordinate; // Extract latitude and longitude from coordinate

    //Convert coordinates to radians
    latitude = toRadians(latitude);
    longitude = toRadians(longitude);

    // Stupid formula
    double difference = acos((cos(distance / 3963) - pow(sin(latitude), 2)) / pow(cos(latitude), 2));

    // Make difference negative if distance is negative
    if (distance < 0) difference *= -1;

    return toDegrees(longitude + difference);
}

constexpr double calcCoordLat(const Point& coordinate, const double distance)
{
    const double difference = distance * LAT_IN_1_MILE; // Not stupid formula
    return coordinate.lat + difference;
}

static std::pair<Point, Point> getTestCoordinateBounds(const Point& stationCoordinate, const double boxRadius)
{
    const double highLat = calcCoordLat(stationCoordinate, boxRadius);
    const double lowLat = calcCoordLat(stationCoordinate, -boxRadius);
    const double highLong = calcCoordLong(stationCoordinate, boxRadius);
    const double lowLong = calcCoordLong(stationCoordinate, -boxRadius);
    return { {lowLat, lowLong}, {highLat, highLong} };
}

// Returns the corners of the rectangles of the indexes you should test
std::pair<Index, Index> getTestIndexBounds(const Point& stationCoordinate, const double boxRadius)
{
    //Extract the corners from the coordinate bounds
    const auto [lowCorner, highCorner] = getTestCoordinateBounds(stationCoordinate, boxRadius);

    //Calculate the index bounds
    auto [lowLat, lowLong] = coordToIndex(lowCorner, floor);
    auto [highLat, highLong] = coordToIndex(highCorner, ceil);

    // Don't test indexes that are out of bounds of the points matrix
    if (lowLat < 0) lowLat = 0;
    if (lowLong < 0) lowLong = 0;
    if (highLat >= LAT_SIZE) highLat = LAT_SIZE - 1;
    if (highLong >= LONG_SIZE) highLong = LONG_SIZE - 1;

    return { {lowLat, lowLong}, {highLat, highLong} };
}