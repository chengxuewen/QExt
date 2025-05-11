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
        Qt${QEXT_QT_VERSION_MAJOR}::Svg
        Qt${QEXT_QT_VERSION_MAJOR}::OpenGL
        Qt${QEXT_QT_VERSION_MAJOR}::Quick)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_QML_LINK_LIBRARIES QExt::Qml)
qext_find_package(WrapQwt PROVIDED_TARGETS QExt3rdparty::WrapQwt)
list(APPEND QEXT_QML_LINK_LIBRARIES QExt3rdparty::WrapQwt)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qt_internal_add_qml_module(QuickQwt
    URI "QExtQuick.Qwt"
    VERSION "${QEXT_VERSION}"
    CLASS_NAME QExtQuickQwtPlugin
    PLUGIN_TARGET QExtQuickQwtPlugin
    PLUGIN_SOURCES source/qextQuickQwtPlugin.cpp
    DEPENDENCIES
    QExt::Core
    SOURCES
    source/plotdata.cpp
    source/plotdata.h
    source/qwtquick2.cpp
    source/qwtquick2.h
    source/qextQuickQwt.cpp
    source/qextQuickQwt_p.h
    source/qextQuickQwt.h
    source/qextQuickQwtGlobal.h
    resources/qextQuickQwt.qrc
    PRECOMPILED_HEADER
    source/qextQuickQwtPch.h
    PUBLIC_LIBRARIES
    ${QEXT_QML_LINK_LIBRARIES})
set_target_properties(QExtQuickQwtPlugin PROPERTIES
    INSTALL_RPATH "\$ORIGIN/../../../lib"
    BUILD_WITH_INSTALL_RPATH TRUE)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
qext_add_subdirectory(tests QEXT_BUILD_TESTS)
