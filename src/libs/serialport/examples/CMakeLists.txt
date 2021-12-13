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
set(EXECUTABLE_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/serialPort)
set(LIBRARY_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/serialPort)



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
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES QEXTSerialPort)



#--------------------------------------------------------------------------------
# Add qext_exp_serialportenumerator example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_serialportenumerator)
set(qext_example_headers

    )
set(qext_example_sources
    enumerator/main.cpp
    )
set(qext_example_forms

    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    )
target_link_libraries(${qext_example_name} PRIVATE ${QEXT_EXAMPLE_LINK_LIBRARIES})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/enumerator)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextFunctionCopyDependencyInternal(
        TARGET ${qext_example_name}
        LIBS QEXTCore QEXTSerialPort
        DESTINATION ${EXECUTABLE_OUTPUT_PATH}
        POST_BUILD
        )
endif()


#--------------------------------------------------------------------------------
# Add qext_exp_serialportevent example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_serialportevent)
set(qext_example_headers
    event/PortListener.h
    )
set(qext_example_sources
    event/PortListener.cpp
    event/main.cpp
    )
set(qext_example_forms

    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    )
target_link_libraries(${qext_example_name} PRIVATE ${QEXT_EXAMPLE_LINK_LIBRARIES})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/event)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextFunctionCopyDependencyInternal(
        TARGET ${qext_example_name}
        LIBS QEXTCore QEXTSerialPort
        DESTINATION ${EXECUTABLE_OUTPUT_PATH}
        POST_BUILD
        )
endif()


#--------------------------------------------------------------------------------
# Add qext_exp_serialportsimple example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_serialportsimple)
set(qext_example_headers
    simple/MainWindow.h
    simple/MessageWindow.h
    simple/Test.h
    )
set(qext_example_sources
    simple/MainWindow.cpp
    simple/MessageWindow.cpp
    simple/Test.cpp
    simple/main.cpp
    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    )
target_link_libraries(${qext_example_name} PRIVATE ${QEXT_EXAMPLE_LINK_LIBRARIES})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/simple)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextFunctionCopyDependencyInternal(
        TARGET ${qext_example_name}
        LIBS QEXTCore QEXTSerialPort
        DESTINATION ${EXECUTABLE_OUTPUT_PATH}
        POST_BUILD
        )
endif()


#--------------------------------------------------------------------------------
# Add qext_exp_serialportuartassistant example
#--------------------------------------------------------------------------------
set(qext_example_name qext_exp_serialportuartassistant)
set(qext_example_headers
    uartassistant/dialog.h
    uartassistant/hled.h
    )
set(qext_example_sources
    uartassistant/dialog.cpp
    uartassistant/hled.cpp
    uartassistant/main.cpp
    )
set(qext_example_forms
    uartassistant/dialog.ui
    )
add_executable(${qext_example_name}
    ${qext_example_headers}
    ${qext_example_sources}
    ${qext_example_forms}
    )
target_link_libraries(${qext_example_name} PRIVATE ${QEXT_EXAMPLE_LINK_LIBRARIES})
target_include_directories(${qext_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/uartassistant)
set_property(TARGET ${qext_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextFunctionCopyDependencyInternal(
        TARGET ${qext_example_name}
        LIBS QEXTCore QEXTSerialPort
        DESTINATION ${EXECUTABLE_OUTPUT_PATH}
        POST_BUILD
        )
endif()
