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
# Add lib link libraries
#--------------------------------------------------------------------------------
set(QEXT_LIB_LINK_LIBRARIES)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui Qt4::QtNetwork)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
            Qt${QEXT_QT_VERSION_MAJOR}::Core
            Qt${QEXT_QT_VERSION_MAJOR}::Gui
            Qt${QEXT_QT_VERSION_MAJOR}::Widgets
    )
else()
    message(FATAL_ERROR "Not find Qt package")
endif()


#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
qext_add_library(Widgets
        EXCEPTIONS
        SOURCES
        source/qextArrowCompass.cpp
        source/qextArrowCompass.h
        source/qextArrowCompass_p.h
        source/qextBreathingLight.cpp
        source/qextBreathingLight.h
        source/qextBreathingLight_p.h
        source/qextCircleGauge.cpp
        source/qextCircleGauge.h
        source/qextCircleGauge_p.h
        source/qextDateTimeTumbler.cpp
        source/qextDateTimeTumbler.h
        source/qextDateTimeTumbler_p.h
        source/qextDial.cpp
        source/qextDial.h
        source/qextDial_p.h
        source/qextFramelessDialog.h
        source/qextFramelessDialog_p.h
        source/qextFramelessDialog.cpp
        source/qextFramelessMainwindow.h
        source/qextFramelessMainwindow_p.h
        source/qextFramelessMainwindow.cpp
        source/qextFramelessWidget.h
        source/qextFramelessWidget_p.h
        source/qextFramelessWidget.cpp
        source/qextHidableTabWidget.cpp
        source/qextHidableTabWidget.h
        source/qextHidableTabWidget_p.h
        source/qextIconButton.cpp
        source/qextIconButton.h
        source/qextIconButton_p.h
        source/qextIconLabel.cpp
        source/qextIconLabel.h
        source/qextIconLabel_p.h
        source/qextIndicatorLight.cpp
        source/qextIndicatorLight.h
        source/qextIndicatorLight_p.h
        source/qextInput.cpp
        source/qextInput.h
        source/qextInput.ui
        source/qextIpAddressEdit.cpp
        source/qextIpAddressEdit.h
        source/qextIpAddressEdit_p.h
        source/qextLed.cpp
        source/qextLed.h
        source/qextLed_p.h
        source/qextNavigationBar.cpp
        source/qextNavigationBar.h
        source/qextNavigationBar_p.h
        source/qextNavigationButton.cpp
        source/qextNavigationButton.h
        source/qextNavigationButton_p.h
        source/qextNavigationListView.cpp
        source/qextNavigationListView.h
        source/qextNavigationListView_p.h
        source/qextNumberLed.cpp
        source/qextNumberLed.h
        source/qextNumberLed_p.h
        source/qextOvenTimer.cpp
        source/qextOvenTimer.h
        source/qextOvenTimer_p.h
        source/qextProgressBar.cpp
        source/qextProgressBar.h
        source/qextProgressBar_p.h
        source/qextProgressButton.cpp
        source/qextProgressButton.h
        source/qextProgressButton_p.h
        source/qextProgressKnob.cpp
        source/qextProgressKnob.h
        source/qextProgressKnob_p.h
        source/qextProgressPie.cpp
        source/qextProgressPie.h
        source/qextProgressPie_p.h
        source/qextProgressRing.cpp
        source/qextProgressRing.h
        source/qextProgressRing_p.h
        source/qextProgressWait.cpp
        source/qextProgressWait.h
        source/qextProgressWait_p.h
        source/qextRangeSlider.cpp
        source/qextRangeSlider.h
        source/qextRangeSlider_p.h
        source/qextRingCompass.cpp
        source/qextRingCompass.h
        source/qextRingCompass_p.h
        source/qextRulerSlider.cpp
        source/qextRulerSlider.h
        source/qextRulerSlider_p.h
        source/qextScaleKnob.cpp
        source/qextScaleKnob.h
        source/qextScaleKnob_p.h
        source/qextSelectSlider.cpp
        source/qextSelectSlider.h
        source/qextSelectSlider_p.h
        source/qextSemicircleGauge.cpp
        source/qextSemicircleGauge.h
        source/qextSemicircleGauge_p.h
        source/qextSlider.cpp
        source/qextSlider.h
        source/qextSlider_p.h
        source/qextStyleSheet.h
        source/qextStyleSheet_p.h
        source/qextStyleSheet.cpp
        source/qextStyleSheetPalette.cpp
        source/qextStyleSheetPalette.h
        source/qextStyleSheetPalette_p.h
        source/qextSwitchButton.cpp
        source/qextSwitchButton.h
        source/qextSwitchButton_p.h
        source/qextTextLcd.cpp
        source/qextTextLcd.h
        source/qextTextLcd_p.h
        source/qextThermometer.cpp
        source/qextThermometer.h
        source/qextThermometer_p.h
        source/qextTooltip.cpp
        source/qextTooltip.h
        source/qextTooltip_p.h
        source/qextTumbler.cpp
        source/qextTumbler.h
        source/qextTumbler_p.h
        source/qextWaveChart.cpp
        source/qextWaveChart.h
        source/qextWaveChart_p.h
        source/qextWidgetGlobal.h
        resource/qextWidgets.qrc
        PRECOMPILED_HEADER
        source/qextWidgetPch.h
        PUBLIC_LIBRARIES
        ${QEXT_LIB_LINK_LIBRARIES}
        Core IconFont GooglePinYin)


#--------------------------------------------------------------------------------
# Add lib tests and examples
#--------------------------------------------------------------------------------
if(QEXT_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(QEXT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()