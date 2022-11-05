// Uses the data in the RawData folder to calculate the coverage
#include <iostream>
#include <iomanip>
#include <string>
#include "station_coordinates.h"
#include "get_test_bounds.h"
#include "constants.h"
#include "point_map.h"
#include "extract_polygons.h"
#include "check_if_inside.h"
#include "remove_concave_corners.h"

static void changePointsAmbulance(const int stationNum)
{
    // Extract the indexes of the box corners
    const auto [lowCorner, highCorner] = getTestIndexBounds(stationCoordinates[stationNum], AMBULANCE_BOX_RADIUS);
    const auto [lowLatIndex, lowLongIndex] = lowCorner;
    const auto [highLatIndex, highLongIndex] = highCorner;

    for (int i = lowLatIndex; i <= highLatIndex; i++)
    {
        for (int j = lowLongIndex; j <= highLongIndex; j++)
        {
            if (points[i][j] == OUTSIDE)
            {
                continue;
            }

            Point testPoint = indexToCoord({ i, j });

            if (checkIfInside(isochrones[stationNum], testPoint))
            {
                points[i][j] = COVERED_BY_AMBULANCE;
            }
        }
    }
}

static void changePointsAmbulance()
{
    for (int i = 0; i < stationCoordinates.size(); i++)
    {
        changePointsAmbulance(i);
    }
}

static std::tuple<long double, int, int> calculateCoverage()
{
    int pointsCovered = 0;
    int pointsTotal = 0;
    for (int i = 0; i < LAT_SIZE; i++)
    {
        for (int j = 0; j < LONG_SIZE; j++)
        {
            if (points[i][j] == NOT_COVERED)
            {
                pointsTotal++;
            }
            else if (points[i][j] == COVERED_BY_AMBULANCE)
            {
                pointsCovered++;
                pointsTotal++;
            }
        }
    }
    const long double coverage = (long double) pointsCovered / pointsTotal;
    return { coverage, pointsCovered, pointsTotal };
}

static void printCoverage(const long double coverage, const int pointsCovered, const int pointsTotal)
{
    std::cout << std::setprecision(10);
    std::cout << "Coverage: " << coverage * 100 << '%';
    std::cout << " (" << pointsCovered << '/' << pointsTotal << ')';
    std::cout << '\n';
}

static void printPointMap()
{
    for (int i = points.size() - 1; i >= 0; i--)
    {
        for (uint8_t point : points[i])
        {
            if (point == NOT_COVERED)
            {
                std::cout << 'O';
            }
            else if (point == COVERED_BY_AMBULANCE)
            {
                std::cout << '.';
            }
            else
            {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
}

int main()
{
    extractPolygons();
    removeConcaveCorners(isochrones);
    fillPoints();

    changePointsAmbulance();
    const auto [coverage, pointsCovered, pointsTotal] = calculateCoverage();

    printCoverage(coverage, pointsCovered, pointsTotal);
    printPointMap();

    return 0;
}