//
// Created by arek on 28.04.2022.
//

#ifndef CPP_CPU_TRACKER_WATCHDOG_H
#define CPP_CPU_TRACKER_WATCHDOG_H

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

    void analyzer_reload_watchdog();

    void printer_reload_watchdog();

private:
    std::mutex finish_work_mutex;
    bool f_work;

    std::mutex reader_time_mutex;
    std::chrono::steady_clock::time_point reader_time;

    std::mutex analyzer_time_mutex;
    std::chrono::steady_clock::time_point analyzer_time;

    std::mutex printer_time_mutex;
    std::chrono::steady_clock::time_point printer_time;

    /**
     * Get time since last reload
     * @return time[ms]
     */
    unsigned get_reader_time();
    unsigned get_analyzer_time();
    unsigned get_printer_time();

    unsigned get_time(std::mutex &m, std::chrono::steady_clock::time_point &time);

};


#endif //CPP_CPU_TRACKER_WATCHDOG_H
