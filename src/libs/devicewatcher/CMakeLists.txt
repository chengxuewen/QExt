#################################################################################
#
# Library: QExt
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
# Add lib link libraries
#--------------------------------------------------------------------------------
set(QEXT_LIB_LINK_LIBRARIES)

if(UNIX)
    list(APPEND QEXT_LIB_LINK_LIBRARIES ${CMAKE_DL_LIBS})
endif()

if(WIN32)
    list(APPEND QEXT_LIB_LINK_LIBRARIES shlwapi.lib setupapi.lib advapi32.lib user32.lib)
endif()

if(APPLE)
    find_library(COREFOUNDATION_LIB CoreFoundation)
    find_library(DISKARBITRATION_LIB DiskArbitration)
    list(APPEND QEXT_LIB_LINK_LIBRARIES ${COREFOUNDATION_LIB} ${DISKARBITRATION_LIB})
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND QEXT_LIB_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
            Qt${QEXT_QT_VERSION_MAJOR}::Core)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()


#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
qext_add_library(DeviceWatcher
        EXCEPTIONS
        SOURCES
        source/qextDeviceWatcher.cpp
        source/qextDeviceWatcher.h
        source/qextDeviceWatcher_p.h
        source/qextDeviceWatcherGlobal.h
        PRECOMPILED_HEADER
        source/qextDeviceWatcherPch.h
        PUBLIC_LIBRARIES
        ${QEXT_LIB_LINK_LIBRARIES}
        Core)

if(UNIX)
    if(QEXT_SYSTEM_LINUX)
        qext_internal_extend_target(DeviceWatcher SOURCES source/qextDeviceWatcher_linux.cpp)
    elseif(QEXT_SYSTEM_MACOS)
        qext_internal_extend_target(DeviceWatcher SOURCES source/qextDeviceWatcher_mac.cpp)
    endif()
else()
    if(QEXT_SYSTEM_WINCE)
        qext_internal_extend_target(DeviceWatcher SOURCES source/qextDeviceWatcher_wince.cpp)
    else()
        qext_internal_extend_target(DeviceWatcher SOURCES source/qextDeviceWatcher_win32.cpp)
    endif()
endif()


#--------------------------------------------------------------------------------
# Add lib tests and examples
#--------------------------------------------------------------------------------
if(QEXT_BUILD_TESTS)
    #    add_subdirectory(tests)
endif()

if(QEXT_BUILD_EXAMPLES)
    #    add_subdirectory(examples)
endif()