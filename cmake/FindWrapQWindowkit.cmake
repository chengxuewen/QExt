########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2023 ChengXueWen.
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

# We can't create the same interface imported target multiple times, CMake will complain if we do
# that. This can happen if the find_package call is done in multiple different subdirectories.
if(TARGET QExt3rdparty::WrapQWindowkit)
    set(WrapQWindowkit_FOUND ON)
    return()
endif()

add_library(QExt3rdparty::WrapQWindowkit INTERFACE IMPORTED)
set(QWINDOWKIT_DIR_NAME "qwindowkit-1.0.1")
set(QWINDOWKIT_URL_NAME "qwindowkit-1.0.1")
set(QWINDOWKIT_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QWINDOWKIT_URL_NAME}")
set(QWINDOWKIT_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QWINDOWKIT_DIR_NAME}")
set(QWINDOWKIT_BUILD_DIR "${QWINDOWKIT_ROOT_DIR}/build")
set(QWINDOWKIT_SOURCE_DIR "${QWINDOWKIT_ROOT_DIR}/source")
set(QWINDOWKIT_INSTALL_DIR "${QWINDOWKIT_ROOT_DIR}/install")
if(NOT EXISTS ${QWINDOWKIT_SOURCE_DIR})
    include(FetchContent)
    FetchContent_Declare(
        QExt-qwindowkit
        SOURCE_DIR ${QWINDOWKIT_SOURCE_DIR}
        BINARY_DIR ${QWINDOWKIT_BUILD_DIR}
        URL ${QWINDOWKIT_URL_PATH}
        DOWNLOAD_EXTRACT_TIMESTAMP FALSE)
    FetchContent_Populate(QExt-qwindowkit)
endif()
if(NOT EXISTS ${QWINDOWKIT_INSTALL_DIR})
    if(NOT EXISTS ${QWINDOWKIT_SOURCE_DIR})
        message(FATAL_ERROR "${QWINDOWKIT_DIR_NAME} FetchContent failed.")
    endif()
    execute_process(
        COMMAND ${CMAKE_COMMAND}
        -G${CMAKE_GENERATOR}
        -DQWINDOWKIT_BUILD_STATIC=ON
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_INSTALL_PREFIX=${QWINDOWKIT_INSTALL_DIR} ${QWINDOWKIT_SOURCE_DIR}
        WORKING_DIRECTORY "${QWINDOWKIT_BUILD_DIR}"
        RESULT_VARIABLE CONFIGURE_RESULT)
    if(CONFIGURE_RESULT MATCHES 0)
        message(STATUS "${QWINDOWKIT_DIR_NAME} configure success")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS} --config Release
            WORKING_DIRECTORY "${QWINDOWKIT_BUILD_DIR}"
            RESULT_VARIABLE BUILD_RESULT)
        if(BUILD_RESULT MATCHES 0)
            message(STATUS "${QWINDOWKIT_DIR_NAME} build success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --install ./
                WORKING_DIRECTORY "${QWINDOWKIT_BUILD_DIR}"
                RESULT_VARIABLE INSTALL_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${QWINDOWKIT_DIR_NAME} install success")
            else()
                message(FATAL_ERROR "${QWINDOWKIT_DIR_NAME} install failed.")
            endif()
        else()
            message(FATAL_ERROR "${QWINDOWKIT_DIR_NAME} build failed.")
        endif()
    else()
        message(FATAL_ERROR "${QWINDOWKIT_DIR_NAME} configure failed.")
    endif()
endif()
find_package(QWindowKit PATHS ${QWINDOWKIT_INSTALL_DIR} REQUIRED)
target_link_libraries(QExt3rdparty::WrapQWindowkit INTERFACE QWindowKit::Core QWindowKit::Widgets)
set(WrapQWindowkit_FOUND ON)
