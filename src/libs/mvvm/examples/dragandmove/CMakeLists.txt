cmake_minimum_required(VERSION 3.14)
project(dragandmove_example VERSION 0.0.1 LANGUAGES CXX)

set(executable_name qext_exp_mvvmDragandMove)
add_subdirectory(dragandmovecore)
add_executable(${executable_name} main.cpp)

target_link_libraries(${executable_name} dragandmovecore Qt5::Gui Qt5::Widgets QEXTMvvm)
target_include_directories(${executable_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
