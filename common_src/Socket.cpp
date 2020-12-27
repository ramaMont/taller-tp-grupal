#include "Socket.h"
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

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
        fprintf(stderr, "Could not connect\n");
        freeaddrinfo(result);
        throw -1;
    }
    freeaddrinfo(result);
}

void Socket::reUseHost(struct addrinfo *pr){
    int val = 1;
    int sErr;
    sErr = setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR,
        &val, sizeof(val));
    if (sErr == -1) {
        std::cout << "Error: " << strerror(errno) << "\n";
        ::close(socketFd);
        freeaddrinfo(pr);
        throw -1;
    }
}

void Socket::bindHost(struct addrinfo *pr){
    int sErr = bind(socketFd, pr->ai_addr, pr->ai_addrlen);
    if (sErr == -1) {
        std::cout << "Error: " << strerror(errno) << "\n";
        ::close(socketFd);
        freeaddrinfo(pr);
        throw -1;
    }
}

void Socket::hostNBind(struct addrinfo *pr){
    socketFd = socket(pr->ai_family, pr->ai_socktype, pr->ai_protocol);
    if (socketFd == -1)
        throw -1;
    reUseHost(pr);
    bindHost(pr);
    freeaddrinfo(pr);
}

Socket::Socket(){
    socketFd = -1;
}

Socket::Socket(int socketFd):socketFd(socketFd){
}

int Socket::send(Protocol& protocol, size_t size){
    size_t bytes_enviados = 0;
    protocol.serialize();
    while (bytes_enviados < size) {
        int sent;
        // Verificar si este casteo me salva de tener que pasarlo a char* todo
        // el struct.
        sent = ::send(socketFd, (char *)&protocol + bytes_enviados,
            size - bytes_enviados, MSG_NOSIGNAL);
        if (sent == -1){
            printf("Error: %s\n", strerror(errno));
            throw -1;
        } else if (sent == 0){
            printf("Error: %s\n", strerror(errno));
            throw -2;
        } else {
            bytes_enviados += sent;
        }
    }
    return 0;
}

int Socket::recive(Protocol& protocol, size_t size){
    Protocol recived_protocol;
    size_t received = 0;
    while (received < size){
        int rec = 0;
        // Verificar si este casteo me salva de tener que pasarlo a char* todo
        // el struct.
        rec = ::recv(socketFd, (char *)&recived_protocol + received,
            size-received, 0);
        if (rec == 0) {             // socket cerrado :S
            throw -1;
        } else if (rec == -1) {     // error
            throw -2;
        }
        received += rec;
    }
    recived_protocol.unSerialize();
    protocol = recived_protocol;
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
        std::cout << "Error: " << strerror(errno) << "\n";
        ::close(socketFd);
        throw -1;
    }
}

Socket SocketServer::acceptClient(){
    int peersktFd = accept(socketFd, NULL, NULL);
    if (peersktFd == -1) {
        throw -1;
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
    hints.ai_family = AF_INET6;       /* IPv4 */
    hints.ai_socktype = SOCK_STREAM; /* TCP  */
    err = getaddrinfo(host, port, &hints, pr);
    if (err != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        throw -1;
    }
}

void SocketServer::hostOClientConf(struct addrinfo **pr, char *host,
        char *port){
    int err;
    struct addrinfo hints;  
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET6;       /* IPv4 */
    hints.ai_socktype = SOCK_STREAM; /* TCP  */
    hints.ai_flags = AI_PASSIVE;     /* AI_PASSIVE to bind */
    err = getaddrinfo(NULL, port, &hints, pr);
    if (err != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        throw -1;
    }
}

SocketClient::~SocketClient(){
}

SocketServer::~SocketServer(){
}
