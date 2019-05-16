#pragma once

#include <mutex>
#include <queue>

template<typename T>
class threadsafe_queue {
private:
    mutable std::mutex mutex_;
    std::queue<T> queue_;

public:
    bool try_pop(T &value) {
        std::lock_guard<std::mutex> lk(mutex_);
        if (queue_.empty()) {
            return false;
        }
        value = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    void push(T &new_value) {
        std::lock_guard<std::mutex> lk(mutex_);
        queue_.push(std::move(new_value));
    }

    bool empty() const {
        std::lock_guard<std::mutex> lk(mutex_);
        return queue_.empty();
    }
};
