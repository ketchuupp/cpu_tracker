//
// Created by arek on 26.04.2022.
//

#include <iostream>
#include <csignal>
#include "app.h"

bool app::is_rise_sig_int = false;


app::app() {
    watchdog = new Watchdog();
    reader = new Reader(mess_reader_analyzer_queue, *watchdog);
    analyzer = new Analyzer(mess_reader_analyzer_queue, mess_analyzer_printer_queue, *watchdog);
    printer = new Printer(mess_analyzer_printer_queue, *watchdog);
    // register signal SIGINT and signal handler
    std::signal(SIGINT, app::signal_handler);
}

app::~app() {
    delete reader;
    delete analyzer;
    delete printer;
    delete watchdog;
}

void app::start() {
    t_watchdog = watchdog->start_thr();
    t_reader = reader->start_thr();
    t_analyzer = analyzer->start_thr();
    t_printer = printer->start_thr();

    while (!app::is_rise_sig_int)  {
        if (watchdog->is_finish())
            break;
    }
    if (!watchdog->is_finish())
        watchdog->set_finish_work();

    t_watchdog.join();
    t_reader.join();
    t_analyzer.join();
    t_printer.join();
}

void app::signal_handler(int sig_num){
    std::cout << "Interrupt signal (" << sig_num << ") received.\n";
    app::is_rise_sig_int = true;
}


