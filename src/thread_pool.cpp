#include "thread_pool.h"

void thread_pool::worker_thread() {
    while (!shutdown_) {
        std::function<void()> task;
        if (task_queue_.try_pop(task)) {
            task();
        } else {
			condition_.wait();
        }
    }
}

thread_pool::thread_pool() : shutdown_(false) {
    unsigned const thread_count = std::thread::hardware_concurrency();
    if (!thread_count) {
        throw std::runtime_error("Number of concurrent threads can't be obtained.");
    }

    try {
        for (unsigned i = 0; i < thread_count; ++i) {
            threads_.emplace_back(&thread_pool::worker_thread, this);
        }
    }
    catch (...) {
        shutdown_ = true;
		condition_.notify_all();
        throw;
    }

}

thread_pool::~thread_pool() {
    shutdown_ = true;
	condition_.notify_all();

	for (auto& thread : threads_) {
		if (thread.joinable())
			thread.join();
	}
}
