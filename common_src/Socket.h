#ifndef __SOCKET__
#define __SOCKET__

#include <string>

class Socket{
protected:
    int socketFd;
    void hostNBind(struct addrinfo *pr);
    void reUseHost(struct addrinfo *pr);
    void bindHost(struct addrinfo *pr);
    void iteroAddrinfo(struct addrinfo *result, struct addrinfo *rp);
public:
    Socket();
    explicit Socket(std::string port);
    explicit Socket(std::string host, std::string port);
    explicit Socket(int socketFd);
    void hostListening();
    Socket acceptClient();
    void connect();
    int sendStr(std::string msg, size_t size);
    int recive(std::string &reciv, size_t size);
    void shutdown();
    void close();
    Socket(const Socket&) = delete;
    Socket(Socket&& other);
    Socket& operator=(const Socket&) = delete;
    Socket& operator=(Socket&& other);
    ~Socket();
};

#endif
