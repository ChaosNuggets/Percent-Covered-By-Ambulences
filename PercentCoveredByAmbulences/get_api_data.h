#ifndef GET_API_DATA_H
#define GET_API_DATA_H

#include <string>
#include <vector>
#include "point.h"

void promptForAPIKey(std::string& apiKey);
std::string destinationsToString(const std::vector<Point>& coordinates);
std::string originsToString(const std::vector<Point>& coordinates);
std::string generateURL(const std::string& destinations, const std::string& origins, const std::string& apiKey);
bool doCurlStuff(const std::string& URL, std::string& fileName);

#endif