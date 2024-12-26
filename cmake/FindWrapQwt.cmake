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

set(QExtWrapQwt_DIR_NAME "qwt-6.1.3")
set(QExtWrapQwt_URL_NAME "qwt-6.1.3")
set(QExtWrapQwt_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapQwt_URL_NAME}")
set(QExtWrapQwt_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapQwt_DIR_NAME}")
set(QExtWrapQwt_SOURCE_DIR "${QExtWrapQwt_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(QExtWrapQwt_BUILD_DIR "${QExtWrapQwt_ROOT_DIR}/build/${CMAKE_BUILD_TYPE}" CACHE INTERNAL "" FORCE)
set(QExtWrapQwt_INSTALL_DIR "${QExtWrapQwt_ROOT_DIR}/install/${CMAKE_BUILD_TYPE}" CACHE INTERNAL "" FORCE)
qext_stamp_file_info(QExtWrapQwt OUTPUT_DIR "${QExtWrapQwt_ROOT_DIR}")
qext_fetch_3rdparty(QExtWrapQwt URL "${QExtWrapQwt_URL_PATH}")
if(NOT EXISTS ${QExtWrapQwt_STAMP_FILE_PATH})
    if(NOT EXISTS ${QExtWrapQwt_SOURCE_DIR})
        message(FATAL_ERROR "${QExtWrapQwt_DIR_NAME} FetchContent failed.")
    endif()
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QExtWrapQwt_BUILD_DIR}
        WORKING_DIRECTORY "${QExtWrapQwt_ROOT_DIR}"
        RESULT_VARIABLE MKDIR_RESULT)
    if(NOT (MKDIR_RESULT MATCHES 0))
        message(FATAL_ERROR "${QExtWrapQwt_DIR_NAME} lib build directory make failed.")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND}
        -G${CMAKE_GENERATOR}
        -DQWT_BUILD_INSTALL=ON
        -DQWT_BUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_INSTALL_PREFIX=${QExtWrapQwt_INSTALL_DIR} ${QExtWrapQwt_SOURCE_DIR}
        WORKING_DIRECTORY "${QExtWrapQwt_BUILD_DIR}"
        RESULT_VARIABLE CONFIGURE_RESULT)
    if(CONFIGURE_RESULT MATCHES 0)
        message(STATUS "${QExtWrapQwt_DIR_NAME} configure success")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS}
            WORKING_DIRECTORY "${QExtWrapQwt_BUILD_DIR}"
            RESULT_VARIABLE BUILD_RESULT)
        if(BUILD_RESULT MATCHES 0)
            message(STATUS "${QExtWrapQwt_DIR_NAME} build success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --install ./
                WORKING_DIRECTORY "${QExtWrapQwt_BUILD_DIR}"
                RESULT_VARIABLE INSTALL_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${QExtWrapQwt_DIR_NAME} install success")
                qext_make_stamp_file("${QExtWrapQwt_STAMP_FILE_PATH}")
            else()
                message(FATAL_ERROR "${QExtWrapQwt_DIR_NAME} install failed.")
            endif()
        else()
            message(FATAL_ERROR "${QExtWrapQwt_DIR_NAME} build failed.")
        endif()
    else()
        message(FATAL_ERROR "${QExtWrapQwt_DIR_NAME} configure failed.")
    endif()
endif()
# wrap lib
find_package(Qwt PATHS ${QExtWrapQwt_INSTALL_DIR} REQUIRED)
add_library(QExt3rdparty::WrapQwt INTERFACE IMPORTED)
target_link_libraries(QExt3rdparty::WrapQwt INTERFACE Qwt::Qwt)
# copy lib to build dir
set(QExtWrapQwt_INSTALL_DLLDIR "${QExtWrapQwt_INSTALL_DIR}/${QEXT_INSTALL_DLLDIR}")
qext_get_files("${QExtWrapQwt_INSTALL_DLLDIR}" QExtWrapQwt_LIBRARIES)
execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QExtWrapQwt_LIBRARIES}"
    "${QEXT_BUILD_DIR}/${QEXT_INSTALL_DLLDIR}"
    WORKING_DIRECTORY "${QExtWrapQwt_ROOT_DIR}"
    ERROR_QUIET)
qext_install(FILES "${QExtWrapQwt_LIBRARIES}" DESTINATION "${QEXT_INSTALL_DLLDIR}")
set(WrapQwt_FOUND ON)
