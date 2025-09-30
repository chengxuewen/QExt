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
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Qml
        Qt${QEXT_QT_VERSION_MAJOR}::Quick)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_QML_LINK_LIBRARIES QExt::Core)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_qml_module(Qml
    URI QExtQml
    VERSION "${QEXT_VERSION}"
    CLASS_NAME QExtQmlPlugin
    PLUGIN_TARGET QExtQmlPlugin
    PLUGIN_SOURCES source/qextQmlPlugin.cpp
    DEPENDENCIES
    QtQml
    QtQuick
    SOURCES
    source/gadget/qextQmlBackgroundInfo.cpp
    source/gadget/qextQmlBackgroundInfo.h
    source/gadget/qextQmlRectangleInfo.cpp
    source/gadget/qextQmlRectangleInfo.h
    source/gadget/qextQmlBorderInfo.cpp
    source/gadget/qextQmlBorderInfo.h
    source/gadget/qextQmlPaddingInfo.cpp
    source/gadget/qextQmlPaddingInfo.h
    source/gadget/qextQmlIconInfo.cpp
    source/gadget/qextQmlIconInfo.h
    source/gadget/qextQmlSizeInfo.cpp
    source/gadget/qextQmlSizeInfo.h
    source/gadget/qextQmlTextInfo.cpp
    source/gadget/qextQmlTextInfo.h
    source/qextQml.cpp
    source/qextQml.h
    source/qextQmlConstant.h
    source/qextQmlGlobal.h
    source/qextQmlInitializer.cpp
    source/qextQmlInitializer.h
    source/qextQmlRegistration.h
    source/qextQmlSingleton.h
    qextQml.qrc
    QML_FILES
    qml/QExtQmlObject.qml
    PRECOMPILED_HEADER
    source/qextQmlPch.h
    PUBLIC_LIBRARIES
    ${QEXT_QML_LINK_LIBRARIES})


#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
qext_add_subdirectory(tests QEXT_BUILD_TESTS)
