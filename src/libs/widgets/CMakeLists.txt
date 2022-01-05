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

#--------------------------------------------------------------------------------
# Set lib base name and out put path
#--------------------------------------------------------------------------------
set(QEXT_LIB_BASE_NAME QEXTWidgets)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(QEXT_LIB_PUBLIC_HEADERS
    include/qextBreathingLight.h
    include/qextIndicatorLight.h
    include/qextDial.h
    include/qextFramelessDialog.h
    include/qextFramelessMainwindow.h
    include/qextFramelessWidget.h
    include/qextCircleGauge.h
    include/qextArrowCompass.h
    include/qextSemicircleGauge.h
    include/qextIconButton.h
    include/qextIconLabel.h
    include/qextInput.h
    include/qextIpAddressEdit.h
    include/qextNumberLed.h
    include/qextTextLcd.h
    include/qextNavigationButton.h
    include/qextNavigationListView.h
    include/qextNavigationBar.h
    include/qextProgressBar.h
    include/qextProgressButton.h
    include/qextProgressPie.h
    include/qextProgressRing.h
    include/qextProgressWait.h
    include/qextRangeSlider.h
    include/qextSwitchButton.h
    include/qextRulerSlider.h
    include/qextSelectSlider.h
    include/qextSlider.h
    include/qextStyleSheet.h
    include/qextStyleSheetPalette.h
    include/qextThermometer.h
    include/qextTooltip.h
    include/qextTumbler.h
    include/qextDateTimeTumbler.h
    include/qextWaveChart.h
    include/qextRingCompass.h
    include/qextProgressKnob.h
    include/qextScaleKnob.h
    include/qextLed.h
    include/qextOvenTimer.h
    include/qextWidgetGlobal.h
    include/qextWidgetPch.h
    )

set(QEXT_LIB_PRIVATE_HEADERS
    private/qextBreathingLight_p.h
    private/qextIndicatorLight_p.h
    private/qextFramelessDialog_p.h
    private/qextFramelessMainwindow_p.h
    private/qextFramelessWidget_p.h
    private/qextCircleGauge_p.h
    private/qextArrowCompass_p.h
    private/qextSemicircleGauge_p.h
    private/qextIconButton_p.h
    private/qextIconLabel_p.h
    private/qextIpAddressEdit_p.h
    private/qextNumberLed_p.h
    private/qextTextLcd_p.h
    private/qextNavigationButton_p.h
    private/qextNavigationListView_p.h
    private/qextSwitchButton_p.h
    private/qextWaveChart_p.h
    private/qextRingCompass_p.h
    private/qextSelectSlider_p.h
    private/qextSlider_p.h
    private/qextStyleSheetPalette_p.h
    private/qextStyleSheet_p.h
    private/qextTooltip_p.h
    private/qextTumbler_p.h
    private/qextDateTimeTumbler_p.h
    private/qextDial_p.h
    private/qextProgressKnob_p.h
    private/qextScaleKnob_p.h
    private/qextProgressRing_p.h
    private/qextLed_p.h
    private/qextNavigationBar_p.h
    private/qextOvenTimer_p.h
    private/qextProgressBar_p.h
    private/qextProgressButton_p.h
    private/qextProgressPie_p.h
    private/qextProgressWait_p.h
    private/qextRangeSlider_p.h
    private/qextRulerSlider_p.h
    private/qextThermometer_p.h
    )

set(QEXT_LIB_SOURCES
    source/qextBreathingLight.cpp
    source/qextIndicatorLight.cpp
    source/qextDial.cpp
    source/qextFramelessDialog.cpp
    source/qextFramelessMainwindow.cpp
    source/qextFramelessWidget.cpp
    source/qextCircleGauge.cpp
    source/qextArrowCompass.cpp
    source/qextSemicircleGauge.cpp
    source/qextIconButton.cpp
    source/qextIconLabel.cpp
    source/qextInput.cpp
    source/qextIpAddressEdit.cpp
    source/qextNumberLed.cpp
    source/qextTextLcd.cpp
    source/qextNavigationButton.cpp
    source/qextNavigationListView.cpp
    source/qextNavigationBar.cpp
    source/qextProgressBar.cpp
    source/qextProgressButton.cpp
    source/qextProgressPie.cpp
    source/qextProgressRing.cpp
    source/qextProgressWait.cpp
    source/qextRangeSlider.cpp
    source/qextRulerSlider.cpp
    source/qextSelectSlider.cpp
    source/qextSlider.cpp
    source/qextStyleSheet.cpp
    source/qextStyleSheetPalette.cpp
    source/qextSwitchButton.cpp
    source/qextThermometer.cpp
    source/qextTooltip.cpp
    source/qextTumbler.cpp
    source/qextDateTimeTumbler.cpp
    source/qextWaveChart.cpp
    source/qextRingCompass.cpp
    source/qextProgressKnob.cpp
    source/qextScaleKnob.cpp
    source/qextLed.cpp
    source/qextOvenTimer.cpp
    )

set(QEXT_LIB_FORMS
    source/qextInput.ui
    )

set(QEXT_LIB_RESOURCES
    resource/QEXTWidgets.qrc
    )



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(QEXT_LIB_LINK_LIBRARIES)

if(UNIX)
    list(APPEND QEXT_LIB_LINK_LIBRARIES ${CMAKE_DL_LIBS})
endif()

if(WIN32)
    list(APPEND QEXT_LIB_LINK_LIBRARIES shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND QEXT_LIB_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui Qt4::QtNetwork)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets
        )
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QEXTCore QEXTIconFont QEXTGooglePinYin)



#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
add_library(${QEXT_LIB_BASE_NAME}
    ${QEXT_LIB_PUBLIC_HEADERS}
    ${QEXT_LIB_PRIVATE_HEADERS}
    ${QEXT_LIB_SOURCES}
    ${QEXT_LIB_FORMS}
    ${QEXT_LIB_RESOURCES}
    )
if (QEXT_BUILD_COMPILER_WARNING)
    qextFunctionSetCompilerWarnings(${QEXT_LIB_BASE_NAME})
endif()
if (QEXT_BUILD_USE_PCH)
    qextFunctionActivatePrecompiledHeaders(${QEXT_LIB_BASE_NAME} PRIVATE include/qextWidgetPch.h)
endif()
target_link_libraries(${QEXT_LIB_BASE_NAME} PUBLIC ${QEXT_LIB_LINK_LIBRARIES})
target_include_directories(${QEXT_LIB_BASE_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${QEXT_LIB_BASE_NAME}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<INSTALL_INTERFACE:include/${QEXT_LIB_BASE_NAME}/private>
    )
target_compile_definitions(${QEXT_LIB_BASE_NAME} PRIVATE QEXT_BUILD_WIDGETS_LIB)

# set target properties
set_target_properties(${QEXT_LIB_BASE_NAME} PROPERTIES
    VERSION ${QEXT_VERSION} SOVERSION ${QEXT_SO_VERSION}
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    DEBUG_POSTFIX ${QEXT_DEBUG_POSTFIX}
    )
if (QEXT_BUILD_SHARED_LIBS)
    set_target_properties(${QEXT_LIB_BASE_NAME} PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1)
endif()

# set include files copy command
foreach(HEADER ${QEXT_LIB_PUBLIC_HEADERS})
    get_filename_component(HEADER_ABSOLUTE_PATH ${HEADER} ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})
    list(APPEND QEXT_LIB_PUBLIC_ABSOLUTE_HEADERS ${HEADER_ABSOLUTE_PATH})
endforeach()
foreach(HEADER ${QEXT_LIB_PRIVATE_HEADERS})
    get_filename_component(HEADER_ABSOLUTE_PATH ${HEADER} ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})
    list(APPEND QEXT_LIB_PRIVATE_ABSOLUTE_HEADERS ${HEADER_ABSOLUTE_PATH})
endforeach()
add_custom_command(
    TARGET ${QEXT_LIB_BASE_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${QEXT_INCLUDE_OUTPUT_DIR}/${QEXT_LIB_BASE_NAME}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${QEXT_INCLUDE_OUTPUT_DIR}/${QEXT_LIB_BASE_NAME}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${QEXT_INCLUDE_OUTPUT_DIR}/${QEXT_LIB_BASE_NAME}/private
    COMMAND ${CMAKE_COMMAND} -E copy ${QEXT_LIB_PUBLIC_ABSOLUTE_HEADERS} ${QEXT_INCLUDE_OUTPUT_DIR}/${QEXT_LIB_BASE_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy ${QEXT_LIB_PRIVATE_ABSOLUTE_HEADERS} ${QEXT_INCLUDE_OUTPUT_DIR}/${QEXT_LIB_BASE_NAME}/private
    COMMENT "Copy ${QEXT_LIB_BASE_NAME} include files to output dir"
    POST_BUILD
    )



#--------------------------------------------------------------------------------
# Add lib tests and examples
#--------------------------------------------------------------------------------
if (QEXT_BUILD_TESTS OR QEXT_BUILD_ALL)
    add_subdirectory(tests)
endif()

if (QEXT_BUILD_EXAMPLES OR QEXT_BUILD_ALL)
    add_subdirectory(examples)
endif()
