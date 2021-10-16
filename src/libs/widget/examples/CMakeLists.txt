#################################################################################
#
# Library: QEXT
#
# Copyright (c) ChengXueWen. Contact: 1398831004@qq.com
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

#--------------------------------------------------------------------------------
# Set example output path
#--------------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/widget)
set(LIBRARY_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/widget)



#--------------------------------------------------------------------------------
# Set example link libraries
#--------------------------------------------------------------------------------
set(qext_example_link_libraries)

if(UNIX)
    list(APPEND qext_example_link_libraries dl)
endif()

if(WIN32)
    list(APPEND qext_example_link_libraries shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND qext_example_link_libraries ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND qext_example_link_libraries Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND qext_example_link_libraries
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND qext_example_link_libraries QEXTWidget QEXTFontAwesome)
list(APPEND qext_example_include_directories QEXTWidget_PRIVATE_INCLUDE_DIRS)



#--------------------------------------------------------------------------------
# define function
#--------------------------------------------------------------------------------
function(qextWidgetAddExample EXAMPLE_NAME)
    set(multiValueArgs EXAMPLE_SOURCE EXAMPLE_INCLUDE_DIRS)
    cmake_parse_arguments(MY "" "" "${multiValueArgs}" "${ARGN}")
    add_executable(${EXAMPLE_NAME} ${MY_EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE ${qext_example_link_libraries})
    target_include_directories(${EXAMPLE_NAME} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${MY_EXAMPLE_INCLUDE_DIRS}
        ${qext_example_include_directories}
        )
    set_property(TARGET ${EXAMPLE_NAME} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
    if(QEXT_BUILD_SHARED_LIBS AND WIN32)
        qextMacroCopyDependenceLib(${EXAMPLE_NAME} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
        qextMacroCopyDependenceLib(${EXAMPLE_NAME} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
    endif()
endfunction()



#--------------------------------------------------------------------------------
# Add example
#--------------------------------------------------------------------------------
qextWidgetAddExample(qext_exp_widgetNavListWidget
    EXAMPLE_SOURCE
    navlistwidget/navlistwidgetform.cpp
    navlistwidget/navlistwidgetform.h
    navlistwidget/navlistwidgetform.ui
    navlistwidget/navlistwidget.cpp
    navlistwidget/navlistwidget.h
    navlistwidget/navlistwidget.ui
    navlistwidget/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/navlistwidget
    )
qextWidgetAddExample(qext_exp_widgetNavButton
    EXAMPLE_SOURCE
    navbutton/navbutton.cpp
    navbutton/navbutton.h
    navbutton/navbutton.ui
    navbutton/iconhelper.cpp
    navbutton/iconhelper.h
    navbutton/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/navbutton
    )
qextWidgetAddExample(qext_exp_widgetSwitchButton
    EXAMPLE_SOURCE
    switchbutton/frmswitchbutton.cpp
    switchbutton/frmswitchbutton.h
    switchbutton/frmswitchbutton.ui
    switchbutton/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/switchbutton
    )
qextWidgetAddExample(qext_exp_widgetFramelessMainwindow
    EXAMPLE_SOURCE
    framelesswindow/mainwindow.cpp
    framelesswindow/mainwindow.h
    framelesswindow/mainwindow.ui
    framelesswindow/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/framelesswindow
    )
qextWidgetAddExample(qext_exp_widgetFramelessDialog
    EXAMPLE_SOURCE
    framelessdialog/dialog.cpp
    framelessdialog/dialog.h
    framelessdialog/dialog.ui
    framelessdialog/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/framelessdialog
    )
qextWidgetAddExample(qext_exp_widgetFramelessWidget
    EXAMPLE_SOURCE
    framelesswidget/widget.cpp
    framelesswidget/widget.h
    framelesswidget/widget.ui
    framelesswidget/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/framelesswidget
    )
qextWidgetAddExample(qext_exp_widgetLightBreathing
    EXAMPLE_SOURCE
    lightbreathing/mainwindow.cpp
    lightbreathing/mainwindow.h
    lightbreathing/mainwindow.ui
    lightbreathing/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/lightbreathing
    )
qextWidgetAddExample(qext_exp_widgetLightIndicator
    EXAMPLE_SOURCE
    lightindicator/mainwindow.cpp
    lightindicator/mainwindow.h
    lightindicator/mainwindow.ui
    lightindicator/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/lightindicator
    )
qextWidgetAddExample(qext_exp_widgetLcdNumber
    EXAMPLE_SOURCE
    lcdnumber/mainwindow.cpp
    lcdnumber/mainwindow.h
    lcdnumber/mainwindow.ui
    lcdnumber/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/lcdnumber
    )
qextWidgetAddExample(qext_exp_widgetLcdText
    EXAMPLE_SOURCE
    lcdtext/mainwindow.cpp
    lcdtext/mainwindow.h
    lcdtext/mainwindow.ui
    lcdtext/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/lcdtext
    )
qextWidgetAddExample(qext_exp_widgetWaveChart
    EXAMPLE_SOURCE
    wavechart/frmwavechart.cpp
    wavechart/frmwavechart.h
    wavechart/frmwavechart.ui
    wavechart/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/wavechart
    )
qextWidgetAddExample(qext_exp_widgetIpAddress
    EXAMPLE_SOURCE
    ipaddress/frmipaddress.cpp
    ipaddress/frmipaddress.h
    ipaddress/frmipaddress.ui
    ipaddress/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/ipaddress
    )
qextWidgetAddExample(qext_exp_widgetTumbler
    EXAMPLE_SOURCE
    tumbler/frmtumbler.cpp
    tumbler/frmtumbler.h
    tumbler/frmtumbler.ui
    tumbler/frmtumblerdatetime.cpp
    tumbler/frmtumblerdatetime.h
    tumbler/frmtumblerdatetime.ui
    tumbler/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/tumbler
    )
qextWidgetAddExample(qext_exp_widgetDial
    EXAMPLE_SOURCE
    dial/frmgaugedial.cpp
    dial/frmgaugedial.h
    dial/frmgaugedial.ui
    dial/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/dial
    )
qextWidgetAddExample(qext_exp_widgetThermometer
    EXAMPLE_SOURCE
    thermometer/frmthermometer.cpp
    thermometer/frmthermometer.h
    thermometer/frmthermometer.ui
    thermometer/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/thermometer
    )
qextWidgetAddExample(qext_exp_widgetProgressWait
    EXAMPLE_SOURCE
    progresswait/frmprogresswait.cpp
    progresswait/frmprogresswait.h
    progresswait/frmprogresswait.ui
    progresswait/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/progresswait
    )
qextWidgetAddExample(qext_exp_widgetProgressRing
    EXAMPLE_SOURCE
    progressring/frmprogressring.cpp
    progressring/frmprogressring.h
    progressring/frmprogressring.ui
    progressring/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/progressring
    )
qextWidgetAddExample(qext_exp_widgetProgressPie
    EXAMPLE_SOURCE
    progresspie/frmprogresspie.cpp
    progresspie/frmprogresspie.h
    progresspie/frmprogresspie.ui
    progresspie/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/progresspie
    )
qextWidgetAddExample(qext_exp_widgetProgressBar
    EXAMPLE_SOURCE
    progressbar/frmprogressbar.cpp
    progressbar/frmprogressbar.h
    progressbar/frmprogressbar.ui
    progressbar/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/progressbar
    )
qextWidgetAddExample(qext_exp_widgetProgressButton
    EXAMPLE_SOURCE
    progressbutton/frmprogressbutton.cpp
    progressbutton/frmprogressbutton.h
    progressbutton/frmprogressbutton.ui
    progressbutton/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/progressbutton
    )
qextWidgetAddExample(qext_exp_widgetInput
    EXAMPLE_SOURCE
    input/mainwindow.cpp
    input/mainwindow.h
    input/mainwindow.ui
    input/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/input
    )
