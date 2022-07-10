#ifndef ERROR_H
#define ERROR_H

#ifdef UNICODE
    #undef UNICODE
#endif

#ifdef __linux__
    #include <cstring>
    #include <cerrno>
    typedef int ERROR_N;
#elif _WIN32
    #include <Windows.h>
    typedef DWORD ERROR_N; 
#endif

#include <string>

class ErrorHandler
{
    public:
        ErrorHandler();
        ErrorHandler(std::string, ERROR_N);
        void Description(std::string, ERROR_N);
        std::string logFilePath();
    private:
        std::string logFile;
        std::string description;
        ERROR_N errorNum;
};

#endif