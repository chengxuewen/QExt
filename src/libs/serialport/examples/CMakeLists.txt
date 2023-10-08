#################################################################################
#
# Library: QExt
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


#--------------------------------------------------------------------------------
# Set example link libraries
#--------------------------------------------------------------------------------
set(QEXT_EXAMPLE_LINK_LIBRARIES)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES
            Qt${QEXT_QT_VERSION_MAJOR}::Core
            Qt${QEXT_QT_VERSION_MAJOR}::Gui
            Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES QExt::SerialPort)


#--------------------------------------------------------------------------------
# Add examples
#--------------------------------------------------------------------------------
qext_add_executable(exp_QExtSerialportEnumerator
        SOURCES
        enumerator/main.cpp
        LIBRARIES
        ${QEXT_EXAMPLE_LINK_LIBRARIES}
        INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/enumerator
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH}
        DEFINES
        EXECUTABLE_OUTPUT_PATH="${EXECUTABLE_OUTPUT_PATH}")
qext_add_executable(exp_QExtSerialportEvent
        SOURCES
        event/PortListener.h
        event/PortListener.cpp
        event/main.cpp
        LIBRARIES
        ${QEXT_EXAMPLE_LINK_LIBRARIES}
        INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/event
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH}
        DEFINES
        EXECUTABLE_OUTPUT_PATH="${EXECUTABLE_OUTPUT_PATH}")
qext_add_executable(exp_QExtSerialportSimple
        SOURCES
        simple/MainWindow.h
        simple/MessageWindow.h
        simple/Test.h
        simple/MainWindow.cpp
        simple/MessageWindow.cpp
        simple/Test.cpp
        simple/main.cpp
        LIBRARIES
        ${QEXT_EXAMPLE_LINK_LIBRARIES}
        INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/simple
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH}
        DEFINES
        EXECUTABLE_OUTPUT_PATH="${EXECUTABLE_OUTPUT_PATH}")
qext_add_executable(exp_QExtSerialportUartAssistant
        SOURCES
        uartassistant/dialog.ui
        uartassistant/dialog.h
        uartassistant/dialog.cpp
        uartassistant/hled.h
        uartassistant/hled.cpp
        uartassistant/main.cpp
        LIBRARIES
        ${QEXT_EXAMPLE_LINK_LIBRARIES}
        INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/uartassistant
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH}
        DEFINES
        EXECUTABLE_OUTPUT_PATH="${EXECUTABLE_OUTPUT_PATH}")
