//
// Created by arek on 28.04.2022.
//

#ifndef CPP_CPU_TRUCKER_PRINTER_H
#define CPP_CPU_TRUCKER_PRINTER_H

#include <vector>
#include "SafeQueue.hpp"
#include "Analyzer.h"

class Printer {
public:
    Printer() = delete;

    Printer(SafeQueue<std::vector<cpu_usage>> &queue_message, const bool &finish_work);

    std::thread start_thr();

private:
    SafeQueue<std::vector<cpu_usage>> &q_mess_analyzer;
    const bool &f_work;

    void start();
};


#endif //CPP_CPU_TRUCKER_PRINTER_H
