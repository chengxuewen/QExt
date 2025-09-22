########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
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
if(TARGET QExt3rdparty::WrapStringViewLite)
    set(QExtWrapStringViewLite_FOUND ON)
    return()
endif()

set(QExtWrapStringViewLite_NAME "string-view-lite-1.8.0")
set(QExtWrapStringViewLite_DIR_NAME "${QExtWrapStringViewLite_NAME}")
set(QExtWrapStringViewLite_URL_NAME "${QExtWrapStringViewLite_NAME}.tar.gz")
set(QExtWrapStringViewLite_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapStringViewLite_URL_NAME}")
set(QExtWrapStringViewLite_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapStringViewLite_DIR_NAME}")
set(QExtWrapStringViewLite_SOURCE_DIR "${QExtWrapStringViewLite_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(QExtWrapStringViewLite_BUILD_DIR "${QExtWrapStringViewLite_ROOT_DIR}/build" CACHE INTERNAL "" FORCE)
set(QExtWrapStringViewLite_INSTALL_DIR "${QExtWrapStringViewLite_ROOT_DIR}/install" CACHE INTERNAL "" FORCE)
qext_stamp_file_info(QExtWrapStringViewLite OUTPUT_DIR "${QExtWrapStringViewLite_ROOT_DIR}")
qext_fetch_3rdparty(QExtWrapStringViewLite URL "${QExtWrapStringViewLite_URL_PATH}")
if(NOT EXISTS ${QExtWrapStringViewLite_STAMP_FILE_PATH})
    if(NOT EXISTS ${QExtWrapStringViewLite_SOURCE_DIR})
        message(FATAL_ERROR "${QExtWrapStringViewLite_DIR_NAME} FetchContent failed.")
    endif()
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QExtWrapStringViewLite_BUILD_DIR}
        WORKING_DIRECTORY "${QExtWrapStringViewLite_ROOT_DIR}"
        RESULT_VARIABLE MKDIR_RESULT)
    if(NOT (MKDIR_RESULT MATCHES 0))
        message(FATAL_ERROR "${QExtWrapStringViewLite_DIR_NAME} lib build directory make failed.")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND}
        -G${CMAKE_GENERATOR}
        -DVARIANT_LITE_OPT_BUILD_TESTS=OFF
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_INSTALL_PREFIX=${QExtWrapStringViewLite_INSTALL_DIR}
        ${QExtWrapStringViewLite_SOURCE_DIR}
        WORKING_DIRECTORY "${QExtWrapStringViewLite_BUILD_DIR}"
        RESULT_VARIABLE CONFIGURE_RESULT)
    if(CONFIGURE_RESULT MATCHES 0)
        message(STATUS "${QExtWrapStringViewLite_DIR_NAME} configure success")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS}
            WORKING_DIRECTORY "${QExtWrapStringViewLite_BUILD_DIR}"
            RESULT_VARIABLE BUILD_RESULT)
        if(BUILD_RESULT MATCHES 0)
            message(STATUS "${QExtWrapStringViewLite_DIR_NAME} build success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --install ./
                WORKING_DIRECTORY "${QExtWrapStringViewLite_BUILD_DIR}"
                RESULT_VARIABLE INSTALL_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${QExtWrapStringViewLite_DIR_NAME} install success")
                qext_make_stamp_file("${QExtWrapStringViewLite_STAMP_FILE_PATH}")
            else()
                message(FATAL_ERROR "${QExtWrapStringViewLite_DIR_NAME} install failed.")
            endif()
        else()
            message(FATAL_ERROR "${QExtWrapStringViewLite_DIR_NAME} build failed.")
        endif()
    else()
        message(FATAL_ERROR "${QExtWrapStringViewLite_DIR_NAME} configure failed.")
    endif()
endif()
# wrap lib
add_library(QExt3rdparty::WrapStringViewLite INTERFACE IMPORTED)
find_package(string-view-lite PATHS ${QExtWrapStringViewLite_INSTALL_DIR} REQUIRED)
target_link_libraries(QExt3rdparty::WrapStringViewLite INTERFACE nonstd::string-view-lite)
set(QExtWrapStringViewLite_FOUND ON)
