#################################################################################
#
# Library: QEXT
#
# Copyright (c) ChengXueWen. Contact: 1398831004@qq.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#################################################################################

#--------------------------------------------------------------------------------
# Set lib base name and out put path
#--------------------------------------------------------------------------------
set(_lib_base_name QEXTTcp)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(_lib_public_headers
    include/impl/qexttcppacket.h
    include/impl/qexttcppacketdispatcher.h
    include/impl/qexttcppacketheader.h
    include/impl/qexttcppacketparser.h
    include/impl/qexttcptask.h
    include/impl/qexttcptaskpool.h

    include/model/qexttcpservertransferinfomodel.h

    include/qexttcpglobal.h
    include/qexttcpabstracttask.h
    include/qexttcpabstractpacket.h
    include/qexttcpabstractthread.h
    include/qexttcpabstractthreadpool.h
    include/qexttcpclient.h
    include/qexttcpclientproxy.h
    include/qexttcpclientsocket.h
    include/qexttcppacketvariant.h
    include/qexttcpserver.h
    include/qexttcpserversocket.h
    include/qexttcpsocket.h
    include/qexttcptaskthread.h
    include/qexttcptaskthreadpool.h
    include/qexttcptransferthread.h
    include/qexttcptransferthreadpool.h
    )

set(_lib_private_headers
    private/impl/qexttcppacket_p.h
    private/impl/qexttcppacketdispatcher_p.h
    private/impl/qexttcppacketheader_p.h
    private/impl/qexttcppacketparser_p.h
    private/impl/qexttcptask_p.h
    private/impl/qexttcptaskpool_p.h

    private/model/qexttcpservertransferinfomodel_p.h

    private/qexttcpabstracttask_p.h
    private/qexttcpabstractthread_p.h
    private/qexttcpabstractthreadpool_p.h
    private/qexttcpclient_p.h
    private/qexttcpclientproxy_p.h
    private/qexttcpclientsocket_p.h
    private/qexttcpserver_p.h
    private/qexttcpserversocket_p.h
    private/qexttcpsocket_p.h
    private/qexttcptaskthread_p.h
    private/qexttcptaskthreadpool_p.h
    private/qexttcptransferthread_p.h
    private/qexttcptransferthreadpool_p.h
    )

set(_lib_sources
    source/impl/qexttcppacket.cpp
    source/impl/qexttcppacketdispatcher.cpp
    source/impl/qexttcppacketheader.cpp
    source/impl/qexttcppacketparser.cpp
    source/impl/qexttcptask.cpp
    source/impl/qexttcptaskpool.cpp

    source/model/qexttcpservertransferinfomodel.cpp

    source/qexttcpabstracttask.cpp
    source/qexttcpabstractthread.cpp
    source/qexttcpabstractthreadpool.cpp
    source/qexttcpclient.cpp
    source/qexttcpclientproxy.cpp
    source/qexttcpclientsocket.cpp
    source/qexttcppacketvariant.cpp
    source/qexttcpserver.cpp
    source/qexttcpserversocket.cpp
    source/qexttcpsocket.cpp
    source/qexttcptaskthread.cpp
    source/qexttcptaskthreadpool.cpp
    source/qexttcptransferthread.cpp
    source/qexttcptransferthreadpool.cpp
    )

set(_lib_forms

    )

set(_lib_resources

    )



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(_lib_link_libraries)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _lib_link_libraries Qt4::QtCore Qt4::QtNetwork)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _lib_link_libraries Qt5::Core Qt5::Network)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND _lib_link_libraries QEXTCore QEXTUtils)



#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
add_library(${_lib_base_name}
    ${_lib_public_headers}
    ${_lib_private_headers}
    ${_lib_sources}
    ${_lib_forms}
    ${_lib_resources}
    )
if (QEXT_BUILD_COMPILER_WARNING)
    qextFunctionSetCompilerWarnings(${_lib_base_name})
endif()
target_link_libraries(${_lib_base_name} PUBLIC ${_lib_link_libraries})
target_include_directories(${_lib_base_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/impl>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/model>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/impl>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/model>
    $<INSTALL_INTERFACE:include>
    )
target_compile_definitions(${_lib_base_name} PRIVATE QEXT_BUILD_TCP_LIB)


# set target properties
set_target_properties(${_lib_base_name} PROPERTIES
    VERSION ${QEXT_VERSION} SOVERSION ${QEXT_SO_VERSION}
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    DEBUG_POSTFIX ${QEXT_DEBUG_POSTFIX}
    )
if (QEXT_BUILD_SHARED_LIBS)
    set_target_properties(${_lib_base_name} PROPERTIES
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
