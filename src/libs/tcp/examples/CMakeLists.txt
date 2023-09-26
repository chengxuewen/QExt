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
# Set example output path
#--------------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${QEXT_OUTPUT_EXAMPLE_DIR}/tcp)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR}/tcp)



#--------------------------------------------------------------------------------
# Set example link libraries
#--------------------------------------------------------------------------------
set(QEXT_EXAMPLE_LINK_LIBRARIES)

if(UNIX)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES dl)
endif()

if(WIN32)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES QEXTTcp)



#--------------------------------------------------------------------------------
# define function
#--------------------------------------------------------------------------------
function(qextTcpAddExample EXAMPLE_NAME)
    set(multiValueArgs EXAMPLE_SOURCE EXAMPLE_INCLUDE_DIRS)
    cmake_parse_arguments(MY "" "" "${multiValueArgs}" "${ARGN}")
    add_executable(${EXAMPLE_NAME} ${MY_EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE ${QEXT_EXAMPLE_LINK_LIBRARIES})
    target_include_directories(${EXAMPLE_NAME} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${MY_EXAMPLE_INCLUDE_DIRS}
        ${QEXT_EXAMPLE_INCLUDE_DIRECTORIES}
        )
    set_property(TARGET ${EXAMPLE_NAME} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
    if(QEXT_BUILD_SHARED_LIBS AND WIN32)
        qextFunctionCopyDependencyInternal(
            TARGET ${EXAMPLE_NAME}
            LIBS QEXTCore QEXTWidgets
            DESTINATION ${EXECUTABLE_OUTPUT_PATH}
            POST_BUILD
            )
    endif()
endfunction()


#--------------------------------------------------------------------------------
# Add qext_exp_tcpSimpleServer example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_tcpSimpleServer)
set(qext_example_headers
    simpleServer/smainwindow.h
    simpleServer/ssocketmsgbrowser.h
    )
set(qext_example_sources
    simpleServer/main.cpp
    simpleServer/smainwindow.cpp
    simpleServer/ssocketmsgbrowser.cpp
    )
set(qext_example_forms
    simpleServer/smainwindow.ui
    simpleServer/ssocketmsgbrowser.ui
    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    )
target_link_libraries(${qext_example_name} PRIVATE ${QEXT_EXAMPLE_LINK_LIBRARIES})
target_include_directories(${qext_example_name} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleServer
    ${CMAKE_CURRENT_BINARY_DIR}/
    )
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextFunctionCopyDependencyInternal(
        TARGET ${qext_example_name}
        LIBS QEXTCore QEXTTcp
        DESTINATION ${EXECUTABLE_OUTPUT_PATH}
        POST_BUILD
        )
endif()


#--------------------------------------------------------------------------------
# Set qext_exp_tcpSimpleClient example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_tcpSimpleClient)
set(qext_example_headers
    simpleClient/cmainwindow.h
    )
set(qext_example_sources
    simpleClient/main.cpp
    simpleClient/cmainwindow.cpp
    )
set(qext_example_forms
    simpleClient/cmainwindow.ui
    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    )
target_link_libraries(${qext_example_name} PRIVATE ${QEXT_EXAMPLE_LINK_LIBRARIES})
target_include_directories(${qext_example_name} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleClient
    ${CMAKE_CURRENT_BINARY_DIR}/
    )
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextFunctionCopyDependencyInternal(
        TARGET ${qext_example_name}
        LIBS QEXTCore QEXTTcp
        DESTINATION ${EXECUTABLE_OUTPUT_PATH}
        POST_BUILD
        )
endif()
