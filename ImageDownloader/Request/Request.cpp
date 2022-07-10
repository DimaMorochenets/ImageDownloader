#include "Request.h"

Request::Request()
{
    url         = HOSTNAME;
    httpRequest = "GET /images/search?q=Linux&first=1 HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";
    HTML        = "";
    Socket.setParametrs(HOSTNAME, 80);
}
Request::Request(const std::string& host)
{
    url         = host;
    httpRequest = "GET /images/search?q=Linux&first=1 HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";
    HTML        = "";
    Socket.setParametrs(host, 80);
}
Request::Request(const Request& cpRequest)
{
    url          = cpRequest.url;
    httpRequest  = cpRequest.httpRequest;
    HTML         = cpRequest.HTML;
    Socket       = cpRequest.Socket;
    errorHandler = cpRequest.errorHandler;
}
Request::Request(Request&& mvRequest)
{
    url          = std::move(mvRequest.url);
    httpRequest  = std::move(mvRequest.httpRequest);
    HTML         = "";
    Socket       = std::move(mvRequest.Socket);
    errorHandler = std::move(mvRequest.errorHandler);
}
Request::~Request()
{
    Socket.CloseConnection();
    #ifndef __linux__
        WSACleanup();
    #endif 
}

void Request::setKey(std::string& Key) { 
    Key = deleteSpaces(Key);

    httpRequest.clear();
    httpRequest = "GET /images/search?q=" + Key + " HTTP/1.1\r\n";
    httpRequest += "Host: " + url;
    httpRequest += "\r\nConnection: close\r\n\r\n";
}

std::string Request::deleteSpaces(std::string& Key)
{   
    std::string correctKey = "";

    int i = 0;
    int j = (int)Key.size() - 1;

    while(isspace(Key[i])) i++;
    while(isspace(Key[j]) && j > i) j--;

    if(i == j) return "";

    for(int k = i; k <= j; k++){
        if(isspace(Key[k]) && isspace(Key[k + 1]))
            continue;
        else if(isspace(Key[k]) && !isspace(Key[k + 1]))
            correctKey += "%20";
        else
            correctKey += Key[k];
    }

    return correctKey;
}

void Request::setRequest(const std::string& Request) { httpRequest = Request; }

bool Request::sendRequest()
{
    #ifndef __linux__
        WSADATA wsaData;
        if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
            errorHandler.Description("Initialize Winsock", ERROR_NUM);
            return false;
        }
    #endif

    if(!Socket.OpenConnection())
        return false;

    if(!Socket.SendMessageToHost(httpRequest))
        return false;

    if(!getHTML())
        return false;

    if(!findImageURL())
        return false;

    return true;
}

bool Request::getHTML()
{
    std::string answer = Socket.GetMessageFromHost();
    if(answer.empty())
        return false;
    
    for(const auto& i:answer)
        if(i >= 32 || i == '\n' || i == '\r')
            HTML.push_back(i);

    return HTML.empty() ? false : true;
}

bool Request::findImageURL()
{
    std::stringstream stream;
    std::string temp;
    std::string curString;

    stream << HTML;
    while(stream >> curString){
        std::string::size_type begin = curString.find("murl");
        if(begin == std::string::npos)
            continue;

        temp.clear();
        for(std::string::size_type i = begin; i < curString.size(); i++)
            temp.push_back(curString[i]);
        curString = temp;

        begin = curString.find("https://");
        if(begin == std::string::npos){
            begin = curString.find("http://");
            if(begin == std::string::npos)
                continue;
        }

        temp.clear();
        for(std::string::size_type i = begin; i < curString.size(); i++)
            temp.push_back(curString[i]);
        curString = temp;

        std::string::size_type end = curString.find("&quot");
        if(end == std::string::npos) 
            continue;

        temp.clear();
        for(std::string::size_type i = 0; i < curString.size() && i < end; i++)
            temp.push_back(curString[i]);

        if(!temp.empty())
            links.push_back(temp);
    }
    HTML.clear();

    return links.empty() ? false:true;
}

std::vector<std::string> Request::getLinksList() { return links; }