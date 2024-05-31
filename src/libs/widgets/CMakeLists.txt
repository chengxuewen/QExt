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
# Add lib link libraries
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_LIB_LINK_LIBRARIES)
set(QEXT_LIB_NAME Widgets)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui Qt4::QtXml Qt4::QtSvg)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Xml
        Qt${QEXT_QT_VERSION_MAJOR}::Svg
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QExt::Core QExt::Gui QExt::GuiPrivate)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_library(${QEXT_LIB_NAME}
    EXCEPTIONS
    SOURCES
    source/tools/qextPropertyModel.h
    source/tools/qextPropertyModel.cpp
    source/tools/qextStyleSheetHooker.cpp
    source/tools/qextStyleSheetHooker.h
    source/tools/qextStyleSheetHooker_p.h
    source/tools/qextStyleThemes.cpp
    source/tools/qextStyleThemes.h
    source/tools/qextStyleThemes_p.h
    source/widgets/browser/qextButtonPropertyBrowser.h
    source/widgets/browser/qextGroupBoxPropertyBrowser.h
    source/widgets/browser/qextPropertyBrowser.cpp
    source/widgets/browser/qextPropertyBrowser.h
    source/widgets/browser/qextPropertyBrowser_p.h
    source/widgets/browser/qextTreePropertyBrowser.h
    source/widgets/qextArrowCompass.cpp
    source/widgets/qextArrowCompass.h
    source/widgets/qextArrowCompass_p.h
    source/widgets/qextBreathingLight.cpp
    source/widgets/qextBreathingLight.h
    source/widgets/qextBreathingLight_p.h
    source/widgets/qextCircleGauge.cpp
    source/widgets/qextCircleGauge.h
    source/widgets/qextCircleGauge_p.h
    source/widgets/qextCollapseTabWidget.cpp
    source/widgets/qextCollapseTabWidget.h
    source/widgets/qextCollapseTabWidget_p.h
    source/widgets/qextDateTimeTumbler.cpp
    source/widgets/qextDateTimeTumbler.h
    source/widgets/qextDateTimeTumbler_p.h
    source/widgets/qextDial.cpp
    source/widgets/qextDial.h
    source/widgets/qextDial_p.h
    source/widgets/qextFramelessDialog.h
    source/widgets/qextFramelessDialog_p.h
    source/widgets/qextFramelessDialog.cpp
    source/widgets/qextFramelessMainwindow.h
    source/widgets/qextFramelessMainwindow_p.h
    source/widgets/qextFramelessMainwindow.cpp
    source/widgets/qextFramelessWidget.h
    source/widgets/qextFramelessWidget_p.h
    source/widgets/qextFramelessWidget.cpp
    source/widgets/qextIconLabel.cpp
    source/widgets/qextIconLabel.h
    source/widgets/qextIconLabel_p.h
    source/widgets/qextIndicatorLight.cpp
    source/widgets/qextIndicatorLight.h
    source/widgets/qextIndicatorLight_p.h
    source/widgets/qextInput.cpp
    source/widgets/qextInput.h
    source/widgets/qextInput.ui
    source/widgets/qextIpAddressEdit.cpp
    source/widgets/qextIpAddressEdit.h
    source/widgets/qextIpAddressEdit_p.h
    source/widgets/qextKeyboard.cpp
    source/widgets/qextKeyboard.h
    source/widgets/qextKeyboard_p.h
    source/widgets/qextLed.cpp
    source/widgets/qextLed.h
    source/widgets/qextLed_p.h
    source/widgets/qextMessageBox.cpp
    source/widgets/qextMessageBox.h
    source/widgets/qextNavigationBar.cpp
    source/widgets/qextNavigationBar.h
    source/widgets/qextNavigationBar_p.h
    source/widgets/qextNavigationButton.cpp
    source/widgets/qextNavigationButton.h
    source/widgets/qextNavigationButton_p.h
    source/widgets/qextNavigationListView.cpp
    source/widgets/qextNavigationListView.h
    source/widgets/qextNavigationListView_p.h
    source/widgets/qextNumberLed.cpp
    source/widgets/qextNumberLed.h
    source/widgets/qextNumberLed_p.h
    source/widgets/qextOvenTimer.cpp
    source/widgets/qextOvenTimer.h
    source/widgets/qextOvenTimer_p.h
    source/widgets/qextProgressBar.cpp
    source/widgets/qextProgressBar.h
    source/widgets/qextProgressBar_p.h
    source/widgets/qextProgressButton.cpp
    source/widgets/qextProgressButton.h
    source/widgets/qextProgressButton_p.h
    source/widgets/qextProgressKnob.cpp
    source/widgets/qextProgressKnob.h
    source/widgets/qextProgressKnob_p.h
    source/widgets/qextProgressPie.cpp
    source/widgets/qextProgressPie.h
    source/widgets/qextProgressPie_p.h
    source/widgets/qextProgressRing.cpp
    source/widgets/qextProgressRing.h
    source/widgets/qextProgressRing_p.h
    source/widgets/qextProgressWait.cpp
    source/widgets/qextProgressWait.h
    source/widgets/qextProgressWait_p.h
    source/widgets/qextRangeSlider.cpp
    source/widgets/qextRangeSlider.h
    source/widgets/qextRangeSlider_p.h
    source/widgets/qextRingCompass.cpp
    source/widgets/qextRingCompass.h
    source/widgets/qextRingCompass_p.h
    source/widgets/qextRulerSlider.cpp
    source/widgets/qextRulerSlider.h
    source/widgets/qextRulerSlider_p.h
    source/widgets/qextScaleKnob.cpp
    source/widgets/qextScaleKnob.h
    source/widgets/qextScaleKnob_p.h
    source/widgets/qextScroller.cpp
    source/widgets/qextScroller.h
    source/widgets/qextScroller_p.h
    source/widgets/qextSelectSlider.cpp
    source/widgets/qextSelectSlider.h
    source/widgets/qextSelectSlider_p.h
    source/widgets/qextSemicircleGauge.cpp
    source/widgets/qextSemicircleGauge.h
    source/widgets/qextSemicircleGauge_p.h
    source/widgets/qextSlider.cpp
    source/widgets/qextSlider.h
    source/widgets/qextSlider_p.h
    source/widgets/qextSwitchButton.cpp
    source/widgets/qextSwitchButton.h
    source/widgets/qextSwitchButton_p.h
    source/widgets/qextTextLcd.cpp
    source/widgets/qextTextLcd.h
    source/widgets/qextTextLcd_p.h
    source/widgets/qextThermometer.cpp
    source/widgets/qextThermometer.h
    source/widgets/qextThermometer_p.h
    source/widgets/qextTooltip.cpp
    source/widgets/qextTooltip.h
    source/widgets/qextTooltip_p.h
    source/widgets/qextTumbler.cpp
    source/widgets/qextTumbler.h
    source/widgets/qextTumbler_p.h
    source/widgets/qextWaveChart.cpp
    source/widgets/qextWaveChart.h
    source/widgets/qextWaveChart_p.h
    source/qextWidgetGlobal.h
    resource/qextWidgets.qrc
    PRECOMPILED_HEADER
    source/qextWidgetPch.h
    PUBLIC_LIBRARIES
    ${QEXT_LIB_LINK_LIBRARIES})

#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
qext_add_subdirectory(tests QEXT_BUILD_TESTS)
