cmake_minimum_required(VERSION 3.21)
project(cpp_cpu_trucker)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(cpp_cpu_trucker main.cpp app.cpp app.h Reader.cpp Reader.h SafeQueue.hpp Analyzer.cpp Analyzer.h Printer.cpp Printer.h)
