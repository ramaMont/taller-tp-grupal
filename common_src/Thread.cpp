#include "Thread.h"
#include <thread>
#include <utility>

Thread::Thread():is_running(false){
}

void Thread::start() {
    is_running = true;
    thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    thread.join();
}

Thread::Thread(Thread&& other) {
    this->thread = std::move(other.thread);
}

Thread& Thread::operator=(Thread&& other) {
    this->thread = std::move(other.thread);
    return *this;
}

bool Thread::isDone(){
    return !is_running;
}

Thread::~Thread(){
}
