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
# Set cmake min version and policy
#--------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)



#--------------------------------------------------------------------------------
# Set project name and version
#--------------------------------------------------------------------------------
project(QEXT VERSION 0.3.5.1 LANGUAGES CXX C)
set(QEXT_VERSION_NAME ${PROJECT_VERSION})
set(QEXT_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(QEXT_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(QEXT_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(QEXT_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})
set(QEXT_VERSION ${QEXT_VERSION_MAJOR}.${QEXT_VERSION_MINOR}.${QEXT_VERSION_PATCH})
set(QEXT_SO_VERSION ${QEXT_VERSION_MAJOR}.${QEXT_VERSION_MINOR})
set(QEXT_DEBUG_POSTFIX "d")
set(QEXT_VERSION_STR "${QEXT_VERSION_MAJOR}.${QEXT_VERSION_MINOR}.${QEXT_VERSION_PATCH}")
set(QEXT_COPYRIGHT "Copyright (c) 2021 ChengXueWen 1398831004@qq.com")
set(QEXT_LICENSE "Apache 2.0 License")
set(QEXT_PRODUCT_NAME "QEXT")
set(QEXT_CXX_STANDARD 98)
math(EXPR QEXT_VERSION_CALC "${QEXT_VERSION_MAJOR}*1000 + ${QEXT_VERSION_MINOR}*100 + ${QEXT_VERSION_PATCH}")
message(STATUS "==============================================================================")
message(STATUS "----QEXT---- Project version: ${QEXT_VERSION}")
message(STATUS "----QEXT---- Project copyright: ${QEXT_COPYRIGHT}")
message(STATUS "----QEXT---- Project license: ${QEXT_LICENSE}")



#--------------------------------------------------------------------------------
# find qt and include path, set cmake moc uic rcc on
#--------------------------------------------------------------------------------
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(QEXT_BUILD_QML OFF)
set(QEXT_BUILD_QJSON OFF)

find_package(Qt4 QUIET COMPONENTS QtCore QUIET)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core QUIET)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core QUIET)
set(QEXT_QT_VERSION_MAJOR ${QT_VERSION_MAJOR})
set(QEXT_QT_VERSION_MINOR ${QT_VERSION_MINOR})
set(QEXT_QT_VERSION_PATCH ${QT_VERSION_PATCH})
set(QEXT_QT_VERSION "${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
if (QEXT_QT_VERSION_MAJOR EQUAL 4)
    if (QEXT_QT_VERSION_MINOR LESS 5)
        message(FATAL_ERROR "----QEXT---- Expected Qt4 version must greater than or equal to Qt4.5")
    endif()
    message(STATUS "----QEXT---- Expected Qt version is Qt${QEXT_QT_VERSION}")
    find_package(Qt4 REQUIRED QtCore QtGui QtTest QtNetwork)
    INCLUDE(${QT_USE_FILE})
    ADD_DEFINITIONS(${QT_DEFINITIONS})
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    if (QEXT_QT_VERSION_MINOR LESS 7)
        message(FATAL_ERROR "----QEXT---- Expected Qt5 version must greater than or equal to Qt5.7")
    endif()
    message(STATUS "----QEXT---- Expected Qt version is Qt${QEXT_QT_VERSION}")
    find_package(Qt5 COMPONENTS Core Widgets Network Quick Test REQUIRED)
    set(QEXT_CXX_STANDARD 11)
    set(QEXT_BUILD_QJSON ON)
    if (QEXT_QT_VERSION_MINOR GREATER_EQUAL 12)
        set(QEXT_BUILD_QML ON)
    endif()
elseif(QEXT_QT_VERSION_MAJOR EQUAL 6)
    message(STATUS "----QEXT---- Expected Qt version is Qt${QEXT_QT_VERSION}")
    find_package(Qt5 COMPONENTS Core Widgets Network Quick Test REQUIRED)
    set(QEXT_CXX_STANDARD 17)
    set(QEXT_BUILD_QML ON)
    set(QEXT_BUILD_QJSON ON)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

get_filename_component(QEXT_QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
get_filename_component(QEXT_QT_KIT_DIR "${QEXT_QT_BIN_DIR}" DIRECTORY)
set(QEXT_QT_LIB_DIR ${QEXT_QT_KIT_DIR}/lib)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


#--------------------------------------------------------------------------------
# Specify the C++ standard
#--------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD ${QEXT_CXX_STANDARD})
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "----QEXT---- Using C++: ${QEXT_CXX_STANDARD}")
message(STATUS "----QEXT---- Set C++ extensions: ${CMAKE_CXX_EXTENSIONS}")

set(QEXT_CXX_STANDARD_98 OFF)
set(QEXT_CXX_STANDARD_11 OFF)
set(QEXT_CXX_STANDARD_14 OFF)
set(QEXT_CXX_STANDARD_17 OFF)
set(QEXT_CXX_STANDARD_20 OFF)

if(CMAKE_CXX_STANDARD EQUAL 98)
    set(QEXT_CXX_STANDARD_98 ON)
elseif(CMAKE_CXX_STANDARD EQUAL 11)
    set(QEXT_CXX_STANDARD_98 ON)
    set(QEXT_CXX_STANDARD_11 ON)
elseif(CMAKE_CXX_STANDARD EQUAL 14)
    set(QEXT_CXX_STANDARD_98 ON)
    set(QEXT_CXX_STANDARD_11 ON)
    set(QEXT_CXX_STANDARD_14 ON)
elseif(CMAKE_CXX_STANDARD EQUAL 17)
    set(QEXT_CXX_STANDARD_98 ON)
    set(QEXT_CXX_STANDARD_11 ON)
    set(QEXT_CXX_STANDARD_14 ON)
    set(QEXT_CXX_STANDARD_17 ON)
elseif(CMAKE_CXX_STANDARD EQUAL 20)
    set(QEXT_CXX_STANDARD_98 ON)
    set(QEXT_CXX_STANDARD_11 ON)
    set(QEXT_CXX_STANDARD_14 ON)
    set(QEXT_CXX_STANDARD_17 ON)
    set(QEXT_CXX_STANDARD_20 ON)
endif()



#--------------------------------------------------------------------------------
# specify the host info
#--------------------------------------------------------------------------------
set(QEXT_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})
set(QEXT_SYSTEM_VERSION ${CMAKE_SYSTEM_VERSION})
set(QEXT_SYSTEM_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR})
set(QEXT_CXX_COMPILER_ID ${CMAKE_CXX_COMPILER_ID})

# specify system
if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(QEXT_SYSTEM_LINUX ON)
elseif(CMAKE_SYSTEM_NAME STREQUAL Darwin)
    set(QEXT_SYSTEM_MAC ON)
    set(QEXT_SYSTEM_DARWIN ON)
elseif(CMAKE_SYSTEM_NAME STREQUAL Windows)
    set(QEXT_SYSTEM_WIN ON)
elseif(CMAKE_SYSTEM_NAME STREQUAL WindowsCE)
    set(QEXT_SYSTEM_WIN ON)
    set(QEXT_SYSTEM_WINCE ON)
elseif(CMAKE_SYSTEM_NAME STREQUAL QNX)
    set(QEXT_SYSTEM_QNX ON)
else()
    set(QEXT_SYSTEM_UNKNOWN ON)
endif()

# specify compiler
if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(QEXT_CXX_COMPILER_MSVC ON)
elseif(CMAKE_CXX_COMPILER_ID MATCHES Intel)
    set(QEXT_CXX_COMPILER_INTEL ON)
elseif(CMAKE_CXX_COMPILER_ID MATCHES AppleClang)
    set(QEXT_CXX_COMPILER_CLANG_APPLE ON)
    set(QEXT_CXX_COMPILER_CLANG ON)
elseif(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    set(QEXT_CXX_COMPILER_CLANG ON)
elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(QEXT_CXX_COMPILER_GNU ON)
else()
    set(QEXT_CXX_COMPILER_UNKNOWN Unknown)
endif()

# specify arch bit
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(QEXT_ARCH_64 ON)
else()
    set(QEXT_ARCH_32 ON)
endif()

# specify processor
if (CMAKE_SYSTEM_PROCESSOR MATCHES i386)
    set(QEXT_SYSTEM_PROCESSOR_I386 ON)
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES i686)
    set(QEXT_SYSTEM_PROCESSOR_I686 ON)
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES x86_64)
    set(QEXT_SYSTEM_PROCESSOR_X86_64 ON)
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES AMD64)
    set(QEXT_SYSTEM_PROCESSOR_AMD64 ON)
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES ARM)
    set(QEXT_SYSTEM_PROCESSOR_ARM ON)
else ()
    set(QEXT_SYSTEM_PROCESSOR_UNKNOWN Unknown)
endif ()



#--------------------------------------------------------------------------------
# Specify the output dir
#--------------------------------------------------------------------------------
set(QEXT_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(QEXT_PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR})
if (NOT QEXT_APP_OUTPUT_DIR)
    set(QEXT_APP_OUTPUT_DIR "${PROJECT_BINARY_DIR}/bin")
endif()

if (NOT QEXT_LIB_OUTPUT_DIR)
    set(QEXT_LIB_OUTPUT_DIR "${PROJECT_BINARY_DIR}/lib")
endif()

if (NOT QEXT_QTLIB_OUTPUT_DIR)
    set(QEXT_QTLIB_OUTPUT_DIR "${PROJECT_BINARY_DIR}/lib/qt")
endif()

if (NOT QEXT_SYSLIB_OUTPUT_DIR)
    set(QEXT_SYSLIB_OUTPUT_DIR "${PROJECT_BINARY_DIR}/lib/sys")
endif()

if (NOT QEXT_PLUGIN_OUTPUT_DIR)
    set(QEXT_PLUGIN_OUTPUT_DIR "${PROJECT_BINARY_DIR}/plugin")
endif()

if (NOT QEXT_QML_OUTPUT_DIR)
    set(QEXT_QML_OUTPUT_DIR "${PROJECT_BINARY_DIR}/qml")
endif()

if (NOT QEXT_INCLUDE_OUTPUT_DIR)
    set(QEXT_INCLUDE_OUTPUT_DIR "${PROJECT_BINARY_DIR}/include")
endif()

if (NOT QEXT_EXAMPLE_OUTPUT_DIR)
    set(QEXT_EXAMPLE_OUTPUT_DIR "${PROJECT_BINARY_DIR}/example")
endif()

if (NOT QEXT_TEST_OUTPUT_DIR)
    set(QEXT_TEST_OUTPUT_DIR "${PROJECT_BINARY_DIR}/test")
endif()

# here we specify the installation directory
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/install" CACHE PATH  "QEXT install prefix" FORCE)
endif()



#--------------------------------------------------------------------------------
# Configure a header file to pass some of the CMake settings to the source code
#--------------------------------------------------------------------------------
set(QEXT_CONFIG_HPP_FILE_DIR ${QEXT_INCLUDE_OUTPUT_DIR})
set(QEXT_CONFIG_HPP_FILE_PATH ${QEXT_CONFIG_HPP_FILE_DIR}/qextconfig.h)
configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/qextconfig.h.in"
    "${QEXT_CONFIG_HPP_FILE_PATH}"
    )



#--------------------------------------------------------------------------------
# Add CMake function(s) and macro(s)
#--------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
include(qextFunctionActivatePrecompiledHeaders)
include(qextFunctionSetCompilerWarnings)
include(qextFunctionQmlPlugin)
include(qextMacroBuildDoxygen)
include(qextMacroFindQmlPluginDump)



#--------------------------------------------------------------------------------
# Set option
#--------------------------------------------------------------------------------
option(QEXT_BUILD_SHARED_LIBS "Build shared library" ON)
option(QEXT_BUILD_TESTS "Build tests" ON)
option(QEXT_BUILD_EXAMPLES "Build examples" ON)
option(QEXT_BUILD_PLUGINS "Build plugins" OFF)
option(QEXT_BUILD_QML_PLUGINS "Build qml plugins" OFF)
option(QEXT_BUILD_USE_PCH "Enable this to build use precompiled header files for compilation" ON)
option(QEXT_BUILD_DOCUMENTATION "Enable this to build the documentation" OFF)
option(QEXT_BUILD_COMPILER_WARNING "Build target with compiler warnings" OFF)
option(QEXT_BUILD_ALL "Build all artifacts" OFF)

if(QEXT_BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build as shared libraries")
    message(STATUS "----QEXT---- Build as shared libraries")
else()
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build as static libraries")
    message(STATUS "----QEXT---- Build as static libraries")
endif()

# one precompiled headers cannot be used for multiple ninja targets
# thats why we have to disable this option, when MTK_BUILD_SHARED_LIBS is OFF
# (every target will create the same PCH.pch file)
# to get it working, we need the feature to enable different source properties
# for different targets
if (QEXT_BUILD_USE_PCH)
    if (!QEXT_BUILD_SHARED_LIBS)
        set(QEXT_BUILD_USE_PCH FALSE)
        message(STATUS "----QEXT---- Set QEXT_BUILD_USE_PCH as FALSE")
    endif()
endif()

# enable build doc
if (QEXT_BUILD_DOCUMENTATION)
    qextMacroBuildDoxygen()
    message(STATUS "----QEXT---- Build with the documentation")
else()
    message(STATUS "----QEXT---- Build with no documentation")
endif()

if(QEXT_BUILD_TESTS OR QEXT_BUILD_ALL)
    enable_testing()
endif()



#--------------------------------------------------------------------------------
# add subdirectory
#--------------------------------------------------------------------------------
add_subdirectory(thirdparty/lua)
#add_subdirectory(thirdparty/luajit)
#add_subdirectory(thirdparty/nanopainter)
#add_subdirectory(thirdparty/qt-mvvm-0.2.0)
#add_subdirectory(thirdparty/qjson-0.9.0)
add_subdirectory(src/applications)
add_subdirectory(src/libs)

