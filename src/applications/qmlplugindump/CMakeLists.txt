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
set(_app_base_name qmlplugindump)
set(EXECUTABLE_OUTPUT_PATH ${QEXT_APP_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set app link libraries
#--------------------------------------------------------------------------------
set(_app_link_libraries)

if(UNIX)
    list(APPEND _app_link_libraries ${CMAKE_DL_LIBS})
endif()

if(WIN32)
    list(APPEND _app_link_libraries shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND _app_link_libraries ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _app_link_libraries Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _app_link_libraries Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Quick)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

include_directories(${Qt${QT_VERSION_MAJOR}Core_PRIVATE_INCLUDE_DIRS})
include_directories(${Qt${QT_VERSION_MAJOR}Quick_PRIVATE_INCLUDE_DIRS})

#--------------------------------------------------------------------------------
# Set file list
#--------------------------------------------------------------------------------
set(_app_public_headers
    qmlstreamwriter.h
    qmltypereader.h
    )
set(_app_private_headers
    )
set(_app_sources
    main.cpp
    qmlstreamwriter.cpp
    qmltypereader.cpp
    )
set(_app_forms
    )
set(_app_resources
    )



#--------------------------------------------------------------------------------
# Add app target
#--------------------------------------------------------------------------------
add_executable(${_app_base_name}
    ${_app_public_headers}
    ${_app_private_headers}
    ${_app_sources}
    ${_app_forms}
    ${_app_resources}
    )
if (QEXT_BUILD_COMPILER_WARNING)
    qextFunctionSetCompilerWarnings(${_lib_base_name})
endif()
target_link_libraries(${_app_base_name} PUBLIC ${_app_link_libraries})
target_include_directories(${_app_base_name} PUBLIC
    $<BUILD_INTERFACE:${QEXT_CONFIG_HPP_FILE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
    )


# set target properties
set_target_properties(${_app_base_name} PROPERTIES
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    )
