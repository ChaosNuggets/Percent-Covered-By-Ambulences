//// Uses the data in the TravelTimes folder to calculate the coverage
//#include <iostream>
//#include <iomanip>
//#include <string>
//#include "station_coordinates.h"
//#include "get_test_bounds.h"
//#include "constants.h"
//#include "point_map.h"
//#include "extract_polygons.h"
//#include "check_if_inside.h"
//#include "remove_concave_corners.h"
//
//static bool setPoints(const int stationNum)
//{
//    // Extract the indexes of the box corners
//    const auto [lowCorner, highCorner] = getTestIndexBounds(stationCoordinates[stationNum], BOX_RADIUS);
//    const auto [lowLatIndex, lowLongIndex] = lowCorner;
//    const auto [highLatIndex, highLongIndex] = highCorner;
//
//    for (int i = lowLatIndex; i <= highLatIndex; i++)
//    {
//        for (int j = lowLongIndex; j <= highLongIndex; j++)
//        {
//            Point testPoint = indexToCoord({ i, j });
//            if (checkIfInside(isochrones[stationNum], testPoint))
//            {
//                points[i][j] = COVERED;
//            }
//        }
//    }
//    return true;
//}
//
//static std::tuple<long double, int, int> calculateCoverage()
//{
//    int pointsCovered = 0;
//    int pointsTotal = 0;
//    for (int i = 0; i < LAT_SIZE; i++)
//    {
//        for (int j = 0; j < LONG_SIZE; j++)
//        {
//            if (points[i][j] == COVERED)
//            {
//                pointsCovered++;
//                pointsTotal++;
//            }
//            else if (points[i][j] == NOT_COVERED)
//            {
//                pointsTotal++;
//            }
//        }
//    }
//    const long double coverage = (long double) pointsCovered / pointsTotal;
//    return { coverage, pointsCovered, pointsTotal };
//}
//
//int main()
//{
//    fillPoints();
//    extractPolygons();
//    removeConcaveCorners(isochrones);
//
//    for (int i = 0; i < stationCoordinates.size(); i++)
//    {
//        bool success = setPoints(i);
//        if (!success)
//        {
//            return 1;
//        }
//	}
//    // Calculate and print coverage
//    auto [coverage, pointsCovered, pointsTotal] = calculateCoverage();
//    std::cout << std::setprecision(10);
//    std::cout << "Coverage: " << coverage * 100 << "% (" << pointsCovered << '/' << pointsTotal << ")\n";
//
//    // Print Indiana point map
//    for (int i = points.size() - 1; i >= 0; i--)
//    {
//        for (uint8_t point : points[i])
//        {
//            if (point == 1)
//            {
//                std::cout << 'O';
//            }
//            else if (point == 2)
//            {
//                std::cout << '.';
//            }
//            else
//            {
//                std::cout << ' ';
//            }
//        }
//        std::cout << '\n';
//    }
//
//    std::cout << "Press enter to exit";
//    std::cin.ignore();
//    return 0;
//}