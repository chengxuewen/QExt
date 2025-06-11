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
if(TARGET QExt3rdparty::WrapBreakpad)
    set(WrapBreakpad_FOUND ON)
    return()
endif()

if(QEXT_FEATURE_USE_BREAKPAD_SOURCE)
    set(QExtWrapBreakpad_PKG_SOURCE TRUE)
elseif(WIN32)
    set(QExtWrapBreakpad_PKG_SOURCE FALSE)
    set(QExtWrapBreakpad_DIR_NAME "breakpad-windows-x64")
    set(QExtWrapBreakpad_PKG_NAME "breakpad-windows-x64.7z")
else()
    set(QExtWrapBreakpad_PKG_SOURCE TRUE)
endif()
if(QExtWrapBreakpad_PKG_SOURCE)
    set(QExtWrapBreakpad_DIR_NAME "breakpad-v2024.02.16")
    set(QExtWrapBreakpad_PKG_NAME "breakpad-v2024.02.16.7z")
endif()

set(QExtWrapBreakpad_PKG_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapBreakpad_PKG_NAME}")
set(QExtWrapBreakpad_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapBreakpad_DIR_NAME}")
set(QExtWrapBreakpad_SOURCE_DIR "${QExtWrapBreakpad_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(QExtWrapBreakpad_BUILD_DIR "${QExtWrapBreakpad_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(QExtWrapBreakpad_INSTALL_DIR "${QExtWrapBreakpad_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(QExtWrapBreakpad_USE_SOURCE "${QExtWrapBreakpad_PKG_SOURCE}" CACHE INTERNAL "" FORCE)
qext_stamp_file_info(QExtWrapBreakpad OUTPUT_DIR "${QExtWrapBreakpad_ROOT_DIR}")
qext_fetch_3rdparty(QExtWrapBreakpad URL "${QExtWrapBreakpad_PKG_PATH}")
if(NOT EXISTS ${QExtWrapBreakpad_STAMP_FILE_PATH})
    if(NOT EXISTS ${QExtWrapBreakpad_SOURCE_DIR})
        message(FATAL_ERROR "${QExtWrapBreakpad_DIR_NAME} FetchContent failed.")
    endif()
    qext_make_stamp_file("${QExtWrapBreakpad_STAMP_FILE_PATH}")
endif()
# wrap lib
if(QExtWrapBreakpad_PKG_SOURCE)
    add_library(QExt3rdparty::WrapBreakpad INTERFACE IMPORTED)
    target_include_directories(QExt3rdparty::WrapBreakpad INTERFACE ${QExtWrapBreakpad_SOURCE_DIR})
else()
    add_library(QExt3rdparty::WrapBreakpad STATIC IMPORTED)
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(QExtWrapBreakpad_LIBRARY "${QExtWrapBreakpad_INSTALL_DIR}/debug/lib/libbreakpadd.lib")
        list(APPEND QExtWrapBreakpad_DEPENDS
            "${QExtWrapBreakpad_INSTALL_DIR}/debug/lib/libbreakpad_clientd.lib"
            "${QExtWrapBreakpad_INSTALL_DIR}/debug/lib/libdisasmd.lib")
    else()
        set(QExtWrapBreakpad_LIBRARY "${QExtWrapBreakpad_INSTALL_DIR}/lib/libbreakpad.lib")
        list(APPEND QExtWrapBreakpad_DEPENDS
            "${QExtWrapBreakpad_INSTALL_DIR}/lib/libbreakpad_client.lib"
            "${QExtWrapBreakpad_INSTALL_DIR}/lib/libdisasm.lib")
    endif()
    set_target_properties(QExt3rdparty::WrapBreakpad PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES
        ${QExtWrapBreakpad_INSTALL_DIR}/include
        IMPORTED_LOCATION
        ${QExtWrapBreakpad_LIBRARY})
    target_link_libraries(QExt3rdparty::WrapBreakpad INTERFACE ${QExtWrapBreakpad_DEPENDS})
endif()
if(APPLE)
    # without c++11 & AppKit library compiler can't solve address for symbols
    target_link_libraries(QExt3rdparty::WrapBreakpad INTERFACE "-framework AppKit")
endif()

set(WrapBreakpad_FOUND ON)
