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
set(QEXT_APP_BASE_NAME qext_tool_qmlplugindump)
set(EXECUTABLE_OUTPUT_PATH ${QEXT_OUTPUT_APP_DIR})
set(QEXT_QML_IMPORT_PATH ${QML_IMPORT_PATH} ${QEXT_OUTPUT_QML_DIR})
set(QML_IMPORT_PATH "${QEXT_QML_IMPORT_PATH}" CACHE STRING "Qt Creator extra qml import paths")



#--------------------------------------------------------------------------------
# Set app link libraries
#--------------------------------------------------------------------------------
if(UNIX)
    list(APPEND QEXT_APP_LINK_LIBRARIES ${CMAKE_DL_LIBS})
endif()

if(WIN32)
    list(APPEND QEXT_APP_LINK_LIBRARIES shlwapi.lib)
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
        Qt${QEXT_QT_VERSION_MAJOR}::Quick
        Qt${QEXT_QT_VERSION_MAJOR}::QuickControls2
        )
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

include_directories(${Qt${QT_VERSION_MAJOR}Core_PRIVATE_INCLUDE_DIRS})
include_directories(${Qt${QT_VERSION_MAJOR}Quick_PRIVATE_INCLUDE_DIRS})



#--------------------------------------------------------------------------------
# Set file list
#--------------------------------------------------------------------------------
if(QEXT_QT_VERSION_MAJOR EQUAL 5)
    if(QEXT_QT_VERSION_MINOR EQUAL 9)
        list(APPEND QEXT_APP_SOURCES
            qt509/qmlstreamwriter.h
            qt509/qmlstreamwriter.cpp
            qt509/qmltypereader.h
            qt509/qmltypereader.cpp
            qt509/main.cpp
            )
    elseif(QEXT_QT_VERSION_MINOR EQUAL 12)
        list(APPEND QEXT_APP_SOURCES
            qt512/qmlstreamwriter.h
            qt512/qmlstreamwriter.cpp
            qt512/qmltypereader.h
            qt512/qmltypereader.cpp
            qt512/main.cpp
            )
    elseif(QEXT_QT_VERSION_MINOR EQUAL 15)
        list(APPEND QEXT_APP_SOURCES
            qt515/qmlstreamwriter.h
            qt515/qmlstreamwriter.cpp
            qt515/qmltypereader.h
            qt515/qmltypereader.cpp
            qt515/main.cpp
            )
    else()
        message(FATAL_ERROR "----QEXT---- qmlplugindump unknown version")
    endif()
elseif(QEXT_QT_VERSION_MAJOR EQUAL 6)
    message(FATAL_ERROR "----QEXT---- qmlplugindump unknown version")
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

if(QEXT_APP_SOURCES)
    message(STATUS "----QEXT---- Build in qmlplugindump app with Qt${QEXT_QT_VERSION}")
    set(QEXT_BUILDIN_QMLPLUGINDUMP ON CACHE INTERNAL "Build in qmlplugindump")
else(QEXT_APP_SOURCES)
    message(STATUS "----QEXT---- Not build in qmlplugindump app!")
    set(QEXT_BUILDIN_QMLPLUGINDUMP OFF CACHE INTERNAL "Build in qmlplugindump")
endif(QEXT_APP_SOURCES)



#--------------------------------------------------------------------------------
# Add app target
#--------------------------------------------------------------------------------
add_executable(${QEXT_APP_BASE_NAME} ${QEXT_APP_SOURCES})
if (QEXT_BUILD_COMPILER_WARNING)
    qextFunctionSetCompilerWarnings(${QEXT_APP_BASE_NAME})
endif()
target_link_libraries(${QEXT_APP_BASE_NAME} PUBLIC ${QEXT_APP_LINK_LIBRARIES})
target_include_directories(${QEXT_APP_BASE_NAME} PUBLIC
    $<BUILD_INTERFACE:${QEXT_CONFIG_HPP_FILE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
    )
# set target properties
set_target_properties(${QEXT_APP_BASE_NAME} PROPERTIES
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    )
# copy dependency libs
if(WIN32)
    if(CMAKE_BUILD_TYPE MATCHES Release)
        set(QEXT_APP_DEPLOY_TYPE --release)
    else()
        set(QEXT_APP_DEPLOY_TYPE --debug)
    endif()
    find_program(QEXT_QT_WINDEPLOY NAMES windeployqt.exe PATHS ${QEXT_QT_BIN_DIR} NO_DEFAULT_PATH)
    if(QEXT_QT_WINDEPLOY EQUAL "QEXT_QT_WINDEPLOY-NOTFOUND")
        message(FATAL_ERROR "----QEXT---- Not find Qt windeployqt.exe")
    else()
        message(STATUS "----QEXT---- Qt${QEXT_QT_VERSION_MAJOR} windeployqt.exe found")
        add_custom_command(
            TARGET ${QEXT_APP_BASE_NAME}
            COMMAND ${QEXT_QT_WINDEPLOY} ${QEXT_APP_DEPLOY_TYPE} --qmldir ${QEXT_QT_KIT_DIR}/qml ${EXECUTABLE_OUTPUT_PATH}/${QEXT_APP_BASE_NAME}.exe --verbose 2
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${QEXT_QT_KIT_DIR}/plugins/platforms ${EXECUTABLE_OUTPUT_PATH}/platforms
            COMMENT "Run windeployqt to deploy ${QEXT_APP_BASE_NAME}"
            POST_BUILD
            )
    endif()
endif()
