cmake_minimum_required(VERSION 3.14)
project(concurrentplot_example VERSION 0.0.1 LANGUAGES CXX)

set(executable_name qext_exp_mvvmConcurrentPlot)
add_subdirectory(concurrentplotcore)
add_executable(${executable_name} main.cpp)

target_link_libraries(${executable_name} concurrentplotcore Qt5::Gui Qt5::Widgets QEXTMvvm pthread)
target_include_directories(${executable_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
