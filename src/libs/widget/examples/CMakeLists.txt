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
set(_example_link_libraries)

if(UNIX)
    list(APPEND _example_link_libraries dl)
endif()

if(WIN32)
    list(APPEND _example_link_libraries shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND _example_link_libraries ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _example_link_libraries Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _example_link_libraries Qt5::Core Qt5::Gui Qt5::Widgets)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND _example_link_libraries QEXTWidget QEXTFontAwesome)



#--------------------------------------------------------------------------------
# Add exp_qextWidgetNavTreeWidget example
#--------------------------------------------------------------------------------
set(_example_name exp_qextWidgetNavTreeWidget)
set(_example_headers
    navtreeview/navtreeview.h
    navtreeview/navtreeviewform.h
    )
set(_example_sources
    navtreeview/navtreeview.cpp
    navtreeview/navtreeviewform.cpp
    navtreeview/main.cpp
    )
set(_example_forms
    navtreeview/navtreeview.ui
    navtreeview/navtreeviewform.ui
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/navtreeview)
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()

#--------------------------------------------------------------------------------
# Add exp_qextWidgetNavListWidget example
#--------------------------------------------------------------------------------
set(_example_name exp_qextWidgetNavListWidget)
set(_example_headers
    navlistwidget/navlistwidget.h
    navlistwidget/navlistwidgetform.h
    )
set(_example_sources
    navlistwidget/navlistwidget.cpp
    navlistwidget/navlistwidgetform.cpp
    navlistwidget/main.cpp
    )
set(_example_forms
    navlistwidget/navlistwidget.ui
    navlistwidget/navlistwidgetform.ui
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/navlistwidget)
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()


#--------------------------------------------------------------------------------
# Add exp_qextWidgetNavButton example
#--------------------------------------------------------------------------------
set(_example_name exp_qextWidgetNavButton)
set(_example_headers
    navbutton/navbutton.h
    navbutton/iconhelper.h
    )
set(_example_sources
    navbutton/navbutton.cpp
    navbutton/iconhelper.cpp
    navbutton/main.cpp
    )
set(_example_forms
    navbutton/navbutton.ui
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/navbutton)
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()


#--------------------------------------------------------------------------------
# Add exp_qextWidgetSwitchButton example
#--------------------------------------------------------------------------------
set(_example_name exp_qextWidgetSwitchButton)
set(_example_headers
    switchbutton/frmswitchbutton.h
    )
set(_example_sources
    switchbutton/frmswitchbutton.cpp
    switchbutton/main.cpp
    )
set(_example_forms
    switchbutton/frmswitchbutton.ui
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/switchbutton)
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()




#--------------------------------------------------------------------------------
# Add exp_qextWidgetFramelessMainwindow example
#--------------------------------------------------------------------------------
set(_example_name exp_qextWidgetFramelessMainwindow)
set(_example_headers
    framelesswindow/mainwindow.h
    )
set(_example_sources
    framelesswindow/mainwindow.cpp
    framelesswindow/main.cpp
    )
set(_example_forms
    framelesswindow/mainwindow.ui
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/framelesswindow)
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()




#--------------------------------------------------------------------------------
# Add exp_qextWidgetFramelessDialog example
#--------------------------------------------------------------------------------
set(_example_name exp_qextWidgetFramelessDialog)
set(_example_headers
    framelessdialog/dialog.h
    )
set(_example_sources
    framelessdialog/dialog.cpp
    framelessdialog/main.cpp
    )
set(_example_forms
    framelessdialog/dialog.ui
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/framelessdialog)
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()




#--------------------------------------------------------------------------------
# Add exp_qextWidgetFramelessWidget example
#--------------------------------------------------------------------------------
set(_example_name exp_qextWidgetFramelessWidget)
set(_example_headers
    framelesswidget/widget.h
    )
set(_example_sources
    framelesswidget/widget.cpp
    framelesswidget/main.cpp
    )
set(_example_forms
    framelesswidget/widget.ui
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/framelesswidget)
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()


#--------------------------------------------------------------------------------
# Add exp_qextWidgetBreathingLight example
#--------------------------------------------------------------------------------
set(_example_name exp_qextWidgetBreathingLight)
set(_example_headers
    breathinglight/mainwindow.h
    )
set(_example_sources
    breathinglight/mainwindow.cpp
    breathinglight/main.cpp
    )
set(_example_forms
    breathinglight/mainwindow.ui
    )
set(_example_resource
    breathinglight/resources.qrc
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    ${_example_resource}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/breathinglight)
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()



#--------------------------------------------------------------------------------
# Add exp_qextWidgetIndicatorLight example
#--------------------------------------------------------------------------------
set(_example_name exp_qextWidgetIndicatorLight)
set(_example_headers
    indicatorlight/mainwindow.h
    )
set(_example_sources
    indicatorlight/mainwindow.cpp
    indicatorlight/main.cpp
    )
set(_example_forms
    indicatorlight/mainwindow.ui
    )
set(_example_resource

    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    ${_example_resource}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/indicatorlight)
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()



#--------------------------------------------------------------------------------
# Add exp_qextWidgetLcdNumber example
#--------------------------------------------------------------------------------
set(_example_name exp_qextWidgetLcdNumber)
set(_example_headers
    lcdnumber/mainwindow.h
    )
set(_example_sources
    lcdnumber/mainwindow.cpp
    lcdnumber/main.cpp
    )
set(_example_forms
    lcdnumber/mainwindow.ui
    )
set(_example_resource

    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    ${_example_resource}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lcdnumber)
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()



#--------------------------------------------------------------------------------
# Add exp_qextWidgetLcdText example
#--------------------------------------------------------------------------------
set(_example_name exp_qextWidgetLcdText)
set(_example_headers
    lcdtext/mainwindow.h
    )
set(_example_sources
    lcdtext/mainwindow.cpp
    lcdtext/main.cpp
    )
set(_example_forms
    lcdtext/mainwindow.ui
    )
set(_example_resource

    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    ${_example_resource}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lcdtext)
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()




#--------------------------------------------------------------------------------
# Add exp_qextWidgetLcdText example
#--------------------------------------------------------------------------------
set(_example_name exp_qextWidgetWaveChart)
set(_example_headers
    wavechart/frmwavechart.h
    )
set(_example_sources
    wavechart/frmwavechart.cpp
    wavechart/main.cpp
    )
set(_example_forms
    wavechart/frmwavechart.ui
    )
set(_example_resource

    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    ${_example_resource}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/wavechart)
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${_example_name} QEXTWidget ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()
