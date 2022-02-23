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
set(EXECUTABLE_OUTPUT_PATH ${QEXT_OUTPUT_EXAMPLE_DIR}/qml/framelesshelper)
set(LIBRARY_OUTPUT_PATH ${QEXT_OUTPUT_EXAMPLE_DIR}/qml/framelesshelper)



#--------------------------------------------------------------------------------
# Configure a header file to pass some of the CMake settings to the source code
#--------------------------------------------------------------------------------
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/qextQmlFramelessHelperExampleConfig.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/qextQmlFramelessHelperExampleConfig.h"
    )



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

if(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Qml
        Qt${QEXT_QT_VERSION_MAJOR}::Quick
        )
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES QEXTQmlFramelessHelper)



#--------------------------------------------------------------------------------
# define function
#--------------------------------------------------------------------------------
function(qextFunctionAddQmlFramelessHelperExample EXAMPLE_NAME)
    set(multiValueArgs EXAMPLE_SOURCE EXAMPLE_INCLUDE_DIRS)
    cmake_parse_arguments(MY "" "" "${multiValueArgs}" "${ARGN}")
    add_executable(${EXAMPLE_NAME} ${MY_EXAMPLE_SOURCE} ${QEXT_EXAMPLE_CONFIG_FILE_PATH})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE ${QEXT_EXAMPLE_LINK_LIBRARIES})
    target_include_directories(${EXAMPLE_NAME} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${MY_EXAMPLE_INCLUDE_DIRS}
        )
    set_property(TARGET ${EXAMPLE_NAME} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
    if(QEXT_BUILD_SHARED_LIBS AND WIN32)
        qextFunctionCopyDependencyInternal(
            TARGET ${EXAMPLE_NAME}
            LIBS QEXTCore QEXTQmlFramelessHelper
            DESTINATION ${EXECUTABLE_OUTPUT_PATH}
            POST_BUILD
            )
    endif()
endfunction()



#--------------------------------------------------------------------------------
# Add example
#--------------------------------------------------------------------------------
qextFunctionAddQmlFramelessHelperExample(qext_exp_qmlFramelessHelper
    EXAMPLE_SOURCE
    framelesshelper/framelesshelper.qrc
    framelesshelper/main.cpp
    EXAMPLE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/framelesshelper
    )
