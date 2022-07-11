#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#ifdef __linux__
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>

    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define ERROR_NUM errno
    #define CloseSocket(sk) close(sk)

    typedef int SOCKET;
#elif _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define _WINSOCKAPI_

    #include <Windows.h>
    #include <WinSock2.h>
    #include <WS2tcpip.h>

    #pragma comment(lib, "Ws2_32.lib")
    #pragma comment(lib, "Mswsock.lib")
    #pragma comment(lib, "AdvApi32.lib")

    #define ERROR_NUM WSAGetLastError()
    #define CloseSocket(sk) closesocket(sk)
#else
    #error "OS not suported"  
#endif

#include "src/Errors/Error.h"

#include <utility>

#define LOCAL_HOST "127.0.0.1"
#define DEFAULP_PORT 27015

class TCPSocket{
    public:
        TCPSocket();
        TCPSocket(const std::string& Host, const int Port);
        TCPSocket(const TCPSocket& cpSocket);
        TCPSocket(TCPSocket&& mvSocket);
        ~TCPSocket();

        TCPSocket& operator=(const TCPSocket& cpSocket);
        TCPSocket& operator=(TCPSocket&& mvSocket);

        void setParametrs(const std::string& Host, const int Port);
        void setHost(const std::string& Host);
        void setPort(const int Port);
        std::string getHost();
        int getPort();

        bool OpenConnection();
        bool CloseConnection();

        bool SendMessageToHost(const std::string& message);
        std::string GetMessageFromHost();
    private:
        std::string host;
        int port;
        SOCKET Socket;
        ErrorHandler errorHandler;
};

#endif