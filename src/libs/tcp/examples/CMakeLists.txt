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
set(EXECUTABLE_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/tcp)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR}/tcp)



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

list(APPEND _example_link_libraries QEXTTcp)



#--------------------------------------------------------------------------------
# Add exp_qextTcpSimpleServer example
#--------------------------------------------------------------------------------
set(_example_name exp_qextTcpSimpleServer)
set(_example_headers
    simpleServer/smainwindow.h
    )
set(_example_sources
    simpleServer/main.cpp
    simpleServer/smainwindow.cpp
    )
set(_example_forms
    simpleServer/smainwindow.ui
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleServer
    ${CMAKE_CURRENT_BINARY_DIR}/
    )
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${_example_name} QEXTTcp ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()


#--------------------------------------------------------------------------------
# Set exp_qextTcpSimpleClient example
#--------------------------------------------------------------------------------
set(_example_name exp_qextTcpSimpleClient)
set(_example_headers
    simpleClient/cmainwindow.h
    )
set(_example_sources
    simpleClient/main.cpp
    simpleClient/cmainwindow.cpp
    )
set(_example_forms
    simpleClient/cmainwindow.ui
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleClient
    ${CMAKE_CURRENT_BINARY_DIR}/
    )
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextMacroCopyDependenceLib(${_example_name} QEXTTcp ${EXECUTABLE_OUTPUT_PATH})
    qextMacroCopyDependenceLib(${_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()
