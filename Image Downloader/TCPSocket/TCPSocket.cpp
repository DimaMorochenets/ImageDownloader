#include "TCPSocket.h"

//ctor/dtor
TCPSocket::TCPSocket(){
    Socket = INVALID_SOCKET;
    host = LOCAL_HOST;
    port = DEFAULP_PORT;
}
TCPSocket::TCPSocket(const std::string& Host, const int Port){
    Socket = INVALID_SOCKET;
    host = Host;
    port = Port;
}
TCPSocket::TCPSocket(const TCPSocket& cpSocket){
    Socket = INVALID_SOCKET;
    host = cpSocket.host;
    port = cpSocket.port;
}
TCPSocket::TCPSocket(TCPSocket&& mvSocket){
    Socket = std::move(mvSocket.Socket);
    host = std::move(mvSocket.host);
    port = std::move(mvSocket.port);
}
TCPSocket::~TCPSocket() { CloseSocket(Socket); }

//assignment
TCPSocket& TCPSocket::operator=(const TCPSocket& cpSocket){
    Socket = INVALID_SOCKET;
    host = cpSocket.host;
    port = cpSocket.port;

    return *this;
}
TCPSocket& TCPSocket::operator=(TCPSocket&& mvSocket){
    Socket = std::move(mvSocket.Socket);
    host = std::move(mvSocket.host);
    port = std::move(mvSocket.port);

    return *this;
}

//get/set
void TCPSocket::setParametrs(const std::string& Host, const int Port){
    host = Host;
    port = Port;
}
void TCPSocket::setHost(const std::string& Host) { host = Host; }
void TCPSocket::setPort(const int Port) { port = Port; }
std::string TCPSocket::getHost() { return host; }
int TCPSocket::getPort() { return port; }

//open/close
bool TCPSocket::OpenConnection(){
    addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family     = AF_INET;
    hints.ai_socktype   = SOCK_STREAM;
    hints.ai_protocol   = IPPROTO_TCP;
    addrinfo *addrs = nullptr;

    if(getaddrinfo(host.c_str(), nullptr, &hints, &addrs) || addrs == nullptr){
        errorHandler.Description("Host " + host, ERROR_NUM);
        return false;
    }
    
    sockaddr_in sockAddr;
    sockAddr.sin_addr = ((sockaddr_in*)addrs->ai_addr)->sin_addr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(port);

    freeaddrinfo(addrs);

    Socket = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
    if(Socket == INVALID_SOCKET){
        errorHandler.Description("Connection the socket", ERROR_NUM);
        return false;
    }
    if(connect(Socket, (sockaddr*)&sockAddr, sizeof(sockAddr))){
        errorHandler.Description("Connection to host " + host, ERROR_NUM);
        return false;
    }

    return true;
}
bool TCPSocket::CloseConnection(){
    if(CloseSocket(Socket)){
        errorHandler.Description("Closing the socket", ERROR_NUM);
        return false;
    }
    return true;
}

//get/send message
bool TCPSocket::SendMessageToHost(const std::string& message){
    if(send(Socket, (char*)message.c_str(), (int)message.size(), 0) == SOCKET_ERROR){
        errorHandler.Description("Message sending", ERROR_NUM);
        return false;
    }
    return true;
}
std::string TCPSocket::GetMessageFromHost(){
    int buffer_size = 1024;
    char* buffer = (char*)malloc(buffer_size);
    int message_size = 0;
    char* message = nullptr;

    int bytes_rec = 0;
    while((bytes_rec = recv(Socket, buffer, buffer_size, 0)) > 0){
        message = (char*)realloc(message, message_size + bytes_rec);
        memcpy(message + message_size, buffer, bytes_rec);
        message_size += bytes_rec;
        memset(buffer, 0, buffer_size);
    }

    return message_size ? std::string(message) : "";
}