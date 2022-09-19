#define _USE_MATH_DEFINES
#include "points.h"
#include "constants.h"
#include <cmath>

//This convoluted line creates a 2d matrix of points of size LATSIZE by LONGSIZE
std::vector<std::vector<bool>> points(LATSIZE, std::vector<bool>(LONGSIZE, false));
int totalPoints; // The total number of points in Indiana
bool firstTimeFilling = true;

std::pair<int, int> coordToIndex(const std::pair<float, float>& coordinate)
{
    const auto [latitude, longitude] = coordinate; // Extract data

    // Calculate the coordinate's difference in miles from LOWEST_LAT and LOWEST_LONG
    const float latMileDifference = (latitude - LOWEST_LAT) / LAT_IN_1_MILE;
    const float longMileDifference = (longitude - LOWEST_LONG) / LONG_IN_1_MILE;

    // Round the difference so it's an integer
    int latIndex = round(latMileDifference / MILES_BETWEEN_POINTS); // Also why is round not constexpr aaaaa
    int longIndex = round(longMileDifference / MILES_BETWEEN_POINTS);

    return { latIndex, longIndex };
}

std::pair<float, float> indexToCoord(const std::pair<int, int>& index)
{
    const auto [latIndex, longIndex] = index; // Extract data

    // Do the conversion
    const float latitude = latIndex * LAT_IN_1_MILE * MILES_BETWEEN_POINTS + LOWEST_LAT;
    const float longitude = longIndex * LONG_IN_1_MILE * MILES_BETWEEN_POINTS + LOWEST_LONG;

    return { latitude, longitude };
}

void fillPoints()
{
    // These are the coordinates of corners of rectangles that make up the points in Indiana
    const std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> rectangleCorners =
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
        const float lowLat = rectangleCornerSet.first.first;
        const float highLat = rectangleCornerSet.second.first;
        const float lowLong = rectangleCornerSet.first.second;
        const float highLong = rectangleCornerSet.second.second;

        const auto [lowLatIndex, lowLongIndex] = coordToIndex({ lowLat, lowLong });
        const auto [highLatIndex, highLongIndex] = coordToIndex({ highLat, highLong });

        // Fill the points to be spaced less than MILES_BETWEEN_POINTS apart
        for (int i = lowLatIndex; i <= highLatIndex; i++)
        {
            for (int j = lowLongIndex; j <= highLongIndex; j++)
            {
                if (firstTimeFilling)
                {
                    totalPoints++;
                }
                points[i][j] = true;
            }
        }
    }
    firstTimeFilling = false;
}