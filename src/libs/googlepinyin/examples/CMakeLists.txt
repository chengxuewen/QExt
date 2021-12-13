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
set(EXECUTABLE_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/fontawesome)
set(LIBRARY_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/fontawesome)



#--------------------------------------------------------------------------------
# Set example link libraries
#--------------------------------------------------------------------------------
set(QEXT_EXAMPLE_LINK_LIBRARIES)

if(UNIX)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES dl)
endif()

if(WIN32)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES QEXTFontAwesome)



#--------------------------------------------------------------------------------
# Add qext_exp_fontAwesome example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_fontAwesome)
set(qext_example_headers
    fontAwesomeView/MainWindow.h
    )
set(qext_example_sources
    fontAwesomeView/MainWindow.cpp
    fontAwesomeView/main.cpp
    )
set(qext_example_forms
    fontAwesomeView/MainWindow.ui
    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    )
target_link_libraries(${qext_example_name} PRIVATE ${QEXT_EXAMPLE_LINK_LIBRARIES})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fontAwesomeView)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextFunctionCopyDependencyInternal(${qext_example_name} QEXTFontAwesome ${EXECUTABLE_OUTPUT_PATH})
    qextFunctionCopyDependencyInternal(${qext_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()
