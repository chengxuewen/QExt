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

set(QExtWrapQWindowkit_DIR_NAME "qwindowkit-1.4.0")
set(QExtWrapQWindowkit_URL_NAME "qwindowkit-1.4.0.7z")
set(QExtWrapQWindowkit_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapQWindowkit_URL_NAME}")
set(QExtWrapQWindowkit_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapQWindowkit_DIR_NAME}")
set(QExtWrapQWindowkit_SOURCE_DIR "${QExtWrapQWindowkit_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(QExtWrapQWindowkit_BUILD_DIR "${QExtWrapQWindowkit_ROOT_DIR}/build/${CMAKE_BUILD_TYPE}" CACHE INTERNAL "" FORCE)
set(QExtWrapQWindowkit_INSTALL_DIR "${QExtWrapQWindowkit_ROOT_DIR}/install/${CMAKE_BUILD_TYPE}" CACHE INTERNAL "" FORCE)
qext_stamp_file_info(QExtWrapQWindowkit OUTPUT_DIR "${QExtWrapQWindowkit_ROOT_DIR}")
qext_fetch_3rdparty(QExtWrapQWindowkit URL "${QExtWrapQWindowkit_URL_PATH}")
if(NOT EXISTS ${QExtWrapQWindowkit_STAMP_FILE_PATH})
    if(NOT EXISTS ${QExtWrapQWindowkit_SOURCE_DIR})
        message(FATAL_ERROR "${QExtWrapQWindowkit_DIR_NAME} FetchContent failed.")
    endif()
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QExtWrapQWindowkit_BUILD_DIR}
        WORKING_DIRECTORY "${QExtWrapQWindowkit_ROOT_DIR}"
        RESULT_VARIABLE MKDIR_RESULT)
    if(NOT (MKDIR_RESULT MATCHES 0))
        message(FATAL_ERROR "${QExtWrapQWindowkit_DIR_NAME} lib build directory make failed.")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND}
        -G${CMAKE_GENERATOR}
        -DQWINDOWKIT_BUILD_STATIC=ON
        -DQWINDOWKIT_BUILD_QUICK=ON
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_INSTALL_PREFIX=${QExtWrapQWindowkit_INSTALL_DIR} ${QExtWrapQWindowkit_SOURCE_DIR}
        WORKING_DIRECTORY "${QExtWrapQWindowkit_BUILD_DIR}"
        RESULT_VARIABLE CONFIGURE_RESULT)
    if(CONFIGURE_RESULT MATCHES 0)
        message(STATUS "${QExtWrapQWindowkit_DIR_NAME} configure success")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS}
            WORKING_DIRECTORY "${QExtWrapQWindowkit_BUILD_DIR}"
            RESULT_VARIABLE BUILD_RESULT)
        if(BUILD_RESULT MATCHES 0)
            message(STATUS "${QExtWrapQWindowkit_DIR_NAME} build success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --install ./
                WORKING_DIRECTORY "${QExtWrapQWindowkit_BUILD_DIR}"
                RESULT_VARIABLE INSTALL_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${QExtWrapQWindowkit_DIR_NAME} install success")
                qext_make_stamp_file("${QExtWrapQWindowkit_STAMP_FILE_PATH}")
            else()
                message(FATAL_ERROR "${QExtWrapQWindowkit_DIR_NAME} install failed.")
            endif()
        else()
            message(FATAL_ERROR "${QExtWrapQWindowkit_DIR_NAME} build failed.")
        endif()
    else()
        message(FATAL_ERROR "${QExtWrapQWindowkit_DIR_NAME} configure failed.")
    endif()
endif()
# wrap lib
find_package(QWindowKit PATHS ${QExtWrapQWindowkit_INSTALL_DIR} REQUIRED)
add_library(QExt3rdparty::WrapQWindowkit INTERFACE IMPORTED)
target_link_libraries(QExt3rdparty::WrapQWindowkit INTERFACE QWindowKit::Core QWindowKit::Widgets)
set(WrapQWindowkit_FOUND ON)
