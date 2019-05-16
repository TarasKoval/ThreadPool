#include "join_threads.h"

join_threads::join_threads(std::vector<std::thread> &rhs_threads) : threads_(rhs_threads) {}

join_threads::~join_threads() {
    for (auto &thread : threads_) {
        if (thread.joinable())
            thread.join();
    }
}
