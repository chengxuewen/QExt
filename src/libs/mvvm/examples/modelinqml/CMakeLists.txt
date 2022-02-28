cmake_minimum_required(VERSION 3.14)
project(modelinqml_example VERSION 0.0.1 LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/mvvm)
set(LIBRARY_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/mvvm)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::PrintSupport
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets
        Qt${QEXT_QT_VERSION_MAJOR}::Quick
        Qt${QEXT_QT_VERSION_MAJOR}::Qml
        )
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

set(executable_name qext_exp_mvvmModelInQml)
add_subdirectory(modelinqmlcore)
add_executable(${executable_name} main.cpp ${CMAKE_CURRENT_LIST_DIR}/qml/app.qrc)

target_link_libraries(${executable_name} modelinqmlcore ${QEXT_EXAMPLE_LINK_LIBRARIES} QEXTMvvm)
target_include_directories(${executable_name} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
