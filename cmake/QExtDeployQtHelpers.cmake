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


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_find_deployqt)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs PATHS)
    cmake_parse_arguments(arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if("${QT_QMAKE_EXECUTABLE}" STREQUAL "")
        message(FATAL_ERROR "QT_QMAKE_EXECUTABLE is empty!")
    endif()
    if(NOT EXISTS "${QT_QMAKE_EXECUTABLE}")
        message(FATAL_ERROR "${QT_QMAKE_EXECUTABLE} path not exist!")
    endif()

    if(WIN32)
        set(tool_name "windeployqt")
    elseif(APPLE)
        set(tool_name "macdeployqt")
    else()
        set(LINUXDEPLOYQT_ROOT "${PROJECT_SOURCE_DIR}/3rdparty/linuxdeployqt")
        if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
            set(tool_name "linuxdeployqt-aarch64.AppImage")
        elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
            set(tool_name "linuxdeployqt-x86_64.AppImage")
        else()
            message(FATAL_ERROR "Unsupported host architecture with linuxdeployqt!")
        endif()
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E make_directory "${QEXT_BUILD_DIR}/${QEXT_INSTALL_TOOLDIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${LINUXDEPLOYQT_ROOT}/${tool_name}"
            "${QEXT_BUILD_DIR}/${QEXT_INSTALL_TOOLDIR}/"
            WORKING_DIRECTORY "${QEXT_BUILD_DIR}"
            ERROR_QUIET)
    endif()
    qext_find_qt_tool(${tool_name} PATHS "${QEXT_BUILD_DIR}/${QEXT_INSTALL_TOOLDIR}")
    set(QEXT_DEPLOYQT_EXECUTABLE "${${tool_name}_EXECUTABLE}" PARENT_SCOPE)
    set(QEXT_DEPLOYQT_BIN_DIR "${${tool_name}_BIN_DIR}" PARENT_SCOPE)
    if(NOT ${tool_name}_EXECUTABLE)
        message(FATAL_ERROR "linuxdeployqt not find in ${QEXT_BUILD_DIR}/${QEXT_INSTALL_TOOLDIR}")
    endif()
    message(STATUS "Found deployqt ${${tool_name}_EXECUTABLE}")
endfunction()
