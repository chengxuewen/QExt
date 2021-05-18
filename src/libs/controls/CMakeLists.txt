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
set(_lib_base_name QEXTControls)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(_lib_public_headers
    include/control/qextcontrolbase.h
    include/control/qextcontrolbuttonbase.h
    include/control/qextcontroldialog.h
    include/control/qextcontroldrawer.h
    include/control/qextcontrolmenu.h
    include/control/qextcontroloverlay.h
    include/control/qextcontrolpopup.h
    include/control/qextcontrolstackview.h
    include/control/qextcontrolswipeview.h
    include/control/qextcontroltooltip.h

    include/painting/qextcontrolbrush.h
    include/painting/qextcontrolcolor.h
    include/painting/qextcontrolfont.h
    include/painting/qextcontrolpainter.h
    include/painting/qextcontrolpalette.h
    include/painting/qextcontrolpen.h

    include/style/qextcontroldrawutil.h
    include/style/qextcontrolstyle.h
    include/style/qextcontrolstylehelper.h
    include/style/qextcontrolstyleoption.h
    include/style/qextcontrolstylesheet.h

    include/qextcontrolsglobal.h
    )

set(_lib_private_headers
    private/control/qextcontrolbase_p.h
    private/control/qextcontrolbuttonbase_p.h
    private/control/qextcontroldialog_p.h
    private/control/qextcontroldrawer_p.h
    private/control/qextcontrolmenu_p.h
    private/control/qextcontroloverlay_p.h
    private/control/qextcontrolpopup_p.h
    private/control/qextcontrolstackview_p.h
    private/control/qextcontrolswipeview_p.h
    private/control/qextcontroltooltip_p.h

    private/style/qextcontroldrawutil_p.h
    private/style/qextcontrolstyle_p.h
    private/style/qextcontrolstylehelper_p.h

    private/painting/qextpainter_p.h
    )

set(_lib_sources
    source/control/qextcontrolbase.cpp
    source/control/qextcontrolbuttonbase.cpp
    source/control/qextcontroldialog.cpp
    source/control/qextcontroldrawer.cpp
    source/control/qextcontrolmenu.cpp
    source/control/qextcontroloverlay.cpp
    source/control/qextcontrolpopup.cpp
    source/control/qextcontrolstackview.cpp
    source/control/qextcontrolswipeview.cpp
    source/control/qextcontroltooltip.cpp

    source/style/qextcontroldrawutil.cpp
    source/style/qextcontrolstyle.cpp
    source/style/qextcontrolstylehelper.cpp
    source/style/qextcontrolstyleoption.cpp
    source/style/qextcontrolstylesheet.cpp

    source/painting/qextcontrolbrush.cpp
    source/painting/qextcontrolcolor.cpp
    source/painting/qextcontrolfont.cpp
    source/painting/qextcontrolpainter.cpp
    source/painting/qextcontrolpalette.cpp
    source/painting/qextcontrolpen.cpp
    )

set(_lib_forms

    )

set(_lib_resources

    )



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(_lib_link_libraries)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _lib_link_libraries Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _lib_link_libraries Qt5::Core Qt5::Gui Qt5::Widgets)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND _lib_link_libraries QEXTCore)



#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
add_library(${_lib_base_name}
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
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/control>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/painting>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/style>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/theme>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/control>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/painting>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/style>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/theme>
    $<INSTALL_INTERFACE:include>
    )
target_compile_definitions(${_lib_base_name} PRIVATE QEXT_BUILD_CONTROLS_LIB)


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
