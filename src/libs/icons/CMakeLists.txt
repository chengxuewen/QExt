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
set(qext_lib_base_name QEXTIcons)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(qext_lib_public_headers
    include/qextIcons.h
    include/qextIconsGlobal.h
    )

set(qext_lib_private_headers
    private/qextIcons_p.h
    )

set(qext_lib_sources
    source/qextIcons.cpp
    )

set(qext_lib_forms

    )

set(qext_lib_resources
    resource/QEXTIcons.qrc
    )

list(APPEND qext_lib_link_libraries QEXTCore)


#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(qext_lib_link_libraries)
set(qext_lib_include_directories)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND qext_lib_link_libraries Qt4::QtCore Qt4::QtGui Qt4::QtSvg)
    list(APPEND qext_lib_include_directories
        ${Qt4Gui_PRIVATE_INCLUDE_DIRS}
        ${Qt4Widgets_PRIVATE_INCLUDE_DIRS}
        )
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND qext_lib_link_libraries
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Svg
        )
    list(APPEND qext_lib_include_directories
        ${Qt${QEXT_QT_VERSION_MAJOR}Gui_PRIVATE_INCLUDE_DIRS}
        ${Qt${QEXT_QT_VERSION_MAJOR}Widgets_PRIVATE_INCLUDE_DIRS}
        )
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND qext_lib_link_libraries QEXTCore)



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
target_include_directories(${qext_lib_base_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<BUILD_INTERFACE:${qext_lib_include_directories}>
    $<INSTALL_INTERFACE:include>
    )
target_compile_definitions(${qext_lib_base_name} PRIVATE QEXT_BUILD_ICONS_LIB)


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
