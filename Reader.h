//
// Created by arek on 26.04.2022.
//

#ifndef CPP_CPU_TRUCKER_READER_H
#define CPP_CPU_TRUCKER_READER_H

#include <string>
#include <vector>
#include <thread>

#include "SafeQueue.hpp"

struct cpu_single_mess {
    std::string cpu;
    long unsigned user;
    long unsigned nice;
    long unsigned system;
    long unsigned idle;
    long unsigned io_wait;
    long unsigned irq;
    long unsigned soft_irq;
     unsigned long steal;
    // unsigned long guest;
    // unsigned long guest_nice;
};

class Reader {
public:
    Reader() = delete;

    Reader(SafeQueue<std::vector<cpu_single_mess>> &queue_message, const bool &finish_work);

    std::thread start_thr();

    void read_single_proc_stat(std::vector<cpu_single_mess> &cpu_mess, std::string proc_path = "/proc/stat");

private:
    SafeQueue<std::vector<cpu_single_mess>> &q_mess_analyzer;
    const bool &f_work;

    void start();

};


#endif //CPP_CPU_TRUCKER_READER_H
