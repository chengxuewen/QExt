#################################################################################
#
# Library: QEXT
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
# Set lib base name and out put path
#--------------------------------------------------------------------------------
set(qext_lib_base_name QEXTTcp)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(qext_lib_public_headers
    include/interface/qextTcpPacketHeaderInterface.h
    include/interface/qextTcpPacketInterface.h
    include/interface/qextTcpPacketParserInterface.h

    include/qextTcpClient.h
    include/qextTcpFactory.h
    include/qextTcpPch.h
    include/qextTcpGlobal.h
    include/qextTcpPacket.h
    include/qextTcpPacketDispatcher.h
    include/qextTcpPacketHeader.h
    include/qextTcpPacketParser.h
    include/qextTcpPacketTransceiver.h
    include/qextTcpPacketVariant.h
    include/qextTcpServer.h
    include/qextTcpSocket.h
    include/qextTcpTask.h
    include/qextTcpTaskPool.h
    include/qextTcpUtils.h
    )

set(qext_lib_private_headers
    private/qextTcpClient_p.h
    private/qextTcpPacket_p.h
    private/qextTcpPacketDispatcher_p.h
    private/qextTcpPacketHeader_p.h
    private/qextTcpPacketParser_p.h
    private/qextTcpPacketTransceiver_p.h
    private/qextTcpServer_p.h
    private/qextTcpSocket_p.h
    private/qextTcpTaskPool_p.h
    private/qextTcpTask_p.h
    )

set(qext_lib_sources
    source/qextTcpClient.cpp
    source/qextTcpFactory.cpp
    source/qextTcpPacket.cpp
    source/qextTcpPacketDispatcher.cpp
    source/qextTcpPacketHeader.cpp
    source/qextTcpPacketParser.cpp
    source/qextTcpPacketTransceiver.cpp
    source/qextTcpPacketVariant.cpp
    source/qextTcpServer.cpp
    source/qextTcpSocket.cpp
    source/qextTcpTask.cpp
    source/qextTcpTaskPool.cpp
    source/qextTcpUtils.cpp
    )

set(qext_lib_forms

    )

set(qext_lib_resources

    )



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(qext_lib_link_libraries)

if(UNIX)
    list(APPEND qext_lib_link_libraries ${CMAKE_DL_LIBS})
endif()

if(WIN32)
    list(APPEND qext_lib_link_libraries shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND qext_lib_link_libraries ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND qext_lib_link_libraries Qt4::QtCore Qt4::QtNetwork)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND qext_lib_link_libraries Qt${QEXT_QT_VERSION_MAJOR}::Core Qt${QEXT_QT_VERSION_MAJOR}::Network)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND qext_lib_link_libraries QEXTCore QEXTUtils)



#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
add_library(${qext_lib_base_name}
    ${qext_lib_public_headers}
    ${qext_lib_private_headers}
    ${qext_lib_sources}
    ${qext_lib_forms}
    ${qext_lib_resources}
    )
if (QEXT_BUILD_COMPILER_WARNING)
    qextFunctionSetCompilerWarnings(${qext_lib_base_name})
endif()
if (QEXT_BUILD_USE_PCH)
    qextFunctionActivatePrecompiledHeaders(${qext_lib_base_name} PRIVATE include/qextTcpPch.h)
endif()
target_link_libraries(${qext_lib_base_name} PUBLIC ${qext_lib_link_libraries})
target_include_directories(${qext_lib_base_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/impl>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/interface>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/model>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/impl>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/model>
    $<INSTALL_INTERFACE:include>
    )
target_compile_definitions(${qext_lib_base_name} PRIVATE QEXT_BUILD_TCP_LIB)


# set target properties
set_target_properties(${qext_lib_base_name} PROPERTIES
    VERSION ${QEXT_VERSION} SOVERSION ${QEXT_SO_VERSION}
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    DEBUG_POSTFIX ${QEXT_DEBUG_POSTFIX}
    )
if (QEXT_BUILD_SHARED_LIBS)
    set_target_properties(${qext_lib_base_name} PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1)
endif()



#--------------------------------------------------------------------------------
# Add lib tests and examples
#--------------------------------------------------------------------------------
if (QEXT_BUILD_TESTS OR QEXT_BUILD_ALL)
    add_subdirectory(tests)
endif()

if (QEXT_BUILD_EXAMPLES OR QEXT_BUILD_ALL)
    add_subdirectory(examples)
endif()
