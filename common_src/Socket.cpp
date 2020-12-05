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
#define PORT_LENGTH 10
#define MSG_LENGTH 500

enum TipoUsuario { CLIENT, SERVER };

void hostOClientConf(struct addrinfo **pr, char *host, char *port,
        bool server){
    int err;
    struct addrinfo hints;  
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 */
    hints.ai_socktype = SOCK_STREAM; /* TCP  */
    if (server)
        hints.ai_flags = AI_PASSIVE;     /* AI_PASSIVE to bind */
    err = getaddrinfo(host, port, &hints, pr);
    if (err != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        throw -1;
    }
}

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

void Socket::hostListening(){
    int s = listen(socketFd, MAX_CLIENTS_HOLD);
    if (s == -1) {
        std::cout << "Error: " << strerror(errno) << "\n";
        ::close(socketFd);
        throw -1;
    }
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

Socket Socket::acceptClient(){
    int peersktFd = accept(socketFd, NULL, NULL);
    if (peersktFd == -1) {
        throw -1;
    }
    return Socket(peersktFd);
}

Socket::Socket(std::string host, std::string port){
    struct addrinfo *pr=0;
    struct addrinfo *rp=0;
    char* localHost = const_cast<char*>(host.c_str());
    char* portChar = const_cast<char*>(port.c_str());
    hostOClientConf(&pr, localHost, portChar, CLIENT);
    iteroAddrinfo(pr, rp);
}

Socket::Socket(std::string port):Socket(){
    struct addrinfo *pr=0;
    char localHost[] = "localhost";
    char* portChar = const_cast<char*>(port.c_str());
    hostOClientConf(&pr, localHost, portChar, SERVER);
    hostNBind(pr);
    hostListening();
}

Socket::Socket(){
    socketFd = -1;
}

Socket::Socket(int socketFd):socketFd(socketFd){
}

int Socket::sendStr(std::string msg, size_t size){
    size_t bytes_enviados = 0;
    ++size;
    msg.push_back(EOF);
    char* msg_to_send = const_cast<char*>(msg.c_str());
    while (bytes_enviados < size) {
        int sent;
        sent = send(socketFd, msg_to_send + bytes_enviados,
            size - bytes_enviados, MSG_NOSIGNAL);
        if (sent == -1) {
            printf("Error: %s\n", strerror(errno));
            return -1;
        } else if (sent == 0) {
            printf("Error: %s\n", strerror(errno));
            return -2;
        } else {
            bytes_enviados += sent;
        }
    }
    return 0;
}

int Socket::recive(std::string &reciv, size_t size){
    char buff[MSG_LENGTH]; 
    size_t received = 0;
    while (received < size) {
        int rec = 0;
        rec = recv(socketFd, &buff[received], size-received, 0);
        if (rec == 0) {             // socket cerrado :)
            reciv = buff;
            return -1;
        } else if (rec == -1) {     // error
            return -2;
        }
        received += rec;
        if (buff[received-1] == EOF){
            buff[received-1] = '\0';
            reciv = buff;
            return received;
        }
    }
    reciv = buff;
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

Socket::Socket(Socket&& other) {
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
