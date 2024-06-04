########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2024~Present ChengXueWen. Contact: 1398831004@qq.com.
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
# Set app link libraries
#-----------------------------------------------------------------------------------------------------------------------
if(WIN32)
    list(APPEND QEXT_APP_LINK_LIBRARIES shlwapi.lib)
endif()
if(UNIX)
    list(APPEND QEXT_APP_LINK_LIBRARIES ${CMAKE_DL_LIBS})
endif()
if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND QEXT_APP_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_APP_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Qml
        Qt${QEXT_QT_VERSION_MAJOR}::Quick)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

# qt_get_tool_target_name(target_name cmake_automoc_parser)
# qt_internal_add_tool(${target_name}
#     CORE_LIBRARY Bootstrap
#     INSTALL_DIR "${INSTALL_LIBEXECDIR}"
#     TOOLS_TARGET Core # special case
#     SOURCES
#     main.cpp
#     DEFINES
#     QT_MOC
#     QT_NO_CAST_FROM_ASCII
#     QT_NO_CAST_FROM_BYTEARRAY
#     QT_NO_FOREACH
#     INCLUDE_DIRECTORIES
#     ${CMAKE_CURRENT_SOURCE_DIR}
# )
# qt_internal_return_unless_building_tools()


#-----------------------------------------------------------------------------------------------------------------------
# Add app target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_executable(automocparser
    SOURCES
    main.cpp
    DEFINES
    QT_MOC
    QT_NO_CAST_FROM_ASCII
    QT_NO_CAST_FROM_BYTEARRAY
    QT_NO_FOREACH
    OUTPUT_SUBDIR
    automocparser
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}>
    LIBRARIES
    ${QEXT_APP_LINK_LIBRARIES})
