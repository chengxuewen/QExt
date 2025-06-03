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

list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES QExt::Toou2D)


#-----------------------------------------------------------------------------------------------------------------------
# Add example
#-----------------------------------------------------------------------------------------------------------------------
qext_add_executable(QExtExpToou2DGallery
    SOURCES
    gallery/qml.qrc
    gallery/main.cpp
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/gallery
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_BUILD_DIR}/${QEXT_INSTALL_EXAMPLESDIR}
    DEFINES
    QT_QML_MODULES_PATH="${QEXT_QT_KIT_DIR}/qml"
    QML_MODULES_DIR="${QEXT_BUILD_DIR}/${QEXT_INSTALL_QMLDIR}")
if(QEXT_BUILD_STATIC)
    qext_internal_extend_target(QExtExpToou2DGallery DEFINES STATICLIB)
endif()
qext_add_executable(QExtExpToou2DMusicPlayer
    SOURCES
    MusicPlayer/qml.qrc
    MusicPlayer/main.cpp
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/MusicPlayer
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_BUILD_DIR}/${QEXT_INSTALL_EXAMPLESDIR}
    DEFINES
    QT_QML_MODULES_PATH="${QEXT_QT_KIT_DIR}/qml"
    QML_MODULES_DIR="${QEXT_BUILD_DIR}/${QEXT_INSTALL_QMLDIR}")
