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

if(TARGET QExt3rdparty::Wraplz4)
    set(Wraplz4_FOUND ON)
    return()
endif()

set(QExtWraplz4_DIR_NAME "lz4-1.10.0")
set(QExtWraplz4_URL_NAME "lz4-1.10.0.tar.gz")
set(QExtWraplz4_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWraplz4_URL_NAME}")
set(QExtWraplz4_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWraplz4_DIR_NAME}")
set(QExtWraplz4_SOURCE_DIR "${QExtWraplz4_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(QExtWraplz4_BUILD_DIR "${QExtWraplz4_ROOT_DIR}/build" CACHE INTERNAL "" FORCE)
set(QExtWraplz4_INSTALL_DIR "${QExtWraplz4_ROOT_DIR}/install" CACHE INTERNAL "" FORCE)
qext_stamp_file_info(QExtWraplz4 OUTPUT_DIR "${QExtWraplz4_ROOT_DIR}")
qext_fetch_3rdparty(QExtWraplz4 URL "${QExtWraplz4_URL_PATH}")
if(NOT EXISTS ${QExtWraplz4_STAMP_FILE_PATH})
    if(NOT EXISTS ${QExtWraplz4_SOURCE_DIR})
        message(FATAL_ERROR "${QExtWraplz4_DIR_NAME} FetchContent failed.")
    endif()
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QExtWraplz4_BUILD_DIR}
        WORKING_DIRECTORY "${QExtWraplz4_ROOT_DIR}"
        RESULT_VARIABLE MKDIR_RESULT)
    if(NOT (MKDIR_RESULT MATCHES 0))
        message(FATAL_ERROR "${QExtWraplz4_DIR_NAME} lib build directory make failed.")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND}
        -G${CMAKE_GENERATOR}
        -DBUILD_STATIC_LIBS=ON
        -DBUILD_SHARED_LIBS=OFF
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_INSTALL_PREFIX=${QExtWraplz4_INSTALL_DIR}
        "${QExtWraplz4_SOURCE_DIR}/build/cmake"
        WORKING_DIRECTORY "${QExtWraplz4_BUILD_DIR}"
        RESULT_VARIABLE CONFIGURE_RESULT)
    if(CONFIGURE_RESULT MATCHES 0)
        message(STATUS "${QExtWraplz4_DIR_NAME} configure success")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS} --config Release
            WORKING_DIRECTORY "${QExtWraplz4_BUILD_DIR}"
            RESULT_VARIABLE BUILD_RESULT)
        if(BUILD_RESULT MATCHES 0)
            message(STATUS "${QExtWraplz4_DIR_NAME} build success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --install ./
                WORKING_DIRECTORY "${QExtWraplz4_BUILD_DIR}"
                RESULT_VARIABLE INSTALL_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${QExtWraplz4_DIR_NAME} install success")
                qext_make_stamp_file("${QExtWraplz4_STAMP_FILE_PATH}")
            else()
                message(FATAL_ERROR "${QExtWraplz4_DIR_NAME} install failed.")
            endif()
        else()
            message(FATAL_ERROR "${QExtWraplz4_DIR_NAME} build failed.")
        endif()
    else()
        message(FATAL_ERROR "${QExtWraplz4_DIR_NAME} configure failed.")
    endif()
endif()
# wrap lib
add_library(QExt3rdparty::Wraplz4 INTERFACE IMPORTED)
find_package(lz4 PATHS ${QExtWraplz4_INSTALL_DIR} REQUIRED)
target_link_libraries(QExt3rdparty::Wraplz4 INTERFACE LZ4::lz4_static)
set(Wraplz4_FOUND ON)
