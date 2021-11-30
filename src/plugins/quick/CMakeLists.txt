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
set(qext_plugin_base_name QEXTQuickPlugin)
set(LIBRARY_OUTPUT_PATH ${QEXT_QML_OUTPUT_DIR}/${qext_plugin_base_name})



#--------------------------------------------------------------------------------
# Set lib qmltype and cfg
#--------------------------------------------------------------------------------
set(QEXTQUICK_GENERATE_QMLTYPE_FILE OFF)
set(QEXTQUICK_USE_KIT_QMLPLUGINDUMP OFF)



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(qext_plugin_public_headers
    ${PROJECT_SOURCE_DIR}/src/libs/quick/include/qextQuick.h
    ${PROJECT_SOURCE_DIR}/src/libs/quick/include/qextQuickFramelessHelper.h
    ${PROJECT_SOURCE_DIR}/src/libs/quick/include/qextQuickPch.h
    ${PROJECT_SOURCE_DIR}/src/libs/quick/include/qextQuickGlobal.h
    ${PROJECT_SOURCE_DIR}/src/libs/quick/include/qextQuickWidgetProxyItem.h
    ${PROJECT_SOURCE_DIR}/src/libs/quick/include/qextQuickWorld.h
    include/qextQuickPlugin.h
    )

set(qext_plugin_private_headers
    ${PROJECT_SOURCE_DIR}/src/libs/quick/private/qextQuick_p.h
    ${PROJECT_SOURCE_DIR}/src/libs/quick/private/qextQuickFramelessHelper_p.h
    ${PROJECT_SOURCE_DIR}/src/libs/quick/private/qextQuickWorld_p.h
    )

set(qext_plugin_sources
    ${PROJECT_SOURCE_DIR}/src/libs/quick/source/qextQuick.cpp
    ${PROJECT_SOURCE_DIR}/src/libs/quick/source/qextQuickFramelessHelper.cpp
    ${PROJECT_SOURCE_DIR}/src/libs/quick/source/qextQuickWidgetProxyItem.cpp
    ${PROJECT_SOURCE_DIR}/src/libs/quick/source/qextQuickWorld.cpp
    source/qextQuickPlugin.cpp
    )

set(qext_plugin_resources
    ${PROJECT_SOURCE_DIR}/src/libs/quick/resource/QEXTQuick.qrc
    )



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(qext_plugin_link_libraries)

if(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND qext_plugin_link_libraries
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets
        Qt${QEXT_QT_VERSION_MAJOR}::Qml
        Qt${QEXT_QT_VERSION_MAJOR}::Quick
        )
    list(APPEND qext_plugin_include_directories
        ${Qt${QEXT_QT_VERSION_MAJOR}Gui_PRIVATE_INCLUDE_DIRS}
        ${Qt${QEXT_QT_VERSION_MAJOR}Widgets_PRIVATE_INCLUDE_DIRS}
        )
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND qext_plugin_link_libraries QEXTCore QEXTFramelessHelper)



#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
add_library(${qext_plugin_base_name}
    ${qext_plugin_public_headers}
    ${qext_plugin_private_headers}
    ${qext_plugin_sources}
    ${qext_plugin_resources}
    )
if (QEXT_BUILD_COMPILER_WARNING)
    qextFunctionSetCompilerWarnings(${qext_plugin_base_name})
endif()
if (QEXT_BUILD_USE_PCH)
    qextFunctionActivatePrecompiledHeaders(${qext_plugin_base_name} PRIVATE ${PROJECT_SOURCE_DIR}/src/libs/quick/include/qextQuickPch.h)
endif()
target_link_libraries(${qext_plugin_base_name} PUBLIC ${qext_plugin_link_libraries})
target_include_directories(${qext_plugin_base_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/libs/quick/include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/libs/quick/private>
    $<BUILD_INTERFACE:${qext_lib_include_directories}>
    $<INSTALL_INTERFACE:include>
    )
target_compile_definitions(${qext_plugin_base_name} PRIVATE QEXT_BUILD_QUICK_LIB)
target_compile_definitions(${qext_plugin_base_name} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

# set target properties
set_target_properties(${qext_plugin_base_name} PROPERTIES
    VERSION ${QEXT_VERSION} SOVERSION ${QEXT_SO_VERSION}
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    DEBUG_POSTFIX ${QEXT_DEBUG_POSTFIX}
    )
if (QEXT_BUILD_SHARED_LIBS)
    set_target_properties(${qext_plugin_base_name} PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1)
endif()

# qmlplugindump -nonrelocatable QEXTQuick 1.2 ${QEXT_QML_OUTPUT_DIR} > ${QEXT_QML_OUTPUT_DIR}/QEXTQuick/plugin.qmltypes
if(QEXTQUICK_GENERATE_QMLTYPE_FILE AND QEXT_BUILD_SHARED_LIBS)
    message(STATUS "----QEXT---- Enable create qml plugin ${qext_plugin_base_name} plugin.qmltypes")
    if(QEXTQUICK_USE_KIT_QMLPLUGINDUMP)
        qextMacroFindQmlPluginDump()
        set(QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE ${QEXT_QT_QMLPLUGINDUMP_EXECUTABLE})
    else()
        add_dependencies(${qext_plugin_base_name} qmlplugindump)
        set(QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE ${QEXT_APP_OUTPUT_DIR}/qmlplugindump)
        if (WIN32)
            set(QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE ${QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE}.exe)
        endif()
    endif()
    set(QEXTQUICK_MODULE_VERSION ${QEXTQUICK_VERSION_MAJOR}.${QEXTQUICK_VERSION_MINOR})
    set(QEXTQUICK_TYPEINFO_GENERATE_DIR ${QEXT_QML_OUTPUT_DIR}/${qext_plugin_base_name})
    set(QEXTQUICK_PLUGIN_TYPEINFO_PATH ${QEXTQUICK_TYPEINFO_GENERATE_DIR}/plugin.qmltypes)
    set(QEXTQUICK_GENERATE_QMLTYPES_COMMAND
        ${QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE}
        -nonrelocatable
        ${qext_plugin_base_name}
        ${QEXTQUICK_MODULE_VERSION}
        ${QEXT_QML_OUTPUT_DIR}
        >
        ${QEXT_QML_OUTPUT_DIR}/${qext_plugin_base_name}/plugin.qmltypes
        )
    add_custom_command(
        TARGET ${qext_plugin_base_name}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${QEXTQUICK_TYPEINFO_GENERATE_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:QEXTCore> ${QEXTQUICK_TYPEINFO_GENERATE_DIR}
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
    #    add_subdirectory(tests)
endif()

if (QEXT_BUILD_EXAMPLES OR QEXT_BUILD_ALL)
    add_subdirectory(examples)
endif()
