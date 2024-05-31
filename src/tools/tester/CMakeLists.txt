########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2021~Present ChengXueWen. Contact: 1398831004@qq.com.
#
# License: MIT License
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
# to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions
# of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE  AUTHORS
# OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
########################################################################################################################


#-----------------------------------------------------------------------------------------------------------------------
# Set app link libraries
#-----------------------------------------------------------------------------------------------------------------------
if(WIN32)
    list(APPEND QEXT_APP_LINK_LIBRARIES shlwapi.lib)
endif()
if(UNIX)
    list(APPEND QEXT_APP_LINK_LIBRARIES ${CMAKE_DL_LIBS})
endif()
if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND QEXT_APP_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_APP_LINK_LIBRARIES Qt4::QtCore)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_APP_LINK_LIBRARIES Qt${QEXT_QT_VERSION_MAJOR}::Core)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Add app target
#-----------------------------------------------------------------------------------------------------------------------
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/qextCTestRunnerConfig.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/qextCTestRunnerConfig.h")
qext_add_executable(QExtCTester
    SOURCES
    ${CMAKE_CURRENT_BINARY_DIR}/qextCTestRunnerConfig.h
    qextCTestRunner.h
    main.cpp
    OUTPUT_SUBDIR
    tester
    INCLUDE_DIRECTORIES
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    LIBRARIES
    ${QEXT_APP_LINK_LIBRARIES})
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/qextAllTestRunnerConfig.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/qextAllTestRunnerConfig.h")
qext_add_executable(QExtTesterAll
    SOURCES
    ${CMAKE_CURRENT_BINARY_DIR}/qextAllTestRunnerConfig.h
    qextTestOutputAll.cpp
    qextTestRunner.h
    OUTPUT_SUBDIR
    tester
    INCLUDE_DIRECTORIES
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    LIBRARIES
    ${QEXT_APP_LINK_LIBRARIES})
qext_add_executable(QExtTesterFailure
    SOURCES
    ${CMAKE_CURRENT_BINARY_DIR}/qextAllTestRunnerConfig.h
    qextTestOutputFailure.cpp
    qextTestRunner.h
    OUTPUT_SUBDIR
    tester
    INCLUDE_DIRECTORIES
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    LIBRARIES
    ${QEXT_APP_LINK_LIBRARIES})
