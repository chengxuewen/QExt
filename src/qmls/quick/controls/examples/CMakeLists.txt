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
# Set example link libraries
#-----------------------------------------------------------------------------------------------------------------------
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

if(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES QExt::QuickControls)


#-----------------------------------------------------------------------------------------------------------------------
# Add example
#-----------------------------------------------------------------------------------------------------------------------
qext_add_executable(QExtExpQuickControlSimple
    SOURCES
    simple/simple.qrc
    simple/main.cpp
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/simple
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_EXAMPLESDIR}
    DEFINES
    QML_MODULES_DIR="${QEXT_BUILD_DIR}/${QEXT_INSTALL_QMLDIR}")
qext_add_executable(QExtExpQuickControlComponent
    SOURCES
    component/component.qrc
    component/main.cpp
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/component
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_EXAMPLESDIR}
    DEFINES
    QML_MODULES_DIR="${QEXT_BUILD_DIR}/${QEXT_INSTALL_QMLDIR}")
qext_add_executable(QExtExpQuickControlPaletteView
    SOURCES
    paletteview/paletteview.qrc
    paletteview/qextquickpalettetablemodel.h
    paletteview/qextquickpalettetablemodel.cpp
    paletteview/main.cpp
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/paletteview
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_EXAMPLESDIR}
    DEFINES
    QML_MODULES_DIR="${QEXT_BUILD_DIR}/${QEXT_INSTALL_QMLDIR}")
