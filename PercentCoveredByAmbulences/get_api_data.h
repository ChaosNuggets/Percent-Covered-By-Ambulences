#ifndef GET_API_DATA_H
#define GET_API_DATA_H

#include <string>
#include <vector>

void promptForAPIKey(std::string& apiKey);
std::string destinationsToString(const std::vector<std::pair<double, double>>& coordinates);
std::string originsToString(const std::vector<std::pair<double, double>>& coordinates);
std::string generateURL(const std::string& destinations, const std::string& origins, const std::string& apiKey);
bool doCurlStuff(const std::string& URL, std::string& fileName);

#endif