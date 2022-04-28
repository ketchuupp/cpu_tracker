//
// Created by arek on 27.04.2022.
//
#include <iostream>
#include <iomanip>
#include "Analyzer.h"

Analyzer::Analyzer(SafeQueue<std::vector<cpu_single_mess>> &queue_message_reader,
                   SafeQueue<std::vector<cpu_usage>> &queue_message_printer, const bool &finish_work)
        :
        q_mess_reader(queue_message_reader),
        q_mess_printer(queue_message_printer),
        f_work(finish_work) {

}

Analyzer::~Analyzer() {

}

void Analyzer::start() {

    std::vector<cpu_single_mess> prev_message;

    while (true) {
        if (f_work == true)
            break;
        if (q_mess_reader.get_size() == 0)
            continue;
        std::vector<cpu_single_mess> message = q_mess_reader.pop();

        // for first iteration
        if (prev_message.empty()) {
            prev_message = message;
            continue;
        }

        std::vector<cpu_usage> v_cpu_usage;
        for (size_t i = 0; i != message.size(); i++) {
            float cpu_usage = analyze_single_core(message.at(i), prev_message.at(i));
            v_cpu_usage.push_back({static_cast<int>(i), cpu_usage});
        }
        q_mess_printer.push(v_cpu_usage);
        prev_message = std::move(message);
    }

//    std::cout << "Analyzer finished!\n";
}

std::thread Analyzer::start_thr() {
    return std::thread([=] { start(); });
}

float Analyzer::analyze_single_core(const cpu_single_mess &core_data, const cpu_single_mess &prev_core_data) const {
    long long PrevIdle;
    long long PrevNonIdle;
    long long PrevTotal;
    long long Idle;
    long long NonIdle;
    long long Total;

    PrevIdle = prev_core_data.idle + prev_core_data.io_wait;
    Idle = core_data.idle + core_data.io_wait;

    PrevNonIdle = prev_core_data.user
                  + prev_core_data.nice
                  + prev_core_data.system
                  + prev_core_data.irq
                  + prev_core_data.soft_irq
                  + prev_core_data.steal;

    NonIdle = core_data.user
              + core_data.nice
              + core_data.system
              + core_data.irq
              + core_data.soft_irq
              + core_data.steal;

    PrevTotal = PrevIdle + PrevNonIdle;
    Total = Idle + NonIdle;

    // differentiate: actual value minus the previous one
    float totald = Total - PrevTotal;
    float idled = Idle - PrevIdle;

    return (totald - idled) / totald * 100;
}


