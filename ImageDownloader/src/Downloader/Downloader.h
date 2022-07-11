#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include "src/TCPSocket/TCPSocket.h"

#include <vector>
#include <string>

class Downloader{
    public:
        Downloader();
        Downloader(const std::vector<std::string>& Links);
        Downloader(const std::vector<std::string>& Links, const std::string& DownloadDir);
        ~Downloader();

        void setLinks(const std::vector<std::string>& Links);
        void setDir(const std::string& DownloadDir);

        void DownloadAll();
        bool Download(std::string link);
        std::string CreateRequest(std::string link);
    
    private:
        std::vector<std::string> links;
        std::string downloadDir;
        TCPSocket Socket;
        struct URLInfo{
            std::string host;
            int port;
            std::string location;
            std::string fileName;
        }urlInfo;
        ErrorHandler errorHandler;

};

#endif