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



#--------------------------------------------------------------------------------
# Add qext_exp_widgetNavTreeWidget example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetNavTreeWidget)
set(qext_example_headers
    navtreeview/navtreeview.h
    navtreeview/navtreeviewform.h
    )
set(qext_example_sources
    navtreeview/navtreeview.cpp
    navtreeview/navtreeviewform.cpp
    navtreeview/main.cpp
    )
set(qext_example_forms
    navtreeview/navtreeview.ui
    navtreeview/navtreeviewform.ui
    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/navtreeview)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()

#--------------------------------------------------------------------------------
# Add qext_exp_widgetNavListWidget example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetNavListWidget)
set(qext_example_headers
    navlistwidget/navlistwidget.h
    navlistwidget/navlistwidgetform.h
    )
set(qext_example_sources
    navlistwidget/navlistwidget.cpp
    navlistwidget/navlistwidgetform.cpp
    navlistwidget/main.cpp
    )
set(qext_example_forms
    navlistwidget/navlistwidget.ui
    navlistwidget/navlistwidgetform.ui
    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/navlistwidget)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()


#--------------------------------------------------------------------------------
# Add qext_exp_widgetNavButton example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetNavButton)
set(qext_example_headers
    navbutton/navbutton.h
    navbutton/iconhelper.h
    )
set(qext_example_sources
    navbutton/navbutton.cpp
    navbutton/iconhelper.cpp
    navbutton/main.cpp
    )
set(qext_example_forms
    navbutton/navbutton.ui
    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/navbutton)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()


#--------------------------------------------------------------------------------
# Add qext_exp_widgetSwitchButton example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetSwitchButton)
set(qext_example_headers
    switchbutton/frmswitchbutton.h
    )
set(qext_example_sources
    switchbutton/frmswitchbutton.cpp
    switchbutton/main.cpp
    )
set(qext_example_forms
    switchbutton/frmswitchbutton.ui
    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/switchbutton)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()




#--------------------------------------------------------------------------------
# Add qext_exp_widgetFramelessMainwindow example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetFramelessMainwindow)
set(qext_example_headers
    framelesswindow/mainwindow.h
    )
set(qext_example_sources
    framelesswindow/mainwindow.cpp
    framelesswindow/main.cpp
    )
set(qext_example_forms
    framelesswindow/mainwindow.ui
    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/framelesswindow)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()




#--------------------------------------------------------------------------------
# Add qext_exp_widgetFramelessDialog example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetFramelessDialog)
set(qext_example_headers
    framelessdialog/dialog.h
    )
set(qext_example_sources
    framelessdialog/dialog.cpp
    framelessdialog/main.cpp
    )
set(qext_example_forms
    framelessdialog/dialog.ui
    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/framelessdialog)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()




#--------------------------------------------------------------------------------
# Add qext_exp_widgetFramelessWidget example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetFramelessWidget)
set(qext_example_headers
    framelesswidget/widget.h
    )
set(qext_example_sources
    framelesswidget/widget.cpp
    framelesswidget/main.cpp
    )
set(qext_example_forms
    framelesswidget/widget.ui
    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/framelesswidget)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()


#--------------------------------------------------------------------------------
# Add qext_exp_widgetBreathingLight example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetBreathingLight)
set(qext_example_headers
    breathinglight/mainwindow.h
    )
set(qext_example_sources
    breathinglight/mainwindow.cpp
    breathinglight/main.cpp
    )
set(qext_example_forms
    breathinglight/mainwindow.ui
    )
set(qext_example_resource
    breathinglight/resources.qrc
    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    ${qext_example_resource}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/breathinglight)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()



#--------------------------------------------------------------------------------
# Add qext_exp_widgetIndicatorLight example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetIndicatorLight)
set(qext_example_headers
    indicatorlight/mainwindow.h
    )
set(qext_example_sources
    indicatorlight/mainwindow.cpp
    indicatorlight/main.cpp
    )
set(qext_example_forms
    indicatorlight/mainwindow.ui
    )
set(qext_example_resource

    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    ${qext_example_resource}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/indicatorlight)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()



#--------------------------------------------------------------------------------
# Add qext_exp_widgetLcdNumber example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetLcdNumber)
set(qext_example_headers
    lcdnumber/mainwindow.h
    )
set(qext_example_sources
    lcdnumber/mainwindow.cpp
    lcdnumber/main.cpp
    )
set(qext_example_forms
    lcdnumber/mainwindow.ui
    )
set(qext_example_resource

    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    ${qext_example_resource}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lcdnumber)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()



#--------------------------------------------------------------------------------
# Add qext_exp_widgetLcdText example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetLcdText)
set(qext_example_headers
    lcdtext/mainwindow.h
    )
set(qext_example_sources
    lcdtext/mainwindow.cpp
    lcdtext/main.cpp
    )
set(qext_example_forms
    lcdtext/mainwindow.ui
    )
set(qext_example_resource

    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    ${qext_example_resource}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lcdtext)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()




#--------------------------------------------------------------------------------
# Add qext_exp_widgetLcdText example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetWaveChart)
set(qext_example_headers
    wavechart/frmwavechart.h
    )
set(qext_example_sources
    wavechart/frmwavechart.cpp
    wavechart/main.cpp
    )
set(qext_example_forms
    wavechart/frmwavechart.ui
    )
set(qext_example_resource

    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    ${qext_example_resource}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/wavechart)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()



#--------------------------------------------------------------------------------
# Add qext_exp_widgetIpAddressEdit example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetIpAddress)
set(qext_example_headers
    ipaddress/frmipaddress.h
    )
set(qext_example_sources
    ipaddress/frmipaddress.cpp
    ipaddress/main.cpp
    )
set(qext_example_forms
    ipaddress/frmipaddress.ui
    )
set(qext_example_resource

    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    ${qext_example_resource}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ipaddress)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()



#--------------------------------------------------------------------------------
# Add qext_exp_widgetTumbler example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetTumbler)
set(qext_example_headers
    tumbler/frmtumbler.h
    tumbler/frmtumblerdatetime.h
    )
set(qext_example_sources
    tumbler/frmtumbler.cpp
    tumbler/frmtumblerdatetime.cpp
    tumbler/main.cpp
    )
set(qext_example_forms
    tumbler/frmtumbler.ui
    tumbler/frmtumblerdatetime.ui
    )
set(qext_example_resource

    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    ${qext_example_resource}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ipaddress)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()



#--------------------------------------------------------------------------------
# Add qext_exp_widgetDial example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetDial)
set(qext_example_headers
    dial/frmgaugedial.h
    )
set(qext_example_sources
    dial/frmgaugedial.cpp
    dial/main.cpp
    )
set(qext_example_forms
    dial/frmgaugedial.ui
    )
set(qext_example_resource

    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    ${qext_example_resource}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ipaddress)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()



#--------------------------------------------------------------------------------
# Add qext_exp_widgetThermometer example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_widgetThermometer)
set(qext_example_headers
    thermometer/frmthermometer.h
    )
set(qext_example_sources
    thermometer/frmthermometer.cpp
    thermometer/main.cpp
    )
set(qext_example_forms
    thermometer/frmthermometer.ui
    )
set(qext_example_resource

    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    ${qext_example_resource}
    )
target_link_libraries(${qext_example_name} PRIVATE ${qext_example_link_libraries})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ipaddress)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${qext_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()
