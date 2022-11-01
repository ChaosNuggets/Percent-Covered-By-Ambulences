// Uses the data in the TravelTimes folder to calculate the coverage
#include <iostream>
#include <iomanip>
#include <string>
#include "station_coordinates.h"
#include "get_test_bounds.h"
#include "constants.h"
#include "point_map.h"
#include "extract_polygons.h"

static bool setPoints(const int stationNum)
{
    // Extract the indexes of the box corners
    const auto [lowCorner, highCorner] = getTestIndexBounds(stationCoordinates[stationNum], BOX_RADIUS);
    const auto [lowLatIndex, lowLongIndex] = lowCorner;
    const auto [highLatIndex, highLongIndex] = highCorner;

    for (int i = lowLatIndex; i <= highLatIndex; i++)
    {
        for (int j = lowLongIndex; j <= highLongIndex; j++)
        {
            std::string line;
            std::getline(fin, line);
            const int time = stoi(line);
            if (time <= 300)
            {
                points[i][j] = false;
            }
        }
    }
    return true;
}

static std::pair<long double, int> calculateCoverage()
{
    int pointsNotCovered = 0;
    for (int i = 0; i < LAT_SIZE; i++)
    {
        for (int j = 0; j < LONG_SIZE; j++)
        {
            if (points[i][j])
            {
                pointsNotCovered++;
            }
        }
    }
    const int pointsCovered = totalPoints - pointsNotCovered;
    const long double coverage = (long double) pointsCovered / totalPoints;
    return { coverage, pointsCovered };
}

int main()
{
    fillPoints(true);
    extractPolygons();

    for (int i = 0; i < stationCoordinates.size(); i++)
    {
        bool success = setPoints(i);
        if (!success)
        {
            return 1;
        }
	}
    // Calculate and print coverage
    auto [coverage, pointsCovered] = calculateCoverage();
    std::cout << std::setprecision(10);
    std::cout << "Coverage: " << coverage * 100 << "% (" << pointsCovered << '/' << totalPoints << ")\n";
    
    //// Print Indiana point map
    //for (int i = points.size() - 1; i >= 0; i--)
    //{
    //    for (bool point : points[i])
    //    {
    //        if (point)
    //        {
    //            std::cout << 'O';
    //        }
    //        else
    //        {
    //            std::cout << ' ';
    //        }
    //    }
    //    std::cout << '\n';
    //}

    std::cout << "Press enter to exit";
    std::cin.ignore();
    return 0;
}