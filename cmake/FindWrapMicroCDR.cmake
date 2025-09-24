########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2025 ChengXueWen.
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

if(TARGET QExt3rdparty::WrapMicroCDR)
    set(QExtWrapMicroCDR_FOUND ON)
    return()
endif()

set(QExtWrapMicroCDR_DIR_NAME "Micro-CDR-2.0.1")
set(QExtWrapMicroCDR_URL_NAME "Micro-CDR-2.0.1.tar.gz")
set(QExtWrapMicroCDR_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapMicroCDR_URL_NAME}")
set(QExtWrapMicroCDR_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapMicroCDR_DIR_NAME}")
set(QExtWrapMicroCDR_SOURCE_DIR "${QExtWrapMicroCDR_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(QExtWrapMicroCDR_BUILD_DIR "${QExtWrapMicroCDR_ROOT_DIR}/build" CACHE INTERNAL "" FORCE)
set(QExtWrapMicroCDR_INSTALL_DIR "${QExtWrapMicroCDR_ROOT_DIR}/install" CACHE INTERNAL "" FORCE)
qext_stamp_file_info(QExtWrapMicroCDR OUTPUT_DIR "${QExtWrapMicroCDR_ROOT_DIR}")
qext_fetch_3rdparty(QExtWrapMicroCDR URL "${QExtWrapMicroCDR_URL_PATH}")
if(NOT EXISTS ${QExtWrapMicroCDR_STAMP_FILE_PATH})
    if(NOT EXISTS ${QExtWrapMicroCDR_SOURCE_DIR})
        message(FATAL_ERROR "${QExtWrapMicroCDR_DIR_NAME} FetchContent failed.")
    endif()
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QExtWrapMicroCDR_BUILD_DIR}
        WORKING_DIRECTORY "${QExtWrapMicroCDR_ROOT_DIR}"
        RESULT_VARIABLE MKDIR_RESULT)
    if(NOT (MKDIR_RESULT MATCHES 0))
        message(FATAL_ERROR "${QExtWrapMicroCDR_DIR_NAME} lib build directory make failed.")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND}
        # -G${CMAKE_GENERATOR} ninja build failed in win
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_INSTALL_PREFIX=${QExtWrapMicroCDR_INSTALL_DIR}
        ${QExtWrapMicroCDR_SOURCE_DIR}
        WORKING_DIRECTORY "${QExtWrapMicroCDR_BUILD_DIR}"
        RESULT_VARIABLE CONFIGURE_RESULT)
    if(CONFIGURE_RESULT MATCHES 0)
        message(STATUS "${QExtWrapMicroCDR_DIR_NAME} configure success")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS} --config Release
            WORKING_DIRECTORY "${QExtWrapMicroCDR_BUILD_DIR}"
            RESULT_VARIABLE BUILD_RESULT)
        if(BUILD_RESULT MATCHES 0)
            message(STATUS "${QExtWrapMicroCDR_DIR_NAME} build success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --install ./
                WORKING_DIRECTORY "${QExtWrapMicroCDR_BUILD_DIR}"
                RESULT_VARIABLE INSTALL_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${QExtWrapMicroCDR_DIR_NAME} install success")
                qext_make_stamp_file("${QExtWrapMicroCDR_STAMP_FILE_PATH}")
            else()
                message(FATAL_ERROR "${QExtWrapMicroCDR_DIR_NAME} install failed.")
            endif()
        else()
            message(FATAL_ERROR "${QExtWrapMicroCDR_DIR_NAME} build failed.")
        endif()
    else()
        message(FATAL_ERROR "${QExtWrapMicroCDR_DIR_NAME} configure failed.")
    endif()
endif()
# wrap lib
add_library(QExt3rdparty::WrapMicroCDR INTERFACE IMPORTED)
list(APPEND CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ${QExtWrapMicroCDR_INSTALL_DIR})
find_package(microcdr HINTS ${QExtWrapMicroCDR_INSTALL_DIR} REQUIRED)
target_link_libraries(QExt3rdparty::WrapMicroCDR INTERFACE microcdr)
set(QExtWrapMicroCDR_FOUND ON)
