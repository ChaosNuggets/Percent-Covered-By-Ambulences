//#include <iostream>
//#include <iomanip>
//#include <fstream>
//#include <string>
//#include "station_coordinates.h"
//#include "get_test_bounds.h"
//#include "constants.h"
//#include "points.h"
//
//std::string generateFilePath(const int stationNum)
//{
//    std::string filePath = "TravelTimes/";
//    filePath.append(std::to_string(stationNum));
//    filePath.append(".txt");
//    return filePath;
//}
//
//static bool setPoints(const int stationNum)
//{
//    // Open file for police station #stationNum
//    const std::string filePath = generateFilePath(stationNum);
//    std::ifstream fin(filePath.c_str());
//    if (!fin.is_open())
//	{
//		std::cout << "unable to open " << filePath;
//		return false;
//	}
//
//    // Extract the indexes of the box corners
//    const auto [lowCorner, highCorner] = getTestIndexBounds(stationCoordinates[stationNum], BOX_RADIUS);
//    const auto [lowLatIndex, lowLongIndex] = lowCorner;
//    const auto [highLatIndex, highLongIndex] = highCorner;
//
//    //std::cout << stationNum << '\n';
//    //std::cout << lowLatIndex << ' ' << highLatIndex << '\n';
//    //std::cout << lowLongIndex << ' ' << highLongIndex << "\n\n";
//
//    for (int i = lowLatIndex; i <= highLatIndex; i++)
//    {
//        for (int j = lowLongIndex; j <= highLongIndex; j++)
//        {
//            std::string line;
//            std::getline(fin, line);
//            const int time = stoi(line);
//            if (time <= 300)
//            {
//                points[i][j] = false;
//            }
//        }
//    }
//    return true;
//}
//
//static std::pair<long double, int> calculateCoverage()
//{
//    int pointsNotCovered = 0;
//    for (int i = 0; i < LAT_SIZE; i++)
//    {
//        for (int j = 0; j < LONG_SIZE; j++)
//        {
//            if (points[i][j])
//            {
//                pointsNotCovered++;
//            }
//        }
//    }
//    const int pointsCovered = totalPoints - pointsNotCovered;
//    const long double coverage = (long double) pointsCovered / totalPoints;
//    return { coverage, pointsCovered };
//}
//
//int main()
//{
//    fillPoints(true);
//    for (int i = 0; i < stationCoordinates.size(); i++)
//    {
//        bool success = setPoints(i);
//        if (!success)
//        {
//            return 1;
//        }
//	}
//    // Calculate and print coverage
//    auto [coverage, pointsCovered] = calculateCoverage();
//    std::cout << std::setprecision(10);
//    std::cout << "Coverage: " << coverage * 100 << "% (" << pointsCovered << '/' << totalPoints << ")\n";
//    
//    //// Print Indiana point map
//    //for (int i = points.size() - 1; i >= 0; i--)
//    //{
//    //    for (bool point : points[i])
//    //    {
//    //        if (point)
//    //        {
//    //            std::cout << 'O';
//    //        }
//    //        else
//    //        {
//    //            std::cout << ' ';
//    //        }
//    //    }
//    //    std::cout << '\n';
//    //}
//
//    std::cout << "Press enter to exit";
//    std::cin.ignore();
//    return 0;
//}