########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2021~Present ChengXueWen. Contact: 1398831004@qq.com.
#
# License: MIT License
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
# to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions
# of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE  AUTHORS
# OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
########################################################################################################################


#-----------------------------------------------------------------------------------------------------------------------
# Add lib link libraries
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_LIB_LINK_LIBRARIES)

if (QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets
        Qt${QEXT_QT_VERSION_MAJOR}::Qml
        Qt${QEXT_QT_VERSION_MAJOR}::Quick
        Qt${QEXT_QT_VERSION_MAJOR}::QuickControls2
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Core)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QExt::Core)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_qml(Quick
    URI "QExtQuick"
    CLASS_NAME QExtQuickPlugin
    PLUGIN_TARGET QExtQuick
    PAST_MAJOR_VERSIONS 1 2
    DESIGNER_SUPPORTED
    DEPENDENCIES
    QtQuick
    SOURCES
    source/qextQuick.cpp
    source/qextQuick_p.h
    source/qextQuick.h
    source/qextQuickBackgroundGadget.cpp
    source/qextQuickBackgroundGadget_p.h
    source/qextQuickBackgroundGadget.h
    source/qextQuickBorderGadget.cpp
    source/qextQuickBorderGadget_p.h
    source/qextQuickBorderGadget.h
    source/qextQuickFontAwesome.cpp
    source/qextQuickFontAwesome.h
    source/qextQuickGlobal.h
    source/qextQuickIconGadget.cpp
    source/qextQuickIconGadget_p.h
    source/qextQuickIconGadget.h
    source/qextQuickItemGadget.cpp
    source/qextQuickItemGadget_p.h
    source/qextQuickItemGadget.h
    source/qextQuickLoader.cpp
    source/qextQuickLoader.h
    source/qextQuickPalette.cpp
    source/qextQuickPalette_p.h
    source/qextQuickPalette.h
    source/qextQuickPlugin.cpp
    source/qextQuickPlugin.h
    source/qextQuickTextGadget.cpp
    source/qextQuickTextGadget_p.h
    source/qextQuickTextGadget.h
    source/qextQuickWorld.cpp
    source/qextQuickWorld_p.h
    source/qextQuickWorld.h
    resource/qextQuick.qrc
    PRECOMPILED_HEADER
    source/qextQuickPch.h
    DEFINES
    QEXT_BUILD_QUICK_LIB
    PUBLIC_LIBRARIES
    ${QEXT_LIB_LINK_LIBRARIES})


#-----------------------------------------------------------------------------------------------------------------------
# Add lib tests and examples
#-----------------------------------------------------------------------------------------------------------------------
if (QEXT_BUILD_TESTS)
    add_subdirectory(tests)
endif ()

if (QEXT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()


# #-----------------------------------------------------------------------------------------------------------------------
# # Set lib base name and out put path
# #-----------------------------------------------------------------------------------------------------------------------
# set(QEXT_QML_PLUGIN_BASE_NAME QExtQuick)
# set(LIBRARY_OUTPUT_PATH ${QEXT_OUTPUT_QML_DIR}/${QEXT_QML_PLUGIN_BASE_NAME})



# #-----------------------------------------------------------------------------------------------------------------------
# # Set lib qmltype and cfg
# #-----------------------------------------------------------------------------------------------------------------------
# set(QEXT_QML_PLUGIN_GENERATE_QMLTYPE_FILE ON)
# set(QEXT_QML_PLUGIN_NAME ${QEXT_QML_PLUGIN_BASE_NAME})
# set(QEXT_QML_PLUGIN_VERSION_MAJOR 1)
# set(QEXT_QML_PLUGIN_VERSION_MINOR 0)
# if (QEXT_BUILDIN_QMLPLUGINDUMP)
#     set(QEXT_QML_PLUGIN_USE_KIT_QMLPLUGINDUMP OFF)
# else()
#     set(QEXT_QML_PLUGIN_USE_KIT_QMLPLUGINDUMP ON)
# endif()



# #-----------------------------------------------------------------------------------------------------------------------
# # Configure a header file to pass some of the CMake settings to the source code
# #-----------------------------------------------------------------------------------------------------------------------
# configure_file(
#     "${CMAKE_CURRENT_SOURCE_DIR}/qextQmlQuickConfig.h.in"
#     "${CMAKE_CURRENT_BINARY_DIR}/qextQmlQuickConfig.h"
# )



# #-----------------------------------------------------------------------------------------------------------------------
# # Set lib file list
# #-----------------------------------------------------------------------------------------------------------------------
# set(QEXT_QML_PLUGIN_PUBLIC_HEADERS
#     ${CMAKE_CURRENT_BINARY_DIR}/qextQmlQuickConfig.h

#     include/gadget/qextQmlQuickBackgroundGadget.h
#     include/gadget/qextQmlQuickBorderGadget.h
#     include/gadget/qextQmlQuickIconGadget.h
#     include/gadget/qextQmlQuickItemGadget.h
#     include/gadget/qextQmlQuickTextGadget.h

#     include/qextQmlQuickFontAwesome.h
#     include/qextQmlQuick.h
#     include/qextQmlQuickLoader.h
#     include/qextQmlQuickPalette.h
#     include/qextQmlQuickPlugin.h
#     include/qextQmlQuickWorld.h
#     include/qextQmlQuickPch.h
#     include/qextQmlQuickGlobal.h
# )

# set(QEXT_QML_PLUGIN_PRIVATE_HEADERS
#     private/gadget/qextQmlQuickBackgroundGadget_p.h
#     private/gadget/qextQmlQuickBorderGadget_p.h
#     private/gadget/qextQmlQuickIconGadget_p.h
#     private/gadget/qextQmlQuickItemGadget_p.h
#     private/gadget/qextQmlQuickTextGadget_p.h

#     private/qextQmlQuick_p.h
#     private/qextQmlQuickWorld_p.h
#     private/qextQmlQuickPalette_p.h
# )

# set(QEXT_QML_PLUGIN_SOURCES
#     source/gadget/qextQmlQuickBackgroundGadget.cpp
#     source/gadget/qextQmlQuickBorderGadget.cpp
#     source/gadget/qextQmlQuickIconGadget.cpp
#     source/gadget/qextQmlQuickItemGadget.cpp
#     source/gadget/qextQmlQuickTextGadget.cpp

#     source/qextQmlQuickFontAwesome.cpp
#     source/qextQmlQuick.cpp
#     source/qextQmlQuickLoader.cpp
#     source/qextQmlQuickPalette.cpp
#     source/qextQmlQuickPlugin.cpp
#     source/qextQmlQuickWorld.cpp
# )

# set(QEXT_QML_PLUGIN_RESOURCES
#     resource/QExtQuick.qrc
# )







# #-----------------------------------------------------------------------------------------------------------------------
# # Add lib target
# #-----------------------------------------------------------------------------------------------------------------------
# add_library(${QEXT_QML_PLUGIN_BASE_NAME}
#     ${QEXT_QML_PLUGIN_PUBLIC_HEADERS}
#     ${QEXT_QML_PLUGIN_PRIVATE_HEADERS}
#     ${QEXT_QML_PLUGIN_SOURCES}
#     ${QEXT_QML_PLUGIN_RESOURCES}
# )
# if (QEXT_BUILD_COMPILER_WARNING)
#     qextFunctionSetCompilerWarnings(${QEXT_QML_PLUGIN_BASE_NAME})
# endif()
# if (QEXT_BUILD_USE_PCH)
#     qextFunctionActivatePrecompiledHeaders(${QEXT_QML_PLUGIN_BASE_NAME} PRIVATE include/qextQmlQuickPch.h)
# endif()
# target_link_libraries(${QEXT_QML_PLUGIN_BASE_NAME} PUBLIC ${QEXT_QML_PLUGIN_LINK_LIBRARIES})
# target_include_directories(${QEXT_QML_PLUGIN_BASE_NAME}
#     PUBLIC
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/gadget>
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/theme>
#     $<INSTALL_INTERFACE:include/${QEXT_LIB_BASE_NAME}>
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/gadget>
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/theme>
#     $<INSTALL_INTERFACE:include/${QEXT_LIB_BASE_NAME}/private>
# )
# target_compile_definitions(${QEXT_QML_PLUGIN_BASE_NAME} PRIVATE QEXT_BUILD_QUICK_LIB)
# target_compile_definitions(${QEXT_QML_PLUGIN_BASE_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

# # set target properties
# set_target_properties(${QEXT_QML_PLUGIN_BASE_NAME} PROPERTIES
#     CXX_STANDARD ${QEXT_CXX_STANDARD}
#     OUTPUT_NAME ${QEXT_QML_PLUGIN_BASE_NAME}
# )
# if(WIN32)
#     set_target_properties(${QEXT_QML_PLUGIN_BASE_NAME} PROPERTIES
#         PREFIX ""
#     )
# endif()
# if (QEXT_BUILD_SHARED_LIBS)
#     set_target_properties(${QEXT_QML_PLUGIN_BASE_NAME} PROPERTIES
#         CXX_VISIBILITY_PRESET hidden
#         VISIBILITY_INLINES_HIDDEN 1
#     )
# endif()

# # set include files copy command
# foreach(HEADER ${QEXT_QML_PLUGIN_PUBLIC_HEADERS})
#     get_filename_component(HEADER_ABSOLUTE_PATH ${HEADER} ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})
#     list(APPEND QEXT_QML_PLUGIN_PUBLIC_ABSOLUTE_HEADERS ${HEADER_ABSOLUTE_PATH})
# endforeach()
# foreach(HEADER ${QEXT_QML_PLUGIN_PRIVATE_HEADERS})
#     get_filename_component(HEADER_ABSOLUTE_PATH ${HEADER} ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})
#     list(APPEND QEXT_QML_PLUGIN_PRIVATE_ABSOLUTE_HEADERS ${HEADER_ABSOLUTE_PATH})
# endforeach()
# add_custom_command(
#     TARGET ${QEXT_QML_PLUGIN_BASE_NAME}
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${QEXT_OUTPUT_INCLUDE_DIR}/${QEXT_QML_PLUGIN_BASE_NAME}
#     COMMAND ${CMAKE_COMMAND} -E make_directory ${QEXT_OUTPUT_INCLUDE_DIR}/${QEXT_QML_PLUGIN_BASE_NAME}
#     COMMAND ${CMAKE_COMMAND} -E make_directory ${QEXT_OUTPUT_INCLUDE_DIR}/${QEXT_QML_PLUGIN_BASE_NAME}/private
#     COMMAND ${CMAKE_COMMAND} -E copy ${QEXT_QML_PLUGIN_PUBLIC_ABSOLUTE_HEADERS} ${QEXT_OUTPUT_INCLUDE_DIR}/${QEXT_QML_PLUGIN_BASE_NAME}
#     COMMAND ${CMAKE_COMMAND} -E copy ${QEXT_QML_PLUGIN_PRIVATE_ABSOLUTE_HEADERS} ${QEXT_OUTPUT_INCLUDE_DIR}/${QEXT_QML_PLUGIN_BASE_NAME}/private
#     COMMENT "Copy ${QEXT_QML_PLUGIN_BASE_NAME} include files to output dir"
#     POST_BUILD)

# # qmlplugindump -nonrelocatable QExtQuick 1.2 ${QEXT_OUTPUT_QML_DIR} > ${QEXT_OUTPUT_QML_DIR}/QExtQuick/plugin.qmltypes
# if(QEXT_QML_PLUGIN_GENERATE_QMLTYPE_FILE AND QEXT_BUILD_SHARED_LIBS)
#     message(STATUS "Enable create qml plugin ${QEXT_QML_PLUGIN_BASE_NAME} plugin.qmltypes")
#     if(QEXT_QML_PLUGIN_USE_KIT_QMLPLUGINDUMP)
#         qextMacroFindQmlPluginDump()
#         set(QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE ${QEXT_QT_QMLPLUGINDUMP_EXECUTABLE})
#     else()
#         add_dependencies(${QEXT_QML_PLUGIN_BASE_NAME} qext_tool_qmlplugindump)
#         set(QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE ${QEXT_OUTPUT_APP_DIR}/qmlplugindump/qext_tool_qmlplugindump)
#         if (WIN32)
#             set(QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE ${QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE}.exe)
#         endif()
#     endif()
#     set(QEXTQUICK_MODULE_VERSION ${QEXT_QML_PLUGIN_VERSION_MAJOR}.${QEXT_QML_PLUGIN_VERSION_MINOR})
#     set(QEXTQUICK_TYPEINFO_GENERATE_DIR ${QEXT_OUTPUT_QML_DIR}/${QEXT_QML_PLUGIN_BASE_NAME})
#     set(QEXTQUICK_PLUGIN_TYPEINFO_PATH ${QEXTQUICK_TYPEINFO_GENERATE_DIR}/plugin.qmltypes)
#     set(QEXT_QML_GENERATE_QMLTYPES_COMMAND
#         ${QEXTQUICK_QMLPLUGINDUMP_EXECUTABLE}
#         -nonrelocatable
#         ${QEXT_QML_PLUGIN_BASE_NAME}
#         ${QEXTQUICK_MODULE_VERSION}
#         ${QEXT_OUTPUT_QML_DIR}
#         >
#         ${QEXT_OUTPUT_QML_DIR}/${QEXT_QML_PLUGIN_BASE_NAME}/plugin.qmltypes
#     )
# qextFunctionCopyDependencyInternal(
#     TARGET ${QEXT_QML_PLUGIN_BASE_NAME}
#     LIBS QExtCore
#     DESTINATION ${QEXT_OUTPUT_APP_DIR}
#     POST_BUILD
# )
# add_custom_command(
#     TARGET ${QEXT_QML_PLUGIN_BASE_NAME}
#     COMMAND ${CMAKE_COMMAND} -E make_directory ${QEXTQUICK_TYPEINFO_GENERATE_DIR}
#     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/qmldir ${QEXTQUICK_TYPEINFO_GENERATE_DIR}
#     COMMAND ${QEXT_QML_GENERATE_QMLTYPES_COMMAND}
#     COMMENT "Generating ${QEXT_QML_PLUGIN_BASE_NAME} quick.qmltypes with qmlplugindump."
#     POST_BUILD
# )
# endif()
