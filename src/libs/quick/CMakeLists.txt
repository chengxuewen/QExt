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
set(_lib_base_name QEXTQuick)
set(QEXTQUICK_GENERATE_QMLTYPE_FILE ON)
set(QEXTQUICK_NAME ${_lib_base_name})
set(QEXTQUICK_VERSION_MAJOR 1)
set(QEXTQUICK_VERSION_MINOR 2)
set(QEXTQUICK_CONFIG_FILE_DIR ${QEXT_INCLUDE_OUTPUT_DIR}/${_lib_base_name})
set(QEXTQUICK_CONFIG_FILE_PATH ${QEXTQUICK_CONFIG_FILE_DIR}/qextquickconfig.h)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/qextquickconfig.h.in"
    "${QEXTQUICK_CONFIG_FILE_PATH}"
    )

set(LIBRARY_OUTPUT_PATH ${QEXT_QML_OUTPUT_DIR}/${_lib_base_name})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(_lib_public_headers
    include/gadget/qextbackgroundgadget.h
    include/gadget/qextbordergadget.h
    include/gadget/qexticongadget.h
    include/gadget/qextitemgadget.h
    include/gadget/qextscrollbargadget.h
    include/gadget/qexttextgadget.h

    include/theme/qextquickthemebinder.h
    include/theme/qextquickthemeconstant.h
    include/theme/qextquickthemefileparser.h
    include/theme/qextquickthemehandler.h
    include/theme/qextquickthemejsonfileparser.h
    include/theme/qextquickthememanager.h

    include/qextquickfontawesome.h
    include/qextquick.h
    include/qextquickglobal.h
    include/qextquickloader.h
    include/qextquickpalette.h
    include/qextquickqmlplugin.h
    include/qextquickworld.h
    )

set(_lib_private_headers
    private/gadget/qextbackgroundgadget_p.h
    private/gadget/qextbordergadget_p.h
    private/gadget/qexticongadget_p.h
    private/gadget/qextitemgadget_p.h
    private/gadget/qexttextgadget_p.h
    private/gadget/qextscrollbargadget_p.h

    private/theme/qextquickthemebinder_p.h
    private/theme/qextquickthemehandler_p.h
    private/theme/qextquickthememanager_p.h

    private/qextquick_p.h
    private/qextquickpalette_p.h
    private/qextquickworld_p.h
    )

set(_lib_sources
    source/gadget/qextbackgroundgadget.cpp
    source/gadget/qextbordergadget.cpp
    source/gadget/qexticongadget.cpp
    source/gadget/qextitemgadget.cpp
    source/gadget/qextscrollbargadget.cpp
    source/gadget/qexttextgadget.cpp

    source/theme/qextquickthemebinder.cpp
    source/theme/qextquickthemeconstant.cpp
    source/theme/qextquickthemehandler.cpp
    source/theme/qextquickthemejsonfileparser.cpp
    source/theme/qextquickthememanager.cpp

    source/qextquickfontawesome.cpp
    source/qextquick.cpp
    source/qextquickglobal.cpp
    source/qextquickloader.cpp
    source/qextquickpalette.cpp
    source/qextquickqmlplugin.cpp
    source/qextquickworld.cpp
    )

set(_lib_forms

    )

set(_lib_resources
    resource/QEXTQuick.qrc
    )

set(_lib_forms
    )


#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(_lib_link_libraries)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _lib_link_libraries Qt4::QtCore Qt4::QtNetwork)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _lib_link_libraries Qt5::Core Qt5::Gui Qt5::Quick)
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
    ${QEXTQUICK_CONFIG_FILE_PATH}
    )
qextFunctionSetCompilerWarnings(${_lib_base_name})
target_link_libraries(${_lib_base_name} PUBLIC ${_lib_link_libraries})
target_include_directories(${_lib_base_name} PUBLIC
    $<BUILD_INTERFACE:${QEXTQUICK_CONFIG_FILE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/gadget>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/theme>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/gadget>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/theme>
    $<INSTALL_INTERFACE:include>
    )
target_compile_definitions(${_lib_base_name} PRIVATE QEXT_BUILD_QUICK_LIB)
target_compile_definitions(${_lib_base_name} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

# set target properties
set_target_properties(${_lib_base_name} PROPERTIES
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    )
if (QEXT_BUILD_SHARED_LIBS)
    set_target_properties(${_lib_base_name} PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1)
endif()


if(QEXTQUICK_GENERATE_QMLTYPE_FILE)
    message(STATUS "----QEXT---- Enable create qml plugin ${_lib_base_name} plugin.qmltypes")
    add_dependencies(${_lib_base_name} qmlplugindump)
    set(QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE ${QEXT_APP_OUTPUT_DIR}/qmlplugindump)
    set(QEXTQUICK_MODULE_VERSION ${QEXTQUICK_VERSION_MAJOR}.${QEXTQUICK_VERSION_MINOR})
    set(QEXTQUICK_TYPEINFO_GENERATE_DIR ${QEXT_QML_OUTPUT_DIR}/${_lib_base_name})
    set(QEXTQUICK_PLUGIN_TYPEINFO_PATH ${QEXTQUICK_TYPEINFO_GENERATE_DIR}/plugin.qmltypes)
    set(QEXTQUICK_GENERATE_QMLTYPES_COMMAND
        ${QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE}
        -nonrelocatable
        ${_lib_base_name}
        ${QEXTQUICK_MODULE_VERSION}
        ${QEXT_QML_OUTPUT_DIR}
        >
        ${QEXT_QML_OUTPUT_DIR}/${_lib_base_name}/plugin.qmltypes
        )
    add_custom_command(
        TARGET ${_lib_base_name}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QEXTQUICK_TYPEINFO_GENERATE_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/qmldir ${QEXTQUICK_TYPEINFO_GENERATE_DIR}
        COMMAND ${QEXTQUICK_GENERATE_QMLTYPES_COMMAND}
        COMMENT "Generating qextquick.qmltypes with qmlplugindump"
        POST_BUILD
        )
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
