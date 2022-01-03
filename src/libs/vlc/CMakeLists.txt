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
set(QEXT_LIB_BASE_NAME QEXTVLC)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Configure a header file to pass some of the CMake settings to the source code
#--------------------------------------------------------------------------------
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/qextVLCConfig.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/qextVLCConfig.h"
    )



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(QEXT_LIB_PUBLIC_HEADERS
    ${CMAKE_CURRENT_BINARY_DIR}/qextVLCConfig.h

    include/qextVLCPch.h
    include/qextVLCHeaders.h
    include/qextVLCGlobal.h
    include/qextVLCAbstractVideoFrame.h
    include/qextVLCAbstractVideoStream.h
    include/qextVLCAudio.h
    include/qextVLCCommon.h
    include/qextVLCControlAudio.h
    include/qextVLCControlVideo.h
    include/qextVLC.h
    include/qextVLCEqualizer.h
    include/qextVLCError.h
    include/qextVLCInstance.h
    include/qextVLCMedia.h
    include/qextVLCMediaList.h
    include/qextVLCMediaListPlayer.h
    include/qextVLCMediaPlayer.h
    include/qextVLCMetaManager.h
    include/qextVLCModuleDescription.h
    include/qextVLCStats.h
    include/qextVLCTrackModel.h
    include/qextVLCVideo.h
    include/qextVLCVideoDelegate.h
    include/qextVLCVideoFrame.h
    include/qextVLCVideoStream.h
    include/qextVLCWidgetSeek.h
    include/qextVLCWidgetSeekProgress.h
    include/qextVLCWidgetVideo.h
    include/qextVLCWidgetVolumeSlider.h
    include/qextVLCYUVVideoFrame.h
    include/qextVLCASprintf.h
    include/qextVLC.h
    include/qextVLCThread.h
    )

set(QEXT_LIB_PRIVATE_HEADERS
    )

set(QEXT_LIB_SOURCES
    source/qextVLCAbstractVideoFrame.cpp
    source/qextVLCAbstractVideoStream.cpp
    source/qextVLCAudio.cpp
    source/qextVLCCommon.cpp
    source/qextVLCControlAudio.cpp
    source/qextVLCControlVideo.cpp
    source/qextVLC.cpp
    source/qextVLCEqualizer.cpp
    source/qextVLCError.cpp
    source/qextVLCInstance.cpp
    source/qextVLCMedia.cpp
    source/qextVLCMediaList.cpp
    source/qextVLCMediaListPlayer.cpp
    source/qextVLCMediaPlayer.cpp
    source/qextVLCMetaManager.cpp
    source/qextVLCModuleDescription.cpp
    source/qextVLCTrackModel.cpp
    source/qextVLCVideo.cpp
    source/qextVLCVideoFrame.cpp
    source/qextVLCVideoStream.cpp
    source/qextVLCWidgetSeek.cpp
    source/qextVLCWidgetSeekProgress.cpp
    source/qextVLCWidgetVideo.cpp
    source/qextVLCWidgetVolumeSlider.cpp
    source/qextVLCYUVVideoFrame.cpp
    source/qextVLCASprintf.c
    source/qextVLCVASprintf.c
    source/qextVLCThread.cpp
    )

set(QEXT_LIB_FORMS

    )

set(QEXT_LIB_RESOURCES
    resource/QEXTVLC.qrc
    )

list(APPEND QEXT_LIB_LINK_LIBRARIES QEXTCore)


#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(QEXT_LIB_LINK_LIBRARIES)
set(QEXT_LIB_INCLUDE_DIRECTORIES)

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
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui)
    list(APPEND QEXT_LIB_INCLUDE_DIRECTORIES
        ${Qt4Gui_PRIVATE_INCLUDE_DIRS}
        ${Qt4Widgets_PRIVATE_INCLUDE_DIRS}
        )
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets
        )
    list(APPEND QEXT_LIB_INCLUDE_DIRECTORIES
        ${Qt${QEXT_QT_VERSION_MAJOR}Gui_PRIVATE_INCLUDE_DIRS}
        ${Qt${QEXT_QT_VERSION_MAJOR}Widgets_PRIVATE_INCLUDE_DIRS}
        )
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()


list(APPEND QEXT_LIB_LINK_LIBRARIES QEXTCore)

set(QEXT_LIBVLC_FIND_REQUIRED ON)
qextMacroFindLibVLC()
list(APPEND QEXT_LIB_LINK_LIBRARIES ${QEXT_LIBVLC_LIBRARY} ${QEXT_LIBVLC_CORE_LIBRARY})
list(APPEND QEXT_LIB_INCLUDE_DIRECTORIES
    ${QEXT_LIBVLC_EXTRA_INCLUDE_DIR}
    ${QEXT_LIBVLC_EXTRA_INCLUDE_DIR}/vlc
    ${QEXT_LIBVLC_EXTRA_INCLUDE_DIR}/vlc/plugins
    ${QEXT_LIBVLC_INCLUDE_DIR}
    ${QEXT_LIBVLC_INCLUDE_DIR}/vlc
    ${QEXT_LIBVLC_INCLUDE_DIR}/vlc/plugins
    )
SET(QEXT_LIBVLC_VERSION 2 CACHE STRING "libVLC version used")



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
    qextFunctionActivatePrecompiledHeaders(${QEXT_LIB_BASE_NAME} PRIVATE include/qextVLCPch.h)
endif()
target_link_libraries(${QEXT_LIB_BASE_NAME} PUBLIC ${QEXT_LIB_LINK_LIBRARIES})
target_include_directories(${QEXT_LIB_BASE_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${QEXT_LIB_BASE_NAME}>
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<INSTALL_INTERFACE:include/${QEXT_LIB_BASE_NAME}/private>
    )
target_compile_definitions(${QEXT_LIB_BASE_NAME} PRIVATE QEXT_BUILD_VLC_LIB)

# set target properties
set_target_properties(${QEXT_LIB_BASE_NAME} PROPERTIES
    VERSION ${QEXT_VERSION} SOVERSION ${QEXT_SO_VERSION}
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    DEBUG_POSTFIX ${QEXT_DEBUG_POSTFIX}
    )
if (QEXT_BUILD_SHARED_LIBS)
    set_target_properties(${QEXT_LIB_BASE_NAME} PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1)
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
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${QEXT_INCLUDE_OUTPUT_DIR}/${QEXT_LIB_BASE_NAME}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${QEXT_INCLUDE_OUTPUT_DIR}/${QEXT_LIB_BASE_NAME}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${QEXT_INCLUDE_OUTPUT_DIR}/${QEXT_LIB_BASE_NAME}/private
    COMMAND ${CMAKE_COMMAND} -E copy ${QEXT_LIB_PUBLIC_ABSOLUTE_HEADERS} ${QEXT_INCLUDE_OUTPUT_DIR}/${QEXT_LIB_BASE_NAME}
#    COMMAND ${CMAKE_COMMAND} -E copy ${QEXT_LIB_PRIVATE_ABSOLUTE_HEADERS} ${QEXT_INCLUDE_OUTPUT_DIR}/${QEXT_LIB_BASE_NAME}/private
    COMMENT "Copy ${QEXT_LIB_BASE_NAME} include files to output dir"
    POST_BUILD
    )



#--------------------------------------------------------------------------------
# Add lib tests and examples
#--------------------------------------------------------------------------------
if (QEXT_BUILD_TESTS OR QEXT_BUILD_ALL)
    add_subdirectory(tests)
endif()

if (QEXT_BUILD_EXAMPLES OR QEXT_BUILD_ALL)
    add_subdirectory(examples)
endif()
