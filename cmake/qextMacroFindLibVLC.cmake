#################################################################################
#
# Library: QEXT
#
# Copyright (c) ChengXueWen. Contact: 1398831004@qq.com
# Copyright (C) 2014 Tadej Novak <tadej@tano.si>
# Original author: Rohit Yadav <rohityadav89@gmail.com>
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

# If it's found it sets QEXT_LIBVLC_FOUND to TRUE
# and following variables are set:
#  QEXT_LIBVLC_INCLUDE_DIR
#  QEXT_LIBVLC_LIBRARY
# FIND_PATH and FIND_LIBRARY normally search standard locations
# before the specified paths. To search non-standard paths first,
# FIND_* is invoked first with specified paths and NO_DEFAULT_PATH
# and then again with no specified paths to search the default
# locations. When an earlier FIND_* succeeds, subsequent FIND_*s
# searching for the same item do nothing.

#Put here path to custom location
#example: /home/user/vlc/include etc..
macro(qextMacroFindLibVLC)

    find_path(QEXT_LIBVLC_INCLUDE_DIR vlc/vlc.h
        HINTS "$ENV{LIBVLC_INCLUDE_PATH}"
        PATHS
        #Env
        "$ENV{LIB_DIR}/include"
        "$ENV{LIB_DIR}/include/vlc"
        #Mac OS and Contribs
        "${CMAKE_CURRENT_SOURCE_DIR}/contribs/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/contribs/include/vlc"
        "/Applications/VLC.app/Contents/MacOS/include"
        "/Applications/VLC.app/Contents/MacOS/include/vlc"
        #Unix
        "/usr/include"
        "/usr/include/vlc"
        "/usr/local/include"
        "/usr/local/include/vlc"
        #MinGW
        c:/msys/local/include
        "c:/Program Files (x86)/VideoLAN/VLC/sdk/include"
        )


    #Put here path to custom location
    #example: /home/user/vlc/lib etc..
    find_library(QEXT_LIBVLC_LIBRARY NAMES vlc libvlc libvlc.so.5
        HINTS "$ENV{LIBVLC_LIBRARY_PATH}"
        PATHS
        #Env
        "$ENV{LIB_DIR}/lib"
        #Mac OS
        "${CMAKE_CURRENT_SOURCE_DIR}/contribs/lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/contribs/plugins"
        "/Applications/VLC.app/Contents/MacOS/lib"
        "/Applications/VLC.app/Contents/MacOS/plugins"
        #Unix
        "/usr/lib"
        "/usr/lib/vlc"
        "/usr/local/lib"
        "/usr/local/lib/vlc"
        #MinGW
        c:/msys/local/lib
        "c:/Program Files (x86)/VideoLAN/VLC/sdk/lib"
        )


    find_library(QEXT_LIBVLC_CORE_LIBRARY NAMES vlccore libvlccore libvlccore.so.8
        HINTS "$ENV{LIBVLC_LIBRARY_PATH}"
        PATHS
        #Env
        "$ENV{LIB_DIR}/lib"
        #Mac OS
        "${CMAKE_CURRENT_SOURCE_DIR}/contribs/lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/contribs/plugins"
        "/Applications/VLC.app/Contents/MacOS/lib"
        "/Applications/VLC.app/Contents/MacOS/plugins"
        #Unix
        "/usr/lib"
        "/usr/lib/vlc"
        "/usr/local/lib"
        "/usr/local/lib/vlc"
        #MinGW
        c:/msys/local/lib
        "c:/Program Files (x86)/VideoLAN/VLC/sdk/lib"
        )


    if(QEXT_LIBVLC_INCLUDE_DIR AND QEXT_LIBVLC_LIBRARY AND QEXT_LIBVLC_CORE_LIBRARY)
        set(QEXT_LIBVLC_FOUND TRUE)
        set(QEXT_LIBVLC_PLUGIN_DIR ${QEXT_LIBVLC_INCLUDE_DIR}/vlc/plugins)
    else()
        if(NOT QEXT_LIBVLC_INCLUDE_DIR AND QEXT_LIBVLC_FIND_REQUIRED)
            message(FATAL_ERROR "Could not find LibVLC,${QEXT_LIBVLC_INCLUDE_DIR}")
        endif()
        if(NOT QEXT_LIBVLC_LIBRARY AND QEXT_LIBVLC_FIND_REQUIRED)
            message(FATAL_ERROR "Could not find LibVLC,${QEXT_LIBVLC_LIBRARY}")
        endif()
        if(NOT QEXT_LIBVLC_CORE_LIBRARY AND QEXT_LIBVLC_FIND_REQUIRED)
            message(FATAL_ERROR "Could not find LibVLC,${QEXT_LIBVLC_CORE_LIBRARY}")
        endif()
    endif()


    if(QEXT_LIBVLC_FOUND)
        message(STATUS "Found LibVLC include-dir path: ${QEXT_LIBVLC_INCLUDE_DIR}")
        message(STATUS "Found LibVLC library path:${QEXT_LIBVLC_LIBRARY}")
        message(STATUS "Found LibVLCcore library path:${QEXT_LIBVLC_CORE_LIBRARY}")
    else(QEXT_LIBVLC_FOUND)
        if(QEXT_LIBVLC_FIND_REQUIRED)
            message(FATAL_ERROR "Could not find LibVLC")
        endif(QEXT_LIBVLC_FIND_REQUIRED)
    endif(QEXT_LIBVLC_FOUND)

endmacro(qextMacroFindLibVLC)
