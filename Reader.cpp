//
// Created by arek on 26.04.2022.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include "Reader.h"
#include "SafeQueue.hpp"


Reader::Reader(SafeQueue<std::vector<cpu_single_mess>> &queue_message, Watchdog &watchdog)
        :
        q_mess_analyzer(queue_message), wdg(watchdog) {
}

void Reader::start() {
    using namespace std::chrono_literals;
    while (true) {
        if (wdg.is_finish() == true)
            break;
        if (q_mess_analyzer.get_size() > 10)
            continue;
        std::vector<cpu_single_mess> mess;
        read_single_proc_stat(mess);
        q_mess_analyzer.push(mess);
        wdg.reader_reload_watchdog();
        std::this_thread::sleep_for(1000ms);
    }
//    std::cout << "Reader finished!\n";
}

void Reader::read_single_proc_stat(std::vector<cpu_single_mess> &cpu_mess, std::string proc_path) {
    std::ifstream proc_file;
    proc_file.open(proc_path, std::ios::in);
    if (!proc_file.is_open()) // cannot open the file
        return;

    std::string line;
    while (getline(proc_file, line)) {
        cpu_single_mess csm;
//        std::cout << line << "\n";
        std::stringstream iss(line);
        iss >> csm.cpu;
        if (csm.cpu.substr(0, 3) != "cpu") {
            break;
        }

        auto get_param = [&iss]
                (long unsigned &data) {
            iss.ignore(1, ' ');
            iss >> data;
        };

        get_param(csm.user);
        get_param(csm.nice);
        get_param(csm.system);
        get_param(csm.idle);
        get_param(csm.io_wait);
        get_param(csm.irq);
        get_param(csm.soft_irq);
        get_param(csm.steal);

        cpu_mess.push_back(csm);

    }
    proc_file.close();
}

std::thread Reader::start_thr() {
    return std::thread([=] { start(); });
}
