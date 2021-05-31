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
set(_lib_base_name QNanoPainter)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})

option(QNANO_QT_GL_INCLUDE "Enable this to let Qt include OpenGL headers" ON)
option(QNANO_ENABLE_GLES3 "This will enable GLES3 (disable to force GLES2)" ON)
option(QNANO_ENABLE_TOUCH_SIGNALS "This will enable signalling touch events" OFF) # Can be useful when using view/widget classes directly
option(QNANO_ENABLE_PAINT_SIGNALS "This will enable signalling paint events" OFF) # Can be useful when using view/widget classes directly
option(QNANO_USE_RENDERNODE "Enable this to use QRenderNode" OFF) # (available since Qt 5.8.0) instead of QQuickFramebufferObject
#option(QNANO_BUILD_GLES_BACKENDS "Build OpenGLES library" OFF)
#option(QNANO_BUILD_GL_BACKENDS "Build OpenGL library" OFF)
set(QNANO_BUILD_GLES_BACKENDS OFF)
set(QNANO_BUILD_GL_BACKENDS ON)

if (WIN32 OR ANDROID OR IOS)
    set(QNANO_BUILD_GLES_BACKENDS ON)
    set(QNANO_BUILD_GL_BACKENDS OFF)
endif()



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(_lib_public_headers
    source/qnanopainterglobal.h

    source/private/qnanobrush.h
    source/qnanopainter.h
    source/qnanocolor.h
    source/qnanolineargradient.h
    source/qnanoimagepattern.h
    source/qnanoimage.h
    source/qnanofont.h
    source/qnanoradialgradient.h
    source/qnanoboxgradient.h
    source/private/qnanodataelement.h
    source/private/qnanobackend.h
    source/private/qnanobackendfactory.h
    source/qnanowindow.h
    source/private/qnanodebug.h
    )

set(_lib_private_headers

    )

set(_lib_sources
    source/qnanopainter.cpp
    source/qnanocolor.cpp
    source/qnanolineargradient.cpp
    source/qnanoimagepattern.cpp
    source/qnanoimage.cpp
    source/qnanofont.cpp
    source/qnanoradialgradient.cpp
    source/qnanoboxgradient.cpp
    source/qnanowindow.cpp
    source/private/qnanodebug.cpp

    source/qnanowidget.cpp
    source/qnanowidget.h

    source/nanovg/nanovg.c
    source/nanovg/nanovg.h
    )

set(_lib_forms

    )

set(_lib_resources
    source/qnanopainterdata.qrc
    )

if (QEXT_BUILD_QML)
    list(APPEND _lib_sources
        source/qnanoquickitem.cpp
        source/qnanoquickitempainter.cpp
        )
    list(APPEND _lib_public_headers
        source/qnanoquickitem.h
        source/qnanoquickitempainter.h
        )
endif()

if(QNANO_BUILD_GLES_BACKENDS)
    message(STATUS "----QEXT---- Including QNanoPainter OpenGL ES backends")
    list(APPEND _lib_public_headers
        source/private/qnanobackendgles2.h
        source/private/qnanobackendgles3.h
        )
    list(APPEND _lib_sources
        source/private/qnanobackendgles2.cpp
        source/private/qnanobackendgles3.cpp
        )
endif()

if(QNANO_BUILD_GL_BACKENDS)
    message(STATUS "----QEXT---- Including QNanoPainter OpenGL backends")
    list(APPEND _lib_public_headers
        source/private/qnanobackendgl2.h
        source/private/qnanobackendgl3.h
        )
    list(APPEND _lib_sources
        source/private/qnanobackendgl2.cpp
        source/private/qnanobackendgl3.cpp
        )
endif()



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(_lib_link_libraries)

if (WIN32)
    if(QEXT_QT_VERSION_MAJOR EQUAL 5 AND QEXT_QT_VERSION_MINOR LESS 14)
        list(APPEND _lib_link_libraries GLESv2)
    endif()
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _lib_link_libraries Qt4::QtCore Qt4::QtNetwork)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _lib_link_libraries Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Quick)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 6)
    list(APPEND _lib_link_libraries Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Quick Qt6::OpenGL)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND _lib_link_libraries QEXTCore)



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
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
    $<INSTALL_INTERFACE:include>
    )
target_compile_definitions(${_lib_base_name} PRIVATE QEXT_BUILD_NANOPAINTER_LIB)
if (QNANO_BUILD_GL_BACKENDS)
    target_compile_definitions(${_lib_base_name} PRIVATE QNANO_BUILD_GL_BACKENDS)
endif()
if (QNANO_BUILD_GLES_BACKENDS)
    target_compile_definitions(${_lib_base_name} PRIVATE QNANO_BUILD_GLES_BACKENDS)
endif()
if (QNANO_QT_GL_INCLUDE)
    target_compile_definitions(${_lib_base_name} PRIVATE QNANO_QT_GL_INCLUDE)
endif()
if (QNANO_ENABLE_GLES3)
    target_compile_definitions(${_lib_base_name} PRIVATE QNANO_ENABLE_GLES3)
endif()


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
