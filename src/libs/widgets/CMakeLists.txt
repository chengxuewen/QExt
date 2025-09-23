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
    source/controls/buttons/qextNavigationBar.cpp
    source/controls/buttons/qextNavigationBar.h
    source/controls/buttons/qextNavigationBar_p.h
    source/controls/buttons/qextNavigationButton.cpp
    source/controls/buttons/qextNavigationButton.h
    source/controls/buttons/qextNavigationButton_p.h
    source/controls/buttons/qextNavigationListView.cpp
    source/controls/buttons/qextNavigationListView.h
    source/controls/buttons/qextNavigationListView_p.h
    source/controls/buttons/qextProgressButton.cpp
    source/controls/buttons/qextProgressButton.h
    source/controls/buttons/qextProgressButton_p.h
    source/controls/buttons/qextSwitchButton.cpp
    source/controls/buttons/qextSwitchButton.h
    source/controls/buttons/qextSwitchButton_p.h
    source/controls/containers/qextCollapseTabWidget.cpp
    source/controls/containers/qextCollapseTabWidget.h
    source/controls/containers/qextCollapseTabWidget_p.h
    source/controls/dialogs/qextInputDialog.cpp
    source/controls/dialogs/qextInputDialog.h
    source/controls/dialogs/qextMessageBox.cpp
    source/controls/dialogs/qextMessageBox.h
    source/controls/displays/qextCircleGauge.cpp
    source/controls/displays/qextCircleGauge.h
    source/controls/displays/qextCircleGauge_p.h
    source/controls/displays/qextIconLabel.cpp
    source/controls/displays/qextIconLabel.h
    source/controls/displays/qextIconLabel_p.h
    source/controls/displays/qextProcessWidget.cpp
    source/controls/displays/qextProcessWidget.h
    source/controls/displays/qextProcessWidget_p.h
    source/controls/displays/qextProgressBar.cpp
    source/controls/displays/qextProgressBar.h
    source/controls/displays/qextProgressBar_p.h
    source/controls/displays/qextProgressPie.cpp
    source/controls/displays/qextProgressPie.h
    source/controls/displays/qextProgressPie_p.h
    source/controls/displays/qextProgressRing.cpp
    source/controls/displays/qextProgressRing.h
    source/controls/displays/qextProgressRing_p.h
    source/controls/displays/qextProgressWait.cpp
    source/controls/displays/qextProgressWait.h
    source/controls/displays/qextProgressWait_p.h
    source/controls/displays/qextThermometer.cpp
    source/controls/displays/qextThermometer.h
    source/controls/displays/qextThermometer_p.h
    source/controls/displays/qextTooltip.cpp
    source/controls/displays/qextTooltip.h
    source/controls/displays/qextTooltip_p.h
    source/controls/displays/qextWaveChart.cpp
    source/controls/displays/qextWaveChart.h
    source/controls/displays/qextWaveChart_p.h
    source/controls/inputs/qextCheckComboBox.cpp
    source/controls/inputs/qextCheckComboBox.h
    source/controls/inputs/qextDateTimeTumbler.cpp
    source/controls/inputs/qextDateTimeTumbler.h
    source/controls/inputs/qextDateTimeTumbler_p.h
    source/controls/inputs/qextDial.cpp
    source/controls/inputs/qextDial.h
    source/controls/inputs/qextDial_p.h
    source/controls/inputs/qextDoubleSpinBox.cpp
    source/controls/inputs/qextDoubleSpinBox.h
    source/controls/inputs/qextIpAddressEdit.cpp
    source/controls/inputs/qextIpAddressEdit.h
    source/controls/inputs/qextIpAddressEdit_p.h
    source/controls/inputs/qextOvenTimer.cpp
    source/controls/inputs/qextOvenTimer.h
    source/controls/inputs/qextOvenTimer_p.h
    source/controls/inputs/qextRangeSlider.cpp
    source/controls/inputs/qextRangeSlider.h
    source/controls/inputs/qextRangeSlider_p.h
    source/controls/inputs/qextRulerSlider.cpp
    source/controls/inputs/qextRulerSlider.h
    source/controls/inputs/qextRulerSlider_p.h
    source/controls/inputs/qextScaleKnob.cpp
    source/controls/inputs/qextScaleKnob.h
    source/controls/inputs/qextScaleKnob_p.h
    source/controls/inputs/qextSelectSlider.cpp
    source/controls/inputs/qextSelectSlider.h
    source/controls/inputs/qextSelectSlider_p.h
    source/controls/inputs/qextSlider.cpp
    source/controls/inputs/qextSlider.h
    source/controls/inputs/qextSlider_p.h
    source/controls/lights/qextBreathingLight.cpp
    source/controls/lights/qextBreathingLight.h
    source/controls/lights/qextBreathingLight_p.h
    source/controls/lights/qextIndicatorLight.cpp
    source/controls/lights/qextIndicatorLight.h
    source/controls/lights/qextIndicatorLight_p.h
    source/controls/lights/qextLed.cpp
    source/controls/lights/qextLed.h
    source/controls/lights/qextLed_p.h
    source/controls/lights/qextNumberLed.cpp
    source/controls/lights/qextNumberLed.h
    source/controls/lights/qextNumberLed_p.h
    source/controls/lights/qextTextLcd.cpp
    source/controls/lights/qextTextLcd.h
    source/controls/lights/qextTextLcd_p.h
    source/controls/qextArrowCompass.cpp
    source/controls/qextArrowCompass.h
    source/controls/qextArrowCompass_p.h
    source/controls/qextProgressKnob.cpp
    source/controls/qextProgressKnob.h
    source/controls/qextProgressKnob_p.h
    source/controls/qextRingCompass.cpp
    source/controls/qextRingCompass.h
    source/controls/qextRingCompass_p.h
    source/controls/qextSemicircleGauge.cpp
    source/controls/qextSemicircleGauge.h
    source/controls/qextSemicircleGauge_p.h
    source/controls/qextTumbler.cpp
    source/controls/qextTumbler.h
    source/controls/qextTumbler_p.h
    source/editors/property/qextPEAbstractPropertyEditor.cpp
    source/editors/property/qextPEAbstractPropertyEditor.h
    source/editors/property/qextPEAbstractPropertyEditor_p.h
    source/editors/property/qextPEProperty.cpp
    source/editors/property/qextPEProperty.h
    source/editors/property/qextPEProperty_p.h
    source/editors/property/qextPEPropertyButtonEditor.cpp
    source/editors/property/qextPEPropertyButtonEditor.h
    source/editors/property/qextPEPropertyEditor.h
    source/editors/property/qextPEPropertyGroupBoxEditor.cpp
    source/editors/property/qextPEPropertyGroupBoxEditor.h
    source/editors/property/qextPEPropertyManager.cpp
    source/editors/property/qextPEPropertyManager.h
    source/editors/property/qextPEPropertyManager_p.h
    source/editors/property/qextPEPropertyTreeEditor.cpp
    source/editors/property/qextPEPropertyTreeEditor.h
    source/editors/property/qextPEPropertyTreeEditor_p.h
    source/editors/property/qextPEVariantProperty.cpp
    source/editors/property/qextPEVariantProperty.h
    source/editors/property/qextPEVariantProperty_p.h
    source/editors/property/qextPEWidgetFactory.cpp
    source/editors/property/qextPEWidgetFactory.h
    source/editors/property/qextPEWidgetFactory_p.h
    source/tools/qextPropertyModel.h
    source/tools/qextPropertyModel.cpp
    source/tools/qextScroller.cpp
    source/tools/qextScroller.h
    source/tools/qextScroller_p.h
    source/tools/qextStyleSheetHooker.cpp
    source/tools/qextStyleSheetHooker.h
    source/tools/qextStyleSheetHooker_p.h
    source/tools/qextStyleThemes.cpp
    source/tools/qextStyleThemes.h
    source/tools/qextStyleThemes_p.h
    source/qextWidgetConstants.h
    source/qextWidgetGlobal.h
    resources/qextWidgets.qrc
    PRECOMPILED_HEADER
    source/qextWidgetPch.h
    PUBLIC_LIBRARIES
    ${QEXT_LIB_LINK_LIBRARIES})

#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
qext_add_subdirectory(tests QEXT_BUILD_TESTS)
