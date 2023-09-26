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
set(QEXT_LIB_BASE_NAME QEXTTcp)
set(LIBRARY_OUTPUT_PATH ${QEXT_OUTPUT_LIB_DIR})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(QEXT_LIB_PUBLIC_HEADERS
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

set(QEXT_LIB_PRIVATE_HEADERS
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

set(QEXT_LIB_SOURCES
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

set(QEXT_LIB_FORMS

    )

set(QEXT_LIB_RESOURCES

    )



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(QEXT_LIB_LINK_LIBRARIES)

if(UNIX)
    list(APPEND QEXT_LIB_LINK_LIBRARIES ${CMAKE_DL_LIBS})
endif()

if(WIN32)
    list(APPEND QEXT_LIB_LINK_LIBRARIES shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND QEXT_LIB_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtNetwork)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt${QEXT_QT_VERSION_MAJOR}::Core Qt${QEXT_QT_VERSION_MAJOR}::Network)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QEXTCore QEXTUtils)



#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
add_library(${QEXT_LIB_BASE_NAME}
    ${QEXT_LIB_PUBLIC_HEADERS}
    ${QEXT_LIB_PRIVATE_HEADERS}
    ${QEXT_LIB_SOURCES}
    ${QEXT_LIB_FORMS}
    ${QEXT_LIB_RESOURCES}
    )
if (QEXT_BUILD_COMPILER_WARNING)
    qextFunctionSetCompilerWarnings(${QEXT_LIB_BASE_NAME})
endif()
if (QEXT_BUILD_USE_PCH)
    qextFunctionActivatePrecompiledHeaders(${QEXT_LIB_BASE_NAME} PRIVATE include/qextTcpPch.h)
endif()
target_link_libraries(${QEXT_LIB_BASE_NAME} PUBLIC ${QEXT_LIB_LINK_LIBRARIES})
target_include_directories(${QEXT_LIB_BASE_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/impl>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/interface>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/model>
    $<INSTALL_INTERFACE:include/${QEXT_LIB_BASE_NAME}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/impl>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/interface>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/model>
    $<INSTALL_INTERFACE:include/${QEXT_LIB_BASE_NAME}/private>
    )
target_compile_definitions(${QEXT_LIB_BASE_NAME} PRIVATE QEXT_BUILD_TCP_LIB)

# set target properties
set_target_properties(${QEXT_LIB_BASE_NAME} PROPERTIES
    VERSION ${QEXT_VERSION}
    SOVERSION ${QEXT_SO_VERSION}
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    DEBUG_POSTFIX ${QEXT_DEBUG_POSTFIX}
    )
if (QEXT_BUILD_SHARED_LIBS)
    set_target_properties(${QEXT_LIB_BASE_NAME} PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1
        )
endif()

# set include files copy command
foreach(HEADER ${QEXT_LIB_PUBLIC_HEADERS})
    get_filename_component(HEADER_ABSOLUTE_PATH ${HEADER} ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})
    list(APPEND QEXT_LIB_PUBLIC_ABSOLUTE_HEADERS ${HEADER_ABSOLUTE_PATH})
endforeach()
foreach(HEADER ${QEXT_LIB_PRIVATE_HEADERS})
    get_filename_component(HEADER_ABSOLUTE_PATH ${HEADER} ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})
    list(APPEND QEXT_LIB_PRIVATE_ABSOLUTE_HEADERS ${HEADER_ABSOLUTE_PATH})
endforeach()
add_custom_command(
    TARGET ${QEXT_LIB_BASE_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${QEXT_OUTPUT_INCLUDE_DIR}/${QEXT_LIB_BASE_NAME}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${QEXT_OUTPUT_INCLUDE_DIR}/${QEXT_LIB_BASE_NAME}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${QEXT_OUTPUT_INCLUDE_DIR}/${QEXT_LIB_BASE_NAME}/private
    COMMAND ${CMAKE_COMMAND} -E copy ${QEXT_LIB_PUBLIC_ABSOLUTE_HEADERS} ${QEXT_OUTPUT_INCLUDE_DIR}/${QEXT_LIB_BASE_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy ${QEXT_LIB_PRIVATE_ABSOLUTE_HEADERS} ${QEXT_OUTPUT_INCLUDE_DIR}/${QEXT_LIB_BASE_NAME}/private
    COMMENT "Copy ${QEXT_LIB_BASE_NAME} include files to output dir"
    POST_BUILD
    )



#--------------------------------------------------------------------------------
# Add lib tests and examples
#--------------------------------------------------------------------------------
if (QEXT_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if (QEXT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
