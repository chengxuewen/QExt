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
            COMMAND ${CMAKE_COMMAND} -E make_directory "${QEXT_BUILD_DIR}/${QEXT_INSTALL_TOOLSDIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${LINUXDEPLOYQT_ROOT}/${tool_name}"
            "${QEXT_BUILD_DIR}/${QEXT_INSTALL_TOOLSDIR}/${tool_name}"
            WORKING_DIRECTORY "${QEXT_BUILD_DIR}")
    endif()
    qext_find_qt_tool(${tool_name} PATHS "${QEXT_BUILD_DIR}/${QEXT_INSTALL_TOOLSDIR}")
    set(QEXT_DEPLOYQT_EXECUTABLE "${${tool_name}_EXECUTABLE}" PARENT_SCOPE)
    set(QEXT_DEPLOYQT_BIN_DIR "${${tool_name}_BIN_DIR}" PARENT_SCOPE)
    if(NOT ${tool_name}_EXECUTABLE)
        message(WARNING "linuxdeployqt not found, deploy/pack will not be available")
        return()
    endif()
    message(STATUS "Found deployqt ${${tool_name}_EXECUTABLE}")
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_deploy_qt_conf qt_conf_absolute_path)
    set(no_value_options "")
    set(single_value_options
        PREFIX
        DOC_DIR
        HEADERS_DIR
        LIB_DIR
        LIBEXEC_DIR
        BIN_DIR
        PLUGINS_DIR
        QML_DIR
        ARCHDATA_DIR
        DATA_DIR
        TRANSLATIONS_DIR
        EXAMPLES_DIR
        TESTS_DIR
        SETTINGS_DIR
    )
    set(multi_value_options "")
    cmake_parse_arguments(PARSE_ARGV 1 arg "${no_value_options}" "${single_value_options}" "${multi_value_options}")

    if(arg_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unparsed arguments: ${arg_UNPARSED_ARGUMENTS}")
    endif()

    if(NOT IS_ABSOLUTE "${qt_conf_absolute_path}")
        message(FATAL_ERROR "Given qt.conf path is not an absolute path: '${qt_conf_absolute_path}'")
    endif()

    # Only write out locations that differ from the defaults
    set(contents "[Paths]\n")
    if(arg_PREFIX)
        string(APPEND contents "Prefix = ${arg_PREFIX}\n")
    endif()
    if(arg_DOC_DIR AND NOT arg_DOC_DIR STREQUAL "doc")
        string(APPEND contents "Documentation = ${arg_DOC_DIR}\n")
    endif()
    if(arg_HEADERS_DIR AND NOT arg_HEADERS_DIR STREQUAL "include")
        string(APPEND contents "Headers = ${arg_HEADERS_DIR}\n")
    endif()
    if(arg_LIB_DIR AND NOT arg_LIB_DIR STREQUAL "lib")
        string(APPEND contents "Libraries = ${arg_LIB_DIR}\n")
    endif()

    # This one is special, the default is platform-specific
    if(arg_LIBEXEC_DIR AND
       ((WIN32 AND NOT arg_LIBEXEC_DIR STREQUAL "bin") OR
        (NOT WIN32 AND NOT arg_LIBEXEC_DIR STREQUAL "libexec")))
        string(APPEND contents "LibraryExecutables = ${arg_LIBEXEC_DIR}\n")
    endif()

    if(arg_BIN_DIR AND NOT arg_BIN_DIR STREQUAL "bin")
        string(APPEND contents "Binaries = ${arg_BIN_DIR}\n")
    endif()
    if(arg_PLUGINS_DIR AND NOT arg_PLUGINS_DIR STREQUAL "plugins")
        string(APPEND contents "Plugins = ${arg_PLUGINS_DIR}\n")
    endif()
    if(arg_QML_DIR AND NOT arg_QML_DIR STREQUAL "qml")
        if(QT_VERSION_MAJOR EQUAL 5)
            string(APPEND contents "Qml2Imports = ${arg_QML_DIR}\n")
        else()
            string(APPEND contents "QmlImports = ${arg_QML_DIR}\n")
        endif()
    endif()
    if(arg_ARCHDATA_DIR AND NOT arg_ARCHDATA_DIR STREQUAL ".")
        string(APPEND contents "ArchData = ${arg_ARCHDATA_DIR}\n")
    endif()
    if(arg_DATA_DIR AND NOT arg_DATA_DIR STREQUAL ".")
        string(APPEND contents "Data = ${arg_DATA_DIR}\n")
    endif()
    if(arg_TRANSLATIONS_DIR AND NOT arg_TRANSLATIONS_DIR STREQUAL "translations")
        string(APPEND contents "Translations = ${arg_TRANSLATIONS_DIR}\n")
    endif()
    if(arg_EXAMPLES_DIR AND NOT arg_EXAMPLES_DIR STREQUAL "examples")
        string(APPEND contents "Examples = ${arg_EXAMPLES_DIR}\n")
    endif()
    if(arg_TESTS_DIR AND NOT arg_TESTS_DIR STREQUAL "tests")
        string(APPEND contents "Tests = ${arg_TESTS_DIR}\n")
    endif()
    if(arg_SETTINGS_DIR AND NOT arg_SETTINGS_DIR STREQUAL ".")
        string(APPEND contents "Settings = ${arg_SETTINGS_DIR}\n")
    endif()

    message(STATUS "Writing ${qt_conf_absolute_path}")
    file(WRITE "${qt_conf_absolute_path}" "${contents}")
endfunction()
