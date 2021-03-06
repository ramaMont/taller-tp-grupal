#include "Socket.h"
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "SocketException.hpp"

#define MAX_CLIENTS_HOLD 10

void Socket::iteroAddrinfo(struct addrinfo *result, struct addrinfo *rp){
    rp=result;
    for (; rp != NULL; rp = rp->ai_next) {
        socketFd = socket(rp->ai_family, rp->ai_socktype,
            rp->ai_protocol);
        if (socketFd == -1)
            continue;
        if (::connect(socketFd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;
        ::close(socketFd);
    }
    if (rp == NULL) {
        std::string error = "Could not connect\n";
        freeaddrinfo(result);
        throw SocketException(error);
    }
    freeaddrinfo(result);
}

void Socket::reUseHost(struct addrinfo *pr){
    int val = 1;
    int sErr;
    sErr = setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR,
        &val, sizeof(val));
    if (sErr == -1) {
        std::string er_erno = strerror(errno);
        std::string error = "Error: " + er_erno + "\n";
        ::close(socketFd);
        freeaddrinfo(pr);
        throw SocketException(error);
    }
}

void Socket::bindHost(struct addrinfo *pr){
    int sErr = bind(socketFd, pr->ai_addr, pr->ai_addrlen);
    if (sErr == -1) {
        std::string er_erno = strerror(errno);
        std::string error = "Error: " + er_erno + "\n";
        ::close(socketFd);
        freeaddrinfo(pr);
        throw SocketException(error);
    }
}

void Socket::hostNBind(struct addrinfo *pr){
    socketFd = socket(pr->ai_family, pr->ai_socktype, pr->ai_protocol);
    if (socketFd == -1)
        throw SocketException("Could not create a socket\n");
    reUseHost(pr);
    bindHost(pr);
    freeaddrinfo(pr);
}

Socket::Socket(){
    socketFd = -1;
}

Socket::Socket(int socketFd):socketFd(socketFd){
}

int Socket::send(const Protocol& protocol){
    size_t bytes_enviados = 0;
    Protocol::NetworkProtocol sending_protocol = protocol.serialize();
    size_t size = sizeof(sending_protocol);
    while (bytes_enviados < size) {
        int sent;
        sent = ::send(socketFd, (char *)&sending_protocol + bytes_enviados,
            size - bytes_enviados, MSG_NOSIGNAL);
        if (sent == -1){
            std::string er_erno = strerror(errno);
            std::string error = "Error: " + er_erno + "\n";
            throw SocketException(error);
        } else if (sent == 0){
            std::string er_erno = strerror(errno);
            std::string error = "Error: " + er_erno + "\n";
            throw SocketException(error);
        } else {
            bytes_enviados += sent;
        }
    }
    return 0;
}

int Socket::recive(Protocol& protocol){
    Protocol::NetworkProtocol recived_protocol;
    size_t size = sizeof(recived_protocol);
    size_t received = 0;
    while (received < size){
        int rec = 0;
        rec = ::recv(socketFd, (char *)&recived_protocol + received,
            size-received, 0);
        if (rec == 0) {             // socket cerrado :S
            throw SocketException("El socket ha sido cerrado\n");
        } else if (rec == -1) {     // error
            throw SocketException("Ha ocurrido un error en el socket\n");
        }
        received += rec;
    }
    protocol.unSerialize(recived_protocol);
    return received;
}

Socket &Socket::operator=(Socket&& other){
    if (this == &other){
        return*this;        // other is myself!
    }
    this->socketFd = other.socketFd;
    other.socketFd = -1;
    return *this;
}

Socket::Socket(Socket&& other){
    this->socketFd = other.socketFd;
    other.socketFd = -1;
}

void Socket::shutdown(){
    if (socketFd != -1)
        ::shutdown(socketFd, SHUT_RDWR);  
}

void Socket::close(){
    if (socketFd != -1)
        ::close(socketFd);
    socketFd = -1;
}

Socket::~Socket(){
    if (socketFd != -1){
        ::shutdown(socketFd, SHUT_RDWR);
        ::close(socketFd);
    }
}

SocketServer::SocketServer(std::string port):Socket(){
    struct addrinfo *pr=0;
    char localHost[] = "localhost";
    char* portChar = const_cast<char*>(port.c_str());
    hostOClientConf(&pr, localHost, portChar);
    hostNBind(pr);
    hostListening();
}

void SocketServer::hostListening(){
    int s = listen(socketFd, MAX_CLIENTS_HOLD);
    if (s == -1) {
        std::string string_erno = strerror(errno);
        std::string error = "Error: " + string_erno + "\n";
        ::close(socketFd);
        throw SocketException(error);
    }
}

Socket SocketServer::acceptClient(){
    int peersktFd = accept(socketFd, NULL, NULL);
    if (peersktFd == -1) {
        throw SocketException("Client could not be accepted\n");
    }
    return Socket(peersktFd);
}

SocketClient::SocketClient(std::string host, std::string port){
    struct addrinfo *pr=0;
    struct addrinfo *rp=0;
    char* localHost = const_cast<char*>(host.c_str());
    char* portChar = const_cast<char*>(port.c_str());
    hostOClientConf(&pr, localHost, portChar);
    iteroAddrinfo(pr, rp);
}

void SocketClient::hostOClientConf(struct addrinfo **pr, char *host,
        char *port){
    int err;
    struct addrinfo hints;  
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 */
    hints.ai_socktype = SOCK_STREAM; /* TCP  */
    err = getaddrinfo(host, port, &hints, pr);
    if (err != 0) {
        std::string gai_error = gai_strerror(err);
        std::string error = "getaddrinfo: " + gai_error + "\n";
        throw SocketException(error);
    }
}

void SocketServer::hostOClientConf(struct addrinfo **pr, char *host,
        char *port){
    int err;
    struct addrinfo hints;  
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 */
    hints.ai_socktype = SOCK_STREAM; /* TCP  */
    hints.ai_flags = AI_PASSIVE;     /* AI_PASSIVE to bind */
    err = getaddrinfo(NULL, port, &hints, pr);
    if (err != 0) {
        std::string gai_error = gai_strerror(err);
        std::string error = "getaddrinfo: " + gai_error + "\n";
        throw SocketException(error);
    }
}

SocketClient::~SocketClient(){
}

SocketServer::~SocketServer(){
}
