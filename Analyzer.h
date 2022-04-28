//
// Created by arek on 27.04.2022.
//

#ifndef CPP_CPU_TRUCKER_ANALYZER_H
#define CPP_CPU_TRUCKER_ANALYZER_H

#include <thread>
#include "SafeQueue.hpp"
#include "Reader.h"

struct cpu_usage {
    int cpu_num; // 0 is total cpu usage, 1 - first core
    float cpu_usage; // %
};

class Analyzer {
public:
    Analyzer() = delete;

    Analyzer(SafeQueue<std::vector<cpu_single_mess>> &queue_message_reader,
             SafeQueue<std::vector<cpu_usage>> &queue_message_printer, const bool &finish_work);

    ~Analyzer();

    float analyze_single_core(const cpu_single_mess &core_data, const cpu_single_mess &prev_core_data) const;

    std::thread start_thr();

private:
    SafeQueue<std::vector<cpu_single_mess>> &q_mess_reader;
    SafeQueue<std::vector<cpu_usage>> &q_mess_printer;
    const bool &f_work;

    void start();

};


#endif //CPP_CPU_TRUCKER_ANALYZER_H
