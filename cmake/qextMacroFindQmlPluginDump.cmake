#################################################################################
#
# Library: QEXT
#
# Copyright (c) 2021 ChengXueWen 1398831004@qq.com
# Copyright (c) 2014 - 2018 Axel Menzel <info@rttr.org>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#################################################################################

# Qt QML Tools
# ~~~~~~~~~~~~
#
# To generate qmltypes files required by Qt Creator to allow QML code inspection
# (http://doc.qt.io/qtcreator/creator-qml-modules-with-plugins.html#generating-qmltypes-files)
# we need to have installed qmlplugindump unity (shipped with Qt 4.8 and later)
# http://doc.qt.io/qtcreator/creator-qml-modules-with-plugins.html#dumping-plugins-automatically
#
# Find the installed version of qmlplugindump utility.
# FindQtQmlTools should be called after Qt5 has been found
#
# This file defines the following variables:
#
# QMLPLUGINDUMP_FOUND - system has qmlplugindump
# QMLPLUGINDUMP_EXECUTABLE - QEXTMvvmPath to qmlplugindump executable
#
# Also defines MACRO to create qmltypes file, when QML directory is supplied
#
# Copyright (c) 2017, Peter Petrik <zilolv at gmail dot com>
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

macro(qextMacroFindQmlPluginDump)
    get_filename_component(QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
    if(NOT QEXT_QT_QMLPLUGINDUMP_EXECUTABLE)
        if(MSVC)
            find_program(QEXT_QT_QMLPLUGINDUMP_EXECUTABLE qmlplugindump.exe PATHS ${QT_BIN_DIR} NO_DEFAULT_PATH)
        else(MSVC)
            find_program(QEXT_QT_QMLPLUGINDUMP_EXECUTABLE qmlplugindump PATHS ${QT_BIN_DIR})
        endif(MSVC)
    endif(NOT QEXT_QT_QMLPLUGINDUMP_EXECUTABLE)

    if(QEXT_QT_QMLPLUGINDUMP_EXECUTABLE)
        set(QEXT_QT_QMLPLUGINDUMP_FOUND TRUE)
        message(STATUS "----QEXT---- Found qmlplugindump: ${QEXT_QT_QMLPLUGINDUMP_EXECUTABLE}")
    else(QEXT_QT_QMLPLUGINDUMP_EXECUTABLE)
        set(QEXT_QT_QMLPLUGINDUMP_FOUND FALSE)
        if(QEXT_QT_QMLPLUGINDUMP_FIND_REQUIRED)
            message(FATAL_ERROR "Could not find qmlplugindump")
        else(QEXT_QT_QMLPLUGINDUMP_FIND_REQUIRED)
            message(WARNING "Could not find qmlplugindump")
        endif(QEXT_QT_QMLPLUGINDUMP_FIND_REQUIRED)
    endif(QEXT_QT_QMLPLUGINDUMP_EXECUTABLE)
endmacro(qextMacroFindQmlPluginDump)

if(NOT QEXT_QT_QMLPLUGINDUMP_FOUND)
    qextMacroFindQmlPluginDump()
endif(NOT QEXT_QT_QMLPLUGINDUMP_FOUND)
