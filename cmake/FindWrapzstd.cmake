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

if(TARGET QExt3rdparty::Wrapzstd)
    set(Wrapzstd_FOUND ON)
    return()
endif()

set(QExtWrapzstd_DIR_NAME "zstd-1.5.7")
set(QExtWrapzstd_URL_NAME "zstd-1.5.7.tar.gz")
set(QExtWrapzstd_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapzstd_URL_NAME}")
set(QExtWrapzstd_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapzstd_DIR_NAME}")
set(QExtWrapzstd_SOURCE_DIR "${QExtWrapzstd_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(QExtWrapzstd_BUILD_DIR "${QExtWrapzstd_ROOT_DIR}/build" CACHE INTERNAL "" FORCE)
set(QExtWrapzstd_INSTALL_DIR "${QExtWrapzstd_ROOT_DIR}/install" CACHE INTERNAL "" FORCE)
qext_stamp_file_info(QExtWrapzstd OUTPUT_DIR "${QExtWrapzstd_ROOT_DIR}")
qext_fetch_3rdparty(QExtWrapzstd URL "${QExtWrapzstd_URL_PATH}")
if(NOT EXISTS ${QExtWrapzstd_STAMP_FILE_PATH})
    if(NOT EXISTS ${QExtWrapzstd_SOURCE_DIR})
        message(FATAL_ERROR "${QExtWrapzstd_DIR_NAME} FetchContent failed.")
    endif()
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QExtWrapzstd_BUILD_DIR}
        WORKING_DIRECTORY "${QExtWrapzstd_ROOT_DIR}"
        RESULT_VARIABLE MKDIR_RESULT)
    if(NOT (MKDIR_RESULT MATCHES 0))
        message(FATAL_ERROR "${QExtWrapzstd_DIR_NAME} lib build directory make failed.")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND}
        -G${CMAKE_GENERATOR}
        -DZSTD_BUILD_STATIC=ON
        -DZSTD_BUILD_SHARED=OFF
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_INSTALL_PREFIX=${QExtWrapzstd_INSTALL_DIR}
        "${QExtWrapzstd_SOURCE_DIR}/build/cmake"
        WORKING_DIRECTORY "${QExtWrapzstd_BUILD_DIR}"
        RESULT_VARIABLE CONFIGURE_RESULT)
    if(CONFIGURE_RESULT MATCHES 0)
        message(STATUS "${QExtWrapzstd_DIR_NAME} configure success")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS} --config Release
            WORKING_DIRECTORY "${QExtWrapzstd_BUILD_DIR}"
            RESULT_VARIABLE BUILD_RESULT)
        if(BUILD_RESULT MATCHES 0)
            message(STATUS "${QExtWrapzstd_DIR_NAME} build success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --install ./
                WORKING_DIRECTORY "${QExtWrapzstd_BUILD_DIR}"
                RESULT_VARIABLE INSTALL_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${QExtWrapzstd_DIR_NAME} install success")
                qext_make_stamp_file("${QExtWrapzstd_STAMP_FILE_PATH}")
            else()
                message(FATAL_ERROR "${QExtWrapzstd_DIR_NAME} install failed.")
            endif()
        else()
            message(FATAL_ERROR "${QExtWrapzstd_DIR_NAME} build failed.")
        endif()
    else()
        message(FATAL_ERROR "${QExtWrapzstd_DIR_NAME} configure failed.")
    endif()
endif()
# wrap lib
add_library(QExt3rdparty::Wrapzstd INTERFACE IMPORTED)
find_package(zstd PATHS ${QExtWrapzstd_INSTALL_DIR} REQUIRED)
target_link_libraries(QExt3rdparty::Wrapzstd INTERFACE zstd::libzstd_static)
set(Wrapzstd_FOUND ON)
