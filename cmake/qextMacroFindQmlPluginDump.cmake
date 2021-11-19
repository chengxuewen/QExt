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
    else(QEXT_QT_QMLPLUGINDUMP_EXECUTABLE)
        set(QEXT_QT_QMLPLUGINDUMP_FOUND FALSE)
        if(QEXT_QT_QMLPLUGINDUMP_FIND_REQUIRED)
            message(FATAL_ERROR "Could not find qmlplugindump")
        else(QEXT_QT_QMLPLUGINDUMP_FIND_REQUIRED)
            message(WARNING "Could not find qmlplugindump")
        endif(QEXT_QT_QMLPLUGINDUMP_FIND_REQUIRED)
    endif(QEXT_QT_QMLPLUGINDUMP_EXECUTABLE)
endmacro(qextMacroFindQmlPluginDump)
