#include <iostream>
#include <chrono>

#include "thread_pool.h"

int multiply(int a, int b) {
    return a * b;
}

void sum(int &result, int a, int b) {
    result = a + b;
}

int main() {
    thread_pool pool;
    int sum_result = 0;

    auto multiply_result = pool.submit(multiply, 5, 10);
    auto ready = pool.submit(sum, std::ref(sum_result), 5, 10);

    std::cout << multiply_result.get() << std::endl;

    ready.get();
    std::cout << sum_result << std::endl;
}
