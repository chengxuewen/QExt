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
if(TARGET QExt3rdparty::WrapQtADS)
    set(WrapQtADS_FOUND ON)
    return()
endif()

set(QExtWrapQtADS_VERSION "4.4.0")
set(QExtWrapQtADS_DIR_NAME "QtADS-${QExtWrapQtADS_VERSION}")
set(QExtWrapQtADS_URL_NAME "QtADS-${QExtWrapQtADS_VERSION}.7z")
set(QExtWrapQtADS_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapQtADS_URL_NAME}")
set(QExtWrapQtADS_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapQtADS_DIR_NAME}")
set(QExtWrapQtADS_SOURCE_DIR "${QExtWrapQtADS_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
set(QExtWrapQtADS_BUILD_DIR "${QExtWrapQtADS_ROOT_DIR}/build/${CMAKE_BUILD_TYPE}" CACHE INTERNAL "" FORCE)
set(QExtWrapQtADS_INSTALL_DIR "${QExtWrapQtADS_ROOT_DIR}/install/${CMAKE_BUILD_TYPE}" CACHE INTERNAL "" FORCE)
qext_stamp_file_info(QExtWrapQtADS OUTPUT_DIR "${QExtWrapQtADS_ROOT_DIR}")
qext_fetch_3rdparty(QExtWrapQtADS URL "${QExtWrapQtADS_URL_PATH}")
if(NOT EXISTS ${QExtWrapQtADS_STAMP_FILE_PATH})
    if(NOT EXISTS ${QExtWrapQtADS_SOURCE_DIR})
        message(FATAL_ERROR "${QExtWrapQtADS_DIR_NAME} FetchContent failed.")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QExtWrapQtADS_BUILD_DIR}
        WORKING_DIRECTORY "${QExtWrapQtADS_ROOT_DIR}"
        RESULT_VARIABLE MKDIR_RESULT)
    if(NOT (MKDIR_RESULT MATCHES 0))
        message(FATAL_ERROR "${QExtWrapQtADS_DIR_NAME} lib build directory make failed.")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND}
        -G${CMAKE_GENERATOR}
        -DADS_VERSION=${QExtWrapQtADS_VERSION}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_INSTALL_PREFIX=${QExtWrapQtADS_INSTALL_DIR} ${QExtWrapQtADS_SOURCE_DIR}
        WORKING_DIRECTORY "${QExtWrapQtADS_BUILD_DIR}"
        RESULT_VARIABLE CONFIGURE_RESULT)
    if(CONFIGURE_RESULT MATCHES 0)
        message(STATUS "${QExtWrapQtADS_DIR_NAME} configure success")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS}
            WORKING_DIRECTORY "${QExtWrapQtADS_BUILD_DIR}"
            RESULT_VARIABLE BUILD_RESULT)
        if(BUILD_RESULT MATCHES 0)
            message(STATUS "${QExtWrapQtADS_DIR_NAME} build success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --install ./
                WORKING_DIRECTORY "${QExtWrapQtADS_BUILD_DIR}"
                RESULT_VARIABLE INSTALL_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${QExtWrapQtADS_DIR_NAME} install success")
                qext_make_stamp_file("${QExtWrapQtADS_STAMP_FILE_PATH}")
            else()
                message(FATAL_ERROR "${QExtWrapQtADS_DIR_NAME} install failed.")
            endif()
        else()
            message(FATAL_ERROR "${QExtWrapQtADS_DIR_NAME} build failed.")
        endif()
    else()
        message(FATAL_ERROR "${QExtWrapQtADS_DIR_NAME} configure failed.")
    endif()
endif()
# wrap lib
find_package(qtadvanceddocking-qt5 ${QExtWrapQtADS_VERSION} EXACT PATHS ${QExtWrapQtADS_INSTALL_DIR} REQUIRED)
add_library(QExt3rdparty::WrapQtADS INTERFACE IMPORTED)
target_link_libraries(QExt3rdparty::WrapQtADS INTERFACE ads::qtadvanceddocking-qt5)
# copy lib to build dir
set(QExtWrapQtADS_INSTALL_DLLDIR "${QExtWrapQtADS_INSTALL_DIR}/${QEXT_INSTALL_DLLDIR}")
qext_get_files("${QExtWrapQtADS_INSTALL_DLLDIR}" QExtWrapQtADS_LIBRARIES)
qext_install(FILES "${QExtWrapQtADS_LIBRARIES}" DESTINATION "${QEXT_INSTALL_DLLDIR}")
# execute_process(
#     COMMAND ${CMAKE_COMMAND} -E make_directory "${QEXT_BUILD_DIR}/${QEXT_INSTALL_DLLDIR}/"
#     WORKING_DIRECTORY "${QExtWrapQtADS_ROOT_DIR}"
#     ERROR_QUIET)
# foreach(library ${QExtWrapQtADS_LIBRARIES})
#     execute_process(
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different "${library}" "${QEXT_BUILD_DIR}/${QEXT_INSTALL_DLLDIR}/"
#         WORKING_DIRECTORY "${QExtWrapQtADS_ROOT_DIR}"
#         ERROR_QUIET)
# endforeach()
set(WrapQtADS_FOUND ON)
