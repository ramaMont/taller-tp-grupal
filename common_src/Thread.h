#ifndef __THREAD__
#define __THREAD__

#include <thread>
#include <atomic>

class Thread {
private:
    std::thread thread;
    std::atomic<bool> is_running;
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
    bool isDone();
    virtual ~Thread();
};

#endif
