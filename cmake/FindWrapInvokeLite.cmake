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
if(TARGET QExt3rdparty::WrapInvokeLite)
    set(QExtWrapInvokeLite_FOUND ON)
    return()
endif()

set(QExtWrapInvokeLite_DIR_NAME "invoke-lite-master")
set(QExtWrapInvokeLite_URL_NAME "invoke-lite-master.zip")
set(QExtWrapInvokeLite_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapInvokeLite_URL_NAME}")
set(QExtWrapInvokeLite_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapInvokeLite_DIR_NAME}")
set(QExtWrapInvokeLite_SOURCE_DIR "${QExtWrapInvokeLite_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(QExtWrapInvokeLite_BUILD_DIR "${QExtWrapInvokeLite_ROOT_DIR}/build" CACHE INTERNAL "" FORCE)
set(QExtWrapInvokeLite_INSTALL_DIR "${QExtWrapInvokeLite_ROOT_DIR}/install" CACHE INTERNAL "" FORCE)
qext_stamp_file_info(QExtWrapInvokeLite OUTPUT_DIR "${QExtWrapInvokeLite_ROOT_DIR}")
qext_fetch_3rdparty(QExtWrapInvokeLite URL "${QExtWrapInvokeLite_URL_PATH}")
if(NOT EXISTS ${QExtWrapInvokeLite_STAMP_FILE_PATH})
    if(NOT EXISTS ${QExtWrapInvokeLite_SOURCE_DIR})
        message(FATAL_ERROR "${QExtWrapInvokeLite_DIR_NAME} FetchContent failed.")
    endif()
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QExtWrapInvokeLite_BUILD_DIR}
        WORKING_DIRECTORY "${QExtWrapInvokeLite_ROOT_DIR}"
        RESULT_VARIABLE MKDIR_RESULT)
    if(NOT (MKDIR_RESULT MATCHES 0))
        message(FATAL_ERROR "${QExtWrapInvokeLite_DIR_NAME} lib build directory make failed.")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND}
        -G${CMAKE_GENERATOR}
        -DINVOKE_LITE_OPT_BUILD_TESTS=OFF
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_INSTALL_PREFIX=${QExtWrapInvokeLite_INSTALL_DIR}
        ${QExtWrapInvokeLite_SOURCE_DIR}
        WORKING_DIRECTORY "${QExtWrapInvokeLite_BUILD_DIR}"
        RESULT_VARIABLE CONFIGURE_RESULT)
    if(CONFIGURE_RESULT MATCHES 0)
        message(STATUS "${QExtWrapInvokeLite_DIR_NAME} configure success")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS}
            WORKING_DIRECTORY "${QExtWrapInvokeLite_BUILD_DIR}"
            RESULT_VARIABLE BUILD_RESULT)
        if(BUILD_RESULT MATCHES 0)
            message(STATUS "${QExtWrapInvokeLite_DIR_NAME} build success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --install ./
                WORKING_DIRECTORY "${QExtWrapInvokeLite_BUILD_DIR}"
                RESULT_VARIABLE INSTALL_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${QExtWrapInvokeLite_DIR_NAME} install success")
                qext_make_stamp_file("${QExtWrapInvokeLite_STAMP_FILE_PATH}")
            else()
                message(FATAL_ERROR "${QExtWrapInvokeLite_DIR_NAME} install failed.")
            endif()
        else()
            message(FATAL_ERROR "${QExtWrapInvokeLite_DIR_NAME} build failed.")
        endif()
    else()
        message(FATAL_ERROR "${QExtWrapInvokeLite_DIR_NAME} configure failed.")
    endif()
endif()
# wrap lib
add_library(QExt3rdparty::WrapInvokeLite INTERFACE IMPORTED)
find_package(invoke-lite HINTS ${QExtWrapInvokeLite_INSTALL_DIR} REQUIRED)
target_link_libraries(QExt3rdparty::WrapInvokeLite INTERFACE nonstd::invoke-lite)
set(QExtWrapInvokeLite_FOUND ON)
