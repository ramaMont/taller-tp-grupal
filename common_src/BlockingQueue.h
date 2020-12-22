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
    bool open;
public:
    BlockingQueue():open(true){
    }

    void push(T const& data){
        std::lock_guard<std::mutex> lck(m);
        queue.push(data);
        cv.notify_all();
    }

    T pop(){
        std::unique_lock<std::mutex> lck(m);
        while (queue.empty()){
            cv.wait(lck);
            if (!open)
                throw -1;
        }
        T data = queue.front();
        queue.pop();
        return data;
    }
    
    void stop(){
        std::unique_lock<std::mutex> lck(m);
        open = false;
        cv.notify_all();
    }
    ~BlockingQueue(){
    }
};

#endif
