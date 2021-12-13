cmake_minimum_required(VERSION 3.14)
project(helloworld_example VERSION 0.0.1 LANGUAGES CXX)

set(executable_name qext_exp_mvvmHelloWorld)
add_executable(${executable_name} main.cpp)

target_link_libraries(${executable_name} PRIVATE Qt5::Gui Qt5::Widgets QEXTMvvm)
