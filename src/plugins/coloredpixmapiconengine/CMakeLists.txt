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
set(_lib_base_name QEXTColoredPixmapIcon)
set(LIBRARY_OUTPUT_PATH ${QEXT_PLUGIN_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(_lib_public_headers
    include/qextColoredPixmapIconEngine.h
    include/qextColoredPixmapIconGlobal.h
    )

set(_lib_private_headers
    )

set(_lib_sources
    source/qextColoredPixmapIconEngine.cpp
    source/qextColoredPixmapIconEnginePlugin.cpp
    )

set(_lib_forms

    )

set(_lib_resources
    resource/QEXTColoredPixmapIcon.qrc
    )

list(APPEND _lib_link_libraries QEXTCore)


#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(_lib_link_libraries)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _lib_link_libraries Qt4::QtCore Qt4::QtGui Qt4::QtNetwork)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _lib_link_libraries Qt5::Core Qt5::Gui Qt5::Network)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND _lib_link_libraries QEXTCore)



#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
add_library(${_lib_base_name} STATIC
    ${_lib_public_headers}
    ${_lib_private_headers}
    ${_lib_sources}
    ${_lib_forms}
    ${_lib_resources}
    )
if (QEXT_BUILD_COMPILER_WARNING)
    qextFunctionSetCompilerWarnings(${_lib_base_name})
endif()
target_link_libraries(${_lib_base_name} PUBLIC ${_lib_link_libraries})
target_include_directories(${_lib_base_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/resource>
    $<BUILD_INTERFACE:${Qt5Gui_PRIVATE_INCLUDE_DIRS}>
    $<BUILD_INTERFACE:${Qt5Widgets_PRIVATE_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:include>
    )
target_compile_definitions(${_lib_base_name} PRIVATE QEXT_BUILD_COLOREDPIXMAPICON_LIB)


# set target properties
set_target_properties(${_lib_base_name} PROPERTIES
    VERSION ${QEXT_VERSION} SOVERSION ${QEXT_SO_VERSION}
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    DEBUG_POSTFIX ${QEXT_DEBUG_POSTFIX}
    )
if (QEXT_BUILD_SHARED_LIBS)
    set_target_properties(${_lib_base_name} PROPERTIES
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
