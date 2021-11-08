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

if(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND qext_example_link_libraries
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND qext_example_link_libraries QEXTQuick QEXTWidgets)



#--------------------------------------------------------------------------------
# define function
#--------------------------------------------------------------------------------
function(qextQuickAddExample EXAMPLE_NAME)
    set(multiValueArgs EXAMPLE_SOURCE EXAMPLE_INCLUDE_DIRS)
    cmake_parse_arguments(MY "" "" "${multiValueArgs}" "${ARGN}")
    add_executable(${EXAMPLE_NAME} ${MY_EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE ${qext_example_link_libraries})
    target_include_directories(${EXAMPLE_NAME} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${MY_EXAMPLE_INCLUDE_DIRS}
        ${qext_example_include_directories}
        )
    set_property(TARGET ${EXAMPLE_NAME} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
    if(QEXT_BUILD_SHARED_LIBS AND WIN32)
        qextMacroCopyDependenceLib(${EXAMPLE_NAME} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
        qextMacroCopyDependenceLib(${EXAMPLE_NAME} QEXTQuick ${EXECUTABLE_OUTPUT_PATH})
        qextMacroCopyDependenceLib(${EXAMPLE_NAME} QEXTWidgets ${EXECUTABLE_OUTPUT_PATH})
    endif()
endfunction()



#--------------------------------------------------------------------------------
# Add example
#--------------------------------------------------------------------------------
qextQuickAddExample(qext_exp_quickWidgetProxy
    EXAMPLE_SOURCE
    widgetproxy/calendarwidgetproxyitem.cpp
    widgetproxy/calendarwidgetproxyitem.h
    widgetproxy/example.qrc
    widgetproxy/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/widgetproxy
    )
