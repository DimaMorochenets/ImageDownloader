#include "Error.h"

#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <algorithm>

ErrorHandler::ErrorHandler(){
    logFile = logFilePath();
    description = "";
    errorNum = 0;
}
ErrorHandler::ErrorHandler(std::string msg, ERROR_N curError)
{
    logFile = logFilePath();
    description = "";
    errorNum = curError;
    Description(msg, curError);
}

std::string ErrorHandler::logFilePath()
{
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    tm curTime; 

    #ifdef __linux__
        localtime_r(&now, &curTime);
    #elif _WIN32
        _localtime64_s(&curTime, &now);
    #endif

    std::stringstream stream;
    stream << std::put_time(&curTime, "%Y-%m-%d");

    auto path = std::filesystem::current_path().native();
    std::string name;
    std::transform(path.begin(), path.end(), std::back_inserter(name), [](wchar_t c) {return (char)c;});

    #ifdef __linux__
        std::string full_path = name + "//ErrorsLog-" + stream.str() + ".txt";
    #else
        std::string full_path = name + "\\ErrorsLog-" + stream.str() + ".txt";
    #endif

    return full_path;
}

void ErrorHandler::Description(std::string msg, ERROR_N curError)
{
    char desc[256] = "";
    #ifdef __linux__
        strcpy(desc, strerror(errorNum));
    #else
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, curError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)desc, 256, NULL);
    #endif

    description = "\nMessage: " + msg + "\nError: " + std::to_string(curError) +  "\nDescription: " + desc + "\n";
    std::cout << description;

    std::ofstream file(logFile.c_str(), std::ios_base::app);
    file << description;
    file.close();
}