#ifndef __THREAD__
#define __THREAD__

#include <thread>

class Thread {
private:
    std::thread thread;
public:
    Thread();
    void start();
    void join();
    virtual void run() = 0;
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    Thread(Thread&& other);
    Thread& operator=(Thread&& other);
    virtual void stop() = 0;
    virtual bool isDone() = 0;
    virtual ~Thread();
};

#endif
