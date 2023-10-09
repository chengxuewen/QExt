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
# Set example output path
#-----------------------------------------------------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/coloredpixmapiconengine)
set(LIBRARY_OUTPUT_PATH ${QEXT_EXAMPLE_OUTPUT_DIR}/coloredpixmapiconengine)



#-----------------------------------------------------------------------------------------------------------------------
# Set example link libraries
#-----------------------------------------------------------------------------------------------------------------------
set(_example_link_libraries)

if(UNIX)
    list(APPEND _example_link_libraries dl)
endif()

if(WIN32)
    list(APPEND _example_link_libraries shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND _example_link_libraries ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _example_link_libraries Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _example_link_libraries Qt5::Core Qt5::Gui Qt5::Widgets)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND _example_link_libraries QEXTColoredPixmapIcon)



#-----------------------------------------------------------------------------------------------------------------------
# Add exp_qextColoredPixmapIcon example
#-----------------------------------------------------------------------------------------------------------------------
set(_example_name exp_qextColoredPixmapIcon)
set(_example_headers
    coloredpixmap/MainWindow.h
    )
set(_example_sources
    coloredpixmap/MainWindow.cpp
    coloredpixmap/main.cpp
    )
set(_example_forms
    coloredpixmap/MainWindow.ui
    )
set(_example_resources
    coloredpixmap/resources.qrc
    )
add_executable(${_example_name}
    ${_example_headers}
    ${_example_sources}
    ${_example_forms}
    ${_example_resources}
    )
target_link_libraries(${_example_name} PRIVATE ${_example_link_libraries})
target_include_directories(${_example_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/coloredpixmap)
set_property(TARGET ${_example_name} PROPERTY INTERFACE_CXX_EXTENSIONS OFF)
if(WIN32)
    qextFunctionCopyDependencyInternal(${_example_name} QEXTFontAwesome ${EXECUTABLE_OUTPUT_PATH})
    qextFunctionCopyDependencyInternal(${_example_name} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
endif()
