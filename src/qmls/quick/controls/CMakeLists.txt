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

if(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_QML_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Qml
        Qt${QEXT_QT_VERSION_MAJOR}::Quick
        Qt${QEXT_QT_VERSION_MAJOR}::QuickControls2)
    if("${QEXT_QT_VERSION}" GREATER "6.2")
        list(APPEND QEXT_QML_LINK_LIBRARIES
            Qt${QEXT_QT_VERSION_MAJOR}::QuickEffectsPrivate)
    endif()
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_QML_LINK_LIBRARIES QExt::Qml QExt::QmlTheme QExt::QmlFontIcon)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_qml_module(QuickControls
    URI "QExtQuick.Controls"
    VERSION "${QEXT_VERSION}"
    CLASS_NAME QExtQuickControlsPlugin
    PLUGIN_TARGET QExtQuickControlsPlugin
    PLUGIN_SOURCES source/qextQuickControlsPlugin.cpp
    DEPENDENCIES
    QExtQml
    QExtQml.Theme
    QExtQml.FontIcon
    QtQuick.Effects
    SOURCES
    source/qextQuickControls.cpp
    source/qextQuickControls.h
    source/qextQuickControlsConstant.h
    source/qextQuickControlsGlobal.h
    source/qextQuickWorld.cpp
    source/qextQuickWorld.h
    qextQuickControls.qrc
    PRECOMPILED_HEADER
    source/qextQuickControlPch.h
    QML_FILES
    qml/QExtQuickButton.qml
    qml/QExtQuickButtonArea.qml
    qml/QExtQuickCheckBox.qml
    qml/QExtQuickFontIcon.qml
    qml/QExtQuickIconButton.qml
    qml/QExtQuickRectangle.qml
    qml/QExtQuickSvgIcon.qml
    qml/QExtQuickSvgIcon0.qml
    qml/QExtQuickSvgIcon1.qml
    qml/QExtQuickSvgIcon2.qml
    qml/QExtQuickSwitch.qml
    qml/QExtQuickText.qml
    DEFINES
    QEXT_BUILD_QUICK_LIB
    PUBLIC_LIBRARIES
    ${QEXT_QML_LINK_LIBRARIES})


#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
qext_add_subdirectory(tests QEXT_BUILD_TESTS)
