#################################################################################
#
# Library: CommonFramework
#
# Copyright (c) 2021 ChengXueWen 1398831004@qq.com
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
# Set output path
#--------------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${CF_EXAMPLE_OUTPUT_DIR}/mvvmqt)
set(LIBRARY_OUTPUT_PATH ${CF_EXAMPLE_OUTPUT_DIR}/mvvmqt)



#--------------------------------------------------------------------------------
# find qt and include path, set cmake moc uic rcc on
#--------------------------------------------------------------------------------
set(_example_cxx_standard 98)
set(_example_qt_found false)
find_package(Qt4 QUIET COMPONENTS QtCore QtGui)
if (NOT QT4_FOUND)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui)
endif()
set(_examplecf_qt_version_major  ${QT_VERSION_MAJOR})
set(_examplecf_qt_version_minor ${QT_VERSION_MINOR})
set(_examplecf_qt_version_patch ${QT_VERSION_PATCH})
set(_examplecf_qt_version "${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
if (_examplecf_qt_version_major  EQUAL 4)
    if (_examplecf_qt_version_minor LESS 5)
        message(FATAL_ERROR "----CommonFramework---- Expected Qt4 version must greater than or equal to Qt4.5")
    endif()
    find_package(Qt4 REQUIRED QtCore QtGui QtTest QtNetwork)
    INCLUDE(${QT_USE_FILE})
    ADD_DEFINITIONS(${QT_DEFINITIONS})
elseif(_examplecf_qt_version_major  EQUAL 5)
    if (_examplecf_qt_version_minor LESS 7)
        message(FATAL_ERROR "----CommonFramework---- Expected Qt5 version must greater than or equal to Qt5.7")
    endif()
    find_package(Qt5 COMPONENTS Core Widgets Network Test REQUIRED)
    set(_example_cxx_standard 11)
elseif(_examplecf_qt_version_major EQUAL 6)
    find_package(Qt6 COMPONENTS Core Widgets Network Quick Test REQUIRED)
    set(_example_cxx_standard 17)
else()
    message(FATAL_ERROR "----CommonFramework---- Not find Qt package")
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(_examplecf_qt_version_major EQUAL 4)
    list(APPEND _example_link_libraries Qt4::QtCore Qt4::QtGui)
elseif(_examplecf_qt_version_major EQUAL 5)
    list(APPEND _example_link_libraries Qt5::Core Qt5::Gui Qt5::Widgets)
else()
    message(FATAL_ERROR "----CommonFramework---- Not find Qt package")
endif()

list(APPEND _example_link_libraries CFCore CFMvvmQt)
include_directories(${CFCore_PRIVATE_INCLUDE_DIRS})


#--------------------------------------------------------------------------------
# Add exp_cfMvvmQt_hello example
#--------------------------------------------------------------------------------
set(_example_name exp_cfMvvmQt_hello)
set(_example_headers
    )
set(_example_sources
    main.cpp
    )
set(_example_forms
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    )
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
