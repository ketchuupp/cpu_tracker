//
// Created by arek on 28.04.2022.
//


#include "Watchdog.h"

Watchdog::Watchdog()
         {
    reader_time = std::chrono::steady_clock::now();
}

void Watchdog::start() {
    while (true)
    {
        if (f_work == true)
            break;
    }
}

std::thread Watchdog::start_thr() {
    return std::thread([=] { start(); });
}

bool Watchdog::is_finish() {
    std::lock_guard<std::mutex> guard(finish_work_mutex);
    return f_work;
}

void Watchdog::set_finish_work() {
    std::lock_guard<std::mutex> guard(finish_work_mutex);
    f_work = true;
}


void Watchdog::reader_reload_watchdog() {
    std::lock_guard<std::mutex> guard(reader_time_mutex);
    reader_time = std::chrono::steady_clock::now();
}


