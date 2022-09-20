#include <iostream>
#include "get_api_data.h"

#define CURL_STATICLIB
#include <curl/curl.h>

void promptForAPIKey(std::string& apiKey)
{
    std::cout << "Enter API key: ";
    std::getline(std::cin, apiKey);
    apiKey.insert(0, "&key=");
}

static std::string encode(const double number)
{
    // Take the decimal value and multiply it by 1e5, rounding the result:
    int intCoord = round(number * 1e5);

    // Left-shift the binary value one bit:
    intCoord = intCoord << 1;

    // If the original decimal value is negative, invert this encoding:
    if (number < 0)
    {
        intCoord = ~intCoord;
    }

    // Break the binary value out into 5-bit chunks:
    std::vector<int> chunks;
    const int CHUNKSIZE = 5;
    bool removeZeroChunks = true;
    for (int i = (sizeof(intCoord) * 8 / CHUNKSIZE) - 1; i >= 0; i--)
    {
        int chunk = (intCoord >> i * CHUNKSIZE) & 0b11111;
        if (removeZeroChunks)
        {
            if (chunk != 0 || i == 0)
            {
                removeZeroChunks = false;
            }
            else
            {
                continue;
            }
        }
        chunks.push_back(chunk);
    }

    // Place the 5-bit chunks into reverse order:
    std::reverse(chunks.begin(), chunks.end());

    // OR each value with 0x20 if another bit chunk follows:
    for (int i = 0; i < chunks.size() - 1; i++)
    {
        chunks[i] = chunks[i] | 0x20;
    }

    std::string returnString = "";
    for (int& chunk : chunks)
    {
        // Add 63 to each value:
        chunk += 63;

        // Convert each value to its ASCII equivalent and append it to the string:
        returnString.push_back(chunk);
    }

    return returnString;
}

static std::string generatePolyline(const std::string& prefix, const std::string& suffix, const std::vector<std::pair<double, double>>& coordinates)
{
    std::string returnString = prefix;
    for (int i = 0; i < coordinates.size(); i++)
    {
        auto [currentLat, currentLong] = coordinates[i];
        auto [previousLat, previousLong] = i > 0 ? coordinates[i - 1] : std::pair<double, double>{ 0, 0 };
        double latDifference = currentLat - previousLat;
        double longDifference = currentLong - previousLong;

        returnString.append(encode(latDifference));

        returnString.append(encode(longDifference));
    }
    returnString.append(suffix);
    return returnString;
}

std::string destinationsToString(const std::vector<std::pair<double, double>>& coordinates)
{
    return generatePolyline("?destinations=enc:", ":", coordinates);
}

std::string originsToString(const std::vector<std::pair<double, double>>& coordinates)
{
    return generatePolyline("&origins=enc:", ":", coordinates);
}

std::string generateURL(const std::string& destinations, const std::string& origins, const std::string& apiKey)
{
    std::string api = "https://maps.googleapis.com/maps/api/distancematrix/json";
    std::string units = "&units=imperial";
    std::string URL = api + destinations + origins + units + apiKey;
    return URL;
}

static bool initializeCurl(CURL*& curl)
{
    curl = curl_easy_init();
    if (!curl) // If initialization failed
    {
        std::cout << "Curl initialization failed";
        return false;
    }
    return true;
}

static bool openFile(FILE*& filePtr, const std::string& filePath)
{
    errno_t error = fopen_s(&filePtr, filePath.c_str(), "wb"); // wb stands for write binary
    if (error != 0)
    {
        std::cout << "File opening failed";
        return false;
    }
    return true;
}

// This is called whenever a chunk is downloaded
static size_t writeData(void* contents, size_t itemSize, size_t numItems, FILE* stream) {
    size_t written = fwrite(contents, itemSize, numItems, stream);
    return written;
}

static void setUpOptions(CURL*& curl, const std::string& URL, const FILE* filePtr)
{
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, filePtr);
}

static bool performCurlAction(CURL* curl)
{
    CURLcode result; // Result of curl call, equals CURLE_OK if download succeded
    result = curl_easy_perform(curl);
    if (result != CURLE_OK)
    {
        std::cout << "download problem: " << curl_easy_strerror(result);
        return false;
    }
    return true;
}

bool doCurlStuff(const std::string& URL, std::string& filePath)
{
    CURL* curl;
    FILE* filePtr;

    bool initSuccess = initializeCurl(curl);
    if (!initSuccess)
    {
        return false;
    }

    bool fileOpenSuccess = openFile(filePtr, filePath);
    if (!fileOpenSuccess)
    {
        return false;
    }

    setUpOptions(curl, URL, filePtr);

    bool performSuccess = performCurlAction(curl);
    if (!performSuccess)
    {
        return false;
    }

    if (fclose(filePtr))
    {
        std::cout << "file close error";
        return false;
    }
    curl_easy_cleanup(curl);

    return true;
}