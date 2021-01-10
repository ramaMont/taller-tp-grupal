#ifndef __PROTECTED_VECTOR_H__
#define __PROTECTED_VECTOR_H__

#include <mutex>
#include <vector>

template<class T>

class ProtectedVector{
    private:
    std::mutex m;
    std::vector<T> vec;

    public:
    ProtectedVector(){
    }

    size_t size(){
        std::lock_guard<std::mutex> lock(m);
        return vec.size();
    }

    T at(const int n){
        std::lock_guard<std::mutex> lock(m);
        return vec.at(n);
    }

    T &operator[](int n){
        std::lock_guard<std::mutex> lock(m);
        return vec[n];
    }

    void push_back(T t){
        std::lock_guard<std::mutex> lock(m);
        vec.push_back(t);
    }

    void erase(int n){
        std::lock_guard<std::mutex> lock(m);
        vec.erase(vec.begin() + n);
    }

    ~ProtectedVector(){
    }
};

#endif
