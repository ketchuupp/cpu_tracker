//
// Created by arek on 28.04.2022.
//


#include <iostream>
#include "Watchdog.h"

Watchdog::Watchdog() {
    f_work = false;
    reader_reload_watchdog();
    analyzer_reload_watchdog();
    printer_reload_watchdog();
}

void Watchdog::start() {
    while (true) {
        if (is_finish() == true)
            break;

        if (get_reader_time() > 2000) {
//            std::cout << "Reader watchdog interrupt!\nPress ENTER to continue...";
            std::cerr << "Reader watchdog interrupt!\nPress ENTER to continue...";
            set_finish_work();
            break;
        }
        if (get_analyzer_time() > 2000) {
            std::cerr << "Analyzer watchdog interrupt!\nPress ENTER to continue...";
            set_finish_work();
            break;
        }
        if (get_printer_time() > 2000) {
            std::cerr << "Printer watchdog interrupt!\nPress ENTER to continue...";
            set_finish_work();
            break;
        }
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

void Watchdog::analyzer_reload_watchdog() {
    std::lock_guard<std::mutex> guard(analyzer_time_mutex);
    analyzer_time = std::chrono::steady_clock::now();
}

void Watchdog::printer_reload_watchdog() {
    std::lock_guard<std::mutex> guard(printer_time_mutex);
    printer_time = std::chrono::steady_clock::now();
}

unsigned Watchdog::get_time(std::mutex &m, std::chrono::steady_clock::time_point &time) {
    std::lock_guard<std::mutex> guard(m);
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now - time).count() / 1000;
}

unsigned Watchdog::get_reader_time() {
    return get_time(reader_time_mutex, reader_time);
}

unsigned Watchdog::get_analyzer_time() {
    return get_time(analyzer_time_mutex, analyzer_time);
}

unsigned Watchdog::get_printer_time() {
    return get_time(printer_time_mutex, printer_time);
}




