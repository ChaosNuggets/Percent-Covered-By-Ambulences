// This program extracts data from the json files
#include <fstream>
#include "station_coordinates.h"
#include <string>
#include <iostream>
#include <vector>

std::string generateReadFilePath(const int stationNum, const bool firstHalf)
{
	std::string filePath = "RawData/";
	filePath.append(std::to_string(stationNum));
	if (firstHalf) filePath.append("a");
	else filePath.append("b");
	filePath.append(".json");
	return filePath;
}

std::string generateWriteFilePath(const int stationNum)
{
	std::string filePath = "TravelTimes/";
	filePath.append(std::to_string(stationNum));
	filePath.append(".txt");
	return filePath;
}

int getValue(std::ifstream& fin)
{
	std::string line;
	std::getline(fin, line);
	std::getline(fin, line);
	
	// line is now something like "(a bunch of spaces) 'value' : 757"
	line.erase(0, 28);
	return stoi(line);
}

std::vector<int> getDurations(std::ifstream& fin)
{
	std::vector<int> durations;
	std::string line;
	while (std::getline(fin, line))
	{
		if (line.find("duration") != std::string::npos)
		{
			durations.push_back(getValue(fin));
		}
	}
	return durations;
}

void writeDurations(std::ofstream& fout, const std::vector<int>& durations)
{
	for (int duration : durations)
	{
		fout << duration << '\n';
	}
}

bool createCleanFile(const int stationNum, bool firstHalf = true)
{
	const std::string readFilePath = generateReadFilePath(stationNum, firstHalf);
	const std::string writeFilePath = generateWriteFilePath(stationNum);

	std::ifstream fin(readFilePath.c_str()); // Ifstream stands for input file stream
	if (!fin.is_open())
	{
		std::cout << "Unable to open " << readFilePath;
		return false;
	}

	std::ofstream fout(writeFilePath.c_str(), std::ios_base::app);
	if (!fout.is_open())
	{
		std::cout << "Unable to open " << writeFilePath;
		return false;
	}

	
	const std::vector<int> durations = getDurations(fin);
	writeDurations(fout, durations);

	fin.close();
	fout.close();

	if (firstHalf) createCleanFile(stationNum, false);
	return true;
}

int main()
{
	for (int i = 0; i < stationCoordinates.size(); i++)
	{
		bool success = createCleanFile(i);
		if (!success)
			return 1;
	}
	return 0;
}