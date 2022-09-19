#include <iostream>
#include <string>

#define CURL_STATICLIB
#include <curl/curl.h>

static void promptForAPIKey(std::string& apiKey)
{
    std::cout << "Enter API key: ";
    std::getline(std::cin, apiKey);
    apiKey.insert(0, "&key=");
}

// This is called whenever a chunk is downloaded
static size_t writeData(void* contents, size_t itemSize, size_t numItems, FILE* stream) {
    size_t written = fwrite(contents, itemSize, numItems, stream);
    return written;
}

static std::string generateURL(const std::string& destinations, const std::string& origins, const std::string& apiKey)
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

static bool openFile(FILE*& filePtr, const std::string& fileName)
{
    errno_t error = fopen_s(&filePtr, fileName.c_str(), "wb"); // wb stands for write binary
    if (error != 0)
    {
        std::cout << "File opening failed";
        return false;
    }
    return true;
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

static bool doCurlStuff(const std::string& URL, std::string& fileName)
{
    CURL* curl;
    FILE* filePtr;

    bool initSuccess = initializeCurl(curl);
    if (!initSuccess)
    {
        return false;
    }

    bool fileOpenSuccess = openFile(filePtr, fileName);
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

    curl_easy_cleanup(curl);

    return true;
}

int main(void)
{
    std::string apiKey;
    promptForAPIKey(apiKey);

    std::string destinations = "?destinations=New%20York%20City%2C%20NY|Indianapolis";
    std::string origins = "&origins=Washington%2C%20DC|Chicago";
    std::string URL = generateURL(destinations, origins, apiKey);

    std::string fileName = "abc.json";
    bool curlSuccess = doCurlStuff(URL, fileName);
    if (!curlSuccess)
    {
        return 1;
    }
    return 0;
}