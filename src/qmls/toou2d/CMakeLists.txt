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
set(QEXT_QML_LINK_LIBRARIES)

if (QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_QML_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Qml
        Qt${QEXT_QT_VERSION_MAJOR}::Quick
        Qt${QEXT_QT_VERSION_MAJOR}::QuickControls2)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_QML_LINK_LIBRARIES QExt::Core)

qext_find_qt_tool(moc)
set(QEXT_QT_MOC_EXECUTABLE "${moc_EXECUTABLE}" CACHE INTERNAL "" FORCE)
qext_find_qt_tool(rcc)
set(QEXT_QT_RCC_EXECUTABLE "${rcc_EXECUTABLE}" CACHE INTERNAL "" FORCE)
# message(QEXT_QT_RCC_EXECUTABLE=${QEXT_QT_RCC_EXECUTABLE})
qext_find_qt_tool(qmlplugindump)
set(QEXT_QT_QMLPLUGINDUMP_EXECUTABLE "${qmlplugindump_EXECUTABLE}" CACHE INTERNAL "" FORCE)
# message(QEXT_QT_QMLPLUGINDUMP_EXECUTABLE=${QEXT_QT_QMLPLUGINDUMP_EXECUTABLE})
#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qt_internal_add_qml_module(Toou2D
    URI "Toou2D"
    VERSION "1.0"
    CLASS_NAME Toou2DQmlPlugin
    PLUGIN_TARGET Toou2dPlugin
    PLUGIN_SOURCES
    src-toou2d/qml_plugin.cpp
    src-toou2d/qml_plugin.h
    SOURCES
    src-toou2d/controls/gadget/tcolor.cpp
    src-toou2d/controls/gadget/tcolor.h
    src-toou2d/controls/gadget/tgadgetbackground.cpp
    src-toou2d/controls/gadget/tgadgetbackground.h
    src-toou2d/controls/gadget/tgadgetborder.cpp
    src-toou2d/controls/gadget/tgadgetborder.h
    src-toou2d/controls/gadget/tgadgeticon.cpp
    src-toou2d/controls/gadget/tgadgeticon.h
    src-toou2d/controls/gadget/tgadgetitem.cpp
    src-toou2d/controls/gadget/tgadgetitem.h
    src-toou2d/controls/gadget/tgadgetlabel.cpp
    src-toou2d/controls/gadget/tgadgetlabel.h
    src-toou2d/controls/gadget/tgadgetscrollbar.cpp
    src-toou2d/controls/gadget/tgadgetscrollbar.h
    src-toou2d/controls/interface/tdialogitem.cpp
    src-toou2d/controls/interface/tdialogitem.h
    src-toou2d/controls/interface/ttoastitem.cpp
    src-toou2d/controls/interface/ttoastitem.h
    src-toou2d/theme/ThemeManager.cpp
    src-toou2d/theme/ThemeManager.h
    src-toou2d/theme/theme_binder.cpp
    src-toou2d/theme/theme_binder.h
    src-toou2d/theme/theme_handler.cpp
    src-toou2d/theme/theme_handler.h
    src-toou2d/Toou2D.h
    src-toou2d/def.cpp
    src-toou2d/def.h
    src-toou2d/t2d.cpp
    src-toou2d/t2d.h
    src-toou2d/toou2d.cpp
    src-toou2d/world.cpp
    src-toou2d/world.h
    src-toou2d/t2d_res.qrc
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/src-toou2d
    DEFINES
    QEXT_BUILD_TOOU2D_LIB
    VERSION_IN="1.0"
    URI_STR="Toou2D"
    PUBLIC_LIBRARIES
    ${QEXT_QML_LINK_LIBRARIES})


#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
