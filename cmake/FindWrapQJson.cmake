# #######################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2021~Present ChengXueWen. Contact: 1398831004@qq.com.
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
# #######################################################################################################################

# We can't create the same interface imported target multiple times, CMake will complain if we do
# that. This can happen if the find_package call is done in multiple different subdirectories.
if(TARGET QExt3rdparty::WrapQJson)
    set(WrapQJson_FOUND ON)
    return()
endif()

set(WrapQJson_DIR_NAME "qjson-0.9.0")
set(WrapQJson_PKG_NAME "qjson-0.9.0.tar.gz")
set(WrapQJson_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${WrapQJson_PKG_NAME}")
set(WrapQJson_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${WrapQJson_DIR_NAME}")
set(WrapQJson_BUILD_DIR "${WrapQJson_ROOT_DIR}/build" CACHE INTERNAL "" FORCE)
set(WrapQJson_SOURCE_DIR "${WrapQJson_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(WrapQJson_INSTALL_DIR "${WrapQJson_ROOT_DIR}/install" CACHE INTERNAL "" FORCE)
if(NOT EXISTS ${WrapQJson_SOURCE_DIR})
    include(FetchContent)
    FetchContent_Declare(
        QExt-3rdparty-QJson
        SOURCE_DIR ${WrapQJson_SOURCE_DIR}
        BINARY_DIR ${WrapQJson_BUILD_DIR}
        URL ${WrapQJson_URL_PATH})
    FetchContent_Populate(QExt-3rdparty-QJson)
endif()
if(NOT EXISTS ${WrapQJson_INSTALL_DIR})
    if(NOT EXISTS ${WrapQJson_SOURCE_DIR})
        message(FATAL_ERROR "${WrapQJson_DIR_NAME} FetchContent failed.")
    endif()
    execute_process(
        COMMAND ${CMAKE_COMMAND}
        -G${CMAKE_GENERATOR}
        -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_INSTALL_PREFIX=${WrapQJson_INSTALL_DIR} ${WrapQJson_SOURCE_DIR}
        WORKING_DIRECTORY "${WrapQJson_BUILD_DIR}"
        RESULT_VARIABLE CONFIGURE_RESULT)
    if(CONFIGURE_RESULT MATCHES 0)
        message(STATUS "${WrapQJson_DIR_NAME} configure success")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS} --config Release
            WORKING_DIRECTORY "${WrapQJson_BUILD_DIR}"
            RESULT_VARIABLE BUILD_RESULT)
        if(BUILD_RESULT MATCHES 0)
            message(STATUS "${WrapQJson_DIR_NAME} build success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --install ./
                WORKING_DIRECTORY "${WrapQJson_BUILD_DIR}"
                RESULT_VARIABLE INSTALL_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${WrapQJson_DIR_NAME} install success")
            else()
                message(FATAL_ERROR "${WrapQJson_DIR_NAME} install failed.")
            endif()
        else()
            message(FATAL_ERROR "${WrapQJson_DIR_NAME} build failed.")
        endif()
    else()
        message(FATAL_ERROR "${WrapQJson_DIR_NAME} configure failed.")
    endif()
endif()
find_package(QJSON-qt${QEXT_QT_VERSION_MAJOR} PATHS ${WrapQJson_INSTALL_DIR} REQUIRED)
add_library(QExt3rdparty::WrapQJson INTERFACE IMPORTED)
target_link_libraries(QExt3rdparty::WrapQJson INTERFACE QJSON-qt${QEXT_QT_VERSION_MAJOR})
set(WrapQJson_FOUND ON)
