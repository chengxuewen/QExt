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
# Set app link libraries
#-----------------------------------------------------------------------------------------------------------------------
if(WIN32)
    list(APPEND QEXT_APP_LINK_LIBRARIES shlwapi.lib)
endif()
if(UNIX)
    list(APPEND QEXT_APP_LINK_LIBRARIES ${CMAKE_DL_LIBS})
endif()
if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND QEXT_APP_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_APP_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets
        Qt${QEXT_QT_VERSION_MAJOR}::Network
        Qt${QEXT_QT_VERSION_MAJOR}::Qml
        Qt${QEXT_QT_VERSION_MAJOR}::Quick)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()
if(QEXT_QT_VERSION VERSION_GREATER_EQUAL 5.12)
    list(APPEND QEXT_APP_LINK_LIBRARIES Qt${QEXT_QT_VERSION_MAJOR}::QuickControls2)
endif()

include_directories(${Qt${QT_VERSION_MAJOR}Core_PRIVATE_INCLUDE_DIRS})
include_directories(${Qt${QT_VERSION_MAJOR}Quick_PRIVATE_INCLUDE_DIRS})


#-----------------------------------------------------------------------------------------------------------------------
# Set file list
#-----------------------------------------------------------------------------------------------------------------------
if(QEXT_QT_VERSION_MAJOR EQUAL 5)
    if(QEXT_QT_VERSION_MINOR EQUAL 9)
        list(APPEND QEXT_APP_SOURCES
            qt509/qmlstreamwriter.h
            qt509/qmlstreamwriter.cpp
            qt509/qmltypereader.h
            qt509/qmltypereader.cpp
            qt509/main.cpp)
        set(QEXT_APP_SOURCES_DIR qt509)
    elseif(QEXT_QT_VERSION_MINOR EQUAL 12)
        list(APPEND QEXT_APP_SOURCES
            qt512/qmlstreamwriter.h
            qt512/qmlstreamwriter.cpp
            qt512/qmltypereader.h
            qt512/qmltypereader.cpp
            qt512/main.cpp)
        set(QEXT_APP_SOURCES_DIR qt512)
    elseif(QEXT_QT_VERSION_MINOR EQUAL 15)
        list(APPEND QEXT_APP_SOURCES
            qt515/qmlstreamwriter.h
            qt515/qmlstreamwriter.cpp
            qt515/qmltypereader.h
            qt515/qmltypereader.cpp
            qt515/main.cpp)
        set(QEXT_APP_SOURCES_DIR qt515)
    else()
        message(FATAL_ERROR "qmlplugindump unknown version")
    endif()
elseif(QEXT_QT_VERSION_MAJOR EQUAL 6)
    if(QEXT_QT_VERSION_MINOR EQUAL 2)
        list(APPEND QEXT_APP_SOURCES
            qt602/qmltypereader.h
            qt602/qmltypereader.cpp
            qt602/qqmljsstreamwriter_p.h
            qt602/qqmljsstreamwriter.cpp
            qt602/main.cpp)
        set(QEXT_APP_SOURCES_DIR qt602)
    else()
        message(FATAL_ERROR "qmlplugindump unknown version")
    endif()
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

if(QEXT_APP_SOURCES)
    message(STATUS "Build in qmlplugindump app with Qt${QEXT_QT_VERSION}")
    set(QEXT_BUILDIN_QMLPLUGINDUMP ON CACHE INTERNAL "Build in qmlplugindump")
else()
    message(STATUS "Not build in qmlplugindump app!")
    set(QEXT_BUILDIN_QMLPLUGINDUMP OFF CACHE INTERNAL "Build in qmlplugindump")
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Add app target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_executable(qmlplugindump
    SOURCES
    ${QEXT_APP_SOURCES}
    OUTPUT_SUBDIR
    qmlplugindump
    INCLUDE_DIRECTORIES
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${QEXT_APP_SOURCES_DIR}>
    LIBRARIES
    ${QEXT_APP_LINK_LIBRARIES})
if(WIN32)

elseif(UNIX)

elseif(APPLE)

endif()
