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
# Set lib base name and out put path
#--------------------------------------------------------------------------------
set(qext_lib_base_name QEXTWidget)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(qext_lib_public_headers
    include/qextLightBreathing.h
    include/qextLightIndicator.h
    include/qextDial.h
    include/qextFramelessDialog.h
    include/qextFramelessMainwindow.h
    include/qextFramelessWidget.h
    include/qextIconLabel.h
    include/qextInput.h
    include/qextIpAddressEdit.h
    include/qextLcdNumber.h
    include/qextLedText.h
    include/qextNavButton.h
    include/qextNavListWidget.h
    include/qextProgressBar.h
    include/qextProgressButton.h
    include/qextProgressPie.h
    include/qextProgressRing.h
    include/qextProgressWait.h
    include/qextSwitchButton.h
    include/qextThermometer.h
    include/qextTumbler.h
    include/qextTumblerDateTime.h
    include/qextWaveChart.h
    include/qextWidgetGlobal.h
    )

set(qext_lib_private_headers
    private/qextLightBreathing_p.h
    private/qextLightIndicator_p.h
    private/qextFramelessMainwindow_p.h
    private/qextIconLabel_p.h
    private/qextIpAddressEdit_p.h
    private/qextLcdNumber_p.h
    private/qextLedText_p.h
    private/qextNavButton_p.h
    private/qextNavListWidget_p.h
    private/qextSwitchButton_p.h
    private/qextWaveChart_p.h
    )

set(qext_lib_sources
    source/qextLightBreathing.cpp
    source/qextLightIndicator.cpp
    source/qextDial.cpp
    source/qextFramelessDialog.cpp
    source/qextFramelessMainwindow.cpp
    source/qextFramelessWidget.cpp
    source/qextIconLabel.cpp
    source/qextInput.cpp
    source/qextIpAddressEdit.cpp
    source/qextLcdNumber.cpp
    source/qextLedText.cpp
    source/qextNavButton.cpp
    source/qextNavListWidget.cpp
    source/qextProgressBar.cpp
    source/qextProgressButton.cpp
    source/qextProgressPie.cpp
    source/qextProgressRing.cpp
    source/qextProgressWait.cpp
    source/qextSwitchButton.cpp
    source/qextThermometer.cpp
    source/qextTumbler.cpp
    source/qextTumblerDateTime.cpp
    source/qextWaveChart.cpp
    )

set(qext_lib_forms
    source/qextInput.ui
    )

set(qext_lib_resources
    resource/QEXTWidget.qrc
    )



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(qext_lib_link_libraries)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND qext_lib_link_libraries Qt4::QtCore Qt4::QtGui Qt4::QtNetwork)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND qext_lib_link_libraries Qt${QEXT_QT_VERSION_MAJOR}::Core Qt${QEXT_QT_VERSION_MAJOR}::Gui Qt${QEXT_QT_VERSION_MAJOR}::Widgets Qt${QEXT_QT_VERSION_MAJOR}::Network)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND qext_lib_link_libraries QEXTCore QEXTFontAwesome QEXTGooglePinYin)



#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
add_library(${qext_lib_base_name}
    ${qext_lib_public_headers}
    ${qext_lib_private_headers}
    ${qext_lib_sources}
    ${qext_lib_forms}
    ${qext_lib_resources}
    )
if (QEXT_BUILD_COMPILER_WARNING)
    qextFunctionSetCompilerWarnings(${qext_lib_base_name})
endif()
target_link_libraries(${qext_lib_base_name} PUBLIC ${qext_lib_link_libraries})
target_include_directories(${qext_lib_base_name} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<INSTALL_INTERFACE:include>
    )
target_include_directories(${qext_lib_base_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )
set(${qext_lib_base_name}_PRIVATE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/private
    CACHE INTERNAL "${qext_lib_base_name} private include dirs"
    )
target_compile_definitions(${qext_lib_base_name} PRIVATE QEXT_BUILD_WIDGET_LIB)


# set target properties
set_target_properties(${qext_lib_base_name} PROPERTIES
    VERSION ${QEXT_VERSION} SOVERSION ${QEXT_SO_VERSION}
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    DEBUG_POSTFIX ${QEXT_DEBUG_POSTFIX}
    )
if (QEXT_BUILD_SHARED_LIBS)
    set_target_properties(${qext_lib_base_name} PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1)
endif()



#--------------------------------------------------------------------------------
# Add lib tests and examples
#--------------------------------------------------------------------------------
if (QEXT_BUILD_TESTS OR QEXT_BUILD_ALL)
    add_subdirectory(tests)
endif()

if (QEXT_BUILD_EXAMPLES OR QEXT_BUILD_ALL)
    add_subdirectory(examples)
endif()
