#################################################################################
#
# Library: QEXT
#
# Copyright (c) ChengXueWen. Contact: 1398831004@qq.com
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#################################################################################


set(QEXT_QTIFW_SEARCH_SUB_PATHS "")
set(_SEARCH_ROOT_PATHS "")
macro(_findSubDirs)
    set(root_path ${_SEARCH_ROOT_PATHS})
    file(GLOB children RELATIVE ${root_path} ${root_path}/*)
    list(APPEND QEXT_QTIFW_SEARCH_SUB_PATHS ${root_path})
    foreach(child ${children})
        if(IS_DIRECTORY ${root_path}/${child})
            set(_SEARCH_ROOT_PATHS ${root_path}/${child})
            _findSubDirs()
        endif()
    endforeach()
endmacro(_findSubDirs)

# Qt IFW Tools
# ~~~~~~~~~~~~
# QEXT_QTIFW_EXTRA_SEARCH_PATHS
macro(qextMacroFindQTIFW)
    set(QEXT_QTIFWDIR_FOUND FALSE)
    set(QEXT_QTIFW_SEARCH_PATHS "")
    set(QEXT_QTIFW_SEARCH_PATHS_FOUND FALSE)
    get_filename_component(QEXT_QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
    get_filename_component(QEXT_QT_KIT_DIR "${QEXT_QT_BIN_DIR}" DIRECTORY)
    string(REPLACE "/" ";" DIR_NAME_LIST ${QEXT_QT_KIT_DIR})
    foreach(child ${DIR_NAME_LIST})
        if(NOT ${QEXT_QTIFW_SEARCH_PATHS_FOUND})
            if(QEXT_QTIFW_SEARCH_PATHS STREQUAL "")
                set(QEXT_QTIFW_SEARCH_PATHS ${child})
            else()
                set(QEXT_QTIFW_SEARCH_PATHS ${QEXT_QTIFW_SEARCH_PATHS}/${child})
            endif()
            if(${child} MATCHES "Qt")
                set(QEXT_QTIFW_SEARCH_PATHS_FOUND TRUE)
            endif()
        endif()
    endforeach()

    if(${QEXT_QTIFW_SEARCH_PATHS_FOUND})
        file(GLOB children RELATIVE ${QEXT_QTIFW_SEARCH_PATHS} ${QEXT_QTIFW_SEARCH_PATHS}/*)
        foreach(child ${children})
            if(IS_DIRECTORY ${QEXT_QTIFW_SEARCH_PATHS}/${child})
                if(${child} MATCHES "Tools")
                    set(_SEARCH_ROOT_PATHS "${QEXT_QTIFW_SEARCH_PATHS}/${child}/QtInstallerFramework")
                    _findSubDirs()
                elseif(${child} MATCHES "QtIFW" OR ${child} MATCHES "QtInstallerFramework")
                    set(_SEARCH_ROOT_PATHS "${QEXT_QTIFW_SEARCH_PATHS}/${child}")
                    _findSubDirs()
                endif()
            endif()
        endforeach()

        # find exec
        if(MSVC)
            find_program(QEXT_QTIFW_EXECUTABL NAMES binarycreator.exe PATHS ${QEXT_QTIFW_SEARCH_SUB_PATHS} NO_DEFAULT_PATH)
            find_path(QEXT_QTIFWDIR binarycreator.exe ${QEXT_QTIFW_SEARCH_SUB_PATHS})
        else()
            find_program(QEXT_QTIFW_EXECUTABL NAMES binarycreator PATHS ${QEXT_QTIFW_SEARCH_SUB_PATHS} NO_DEFAULT_PATH)
            find_path(QEXT_QTIFWDIR binarycreator ${QEXT_QTIFW_SEARCH_SUB_PATHS})
        endif()
        if(NOT QEXT_QTIFW_EXECUTABL EQUAL "QEXT_QTIFW_EXECUTABL-NOTFOUND")
            set(QEXT_QTIFWDIR_FOUND TRUE)
        endif()

        if(NOT ${QEXT_QTIFWDIR_FOUND})
            if(QEXT_QTIFWDIR_FIND_REQUIRED)
                message(FATAL_ERROR "Could not find QTIFW dir")
            else()
                message(WARNING "Could not find QTIFW dir")
            endif()
        endif()
    else()
        if(QEXT_QTIFWDIR_FIND_REQUIRED)
            message(FATAL_ERROR "Could not find QTIFW search path")
        else()
            message(WARNING "Could not find QTIFW search path")
        endif()
    endif()
endmacro(qextMacroFindQTIFW)
