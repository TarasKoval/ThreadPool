#pragma once

#include <vector>
#include <thread>

class join_threads {
    std::vector<std::thread> &threads_;

public:
    explicit join_threads(std::vector<std::thread> &rhs_threads);

    ~join_threads();
};