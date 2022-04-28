//
// Created by arek on 28.04.2022.
//

#ifndef CPP_CPU_TRUCKER_PRINTER_H
#define CPP_CPU_TRUCKER_PRINTER_H

#include <vector>
#include "SafeQueue.hpp"
#include "Analyzer.h"
#include "Watchdog.h"

class Printer {
public:
    Printer() = delete;

    Printer(SafeQueue<std::vector<cpu_usage>> &queue_message, Watchdog &watchdog);

    std::thread start_thr();

private:
    SafeQueue<std::vector<cpu_usage>> &q_mess_analyzer;
    Watchdog &wdg;

    void start();
};


#endif //CPP_CPU_TRUCKER_PRINTER_H
