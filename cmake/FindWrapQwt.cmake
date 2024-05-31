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
if(TARGET QExt3rdparty::WrapQwt)
    set(WrapQwt_FOUND ON)
    return()
endif()

set(QWT_DIR_NAME "qwt-6.1.3")
set(QWT_URL_NAME "qwt-6.1.3")
set(QWT_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QWT_URL_NAME}")
set(QWT_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QWT_DIR_NAME}")
set(QWT_SOURCE_DIR "${QWT_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(QWT_BUILD_DIR "${QWT_ROOT_DIR}/build/${CMAKE_BUILD_TYPE}" CACHE INTERNAL "" FORCE)
set(QWT_INSTALL_DIR "${QWT_ROOT_DIR}/install/${CMAKE_BUILD_TYPE}" CACHE INTERNAL "" FORCE)
if(NOT EXISTS ${QWT_SOURCE_DIR})
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${QWT_URL_PATH} ${QWT_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QWT_BUILD_DIR}
        RESULT_VARIABLE FETCH_RESULT)
endif()
if(NOT EXISTS ${QWT_INSTALL_DIR})
    if(NOT EXISTS ${QWT_SOURCE_DIR})
        message(FATAL_ERROR "${QWT_DIR_NAME} FetchContent failed.")
    endif()
    execute_process(
        COMMAND ${CMAKE_COMMAND}
        -G${CMAKE_GENERATOR}
        -DQWT_BUILD_INSTALL=ON
        -DQWT_BUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_INSTALL_PREFIX=${QWT_INSTALL_DIR} ${QWT_SOURCE_DIR}
        WORKING_DIRECTORY "${QWT_BUILD_DIR}"
        RESULT_VARIABLE CONFIGURE_RESULT)
    if(CONFIGURE_RESULT MATCHES 0)
        message(STATUS "${QWT_DIR_NAME} configure success")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS}
            WORKING_DIRECTORY "${QWT_BUILD_DIR}"
            RESULT_VARIABLE BUILD_RESULT)
        if(BUILD_RESULT MATCHES 0)
            message(STATUS "${QWT_DIR_NAME} build success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --install ./
                WORKING_DIRECTORY "${QWT_BUILD_DIR}"
                RESULT_VARIABLE INSTALL_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${QWT_DIR_NAME} install success")
            else()
                message(FATAL_ERROR "${QWT_DIR_NAME} install failed.")
            endif()
        else()
            message(FATAL_ERROR "${QWT_DIR_NAME} build failed.")
        endif()
    else()
        message(FATAL_ERROR "${QWT_DIR_NAME} configure failed.")
    endif()
endif()
if(EXISTS ${QWT_INSTALL_DIR})
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${QWT_INSTALL_DIR} ${QEXT_BUILD_DIR}
        RESULT_VARIABLE COPY_RESULT)
endif()
find_package(Qwt PATHS ${QWT_INSTALL_DIR} REQUIRED)
add_library(QExt3rdparty::WrapQwt INTERFACE IMPORTED)
target_link_libraries(QExt3rdparty::WrapQwt INTERFACE Qwt::Qwt)
qext_set_3rdparty_install_info(QExt3rdparty Qwt::Qwt)
set(WrapQwt_FOUND ON)
