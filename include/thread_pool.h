#pragma once

#include <future>
#include <functional>

#include "join_threads.h"
#include "threadsafe_queue.h"
#include "condition_wrapper.h"

class thread_pool {
    std::atomic_bool shutdown_;
    threadsafe_queue<std::function<void()>> task_queue_;
    std::vector<std::thread> threads_;
    join_threads joiner_;
    condition_wrapper condition_;

    void worker_thread();

public:
    thread_pool();

    ~thread_pool();

    template<typename F, typename...Args>
    auto submit(F &&f, Args &&... args) -> std::future<decltype(f(args...))> {
        auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        // Packaged_task wrapped in shared_ptr to be able to copy construct / assign
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(task);

        // Wrap into void function
        std::function<void()> wrapped_task = [task_ptr]() { (*task_ptr)(); };

        task_queue_.push(wrapped_task);
        condition_.notify();

        return task_ptr->get_future();
    }
};
