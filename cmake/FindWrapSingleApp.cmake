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
if(TARGET QExt3rdparty::WrapSingleApp)
    set(QExtWrapSingleApp_FOUND ON)
    return()
endif()

set(QExtWrapSingleApp_DIR_NAME "SingleApplication-3.5.3")
set(QExtWrapSingleApp_URL_NAME "SingleApplication-3.5.3.tar.gz")
set(QExtWrapSingleApp_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapSingleApp_URL_NAME}")
set(QExtWrapSingleApp_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapSingleApp_DIR_NAME}")
set(QExtWrapSingleApp_SOURCE_DIR "${QExtWrapSingleApp_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(QExtWrapSingleApp_BUILD_DIR "${QExtWrapSingleApp_ROOT_DIR}/build/${CMAKE_BUILD_TYPE}" CACHE INTERNAL "" FORCE)
set(QExtWrapSingleApp_INSTALL_DIR "${QExtWrapSingleApp_ROOT_DIR}/install/${CMAKE_BUILD_TYPE}" CACHE INTERNAL "" FORCE)
qext_stamp_file_info(QExtWrapSingleApp OUTPUT_DIR "${QExtWrapSingleApp_ROOT_DIR}")
qext_fetch_3rdparty(QExtWrapSingleApp URL "${QExtWrapSingleApp_URL_PATH}")
if(NOT EXISTS ${QExtWrapSingleApp_STAMP_FILE_PATH})
    if(NOT EXISTS ${QExtWrapSingleApp_SOURCE_DIR})
        message(FATAL_ERROR "${QExtWrapSingleApp_DIR_NAME} FetchContent failed.")
    endif()
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QExtWrapSingleApp_BUILD_DIR}
        WORKING_DIRECTORY "${QExtWrapSingleApp_ROOT_DIR}"
        RESULT_VARIABLE MKDIR_RESULT)
    if(NOT (MKDIR_RESULT MATCHES 0))
        message(FATAL_ERROR "${QExtWrapSingleApp_DIR_NAME} lib build directory make failed.")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND}
        -G${CMAKE_GENERATOR}
        -DSINGLEAPPLICATION_INSTALL=ON
        -DQAPPLICATION_CLASS=FreeStandingSingleApplication
        -DCMAKE_INSTALL_INCLUDEDIR=include
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_INSTALL_PREFIX=${QExtWrapSingleApp_INSTALL_DIR} ${QExtWrapSingleApp_SOURCE_DIR}
        WORKING_DIRECTORY "${QExtWrapSingleApp_BUILD_DIR}"
        RESULT_VARIABLE CONFIGURE_RESULT)
    if(CONFIGURE_RESULT MATCHES 0)
        message(STATUS "${QExtWrapSingleApp_DIR_NAME} configure success")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS}
            WORKING_DIRECTORY "${QExtWrapSingleApp_BUILD_DIR}"
            RESULT_VARIABLE BUILD_RESULT)
        if(BUILD_RESULT MATCHES 0)
            message(STATUS "${QExtWrapSingleApp_DIR_NAME} build success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --install ./
                WORKING_DIRECTORY "${QExtWrapSingleApp_BUILD_DIR}"
                RESULT_VARIABLE INSTALL_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${QExtWrapSingleApp_DIR_NAME} install success")
                qext_make_stamp_file("${QExtWrapSingleApp_STAMP_FILE_PATH}")
            else()
                message(FATAL_ERROR "${QExtWrapSingleApp_DIR_NAME} install failed.")
            endif()
        else()
            message(FATAL_ERROR "${QExtWrapSingleApp_DIR_NAME} build failed.")
        endif()
    else()
        message(FATAL_ERROR "${QExtWrapSingleApp_DIR_NAME} configure failed.")
    endif()
endif()
# wrap lib
add_library(QExt3rdparty::WrapSingleApp INTERFACE IMPORTED)
find_package(SingleApplication HINTS ${QExtWrapSingleApp_INSTALL_DIR} REQUIRED)
target_link_libraries(QExt3rdparty::WrapSingleApp INTERFACE SingleApplication::SingleApplication)
set(QExtWrapSingleApp_FOUND ON)
