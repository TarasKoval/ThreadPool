cmake_minimum_required(VERSION 3.10)

project(thread_pool)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(HEADERS
        include/join_threads.h
        include/threadsafe_queue.h
        include/thread_pool.h
        include/condition_wrapper.h
        )

set(SOURCES
        src/condition_wrapper.cpp
        src/join_threads.cpp
        src/thread_pool.cpp)

add_executable(${PROJECT_NAME}
        ${HEADERS}
        ${SOURCES}
        src/main.cpp
        )

target_link_libraries(${PROJECT_NAME} -pthread)
