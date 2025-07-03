########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
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
set(QEXT_LIB_NAME DAView)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::SerialPort
        Qt${QEXT_QT_VERSION_MAJOR}::Network
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QExt::Core QExt::Plot QExt::Widgets)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_library(${QEXT_LIB_NAME}
    EXCEPTIONS
    SOURCES
    source/device/qextDAIODevice.cpp
    source/device/qextDAIODevice.h
    source/device/qextDAIODevice_p.h
    source/device/qextDAIODeviceFactory.cpp
    source/device/qextDAIODeviceFactory.h
    source/device/qextDAIODeviceManager.cpp
    source/device/qextDAIODeviceManager.h
    source/device/qextDAIODeviceModel.cpp
    source/device/qextDAIODeviceModel.h
    source/device/qextDAIODeviceUtils.cpp
    source/device/qextDAIODeviceUtils.h
    source/device/qextDASerialPortIODevice.cpp
    source/device/qextDASerialPortIODevice.h
    source/device/qextDATcpSocketIODevice.cpp
    source/device/qextDATcpSocketIODevice.h
    source/device/qextDAUdpSocketIODevice.cpp
    source/device/qextDAUdpSocketIODevice.h
    source/reader/qextDAIOReader.cpp
    source/reader/qextDAIOReader.h
    source/reader/qextDAIOReader_p.h
    source/vsdevice/qextDAVSDevice.cpp
    source/vsdevice/qextDAVSDevice.h
    source/vsdevice/qextDAVSDevice_p.h
    source/qextDAConstants.h
    source/qextDAViewGlobal.h
    source/qextDAView.cpp
    source/qextDAView.h
    resources/qextDAView.qrc
    PRECOMPILED_HEADER
    source/qextDAViewPch.h
    PUBLIC_LIBRARIES
    ${QEXT_LIB_LINK_LIBRARIES})


#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
qext_add_subdirectory(tests QEXT_BUILD_TESTS)
