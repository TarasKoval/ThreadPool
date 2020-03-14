#include "condition_wrapper.h"

void condition_wrapper::notify() {
    std::lock_guard<std::mutex> lock(mutex_);
    condition_.notify_one();
}

void condition_wrapper::notify_all() {
    std::lock_guard<std::mutex> lock(mutex_);
    condition_.notify_all();
}

void condition_wrapper::wait() {
    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(lock);
}
