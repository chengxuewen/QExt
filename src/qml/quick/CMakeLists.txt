#################################################################################
#
# Library: QEXT
#
# Copyright (c) ChengXueWen. Contact: 1398831004@qq.com
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#################################################################################

#--------------------------------------------------------------------------------
# Set lib base name and out put path
#--------------------------------------------------------------------------------
set(QEXT_QML_PLUGIN_BASE_NAME QEXTQuick)
set(LIBRARY_OUTPUT_PATH ${QEXT_QML_OUTPUT_DIR}/${QEXT_QML_PLUGIN_BASE_NAME})



#--------------------------------------------------------------------------------
# Set lib qmltype and cfg
#--------------------------------------------------------------------------------
set(QEXT_QML_PLUGIN_GENERATE_QMLTYPE_FILE ON)
set(QEXT_QML_PLUGIN_NAME ${QEXT_QML_PLUGIN_BASE_NAME})
set(QEXT_QML_PLUGIN_VERSION_MAJOR 1)
set(QEXT_QML_PLUGIN_VERSION_MINOR 0)
if (QEXT_BUILDIN_QMLPLUGINDUMP)
    set(QEXT_QML_PLUGIN_USE_KIT_QMLPLUGINDUMP OFF)
else()
    set(QEXT_QML_PLUGIN_USE_KIT_QMLPLUGINDUMP ON)
endif()



#--------------------------------------------------------------------------------
# Configure a header file to pass some of the CMake settings to the source code
#--------------------------------------------------------------------------------
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/qextQuickConfig.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/qextQuickConfig.h"
    )



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(QEXT_QML_PLUGIN_PUBLIC_HEADERS
    ${CMAKE_CURRENT_BINARY_DIR}/qextQuickConfig.h

    include/gadget/qextQuickBackgroundGadget.h
    include/gadget/qextQuickBorderGadget.h
    include/gadget/qextQuickIconGadget.h
    include/gadget/qextQuickItemGadget.h
    include/gadget/qextQuickTextGadget.h

    include/qextQuickFontAwesome.h
    include/qextQuick.h
    include/qextQuickLoader.h
    include/qextQuickPalette.h
    include/qextQuickPlugin.h
    include/qextQuickWorld.h
    include/qextQuickPch.h
    include/qextQuickGlobal.h
    include/qextQuickWidgetProxyItem.h
    )

set(QEXT_QML_PLUGIN_PRIVATE_HEADERS
    private/gadget/qextQuickBackgroundGadget_p.h
    private/gadget/qextQuickBorderGadget_p.h
    private/gadget/qextQuickIconGadget_p.h
    private/gadget/qextQuickItemGadget_p.h
    private/gadget/qextQuickTextGadget_p.h

    private/qextQuick_p.h
    private/qextQuickWorld_p.h
    private/qextQuickPalette_p.h
    )

set(QEXT_QML_PLUGIN_SOURCES
    source/gadget/qextQuickBackgroundGadget.cpp
    source/gadget/qextQuickBorderGadget.cpp
    source/gadget/qextQuickIconGadget.cpp
    source/gadget/qextQuickItemGadget.cpp
    source/gadget/qextQuickTextGadget.cpp

    source/qextQuickFontAwesome.cpp
    source/qextQuick.cpp
    source/qextQuickLoader.cpp
    source/qextQuickPalette.cpp
    source/qextQuickPlugin.cpp
    source/qextQuickWorld.cpp
    source/qextQuickWidgetProxyItem.cpp
    )

set(QEXT_QML_PLUGIN_RESOURCES
    resource/QEXTQuick.qrc
    )



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(QEXT_QML_PLUGIN_LINK_LIBRARIES)

if(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_QML_PLUGIN_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets
        Qt${QEXT_QT_VERSION_MAJOR}::Qml
        Qt${QEXT_QT_VERSION_MAJOR}::Quick
        )
    list(APPEND QEXT_QML_PLUGIN_INCLUDE_DIRECTORIES
        ${Qt${QEXT_QT_VERSION_MAJOR}Gui_PRIVATE_INCLUDE_DIRS}
        ${Qt${QEXT_QT_VERSION_MAJOR}Widgets_PRIVATE_INCLUDE_DIRS}
        )
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND QEXT_QML_PLUGIN_LINK_LIBRARIES QEXTCore)



#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
add_library(${QEXT_QML_PLUGIN_BASE_NAME}
    ${QEXT_QML_PLUGIN_PUBLIC_HEADERS}
    ${QEXT_QML_PLUGIN_PRIVATE_HEADERS}
    ${QEXT_QML_PLUGIN_SOURCES}
    ${QEXT_QML_PLUGIN_RESOURCES}
    )
if (QEXT_BUILD_COMPILER_WARNING)
    qextFunctionSetCompilerWarnings(${QEXT_QML_PLUGIN_BASE_NAME})
endif()
if (QEXT_BUILD_USE_PCH)
    qextFunctionActivatePrecompiledHeaders(${QEXT_QML_PLUGIN_BASE_NAME} PRIVATE include/qextQuickPch.h)
endif()
target_link_libraries(${QEXT_QML_PLUGIN_BASE_NAME} PUBLIC ${QEXT_QML_PLUGIN_LINK_LIBRARIES})
target_include_directories(${QEXT_QML_PLUGIN_BASE_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/gadget>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/theme>
    $<INSTALL_INTERFACE:include/${QEXT_LIB_BASE_NAME}>
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/gadget>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/theme>
    $<INSTALL_INTERFACE:include/${QEXT_LIB_BASE_NAME}/private>
    )
target_compile_definitions(${QEXT_QML_PLUGIN_BASE_NAME} PRIVATE QEXT_BUILD_QUICK_LIB)
target_compile_definitions(${QEXT_QML_PLUGIN_BASE_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

# set target properties
set_target_properties(${QEXT_QML_PLUGIN_BASE_NAME} PROPERTIES
    VERSION ${QEXT_VERSION} SOVERSION ${QEXT_SO_VERSION}
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    )
if (QEXT_BUILD_SHARED_LIBS)
    set_target_properties(${QEXT_QML_PLUGIN_BASE_NAME} PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1)
endif()

# set include files copy command
foreach(HEADER ${QEXT_QML_PLUGIN_PUBLIC_HEADERS})
    get_filename_component(HEADER_ABSOLUTE_PATH ${HEADER} ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})
    list(APPEND QEXT_QML_PLUGIN_PUBLIC_ABSOLUTE_HEADERS ${HEADER_ABSOLUTE_PATH})
endforeach()
foreach(HEADER ${QEXT_QML_PLUGIN_PRIVATE_HEADERS})
    get_filename_component(HEADER_ABSOLUTE_PATH ${HEADER} ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})
    list(APPEND QEXT_QML_PLUGIN_PRIVATE_ABSOLUTE_HEADERS ${HEADER_ABSOLUTE_PATH})
endforeach()
add_custom_command(
    TARGET ${QEXT_QML_PLUGIN_BASE_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${QEXT_INCLUDE_OUTPUT_DIR}/${QEXT_QML_PLUGIN_BASE_NAME}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${QEXT_INCLUDE_OUTPUT_DIR}/${QEXT_QML_PLUGIN_BASE_NAME}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${QEXT_INCLUDE_OUTPUT_DIR}/${QEXT_QML_PLUGIN_BASE_NAME}/private
    COMMAND ${CMAKE_COMMAND} -E copy ${QEXT_QML_PLUGIN_PUBLIC_ABSOLUTE_HEADERS} ${QEXT_INCLUDE_OUTPUT_DIR}/${QEXT_QML_PLUGIN_BASE_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy ${QEXT_QML_PLUGIN_PRIVATE_ABSOLUTE_HEADERS} ${QEXT_INCLUDE_OUTPUT_DIR}/${QEXT_QML_PLUGIN_BASE_NAME}/private
    COMMENT "Copy ${QEXT_QML_PLUGIN_BASE_NAME} include files to output dir"
    POST_BUILD
    )

# qmlplugindump -nonrelocatable QEXTQuick 1.2 ${QEXT_QML_OUTPUT_DIR} > ${QEXT_QML_OUTPUT_DIR}/QEXTQuick/plugin.qmltypes
if(QEXT_QML_PLUGIN_GENERATE_QMLTYPE_FILE AND QEXT_BUILD_SHARED_LIBS)
    message(STATUS "----QEXT---- Enable create qml plugin ${QEXT_QML_PLUGIN_BASE_NAME} plugin.qmltypes")
    if(QEXT_QML_PLUGIN_USE_KIT_QMLPLUGINDUMP)
        qextMacroFindQmlPluginDump()
        set(QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE ${QEXT_QT_QMLPLUGINDUMP_EXECUTABLE})
    else()
        add_dependencies(${QEXT_QML_PLUGIN_BASE_NAME} qmlplugindump)
        set(QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE ${QEXT_APP_OUTPUT_DIR}/qmlplugindump)
        if (WIN32)
            set(QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE ${QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE}.exe)
        endif()
    endif()
    set(QEXTQUICK_MODULE_VERSION ${QEXT_QML_PLUGIN_VERSION_MAJOR}.${QEXT_QML_PLUGIN_VERSION_MINOR})
    set(QEXTQUICK_TYPEINFO_GENERATE_DIR ${QEXT_QML_OUTPUT_DIR}/${QEXT_QML_PLUGIN_BASE_NAME})
    set(QEXTQUICK_PLUGIN_TYPEINFO_PATH ${QEXTQUICK_TYPEINFO_GENERATE_DIR}/plugin.qmltypes)
    set(QEXTQUICK_GENERATE_QMLTYPES_COMMAND
        ${QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE}
        -nonrelocatable
        ${QEXT_QML_PLUGIN_BASE_NAME}
        ${QEXTQUICK_MODULE_VERSION}
        ${QEXT_QML_OUTPUT_DIR}
        >
        ${QEXT_QML_OUTPUT_DIR}/${QEXT_QML_PLUGIN_BASE_NAME}/plugin.qmltypes
        )
    add_custom_command(
        TARGET ${QEXT_QML_PLUGIN_BASE_NAME}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QEXTQUICK_TYPEINFO_GENERATE_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_LINKER_FILE:QEXTCore>* ${QEXTQUICK_TYPEINFO_GENERATE_DIR}
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
