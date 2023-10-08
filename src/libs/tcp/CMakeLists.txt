#################################################################################
#
# Library: QExt
#
# Copyright (c) ChengXueWen. Contact: 1398831004@qq.com
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#################################################################################


#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(QEXT_LIB_LINK_LIBRARIES)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtNetwork)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
            Qt${QEXT_QT_VERSION_MAJOR}::Core
            Qt${QEXT_QT_VERSION_MAJOR}::Network
    )
else()
    message(FATAL_ERROR "Not find Qt package")
endif()


#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
qext_add_library(Tcp
        EXCEPTIONS
        SOURCES
        source/qextTcpClient.cpp
        source/qextTcpClient.h
        source/qextTcpClient_p.h
        source/qextTcpFactory.cpp
        source/qextTcpFactory.h
        source/qextTcpGlobal.h
        source/qextTcpPacket.cpp
        source/qextTcpPacket.h
        source/qextTcpPacket_p.h
        source/qextTcpPacketDispatcher.cpp
        source/qextTcpPacketDispatcher.h
        source/qextTcpPacketDispatcher_p.h
        source/qextTcpPacketHeader.cpp
        source/qextTcpPacketHeader.h
        source/qextTcpPacketHeader_p.h
        source/qextTcpPacketHeaderInterface.h
        source/qextTcpPacketInterface.h
        source/qextTcpPacketParser.cpp
        source/qextTcpPacketParser.h
        source/qextTcpPacketParser_p.h
        source/qextTcpPacketParserInterface.h
        source/qextTcpPacketTransceiver.cpp
        source/qextTcpPacketTransceiver.h
        source/qextTcpPacketTransceiver_p.h
        source/qextTcpPacketVariant.cpp
        source/qextTcpPacketVariant.h
        source/qextTcpServer.cpp
        source/qextTcpServer.h
        source/qextTcpServer_p.h
        source/qextTcpSocket.cpp
        source/qextTcpSocket.h
        source/qextTcpSocket_p.h
        source/qextTcpTask.cpp
        source/qextTcpTask.h
        source/qextTcpTask_p.h
        source/qextTcpTaskPool.cpp
        source/qextTcpTaskPool.h
        source/qextTcpTaskPool_p.h
        source/qextTcpUtils.cpp
        source/qextTcpUtils.h
        PRECOMPILED_HEADER
        source/qextTcpPch.h
        PUBLIC_LIBRARIES
        ${QEXT_LIB_LINK_LIBRARIES}
        Core Utils)


#--------------------------------------------------------------------------------
# Add lib tests and examples
#--------------------------------------------------------------------------------
if(QEXT_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(QEXT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()