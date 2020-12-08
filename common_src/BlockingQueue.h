#ifndef __B_QUEUE__
#define __B_QUEUE__

#include <mutex>
#include <queue>
#include <condition_variable>

template<typename T>
class BlockingQueue{
private:
    std::mutex m;
    std::queue<T> queue;
    std::condition_variable cv;
public:
    void push(T const& data){
        std::lock_guard<std::mutex> lck(m);
        queue.push(data);
        cv.notify_all();
    }
    T pop(){
        std::unique_lock<std::mutex> lck(m);
        while (queue.empty()){
            cv.wait(lck);
        }
        T data = queue.front();
        queue.pop();
        return data;
    }
};

#endif
