#include "Downloader.h"

#include <fstream>

Downloader::Downloader(){
    #ifdef __linux__
        downloadDir = "home/" + std::string(getlogin()) + "/downloads/";
    #elif _WIN32
        downloadDir = "C:\\Users\\" + std::string(getenv("USERNAME")) + "\\Downloads\\";
    #endif
}
Downloader::Downloader(const std::vector<std::string>& Links){
    #ifdef __linux__
        downloadDir = "home/" + std::string(getlogin()) + "/downloads/";
    #elif _WIN32
        downloadDir = "C:\\Users\\" + std::string(getenv("USERNAME")) + "\\Downloads\\";
    #endif

    links = Links;
}
Downloader::Downloader(const std::vector<std::string>& Links, const std::string& DownloadDir){
    links = Links;
    downloadDir = DownloadDir;
}
Downloader::~Downloader(){}

void Downloader::setLinks(const std::vector<std::string>& Links) { links = Links; }
void Downloader::setDir(const std::string& DownloadDir) { downloadDir = DownloadDir; }

void Downloader::DownloadAll(){
    for(auto& i:links){
        if(Download(i))
            printf("downloaded\n\n");
        else
            printf("not downloaded\n\n");
    }
}

bool Downloader::Download(std::string link){
    printf("%s\n\n", link.c_str());

    std::string request = CreateRequest(link);
    printf("%s\n\n", urlInfo.fileName.c_str());
    printf("%s\n\n", request.c_str());

    Socket.setHost(urlInfo.host);
    Socket.setPort(urlInfo.port);

    if(!Socket.OpenConnection())
        return false;
    if(!Socket.SendMessageToHost(request))
        return false;
    
    std::string answer = Socket.GetMessageFromHost();
    if(answer.empty())
        return false;

    printf("%d\n\n", answer.size());

    /*std::ofstream file((downloadDir + urlInfo.fileName).c_str(), std::ios::out | std::ios::binary);
    file.write(answer.c_str(), answer.size());
    file.close();*/

    Socket.CloseConnection();

    return true;
}
std::string Downloader::CreateRequest(std::string link){
    if(link.substr(0, 7) == "http://"){
        urlInfo.port = 80;
        link.erase(link.begin(), link.begin() + 7);
    }
    else if(link.substr(0, 8) == "https://"){
        urlInfo.port = 80;
        link.erase(link.begin(), link.begin() + 8);
    }
    else{
        errorHandler.Description("Incorect link", EACCES);
        return "";
    }
    urlInfo.host.assign(link.begin(), link.begin() + link.find('/'));
    link.erase(link.begin(), link.begin() + link.find('/'));
    urlInfo.location = link;
    urlInfo.fileName.assign(link.begin() + link.find_last_of('/') + 1, link.end());

    return "GET " + urlInfo.location + " HTTP/1.1\r\nHost: " + urlInfo.host + "\r\nConnection: close\r\n\r\n";
}