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

if(TARGET QExt3rdparty::Wrapmcap)
    set(Wrapmcap_FOUND ON)
    return()
endif()

set(QExtWrapmcap_DIR_NAME "mcap-releases-cpp-v1.4.2")
set(QExtWrapmcap_URL_NAME "mcap-releases-cpp-v1.4.2.tar.gz")
set(QExtWrapmcap_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapmcap_URL_NAME}")
set(QExtWrapmcap_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapmcap_DIR_NAME}")
set(QExtWrapmcap_SOURCE_DIR "${QExtWrapmcap_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(QExtWrapmcap_BUILD_DIR "${QExtWrapmcap_ROOT_DIR}/build" CACHE INTERNAL "" FORCE)
set(QExtWrapmcap_INSTALL_DIR "${QExtWrapmcap_ROOT_DIR}/install" CACHE INTERNAL "" FORCE)
qext_stamp_file_info(QExtWrapmcap OUTPUT_DIR "${QExtWrapmcap_ROOT_DIR}")
qext_fetch_3rdparty(QExtWrapmcap URL "${QExtWrapmcap_URL_PATH}")
if(NOT EXISTS ${QExtWrapmcap_STAMP_FILE_PATH})
    if(NOT EXISTS ${QExtWrapmcap_SOURCE_DIR})
        message(FATAL_ERROR "${QExtWrapmcap_DIR_NAME} FetchContent failed.")
    endif()
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QExtWrapmcap_BUILD_DIR}
        WORKING_DIRECTORY "${QExtWrapmcap_ROOT_DIR}"
        RESULT_VARIABLE MKDIR_RESULT)
    if(NOT (MKDIR_RESULT MATCHES 0))
        message(FATAL_ERROR "${QExtWrapmcap_DIR_NAME} lib build directory make failed.")
    endif()
    qext_make_stamp_file("${QExtWrapmcap_STAMP_FILE_PATH}")
endif()
# wrap lib
add_library(QExt3rdparty::Wrapmcap INTERFACE IMPORTED)
qext_find_package(Wraplz4 PROVIDED_TARGETS QExt3rdparty::Wraplz4)
qext_find_package(Wrapzstd PROVIDED_TARGETS QExt3rdparty::Wrapzstd)
target_link_libraries(QExt3rdparty::Wrapmcap INTERFACE QExt3rdparty::Wrapzstd QExt3rdparty::Wraplz4)
target_include_directories(QExt3rdparty::Wrapmcap INTERFACE "${QExtWrapmcap_SOURCE_DIR}/cpp/mcap/include")
set(Wrapmcap_FOUND ON)
