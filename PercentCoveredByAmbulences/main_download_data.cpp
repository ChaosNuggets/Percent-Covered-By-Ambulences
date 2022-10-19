//// Program to get the api data
//#include "get_api_data.h"
//#include "point_map.h"
//#include "constants.h"
//#include "station_coordinates.h"
//#include "get_test_bounds.h"
//#include <iostream>
//#include <chrono>
//#include <thread>
//
//static std::vector<std::pair<double, double>> getDestinations(const int stationNum, const bool firstHalf)
//{
//    // Create box and extract data
//    const auto [lowCorner, highCorner] = getTestIndexBounds(stationCoordinates[stationNum], BOX_RADIUS);
//    const auto [lowLatIndex, lowLongIndex] = lowCorner;
//    const auto [highLatIndex, highLongIndex] = highCorner;
//
//    bool shouldBreak = false;
//    bool firstIteration = true;
//    std::vector<std::pair<double, double>> destinations;
//    for (int i = lowLatIndex; i <= highLatIndex; i++)
//    {
//        for (int j = lowLongIndex; j <= highLongIndex; j++)
//        {
//            // Do this stupidity because of api restrictions (at most 25 destinations per api call)
//            if (!firstHalf)
//            {
//                if (firstIteration)
//                {
//                    // Start the second half at the right indexes
//                    firstIteration = false;
//                    i = lowLatIndex + LAT_INDEX_STOP;
//                    j = lowLongIndex + LONG_INDEX_STOP;
//                    if (i > highLatIndex || j > highLongIndex)
//                    {
//                        shouldBreak = true;
//                        break;
//                    }
//                }
//            }
//            else if (i == lowLatIndex + LAT_INDEX_STOP && j == lowLongIndex + LONG_INDEX_STOP)
//            {
//                // Stop at 25 destinations for the first half
//                shouldBreak = true;
//                break;
//            }
//            const std::pair<double, double> pointCoord = indexToCoord({ i, j });
//            destinations.push_back(pointCoord);
//        }
//        if (shouldBreak) break;
//    }
//    return destinations;
//}
//
//static std::string generateFilePath(const int stationNum, const bool firstHalf)
//{
//    std::string filePath = "RawData/";
//    filePath.append(std::to_string(stationNum));
//    if (firstHalf) filePath.append("a");
//    else filePath.append("b");
//    filePath.append(".json");
//    return filePath;
//}
//
//static bool downloadFirstHalf(const std::string& apiKey, const int stationNum, const bool firstHalf = true)
//{
//    const std::vector<std::pair<double, double>> destinations = getDestinations(stationNum, firstHalf);
//    
//    std::string destinationsStr = destinationsToString(destinations);
//    std::string originStr = originsToString({ stationCoordinates[stationNum] });
//    std::string URL = generateURL(destinationsStr, originStr, apiKey);
//    
//    std::string filePath = generateFilePath(stationNum, firstHalf);
//    bool curlSuccess = doCurlStuff(URL, filePath);
//    if (!curlSuccess)
//    {
//        return false;
//    }
//    return true;
//}
//
//static bool downloadSecondHalf(const std::string& apiKey, const int stationNum)
//{
//    return downloadFirstHalf(apiKey, stationNum, false);
//}
//
//int main(void)
//{
//    std::string apiKey;
//    promptForAPIKey(apiKey);
//
//    for (int i = 0; i < stationCoordinates.size(); i++)
//    {
//        std::cout << "Downloading file " << (i + 1) * 2 << " / " << stationCoordinates.size() * 2 << '\n';
//        const bool downloadSuccess1 = downloadFirstHalf(apiKey, i);
//        if (!downloadSuccess1)
//        {
//            return 1;
//        }
//        const bool downloadSuccess2 = downloadSecondHalf(apiKey, i);
//        if (!downloadSuccess2)
//        {
//            return 1;
//        }
//        std::this_thread::sleep_for(std::chrono::milliseconds(200));
//    }
//    return 0;
//}