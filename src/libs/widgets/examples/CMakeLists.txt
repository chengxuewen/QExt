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
# Set example output path
#--------------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${QEXT_OUTPUT_EXAMPLE_DIR}/widgets)
set(LIBRARY_OUTPUT_PATH ${QEXT_OUTPUT_EXAMPLE_DIR}/widgets)



#--------------------------------------------------------------------------------
# Set example link libraries
#--------------------------------------------------------------------------------
set(QEXT_EXAMPLE_LINK_LIBRARIES)

if(UNIX)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES dl)
endif()

if(WIN32)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
endif()

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

list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES QEXTWidgets QEXTIconFont)
list(APPEND QEXT_EXAMPLE_INCLUDE_DIRECTORIES QEXTWidget_PRIVATE_INCLUDE_DIRS)



#--------------------------------------------------------------------------------
# define function
#--------------------------------------------------------------------------------
function(qextFunctionWidgetAddExample EXAMPLE_NAME)
    set(multiValueArgs EXAMPLE_SOURCE EXAMPLE_INCLUDE_DIRS)
    cmake_parse_arguments(MY "" "" "${multiValueArgs}" "${ARGN}")
    add_executable(${EXAMPLE_NAME} ${MY_EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE ${QEXT_EXAMPLE_LINK_LIBRARIES})
    target_include_directories(${EXAMPLE_NAME} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${MY_EXAMPLE_INCLUDE_DIRS}
        ${QEXT_EXAMPLE_INCLUDE_DIRECTORIES}
        )
    set_property(TARGET ${EXAMPLE_NAME} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
    if(QEXT_BUILD_SHARED_LIBS AND WIN32)
        qextFunctionCopyDependencyInternal(
            TARGET ${EXAMPLE_NAME}
            LIBS QEXTCore QEXTWidgets
            DESTINATION ${EXECUTABLE_OUTPUT_PATH}
            POST_BUILD
            )
    endif()
endfunction()



#--------------------------------------------------------------------------------
# Add example
#--------------------------------------------------------------------------------
qextFunctionWidgetAddExample(qext_exp_widgetNavigationListView
    EXAMPLE_SOURCE
    navigationlistview/frmnavigationlistview.cpp
    navigationlistview/frmnavigationlistview.h
    navigationlistview/frmnavigationlistview.ui
    navigationlistview/navigationlistview.cpp
    navigationlistview/navigationlistview.h
    navigationlistview/navigationlistview.ui
    navigationlistview/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/navigationlistview
    )
qextFunctionWidgetAddExample(qext_exp_widgetNavigationButton
    EXAMPLE_SOURCE
    navigationbutton/frmnavigationbutton.cpp
    navigationbutton/frmnavigationbutton.h
    navigationbutton/frmnavigationbutton.ui
    navigationbutton/iconhelper.cpp
    navigationbutton/iconhelper.h
    navigationbutton/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/navigationbutton
    )
qextFunctionWidgetAddExample(qext_exp_widgetSwitchButton
    EXAMPLE_SOURCE
    switchbutton/frmswitchbutton.cpp
    switchbutton/frmswitchbutton.h
    switchbutton/frmswitchbutton.ui
    switchbutton/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/switchbutton
    )
qextFunctionWidgetAddExample(qext_exp_widgetFramelessMainwindow
    EXAMPLE_SOURCE
    framelesswindow/mainwindow.cpp
    framelesswindow/mainwindow.h
    framelesswindow/mainwindow.ui
    framelesswindow/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/framelesswindow
    )
qextFunctionWidgetAddExample(qext_exp_widgetFramelessDialog
    EXAMPLE_SOURCE
    framelessdialog/dialog.cpp
    framelessdialog/dialog.h
    framelessdialog/dialog.ui
    framelessdialog/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/framelessdialog
    )
qextFunctionWidgetAddExample(qext_exp_widgetFramelessWidget
    EXAMPLE_SOURCE
    framelesswidget/widget.cpp
    framelesswidget/widget.h
    framelesswidget/widget.ui
    framelesswidget/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/framelesswidget
    )
qextFunctionWidgetAddExample(qext_exp_widgetBreathingLight
    EXAMPLE_SOURCE
    breathinglight/mainwindow.cpp
    breathinglight/mainwindow.h
    breathinglight/mainwindow.ui
    breathinglight/main.cpp
    breathinglight/resources.qrc
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/breathinglight
    )
qextFunctionWidgetAddExample(qext_exp_widgetIndicatorLight
    EXAMPLE_SOURCE
    indicatorlight/mainwindow.cpp
    indicatorlight/mainwindow.h
    indicatorlight/mainwindow.ui
    indicatorlight/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/indicatorlight
    )
qextFunctionWidgetAddExample(qext_exp_widgetNumberLed
    EXAMPLE_SOURCE
    numberled/mainwindow.cpp
    numberled/mainwindow.h
    numberled/mainwindow.ui
    numberled/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/numberled
    )
qextFunctionWidgetAddExample(qext_exp_widgetTextLcd
    EXAMPLE_SOURCE
    textlcd/mainwindow.cpp
    textlcd/mainwindow.h
    textlcd/mainwindow.ui
    textlcd/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/textlcd
    )
qextFunctionWidgetAddExample(qext_exp_widgetWaveChart
    EXAMPLE_SOURCE
    wavechart/frmwavechart.cpp
    wavechart/frmwavechart.h
    wavechart/frmwavechart.ui
    wavechart/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/wavechart
    )
qextFunctionWidgetAddExample(qext_exp_widgetIpAddress
    EXAMPLE_SOURCE
    ipaddress/frmipaddress.cpp
    ipaddress/frmipaddress.h
    ipaddress/frmipaddress.ui
    ipaddress/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/ipaddress
    )
qextFunctionWidgetAddExample(qext_exp_widgetTumbler
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
qextFunctionWidgetAddExample(qext_exp_widgetDial
    EXAMPLE_SOURCE
    dial/frmgaugedial.cpp
    dial/frmgaugedial.h
    dial/frmgaugedial.ui
    dial/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/dial
    )
qextFunctionWidgetAddExample(qext_exp_widgetThermometer
    EXAMPLE_SOURCE
    thermometer/frmthermometer.cpp
    thermometer/frmthermometer.h
    thermometer/frmthermometer.ui
    thermometer/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/thermometer
    )
qextFunctionWidgetAddExample(qext_exp_widgetProgressWait
    EXAMPLE_SOURCE
    progresswait/frmprogresswait.cpp
    progresswait/frmprogresswait.h
    progresswait/frmprogresswait.ui
    progresswait/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/progresswait
    )
qextFunctionWidgetAddExample(qext_exp_widgetProgressRing
    EXAMPLE_SOURCE
    progressring/frmprogressring.cpp
    progressring/frmprogressring.h
    progressring/frmprogressring.ui
    progressring/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/progressring
    )
qextFunctionWidgetAddExample(qext_exp_widgetProgressPie
    EXAMPLE_SOURCE
    progresspie/frmprogresspie.cpp
    progresspie/frmprogresspie.h
    progresspie/frmprogresspie.ui
    progresspie/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/progresspie
    )
qextFunctionWidgetAddExample(qext_exp_widgetProgressBar
    EXAMPLE_SOURCE
    progressbar/frmprogressbar.cpp
    progressbar/frmprogressbar.h
    progressbar/frmprogressbar.ui
    progressbar/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/progressbar
    )
qextFunctionWidgetAddExample(qext_exp_widgetProgressButton
    EXAMPLE_SOURCE
    progressbutton/frmprogressbutton.cpp
    progressbutton/frmprogressbutton.h
    progressbutton/frmprogressbutton.ui
    progressbutton/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/progressbutton
    )
qextFunctionWidgetAddExample(qext_exp_widgetInput
    EXAMPLE_SOURCE
    input/mainwindow.cpp
    input/mainwindow.h
    input/mainwindow.ui
    input/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/input
    )
qextFunctionWidgetAddExample(qext_exp_widgetSelectSlider
    EXAMPLE_SOURCE
    selectslider/frmselectslider.cpp
    selectslider/frmselectslider.h
    selectslider/frmselectslider.ui
    selectslider/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/selectslider
    )
qextFunctionWidgetAddExample(qext_exp_widgetRangeSlider
    EXAMPLE_SOURCE
    rangeslider/frmrangeslider.cpp
    rangeslider/frmrangeslider.h
    rangeslider/frmrangeslider.ui
    rangeslider/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/rangeslider
    )
qextFunctionWidgetAddExample(qext_exp_widgetTooltip
    EXAMPLE_SOURCE
    tooltip/frmtooltip.cpp
    tooltip/frmtooltip.h
    tooltip/frmtooltip.ui
    tooltip/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/tooltip
    )
qextFunctionWidgetAddExample(qext_exp_widgetSlider
    EXAMPLE_SOURCE
    slider/frmslider.cpp
    slider/frmslider.h
    slider/frmslider.ui
    slider/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/slider
    )
qextFunctionWidgetAddExample(qext_exp_widgetRulerSlider
    EXAMPLE_SOURCE
    rulerslider/frmrulerslider.cpp
    rulerslider/frmrulerslider.h
    rulerslider/frmrulerslider.ui
    rulerslider/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/rulerslider
    )
qextFunctionWidgetAddExample(qext_exp_widgetIconButton
    EXAMPLE_SOURCE
    iconbutton/FormIconButton.cpp
    iconbutton/FormIconButton.h
    iconbutton/FormIconButton.ui
    iconbutton/FormIconButton.qrc
    iconbutton/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/iconbutton
    )
qextFunctionWidgetAddExample(qext_exp_widgetCircleGauge
    EXAMPLE_SOURCE
    circlegauge/frmcirclegauge.cpp
    circlegauge/frmcirclegauge.h
    circlegauge/frmcirclegauge.ui
    circlegauge/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/circlegauge
    )
qextFunctionWidgetAddExample(qext_exp_widgetSemicircleGauge
    EXAMPLE_SOURCE
    semicirclegauge/frmsemicirclegauge.cpp
    semicirclegauge/frmsemicirclegauge.h
    semicirclegauge/frmsemicirclegauge.ui
    semicirclegauge/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/semicirclegauge
    )
qextFunctionWidgetAddExample(qext_exp_widgetArrowCompass
    EXAMPLE_SOURCE
    arrowcompass/frmarrowcompass.cpp
    arrowcompass/frmarrowcompass.h
    arrowcompass/frmarrowcompass.ui
    arrowcompass/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/arrowcompass
    )
qextFunctionWidgetAddExample(qext_exp_widgetRingCompass
    EXAMPLE_SOURCE
    ringcompass/frmringcompass.cpp
    ringcompass/frmringcompass.h
    ringcompass/frmringcompass.ui
    ringcompass/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/ringcompass
    )
qextFunctionWidgetAddExample(qext_exp_widgetProgressKnob
    EXAMPLE_SOURCE
    progressknob/frmprogressknob.cpp
    progressknob/frmprogressknob.h
    progressknob/frmprogressknob.ui
    progressknob/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/progressknob
    )
qextFunctionWidgetAddExample(qext_exp_widgetScaleKnob
    EXAMPLE_SOURCE
    scaleknob/frmscaleknob.cpp
    scaleknob/frmscaleknob.h
    scaleknob/frmscaleknob.ui
    scaleknob/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/scaleknob
    )
qextFunctionWidgetAddExample(qext_exp_widgetLed
    EXAMPLE_SOURCE
    led/frmled.cpp
    led/frmled.h
    led/frmled.ui
    led/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/led
    )
qextFunctionWidgetAddExample(qext_exp_widgetNavigationBar
    EXAMPLE_SOURCE
    navigationbar/frmnavigationbar.cpp
    navigationbar/frmnavigationbar.h
    navigationbar/frmnavigationbar.ui
    navigationbar/frmnavigationbarform.cpp
    navigationbar/frmnavigationbarform.h
    navigationbar/frmnavigationbarform.ui
    navigationbar/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/navigationbar
    )
qextFunctionWidgetAddExample(qext_exp_widgetOvenTimer
    EXAMPLE_SOURCE
    oventimer/frmoventimer.cpp
    oventimer/frmoventimer.h
    oventimer/frmoventimer.ui
    oventimer/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/oventimer
    )
