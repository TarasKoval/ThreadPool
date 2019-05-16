#pragma once

#include <mutex>
#include <condition_variable>

// From 
// https://en.cppreference.com/w/cpp/thread/condition_variable/notify_one
// Notifying while under the lock may nevertheless be necessary when precise scheduling of events is required, 
// e.g. if the waiting thread would exit the program if the condition is satisfied, causing destruction of the notifying thread's condition_variable.
// That is the reason why this wrapper exists.
class condition_wrapper {
private:
    std::mutex mutex_;
    std::condition_variable condition_;

public:
    void notify();

    void notify_all();

    void wait();
};
