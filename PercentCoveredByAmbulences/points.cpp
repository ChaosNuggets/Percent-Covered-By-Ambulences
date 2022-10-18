#define _USE_MATH_DEFINES
#include "points.h"
#include "constants.h"
#include "get_test_bounds.h"
#include "calculate_distance.h"
#include <cmath>

std::vector<std::vector<bool>> points; // The point map, true if active and false if not active (all the points in Indiana start as true)
int totalPoints; // The total number of points in Indiana

std::pair<int, int> coordToIndex(const std::pair<double, double>& coordinate, funcPtr roundFunc)
{
    const auto& [latitude, longitude] = coordinate; // Extract data

    // Calculate the coordinate's difference in miles from LOWEST_LAT and LOWEST_LONG
    const double latMileDifference = (latitude - LOWEST_LAT) / LAT_IN_1_MILE;
    const double longMileDifference = calculateDistance({ latitude, LOWEST_LONG }, coordinate);

    // Round the difference so it's an integer
    int latIndex = roundFunc(latMileDifference / MILES_BETWEEN_POINTS); // Also why is round not constexpr aaaaa
    int longIndex = roundFunc(longMileDifference / MILES_BETWEEN_POINTS);

    return { latIndex, longIndex };
}

std::pair<double, double> indexToCoord(const std::pair<int, int>& index)
{
    const auto [latIndex, longIndex] = index; // Extract data

    // Do the conversion
    const double latitude = calcCoordLat({ LOWEST_LAT, 0 }, latIndex * MILES_BETWEEN_POINTS);
    const double longitude = calcCoordLong({ latitude, LOWEST_LONG }, longIndex * MILES_BETWEEN_POINTS);

    return { latitude, longitude };
}

void fillPoints(bool countPoints)
{
    // Resizes points to be a 2d matrix of points of size latSize by longSize
    points.resize(LAT_SIZE, std::vector<bool>(LONG_SIZE, false));
    
    if (countPoints)
    {
        totalPoints = 0;
    }
    // These are the coordinates of vertexes of the polygon that make up the Indiana border
    const std::vector<std::pair<double, double>> indianaBorder =
    {
        {41.712028, -87.524126},
        {41.690771, -87.400318},
        {41.639333, -87.399395},
        {41.760356, -86.826046},
        {41.760173, -84.805966},
        {39.105683, -84.820450},
        {38.783325, -84.812752},
        {38.716382, -85.451102},
        {38.262720, -85.749565},
        {37.957369, -86.043145},
        {38.195959, -86.364906},
        {37.840126, -86.647414},
        {37.998914, -86.823140},
        {37.779567, -87.111361},
        {37.972504, -87.594365},
        {37.789831, -88.057587},
        {38.266599, -87.977350},
        {38.755578, -87.498621},
        {39.136105, -87.658967},
        {39.371112, -87.531690},
        {41.712028, -87.524126}
    };

    // Make 2 for loops which go from LOWEST_LAT and LOWEST_LONG to HIGHEST_LAT and HIGHEST_LONG
    // If the point is inside the polyline border, set it to true

    //for (auto& rectangleCornerSet : rectangleCorners)
    //{
    //    // Extract data
    //    const double lowLat = rectangleCornerSet.first.first;
    //    const double highLat = rectangleCornerSet.second.first;
    //    const double lowLong = rectangleCornerSet.first.second;
    //    const double highLong = rectangleCornerSet.second.second;

    //    const auto [lowLatIndex, lowLongIndex] = coordToIndex({ lowLat, lowLong });
    //    const auto [highLatIndex, highLongIndex] = coordToIndex({ highLat, highLong });
    //    
    //    // Fill the points to be spaced less than MILES_BETWEEN_POINTS apart
    //    for (int i = lowLatIndex; i <= highLatIndex; i++)
    //    {
    //        for (int j = lowLongIndex; j <= highLongIndex; j++)
    //        {
    //            if (countPoints)
    //            {   
    //                totalPoints++;
    //            }
    //            points[i][j] = true;
    //        }
    //    }
    //}
}