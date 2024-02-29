########################################################################################################################
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
########################################################################################################################


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_find_qt_tool NAME)
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
        set(tool_name "${NAME}.exe")
    else()
        set(tool_name "${NAME}")
    endif()

    get_filename_component(QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
    get_filename_component(QT_CSDK_DIR "${QT_BIN_DIR}" DIRECTORY)
    get_filename_component(QT_VSDK_DIR "${QT_CSDK_DIR}" DIRECTORY)
    get_filename_component(QT_SDK_DIR "${QT_VSDK_DIR}" DIRECTORY)
    list(APPEND arg_PATHS ${QT_BIN_DIR} "${QT_SDK_DIR}/Tools")
    foreach(PATH ${arg_PATHS})
        file(GLOB_RECURSE children "${PATH}/*")
        foreach(child ${children})
            if(${child} MATCHES "${tool_name}$")
                get_filename_component(TOOL_BIN_DIR "${child}" DIRECTORY)
                set("${NAME}_BIN_DIR" ${TOOL_BIN_DIR} PARENT_SCOPE)
                set("${NAME}_EXECUTABLE" ${child} PARENT_SCOPE)
                return()
            endif()
        endforeach()
    endforeach()
    set("${NAME}_BIN_DIR" "${NAME}_BIN_DIR-NOTFOUND" PARENT_SCOPE)
    set("${NAME}_EXECUTABLE" "${NAME}_EXECUTABLE-NOTFOUND" PARENT_SCOPE)
endfunction()
