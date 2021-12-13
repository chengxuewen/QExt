cmake_minimum_required(VERSION 3.14)
project(graphicsproxy_example VERSION 0.0.1 LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/mvvm)
set(LIBRARY_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/mvvm)

set(executable_name qext_exp_mvvmGraphicsProxy)
add_subdirectory(graphicsproxycore)
add_executable(${executable_name} main.cpp)

target_link_libraries(${executable_name} graphicsproxycore Qt5::Gui Qt5::Widgets QEXTMvvm)
target_include_directories(${executable_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
