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
set(EXECUTABLE_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/quick)
set(LIBRARY_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/quick)
set(QEXTQUICKEXAMPLE_CONFIG_FILE_DIR ${QEXT_EXAMPLE_OUTPUT_DIR}/quick)
set(QEXTQUICKEXAMPLE_CONFIG_FILE_PATH ${QEXTQUICKEXAMPLE_CONFIG_FILE_DIR}/qextquickexampleconfig.h)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/qextquickexampleconfig.h.in"
    "${QEXTQUICKEXAMPLE_CONFIG_FILE_PATH}"
    )
set(QML_IMPORT_PATH "${QEXT_QML_OUTPUT_DIR}" CACHE STRING "Qt Creator extra qml import paths")



#--------------------------------------------------------------------------------
# Set example link libraries
#--------------------------------------------------------------------------------
set(_example_link_libraries)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _example_link_libraries Qt4::QtCore Qt4::QtNetwork)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _example_link_libraries Qt5::Core Qt5::Gui Qt5::Quick)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND _example_link_libraries QEXTQuick)



#--------------------------------------------------------------------------------
# Add QEXTQuickSimple example
#--------------------------------------------------------------------------------
set(_example_name QEXTQuickSimple)
set(_example_headers
    )
set(_example_sources
    simple/main.cpp
    )
set(_example_forms
    )
set(_example_resource
    simple/QEXTQuickSimple.qrc
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    ${_example_resource}
    ${QEXTQUICKEXAMPLE_CONFIG_FILE_PATH}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_compile_definitions(${_example_name} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_include_directories(${_example_name} PUBLIC
    ${QEXTQUICKEXAMPLE_CONFIG_FILE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/simple
    ${CMAKE_CURRENT_BINARY_DIR}
    )


#--------------------------------------------------------------------------------
# Set QEXTQuickComponent example
#--------------------------------------------------------------------------------
set(_example_name QEXTQuickComponent)
set(_example_headers
    )
set(_example_sources
    component/main.cpp
    )
set(_example_forms
    )
set(_example_resource
    component/QEXTQuickComponent.qrc
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    ${_example_resource}
    ${QEXTQUICKEXAMPLE_CONFIG_FILE_PATH}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_compile_definitions(${_example_name} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_include_directories(${_example_name} PUBLIC
    ${QEXTQUICKEXAMPLE_CONFIG_FILE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/component
    ${CMAKE_CURRENT_BINARY_DIR}/
    )



#--------------------------------------------------------------------------------
# Set QEXTQuickCustomWindow example
#--------------------------------------------------------------------------------
set(_example_name QEXTQuickCustomWindow)
set(_example_headers
    )
set(_example_sources
    customwindow/main.cpp
    )
set(_example_forms
    )
set(_example_resource
    customwindow/QEXTQuickCustomWindow.qrc
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    ${_example_resource}
    ${QEXTQUICKEXAMPLE_CONFIG_FILE_PATH}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_compile_definitions(${_example_name} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_include_directories(${_example_name} PUBLIC
    ${QEXTQUICKEXAMPLE_CONFIG_FILE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/customwindow
    ${CMAKE_CURRENT_BINARY_DIR}/
    )



#--------------------------------------------------------------------------------
# Set QEXTQuickPaletteView example
#--------------------------------------------------------------------------------
set(_example_name QEXTQuickPaletteView)
set(_example_headers
    paletteview/qextquickpalettetablemodel.h
    )
set(_example_sources
    paletteview/main.cpp
    paletteview/qextquickpalettetablemodel.cpp
    )
set(_example_forms
    )
set(_example_resource
    paletteview/QEXTQuickPaletteView.qrc
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    ${_example_resource}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_compile_definitions(${_example_name} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_include_directories(${_example_name} PUBLIC
    ${QEXTQUICKEXAMPLE_CONFIG_FILE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/paletteview
    ${CMAKE_CURRENT_BINARY_DIR}/
    )
