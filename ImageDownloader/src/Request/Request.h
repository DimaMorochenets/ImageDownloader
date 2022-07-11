#ifndef REQUEST_H
#define REQUEST_H

#include "src/TCPSocket/TCPSocket.h"

#include <vector>
#include <string>
#include <sstream>

#define MAX_BUF_LEN 1024
#define HOSTNAME "www.bing.com"

class Request{
    public:
        Request();
        Request(const std::string& host);
        Request(const Request&);
        Request(Request&&);
        ~Request();

        void setKey(std::string& keyWords);
        std::string deleteSpaces(std::string& Key);
        void setRequest(const std::string&);

        bool sendRequest();
        bool getHTML();
        bool findImageURL();
        std::vector<std::string> getLinksList();

    private:
        TCPSocket Socket;
        std::string url;
        std::string httpRequest;
        std::string HTML;
        std::vector<std::string> links;
        ErrorHandler errorHandler;
};

#endif