//
// Created by arek on 28.04.2022.
//
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Printer.h"

Printer::Printer(SafeQueue<std::vector<cpu_usage>> &queue_message, Watchdog &watchdog)
        : q_mess_analyzer(queue_message), wdg(watchdog) {

}

void Printer::start() {
    while (true) {
        if (wdg.is_finish() == true)
            break;
        if (q_mess_analyzer.get_size() == 0)
            continue;
        std::vector<cpu_usage> mess = std::move(q_mess_analyzer.pop());
        system("clear");
        std::cout << "\t     CPU USAGE TRUCKER\n";

        for (auto &a: mess) {
            if (a.cpu_num == 0)
                std::cout << "Total:  ";
            else
                std::cout << a.cpu_num << "\t";

            std::cout << "[";
            for (int i = 0; i <= static_cast<int>(a.cpu_usage) / 4; i++) {
                std::cout << "|";
            }
            // fill empty space
            for (int i = static_cast<int>(a.cpu_usage) / 4; i < 100 / 4; i++) {
                std::cout << " ";
            }
            std::cout << "]";

            // print percent cpu usage
            std::cout << "\t"
                      << std::fixed
                      << std::right
                      << std::setprecision(1)
                      << std::setw(5)
                      << a.cpu_usage << "%\n";
        }

    }
//    std::cout << "Printer finished!\n";
}

std::thread Printer::start_thr() {
    return std::thread([=] { start(); });
}
