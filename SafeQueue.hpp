//
// Created by arek on 26.04.2022.
//

#ifndef CPP_CPU_TRACKER_SAFEQUEUE_HPP
#define CPP_CPU_TRACKER_SAFEQUEUE_HPP

#include <queue>
#include <mutex>
#include <utility>
#include <iostream>

template<class T>
class SafeQueue {
    std::queue<T> s_queue;
    std::mutex queue_mutex;
public:
    SafeQueue() = default;

    void push(const T &value) {
        std::lock_guard<std::mutex> guard(queue_mutex);
        s_queue.push(value);
    }

//    push(T &&value) {
//        std::lock_guard<std::mutex> guard(queue_mutex);
//        s_queue.push(value);
//    }

    T pop() {
        std::lock_guard<std::mutex> guard(queue_mutex);
        while (s_queue.empty()) {} // wait for element

        T value = s_queue.front();
        s_queue.pop();
        return value;
    }

    size_t get_size() { return s_queue.size(); }

};


#endif //CPP_CPU_TRACKER_SAFEQUEUE_HPP
