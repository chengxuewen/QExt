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
# Set lib base name and out put path
#-----------------------------------------------------------------------------------------------------------------------
set(_lib_base_name QEXTColoredPixmapIcon)
set(LIBRARY_OUTPUT_PATH ${QEXT_PLUGIN_OUTPUT_DIR})



#-----------------------------------------------------------------------------------------------------------------------
# Set lib file list
#-----------------------------------------------------------------------------------------------------------------------
set(_lib_public_headers
    include/qextColoredPixmapIconEngine.h
    include/qextColoredPixmapIconGlobal.h
    )

set(_lib_private_headers
    )

set(_lib_sources
    source/qextColoredPixmapIconEngine.cpp
    source/qextColoredPixmapIconEnginePlugin.cpp
    )

set(_lib_forms

    )

set(_lib_resources
    resource/QEXTColoredPixmapIcon.qrc
    )

list(APPEND _lib_link_libraries QEXTCore)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib link libraries
#-----------------------------------------------------------------------------------------------------------------------
set(_lib_link_libraries)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _lib_link_libraries Qt4::QtCore Qt4::QtGui Qt4::QtNetwork)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _lib_link_libraries Qt5::Core Qt5::Gui Qt5::Network)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND _lib_link_libraries QEXTCore)



#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
add_library(${_lib_base_name} STATIC
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
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/resource>
    $<BUILD_INTERFACE:${Qt5Gui_PRIVATE_INCLUDE_DIRS}>
    $<BUILD_INTERFACE:${Qt5Widgets_PRIVATE_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:include>
    )
target_compile_definitions(${_lib_base_name} PRIVATE QEXT_BUILD_COLOREDPIXMAPICON_LIB)


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



#-----------------------------------------------------------------------------------------------------------------------
# Add lib tests and examples
#-----------------------------------------------------------------------------------------------------------------------
if (QEXT_BUILD_TESTS OR QEXT_BUILD_ALL)
    add_subdirectory(tests)
endif()

if (QEXT_BUILD_EXAMPLES OR QEXT_BUILD_ALL)
    add_subdirectory(examples)
endif()
