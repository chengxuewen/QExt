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
if(TARGET QExt3rdparty::WrapLuaJIT)
    set(WrapLuaJIT_FOUND ON)
    return()
endif()

set(QExtWrapLuaJIT_DIR_NAME "LuaJIT-2.1.0-beta3")
set(QExtWrapLuaJIT_URL_NAME "LuaJIT-2.1.0-beta3.zip")
set(QExtWrapLuaJIT_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapLuaJIT_URL_NAME}")
set(QExtWrapLuaJIT_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapLuaJIT_DIR_NAME}")
set(QExtWrapLuaJIT_SOURCE_DIR "${QExtWrapLuaJIT_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(QExtWrapLuaJIT_BUILD_DIR "${QExtWrapLuaJIT_ROOT_DIR}/build" CACHE INTERNAL "" FORCE)
set(QExtWrapLuaJIT_INSTALL_DIR "${QExtWrapLuaJIT_ROOT_DIR}/install" CACHE INTERNAL "" FORCE)
qext_stamp_file_info(QExtWrapLuaJIT OUTPUT_DIR "${QExtWrapLuaJIT_ROOT_DIR}")
qext_fetch_3rdparty(QExtWrapLuaJIT URL "${QExtWrapLuaJIT_URL_PATH}")
if(NOT EXISTS ${QExtWrapLuaJIT_STAMP_FILE_PATH})
    if(NOT EXISTS ${QExtWrapLuaJIT_SOURCE_DIR})
        message(FATAL_ERROR "${QExtWrapLuaJIT_DIR_NAME} FetchContent failed.")
    endif()
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QExtWrapLuaJIT_BUILD_DIR}
        WORKING_DIRECTORY "${QExtWrapLuaJIT_ROOT_DIR}"
        RESULT_VARIABLE MKDIR_RESULT)
    if(NOT (MKDIR_RESULT MATCHES 0))
        message(FATAL_ERROR "${QExtWrapLuaJIT_DIR_NAME} lib build directory make failed.")
    endif()


    if(WIN32)
        if(MINGW)

        else()

        endif()
    else()

    endif()
    if(OFF)
    execute_process(
        COMMAND ${CMAKE_COMMAND}
        -G${CMAKE_GENERATOR}
        -DINVOKE_LITE_OPT_BUILD_TESTS=OFF
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_INSTALL_PREFIX=${QExtWrapLuaJIT_INSTALL_DIR}
        ${QExtWrapLuaJIT_SOURCE_DIR}
        WORKING_DIRECTORY "${QExtWrapLuaJIT_BUILD_DIR}"
        RESULT_VARIABLE CONFIGURE_RESULT)
    if(CONFIGURE_RESULT MATCHES 0)
        message(STATUS "${QExtWrapLuaJIT_DIR_NAME} configure success")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS}
            WORKING_DIRECTORY "${QExtWrapLuaJIT_BUILD_DIR}"
            RESULT_VARIABLE BUILD_RESULT)
        if(BUILD_RESULT MATCHES 0)
            message(STATUS "${QExtWrapLuaJIT_DIR_NAME} build success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --install ./
                WORKING_DIRECTORY "${QExtWrapLuaJIT_BUILD_DIR}"
                RESULT_VARIABLE INSTALL_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${QExtWrapLuaJIT_DIR_NAME} install success")
                qext_make_stamp_file("${QExtWrapLuaJIT_STAMP_FILE_PATH}")
            else()
                message(FATAL_ERROR "${QExtWrapLuaJIT_DIR_NAME} install failed.")
            endif()
        else()
            message(FATAL_ERROR "${QExtWrapLuaJIT_DIR_NAME} build failed.")
        endif()
    else()
        message(FATAL_ERROR "${QExtWrapLuaJIT_DIR_NAME} configure failed.")
    endif()
    endif()
endif()
# wrap lib
add_library(QExt3rdparty::WrapLuaJIT INTERFACE IMPORTED)
set(WrapLuaJIT_FOUND ON)
