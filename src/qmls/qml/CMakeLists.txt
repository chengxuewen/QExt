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
        Qt${QEXT_QT_VERSION_MAJOR}::Quick)
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

# add_executable(QExt::moc IMPORTED)
# set_target_properties(QExt::moc PROPERTIES
#   COMPATIBLE_INTERFACE_STRING "QT_MAJOR_VERSION"
#   INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
#   INTERFACE_QT_MAJOR_VERSION "${QEXT_QT_VERSION_MAJOR}"
#   _qt_package_version "${QEXT_VERSION}")


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qt_internal_add_qml_module(Qml
    URI "QExtQml"
    VERSION "${QEXT_VERSION}"
    CLASS_NAME QExtQmlPlugin
    PLUGIN_TARGET QmlPlugin
    PLUGIN_SOURCES source/qextQmlPlugin.cpp
    DEPENDENCIES
    QExt::Core
    SOURCES
    source/qextQml.cpp
    source/qextQml.h
    source/qextQmlGlobal.h
    qextQml.qrc
    PRECOMPILED_HEADER
    source/qextQmlPch.h
    PUBLIC_LIBRARIES
    ${QEXT_QML_LINK_LIBRARIES})


#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
qext_add_subdirectory(tests QEXT_BUILD_TESTS)
