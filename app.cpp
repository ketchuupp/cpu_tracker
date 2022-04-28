//
// Created by arek on 26.04.2022.
//

#include <thread>
#include <iostream>
#include "app.h"


app::app() {
    watchdog = new Watchdog();
    reader = new Reader(mess_reader_analyzer_queue, *watchdog);
    analyzer = new Analyzer(mess_reader_analyzer_queue, mess_analyzer_printer_queue, *watchdog);
    printer = new Printer(mess_analyzer_printer_queue, *watchdog);

}

app::~app() {
    delete reader;
    delete analyzer;
    delete printer;
    delete watchdog;
}

void app::start() {
    std::thread t_watchdog = watchdog->start_thr();
    std::thread t_reader = reader->start_thr();
    std::thread t_analyzer = analyzer->start_thr();
    std::thread t_printer = printer->start_thr();

    std::cin.get();
    watchdog->set_finish_work();

    t_watchdog.join();
    t_reader.join();
    t_analyzer.join();
    t_printer.join();
}

