#ifndef __SOCKET__
#define __SOCKET__

#include <string>
#include "Protocol.h"

class Socket{
protected:
    int socketFd;
    void hostNBind(struct addrinfo *pr);
    void reUseHost(struct addrinfo *pr);
    void bindHost(struct addrinfo *pr);
    void iteroAddrinfo(struct addrinfo *result, struct addrinfo *rp);
public:
    Socket();
    explicit Socket(int socketFd);

    int send(const Protocol& protocol);
    int recive(Protocol& protocol);
    void shutdown();
    void close();
    Socket(const Socket&) = delete;
    Socket(Socket&& other);
    Socket& operator=(const Socket&) = delete;
    Socket& operator=(Socket&& other);
    ~Socket();
};

class SocketClient : public Socket{
private:
    void hostOClientConf(struct addrinfo **pr, char *host, char *port);
public:
    explicit SocketClient(std::string host, std::string port);
    ~SocketClient();
};

class SocketServer : public Socket{
private:
    void hostOClientConf(struct addrinfo **pr, char *host, char *port);
public:
    explicit SocketServer(std::string port);
    void hostListening();
    Socket acceptClient();
    ~SocketServer();
};

#endif
