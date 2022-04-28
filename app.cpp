//
// Created by arek on 26.04.2022.
//

#include <thread>
#include <iostream>
#include <unistd.h>
#include "app.h"


app::app() {
    finish_work = false;
    reader = new Reader(mess_reader_analyzer_queue, finish_work);
    analyzer = new Analyzer(mess_reader_analyzer_queue, mess_analyzer_printer_queue, finish_work);
    printer = new Printer(mess_analyzer_printer_queue, finish_work);
}

app::~app() {
    delete reader;
    delete analyzer;
    delete printer;
}

void app::start() {
    std::thread t_reader = reader->start_thr();
    std::thread t_analyzer = analyzer->start_thr();
    std::thread t_printer = printer->start_thr();

    // press enter to finish
    std::cin.get();
    finish_work = true;

    t_reader.join();
    t_analyzer.join();
    t_printer.join();
    std::cout << "Finish!\n";
}
