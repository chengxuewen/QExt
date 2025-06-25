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
elseif(EXISTS "${PROJECT_SOURCE_DIR}/3rdparty/breakpad-${QEXT_PLATFORM_NAME}.7z")
    set(QExtWrapBreakpad_PKG_SOURCE FALSE)
    set(QExtWrapBreakpad_DIR_NAME "breakpad-${QEXT_PLATFORM_NAME}")
    set(QExtWrapBreakpad_PKG_NAME "breakpad-${QEXT_PLATFORM_NAME}.7z")
elseif(UNIX)
    set(QExtWrapBreakpad_PKG_SOURCE TRUE)
    set(QExtWrapBreakpad_USE_SOURCE "OFF" CACHE INTERNAL "" FORCE)
else()
    set(QExtWrapBreakpad_PKG_SOURCE TRUE)
    set(QExtWrapBreakpad_USE_SOURCE "ON" CACHE INTERNAL "" FORCE)
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
    if(WIN32)
        target_include_directories(QExt3rdparty::WrapBreakpad INTERFACE ${QExtWrapBreakpad_SOURCE_DIR})
    else()
        set(QExtWrapBreakpad_INSTALL_DIR "${QExtWrapBreakpad_ROOT_DIR}/install" CACHE INTERNAL "" FORCE)
        if(NOT EXISTS ${QExtWrapBreakpad_SOURCE_DIR})
            message(FATAL_ERROR "${QExtWrapBreakpad_DIR_NAME} FetchContent failed.")
        endif()
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E make_directory ${QExtWrapBreakpad_BUILD_DIR}
            WORKING_DIRECTORY "${QExtWrapBreakpad_ROOT_DIR}"
            RESULT_VARIABLE MKDIR_RESULT)
        if(NOT (MKDIR_RESULT MATCHES 0))
            message(FATAL_ERROR "${QExtWrapBreakpad_DIR_NAME} lib build directory make failed.")
        endif()
        execute_process(
            COMMAND ./configure --prefix=${QExtWrapBreakpad_INSTALL_DIR}
            WORKING_DIRECTORY "${QExtWrapBreakpad_BUILD_DIR}"
            RESULT_VARIABLE CONFIGURE_RESULT)
        if(CONFIGURE_RESULT MATCHES 0)
            message(STATUS "${QExtWrapBreakpad_DIR_NAME} configure success")
            execute_process(
                COMMAND make -j${QEXT_NUMBER_OF_ASYNC_JOBS}
                WORKING_DIRECTORY "${QExtWrapBreakpad_BUILD_DIR}"
                RESULT_VARIABLE BUILD_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${QExtWrapBreakpad_DIR_NAME} build success")
                execute_process(
                    COMMAND make install
                    WORKING_DIRECTORY "${QExtWrapBreakpad_BUILD_DIR}"
                    RESULT_VARIABLE INSTALL_RESULT)
                if(BUILD_RESULT MATCHES 0)
                    message(STATUS "${QExtWrapBreakpad_DIR_NAME} install success")
                else()
                    message(FATAL_ERROR "${QExtWrapBreakpad_DIR_NAME} install failed.")
                endif()
            else()
                message(FATAL_ERROR "${QExtWrapBreakpad_DIR_NAME} build failed.")
            endif()
        else()
            message(FATAL_ERROR "${QExtWrapBreakpad_DIR_NAME} configure failed.")
        endif()
        find_package(PkgConfig REQUIRED)
        set(_cache_CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH})
        set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QExtWrapBreakpad_INSTALL_DIR})
        pkg_search_module(WrapBreakpad breakpad REQUIRED IMPORTED_TARGET)
        pkg_search_module(WrapBreakpadClient breakpad-client REQUIRED IMPORTED_TARGET)
        set(CMAKE_PREFIX_PATH ${_cache_CMAKE_PREFIX_PATH})
        target_link_libraries(QExt3rdparty::WrapBreakpad INTERFACE
            PkgConfig::WrapBreakpad PkgConfig::WrapBreakpadClient pthread)
    endif()
else()
    add_library(QExt3rdparty::WrapBreakpad STATIC IMPORTED)
    if(WIN32)
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
    else()
        if(CMAKE_BUILD_TYPE MATCHES "Debug")
            set(QExtWrapBreakpad_LIBRARY "${QExtWrapBreakpad_INSTALL_DIR}/debug/lib/liblibbreakpadd.a")
            list(APPEND QExtWrapBreakpad_DEPENDS
                "${QExtWrapBreakpad_INSTALL_DIR}/debug/lib/liblibbreakpad_clientd.a"
                "${QExtWrapBreakpad_INSTALL_DIR}/debug/lib/liblibdisasmd.a")
        else()
            set(QExtWrapBreakpad_LIBRARY "${QExtWrapBreakpad_INSTALL_DIR}/lib/liblibbreakpad.a")
            list(APPEND QExtWrapBreakpad_DEPENDS
                "${QExtWrapBreakpad_INSTALL_DIR}/lib/liblibbreakpad_client.a"
                "${QExtWrapBreakpad_INSTALL_DIR}/lib/liblibdisasm.a")
        endif()
        if(EXISTS "${QExtWrapBreakpad_INSTALL_DIR}/bin")
            execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${QExtWrapBreakpad_INSTALL_DIR}/bin"
                "${QEXT_BUILD_DIR}/${QEXT_DEFAULT_LIBEXEC}")
        endif()
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
