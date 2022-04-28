//
// Created by arek on 28.04.2022.
//

#ifndef CPP_CPU_TRUCKER_WATCHDOG_H
#define CPP_CPU_TRUCKER_WATCHDOG_H

#include <chrono>
#include <thread>
#include <mutex>

class Watchdog {
public:

    Watchdog();

    void start();

    std::thread start_thr();

    bool is_finish();

    void set_finish_work();

    void reader_reload_watchdog();

private:
    std::mutex finish_work_mutex;
    bool f_work;
    std::mutex reader_time_mutex;
    std::chrono::steady_clock::time_point reader_time;

};


#endif //CPP_CPU_TRUCKER_WATCHDOG_H
