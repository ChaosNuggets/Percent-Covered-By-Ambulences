#define _USE_MATH_DEFINES
#include "points.h"
#include "constants.h"
#include "get_test_bounds.h"
#include "calculate_distance.h"
#include <cmath>


#include <iostream>

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
    // These are the coordinates of corners of rectangles that make up the points in Indiana
    const std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>> rectangleCorners =
    {
        {{39.105480, -87.523661}, {41.759907, -84.820157}},
        {{39.056190, -87.571926}, {39.105480, -84.897566}},
        {{38.792125, -87.495200}, {39.056190, -84.897566}},
        {{38.468242, -87.495200}, {38.792125, -85.498866}},
        {{38.288894, -87.730132}, {38.468242, -85.697890}},
        {{38.198666, -87.834796}, {38.288894, -85.885433}},
        {{37.999366, -87.910623}, {38.198666, -86.525765}},
        {{38.016023, -86.190050}, {38.198666, -85.932822}}
    };

    for (auto& rectangleCornerSet : rectangleCorners)
    {
        // Extract data
        const double lowLat = rectangleCornerSet.first.first;
        const double highLat = rectangleCornerSet.second.first;
        const double lowLong = rectangleCornerSet.first.second;
        const double highLong = rectangleCornerSet.second.second;

        const auto [lowLatIndex, lowLongIndex] = coordToIndex({ lowLat, lowLong });
        const auto [highLatIndex, highLongIndex] = coordToIndex({ highLat, highLong });
        
        // Fill the points to be spaced less than MILES_BETWEEN_POINTS apart
        for (int i = lowLatIndex; i <= highLatIndex; i++)
        {
            for (int j = lowLongIndex; j <= highLongIndex; j++)
            {
                if (countPoints)
                {   
                    totalPoints++;
                }
                points[i][j] = true;
            }
        }
    }
}