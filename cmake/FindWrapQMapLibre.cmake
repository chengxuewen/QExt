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

# We can't create the same interface imported target multiple times, CMake will complain if we do
# that. This can happen if the find_package call is done in multiple different subdirectories.
if(TARGET QExt3rdparty::WrapQMapLibre)
    set(QExtWrapQMapLibre_FOUND ON)
    return()
endif()

set(QExtWrapQMapLibre_DIR_NAME "maplibre-native-qt")
set(QExtWrapQMapLibre_URL_NAME "${QExtWrapQMapLibre_DIR_NAME}")
set(QExtWrapQMapLibre_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapQMapLibre_URL_NAME}")
set(QExtWrapQMapLibre_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapQMapLibre_DIR_NAME}")
set(QExtWrapQMapLibre_SOURCE_DIR "${QExtWrapQMapLibre_URL_PATH}" CACHE INTERNAL "" FORCE)
set(QExtWrapQMapLibre_BUILD_DIR "${QExtWrapQMapLibre_ROOT_DIR}/build/${CMAKE_BUILD_TYPE}" CACHE INTERNAL "" FORCE)
set(QExtWrapQMapLibre_INSTALL_DIR "${QExtWrapQMapLibre_ROOT_DIR}/install/${CMAKE_BUILD_TYPE}" CACHE INTERNAL "" FORCE)
qext_stamp_file_info(QExtWrapQMapLibre OUTPUT_DIR "${QExtWrapQMapLibre_ROOT_DIR}")
# qext_fetch_3rdparty(QExtWrapQMapLibre URL "${QExtWrapQMapLibre_URL_PATH}")
if(NOT EXISTS ${QExtWrapQMapLibre_STAMP_FILE_PATH})
    if(NOT EXISTS ${QExtWrapQMapLibre_SOURCE_DIR})
        message(FATAL_ERROR "${QExtWrapQMapLibre_DIR_NAME} FetchContent failed.")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QExtWrapQMapLibre_ROOT_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QExtWrapQMapLibre_BUILD_DIR}
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/3rdparty"
        RESULT_VARIABLE MKDIR_RESULT)
    if(NOT (MKDIR_RESULT MATCHES 0))
        message(FATAL_ERROR "${QExtWrapQMapLibre_DIR_NAME} lib build directory make failed.")
    endif()
    # message(CMAKE_PREFIX_PATH-:${CMAKE_PREFIX_PATH})
    # message(CMAKE_FIND_ROOT_PATH-:${CMAKE_FIND_ROOT_PATH})
    # message(CMAKE_TOOLCHAIN_FILE-:${CMAKE_TOOLCHAIN_FILE})
    # message(QT_QMAKE_EXECUTABLE-:${QT_QMAKE_EXECUTABLE})
    execute_process(
        COMMAND ${CMAKE_COMMAND}
        ${QExtWrapQMapLibre_SOURCE_DIR}
        -G${CMAKE_GENERATOR}
        -DMLN_QT_STATIC=ON
        -DMLN_WITH_WERROR=OFF
        -DMLN_QT_WITH_LOCATION=OFF
        -DANDROID_PLATFORM=${ANDROID_PLATFORM}
        -DANDROID_ABI=${ANDROID_ABI}
        -DANDROID_NDK=${ANDROID_NDK}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_FIND_ROOT_PATH=${CMAKE_FIND_ROOT_PATH}
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
        -DCMAKE_INSTALL_PREFIX=${QExtWrapQMapLibre_INSTALL_DIR}
        WORKING_DIRECTORY "${QExtWrapQMapLibre_BUILD_DIR}"
        RESULT_VARIABLE CONFIGURE_RESULT)
    if(CONFIGURE_RESULT MATCHES 0)
        message(STATUS "${QExtWrapQMapLibre_DIR_NAME} configure success")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS}
            WORKING_DIRECTORY "${QExtWrapQMapLibre_BUILD_DIR}"
            RESULT_VARIABLE BUILD_RESULT)
        if(BUILD_RESULT MATCHES 0)
            message(STATUS "${QExtWrapQMapLibre_DIR_NAME} build success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --install ./
                WORKING_DIRECTORY "${QExtWrapQMapLibre_BUILD_DIR}"
                RESULT_VARIABLE INSTALL_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${QExtWrapQMapLibre_DIR_NAME} install success")
                qext_make_stamp_file("${QExtWrapQMapLibre_STAMP_FILE_PATH}")
            else()
                message(FATAL_ERROR "${QExtWrapQMapLibre_DIR_NAME} install failed.")
            endif()
        else()
            message(FATAL_ERROR "${QExtWrapQMapLibre_DIR_NAME} build failed.")
        endif()
    else()
        message(FATAL_ERROR "${QExtWrapQMapLibre_DIR_NAME} configure failed.")
    endif()
endif()
# wrap lib
add_library(QExt3rdparty::WrapQMapLibre INTERFACE IMPORTED)
set(QMapLibre_DIR "${QExtWrapQMapLibre_INSTALL_DIR}/lib/cmake/QMapLibre")
find_package(QMapLibre PATHS ${QExtWrapQMapLibre_INSTALL_DIR} COMPONENTS Core Widgets NO_DEFAULT_PATH REQUIRED)
target_link_libraries(QExt3rdparty::WrapQMapLibre INTERFACE QMapLibre::Core QMapLibre::Widgets)
if(ANDROID)
    find_package(ZLIB REQUIRED)
    target_link_libraries(QExt3rdparty::WrapQMapLibre INTERFACE ZLIB::ZLIB)
endif()
set(QExtWrapQMapLibre_FOUND ON)
