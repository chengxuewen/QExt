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
# Set cmake min version and policy
#-----------------------------------------------------------------------------------------------------------------------
message(STATUS "===============================================QExt===================================================")
cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0075 NEW) # use CMAKE_REQUIRED_LIBRARIES
cmake_policy(SET CMP0083 NEW) # use check_pie_supported
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 4.0)
    cmake_policy(SET CMP0177 NEW) # use install() DESTINATION
endif()
if(${CMAKE_VERSION} VERSION_LESS 3.24)
    set(QT_CREATOR_SKIP_MAINTENANCE_TOOL_PROVIDER ON)
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Set project name and version
#-----------------------------------------------------------------------------------------------------------------------
project(QExt VERSION 1.4.1.1 LANGUAGES CXX C)
set(QEXT_VERSION_NAME ${PROJECT_VERSION})
set(QEXT_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(QEXT_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(QEXT_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(QEXT_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})
set(QEXT_VERSION ${QEXT_VERSION_MAJOR}.${QEXT_VERSION_MINOR}.${QEXT_VERSION_PATCH})
set(QEXT_SO_VERSION ${QEXT_VERSION_MAJOR}.${QEXT_VERSION_MINOR})
set(QEXT_VERSION_STR "${QEXT_VERSION_MAJOR}.${QEXT_VERSION_MINOR}.${QEXT_VERSION_PATCH}")
set(QEXT_COPYRIGHT "Copyright (c) 2021~Present ChengXueWen 1398831004@qq.com")
set(QEXT_LICENSE "MIT License")
set(QEXT_PRODUCT_NAME "QExt")
math(EXPR QEXT_VERSION_CALC "${QEXT_VERSION_MAJOR}*1000 + ${QEXT_VERSION_MINOR}*100 + ${QEXT_VERSION_PATCH}")
message(STATUS "Project version: ${QEXT_VERSION}")
message(STATUS "Project copyright: ${QEXT_COPYRIGHT}")
message(STATUS "Project license: ${QEXT_LICENSE}")


#-----------------------------------------------------------------------------------------------------------------------
# Decide whether output should be verbose or not. # Default to verbose (--log-level=STATUS) in a developer-build and
# non-verbose (--log-level=NOTICE) otherwise. If a custom CMAKE_MESSAGE_LOG_LEVEL was specified, it takes priority.
# Passing an explicit --log-level=Foo has the highest priority.
#-----------------------------------------------------------------------------------------------------------------------
if(NOT CMAKE_MESSAGE_LOG_LEVEL)
    if(QEXT_FEATURE_DEV_BUILD)
        set(CMAKE_MESSAGE_LOG_LEVEL "STATUS")
    else()
        set(CMAKE_MESSAGE_LOG_LEVEL "NOTICE")
    endif()
endif()
set(CMAKE_MESSAGE_LOG_LEVEL "DEBUG")


#-----------------------------------------------------------------------------------------------------------------------
# find qt and include path, set cmake moc uic rcc on
#-----------------------------------------------------------------------------------------------------------------------
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(QEXT_QT_HAS_QJSON OFF)
find_package(Qt4 QUIET COMPONENTS QtCore QUIET)
if(NOT QT_FOUND)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core QUIET)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core QUIET)
endif()
set(QEXT_QT_VERSION_MAJOR ${QT_VERSION_MAJOR})
set(QEXT_QT_VERSION_MINOR ${QT_VERSION_MINOR})
set(QEXT_QT_VERSION_PATCH ${QT_VERSION_PATCH})
set(QEXT_QT_VERSION "${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    if(QEXT_QT_VERSION_MINOR LESS 8)
        message(FATAL_ERROR "Expected Qt4 version must greater than or equal to Qt4.8")
    endif()
    message(STATUS "Expected Qt version is Qt${QEXT_QT_VERSION}")
    find_package(Qt4 REQUIRED QtCore QtGui QtXml QtSvg QtSql QtTest QtNetwork)
    include(${QT_USE_FILE})
    add_definitions(${QT_DEFINITIONS})
    find_package(Qt4 COMPONENTS QtOpenGL)
    set(QEXT_QT_OPENGL_FOUND ${QT_QTOPENGL_FOUND})
    set(QEXT_QT_SERIALPORT_FOUND OFF)
    set(QEXT_QT_HAS_QML OFF)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    message(STATUS "Expected Qt version is Qt${QEXT_QT_VERSION}")
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS
        Core Network Test PrintSupport Xml Svg Sql Gui Widgets Quick QuickControls2 OpenGL REQUIRED)
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS
        OpenGL Concurrent SerialPort QUIET)
    if(UNIX)
        find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS X11Extras QUIET)
        set(QEXT_QT_X11EXTRAS_FOUND ${Qt${QEXT_QT_VERSION_MAJOR}X11Extras_FOUND})
    else()
        set(QEXT_QT_X11EXTRAS_FOUND OFF)
    endif()
    set(QEXT_QT_OPENGL_FOUND ${Qt${QEXT_QT_VERSION_MAJOR}OpenGL_FOUND})
    set(QEXT_QT_CONCURRENT_FOUND ${Qt${QEXT_QT_VERSION_MAJOR}Concurrent_FOUND})
    set(QEXT_QT_SERIALPORT_FOUND ${Qt${QEXT_QT_VERSION_MAJOR}SerialPort_FOUND})
    set(QEXT_QT_EXPORT_NAMESPACE Qt5)
    set(QEXT_QT_HAS_QJSON ON)
    if(QEXT_QT_VERSION_MINOR GREATER_EQUAL 9)
        set(QEXT_QT_HAS_QML ON)
    else()
        set(QEXT_QT_HAS_QML OFF)
    endif()
elseif(QEXT_QT_VERSION_MAJOR EQUAL 6)
    message(STATUS "Expected Qt version is Qt${QEXT_QT_VERSION}")
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS
        Core Core5Compat Network Test PrintSupport Xml Svg Sql Gui Widgets Quick QuickControls2 REQUIRED)
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS
        OpenGL Concurrent SerialPort OpenGLWidgets QuickEffectsPrivate QUIET)
    if(UNIX)
        find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS X11Extras QUIET)
        set(QEXT_QT_X11EXTRAS_FOUND ${Qt${QEXT_QT_VERSION_MAJOR}X11Extras_FOUND})
    else()
        set(QEXT_QT_X11EXTRAS_FOUND OFF)
    endif()
    set(QEXT_QT_OPENGL_FOUND ${Qt${QEXT_QT_VERSION_MAJOR}OpenGL_FOUND})
    set(QEXT_QT_CONCURRENT_FOUND ${Qt${QEXT_QT_VERSION_MAJOR}Concurrent_FOUND})
    set(QEXT_QT_SERIALPORT_FOUND ${Qt${QEXT_QT_VERSION_MAJOR}SerialPort_FOUND})
    set(QEXT_QT_OPENGLWIDGET_FOUND ${Qt${QEXT_QT_VERSION_MAJOR}OpenGLWidgets_FOUND})
    set(QEXT_QT_EXPORT_NAMESPACE Qt6)
    set(QEXT_QT_HAS_QJSON ON)
    set(QEXT_QT_HAS_QML ON)
    if(QT_KNOWN_POLICY_QTP0001)
        qt_policy(SET QTP0001 NEW)
    endif()
else()
    message(FATAL_ERROR "Not find Qt package")
endif()
set(QEXT_USE_QT${QEXT_QT_VERSION_MAJOR} ON)
set(QEXT_USE_QT${QEXT_QT_VERSION_MAJOR}${QEXT_QT_VERSION_MINOR} ON)
set(QEXT_USE_QT${QEXT_QT_VERSION_MAJOR}${QEXT_QT_VERSION_MINOR}${QEXT_QT_VERSION_PATCH} ON)
set(QEXT_QT_VERSION_MAJOR_LIST 4 5 6)
foreach(major ${QEXT_QT_VERSION_MAJOR_LIST})
    if (${QEXT_QT_VERSION_MAJOR} GREATER_EQUAL ${major})
        set(QEXT_SINCE_QT${major} ON)
    else()
        set(QEXT_SINCE_QT${major} OFF)
    endif()
endforeach()
if(ANDROID AND ("${QT_VERSION}" VERSION_LESS "6.5"))
    set(QEXT_QT_HAS_QML OFF)
endif()

get_filename_component(QEXT_QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
get_filename_component(QEXT_QT_KIT_DIR "${QEXT_QT_BIN_DIR}" DIRECTORY)
set(QEXT_QT_LIB_DIR ${QEXT_QT_KIT_DIR}/lib)
set(QEXT_QT_QML_DIR ${QEXT_QT_KIT_DIR}/qml)
if(NOT EXISTS "${QT_HOST_PATH}")
    set(QT_HOST_PATH ${QEXT_QT_KIT_DIR})
endif()
message(STATUS "QT_HOST_PATH is set to:${QT_HOST_PATH}")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


#-----------------------------------------------------------------------------------------------------------------------
# Specify the C++ standard and flags
#-----------------------------------------------------------------------------------------------------------------------
if(NOT CMAKE_CXX_STANDARD OR "${CMAKE_CXX_STANDARD}" STREQUAL "")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" QEXT_COMPILER_SUPPORTS_CXX11)
    CHECK_CXX_COMPILER_FLAG("-std=c++14" QEXT_COMPILER_SUPPORTS_CXX14)
    CHECK_CXX_COMPILER_FLAG("-std=c++17" QEXT_COMPILER_SUPPORTS_CXX17)
    CHECK_CXX_COMPILER_FLAG("-std=c++20" QEXT_COMPILER_SUPPORTS_CXX20)
    CHECK_CXX_COMPILER_FLAG("-std=c++23" QEXT_COMPILER_SUPPORTS_CXX23)
    if(QEXT_COMPILER_SUPPORTS_CXX23)
        set(QEXT_DEFAULT_CXX_STANDARD 23)
    elseif(QEXT_COMPILER_SUPPORTS_CXX20)
        set(QEXT_DEFAULT_CXX_STANDARD 20)
    elseif(QEXT_COMPILER_SUPPORTS_CXX17)
        set(QEXT_DEFAULT_CXX_STANDARD 17)
    elseif(QEXT_COMPILER_SUPPORTS_CXX14)
        set(QEXT_DEFAULT_CXX_STANDARD 14)
    elseif(QEXT_COMPILER_SUPPORTS_CXX11)
        set(QEXT_DEFAULT_CXX_STANDARD 11)
    else()
        set(QEXT_DEFAULT_CXX_STANDARD 98)
    endif()
    message(STATUS "Support C++ standard: ${QEXT_DEFAULT_CXX_STANDARD}")
    set(QEXT_CXX_STANDARD "${QEXT_DEFAULT_CXX_STANDARD}" CACHE STRING "Set cxx standard(98/11/14/17/20/23)!")
    set(CMAKE_CXX_STANDARD ${QEXT_CXX_STANDARD})
else()
    set(QEXT_CXX_STANDARD "${CMAKE_CXX_STANDARD}" CACHE STRING "Set cxx standard(98/11/14/17/20/23)!" FORCE)
endif()
if("${CMAKE_CXX_STANDARD}" STREQUAL "23")
    set(QEXT_CXX_STANDARD23 ON)
    set(QEXT_CXX_STANDARD20 ON)
    set(QEXT_CXX_STANDARD17 ON)
    set(QEXT_CXX_STANDARD14 ON)
    set(QEXT_CXX_STANDARD11 ON)
elseif("${CMAKE_CXX_STANDARD}" STREQUAL "20")
    set(QEXT_CXX_STANDARD20 ON)
    set(QEXT_CXX_STANDARD17 ON)
    set(QEXT_CXX_STANDARD14 ON)
    set(QEXT_CXX_STANDARD11 ON)
elseif("${CMAKE_CXX_STANDARD}" STREQUAL "17")
    set(QEXT_CXX_STANDARD17 ON)
    set(QEXT_CXX_STANDARD14 ON)
    set(QEXT_CXX_STANDARD11 ON)
elseif("${CMAKE_CXX_STANDARD}" STREQUAL "14")
    set(QEXT_CXX_STANDARD14 ON)
    set(QEXT_CXX_STANDARD14 ON)
    set(QEXT_CXX_STANDARD11 ON)
elseif("${CMAKE_CXX_STANDARD}" STREQUAL "11")
    set(QEXT_CXX_STANDARD11 ON)
endif()
if("${CMAKE_CXX_EXTENSIONS}" STREQUAL "")
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()
if("${CMAKE_CXX_STANDARD_REQUIRED}" STREQUAL "")
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
message(STATUS "Using C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "Set C++ extensions: ${CMAKE_CXX_EXTENSIONS}")
message(STATUS "Set C++ standard: ${CMAKE_CXX_STANDARD_REQUIRED}")

if(WIN32)
    if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
        # open bigobj flags in msvc compiler(bigobj)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
    elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
        # open bigobj flags in gnu/mingw compiler(File too big/too many sections)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
    endif()
    # Set CMAKE_OBJECT_PATH_MAX, avoid The maximum full path to an object file warning.
    set(CMAKE_OBJECT_PATH_MAX 2048)
endif()

## Position independent code:
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Does the linker support position independent code?
include(CheckPIESupported)
check_pie_supported()

# Do not relink dependent libraries when no header has changed:
set(CMAKE_LINK_DEPENDS_NO_SHARED ON)


#-----------------------------------------------------------------------------------------------------------------------
# Set build type
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_DEFAULT_BUILD_TYPE "Release")
if(QEXT_FEATURE_DEV_BUILD)
    set(QEXT_DEFAULT_BUILD_TYPE "Debug")
endif()
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to '${QEXT_DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${QEXT_DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE
        PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo") # Set the possible values for cmake-gui.
endif()
message(STATUS "CMAKE_BUILD_TYPE was set to: '${CMAKE_BUILD_TYPE}'")
if(CMAKE_CONFIGURATION_TYPES)
    message(STATUS "CMAKE_CONFIGURATION_TYPES was set to: '${CMAKE_BUILD_TYPE}'")
    set(CMAKE_CONFIGURATION_TYPES "${CMAKE_BUILD_TYPE}" CACHE INTERNAL "Force disable CMAKE_CONFIGURATION_TYPES." FORCE)
endif()

# Override the generic debug postfixes above with custom debug postfixes (even in a single config build) to follow the
# conventions we had. lib/libQExtCore_debug.6.3.0.dylib
if(WIN32)
    if(MINGW)
        # On MinGW we don't have "d" suffix for debug libraries like on Linux, unless we're building debug and release
        # libraries in one go.
        if(QEXT_GENERATOR_IS_MULTI_CONFIG)
            set(CMAKE_DEBUG_POSTFIX "d")
        endif()
    else()
        # set(CMAKE_DEBUG_POSTFIX "d")
    endif()
elseif(APPLE)
    set(CMAKE_DEBUG_POSTFIX "_debug")
    set(CMAKE_FRAMEWORK_MULTI_CONFIG_POSTFIX_DEBUG "_debug")
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Detect prefix and install
#-----------------------------------------------------------------------------------------------------------------------
# Pre-calculate the developer_build feature if it's set by the user via INPUT_QEXT_FEATURE_DEV_BUILD
if(NOT DEFINED QEXT_FEATURE_DEV_BUILD)
    if(NOT DEFINED INPUT_QEXT_FEATURE_DEV_BUILD)
        set(QEXT_FEATURE_DEV_BUILD ON)
    else()
        set(QEXT_FEATURE_DEV_BUILD ${INPUT_QEXT_FEATURE_DEV_BUILD})
    endif()
endif()

# Pre-calculate the no_prefix feature if it's set by configure via INPUT_QEXT_FEATURE_NO_PREFIX.
# This needs to be done before configure.cmake is processed.
if(NOT DEFINED QEXT_FEATURE_NO_PREFIX)
    if(NOT DEFINED INPUT_QEXT_FEATURE_NO_PREFIX)
        set(QEXT_FEATURE_NO_PREFIX ON)
    else()
        set(QEXT_FEATURE_NO_PREFIX ${INPUT_QEXT_FEATURE_NO_PREFIX})
    endif()
endif()

set(QEXT_BINARY_DIR "${QExt_BINARY_DIR}")
# here we specify the installation directory
# Handle both FEATURE_ and QEXT_FEATURE_ cases when they are specified on the command line explicitly.
# It's possible for one to be set, but not the other, because core/configure.cmake is not processed by this point.
if((QEXT_FEATURE_DEV_BUILD OR QEXT_FEATURE_NO_PREFIX) AND NOT CMAKE_STAGING_PREFIX)
    # Handle non-prefix builds by setting the CMake install prefix to point to QEXT's build dir.
    set(QEXT_DEFAULT_PREFIX "${QEXT_BINARY_DIR}/install")
else()
    if(CMAKE_HOST_WIN32)
        set(QEXT_DEFAULT_PREFIX "C:/QExt/")
    else()
        set(QEXT_DEFAULT_PREFIX "/usr/local/")
    endif()
    string(APPEND QEXT_DEFAULT_PREFIX "QExt${QEXT_VERSION}")
endif()

if(NOT "${CMAKE_INSTALL_PREFIX}" STREQUAL "")
    set(QEXT_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
else()
    set(QEXT_INSTALL_PREFIX "${QEXT_DEFAULT_PREFIX}")
endif()

if(NOT "${CMAKE_STAGING_PREFIX}" STREQUAL "")
    set(QEXT_STAGING_PREFIX "${CMAKE_STAGING_PREFIX}")
else()
    set(QEXT_STAGING_PREFIX "${QEXT_DEFAULT_PREFIX}")
endif()

if(CMAKE_STAGING_PREFIX)
    set(QEXT_PREFIX "${CMAKE_STAGING_PREFIX}")
else()
    set(QEXT_PREFIX "${QEXT_INSTALL_PREFIX}")
endif()

if(QEXT_PREFIX STREQUAL QEXT_BINARY_DIR)
    set(QEXTT_DEFAULT_BUILD_INSTALL OFF)
else()
    set(QEXTT_DEFAULT_BUILD_INSTALL ON)
endif()

if(QEXT_FEATURE_DEV_BUILD)
    if(DEFINED QEXT_CMAKE_EXPORT_COMPILE_COMMANDS)
        set(CMAKE_EXPORT_COMPILE_COMMANDS ${QEXT_CMAKE_EXPORT_COMPILE_COMMANDS})
    else()
        set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    endif()
    set(QEXT_DEFAULT_BUILD_TESTS ON)
    set(QEXT_DEFAULT_BUILD_BENCHMARKS ON)
    set(QEXT_DEFAULT_BUILD_WARNINGS_AS_ERRORS ON)

    # Tests are not built by default with qmake for iOS and friends, and thus the overall build
    # tends to fail. Disable them by default when targeting uikit.
    if(UIKIT OR ANDROID)
        set(QEXT_DEFAULT_BUILD_TESTS OFF)
    endif()

    # Disable benchmarks for single configuration generators which do not build
    # with release configuration.
    if(CMAKE_BUILD_TYPE AND CMAKE_BUILD_TYPE STREQUAL Debug)
        set(QEXT_DEFAULT_BUILD_BENCHMARKS OFF)
    endif()
else()
    set(QEXT_DEFAULT_BUILD_TESTS OFF)
    set(QEXT_DEFAULT_BUILD_BENCHMARKS OFF)
    set(QEXT_DEFAULT_BUILD_WARNINGS_AS_ERRORS OFF)
endif()
message(STATUS "QExt Install prefix set as '${QEXT_INSTALL_PREFIX}'.")


#-----------------------------------------------------------------------------------------------------------------------
# Fetch processor count
#-----------------------------------------------------------------------------------------------------------------------
include(ProcessorCount)
processorcount(QEXT_PROCESSOR_COUNT)
set(QEXT_NUMBER_OF_ASYNC_JOBS ${QEXT_PROCESSOR_COUNT})


#-----------------------------------------------------------------------------------------------------------------------
# Add CMake function(s) and macro(s)
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_CMAKE_DIR "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_MODULE_PATH ${QEXT_CMAKE_DIR} ${CMAKE_MODULE_PATH})
include(QExtPrecompiledHeadersHelpers)
include(QExtScopeFinalizerHelpers)
include(QExtPublicWalkLibsHelpers)
include(QExtPublicTargetHelpers)
include(QExtFlagHandlingHelpers)
include(QExtSubdirectoryHelpers)
include(QExtCMakeVersionHelpers)
include(QExtGlobalStateHelpers)
include(QExtSyncIncludeHelpers)
include(QExtFindPackageHelpers)
include(QExtPrecompiledHelpers)
include(QExtExecutableHelpers)
include(QExtSeparateDebugInfo)
include(QExtPublicToolHelpers)
include(QExtConfigureHelpers)
include(QExtFrameworkHelpers)
include(QExtPkgConfigHelpers)
include(QExtDeployQtHelpers)
include(QExtLibraryHelpers)
include(QExtInstallHelpers)
include(QExtQtToolsHelpers)
include(QExtAndroidHelpers)
include(QExtAutogenHelpers)
include(QExtModuleHelpers)
include(QExtPluginHelpers)
include(QExtTargetHelpers)
include(QExtOptionHelpers)
include(QExtCMakeHelpers)
include(QExtRpathHelpers)
include(QExtTestHelpers)
include(QExtQmlHelpers)


#-----------------------------------------------------------------------------------------------------------------------
# Set build options
#-----------------------------------------------------------------------------------------------------------------------
qext_option(QEXT_BUILD_ALL "Enable this to build all artifacts" OFF)
qext_option(QEXT_BUILD_SHARED_LIBS "Enable this to build as dynamically" ON
    SET BUILD_SHARED_LIBS)
qext_option(QEXT_BUILD_USE_PCH "Enable this to build use precompiled header files for compilation" ON
    DEPENDS BUILD_SHARED_LIBS)
qext_option(QEXT_BUILD_COMPILER_WARNING "Enable this to build target with compiler warnings" OFF)
qext_option(QEXT_BUILD_WARNINGS_ARE_ERRORS "Enable this to build with warnings as errors"
    ${QEXT_DEFAULT_BUILD_WARNINGS_AS_ERRORS})
qext_option(QEXT_BUILD_BENCHMARKS "Enable this to build the benchmarks" ${QEXT_DEFAULT_BUILD_BENCHMARKS}
    SET QEXT_DEFAULT_BUILD_TESTS)
qext_option(QEXT_BUILD_DOCS "Enable this to build the documentation" OFF)
qext_option(QEXT_BUILD_QMLS "Enable this to build qmls" OFF
    DEPENDS QEXT_QT_HAS_QML
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_BUILD_TESTS "Enable this to build tests" OFF
    DEPENDS (NOT CMAKE_CROSSCOMPILING)
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_BUILD_EXAMPLES "Enable this to build examples" OFF
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_BUILD_INSTALL "Enable this to build the installer" ${QEXTT_DEFAULT_BUILD_INSTALL}
    OR_CONDITION QEXT_BUILD_ALL)

qext_option(QEXT_ENABLE_LIB_GUI "Enable this to build the gui lib" OFF
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_LIB_PLOT "Enable this to build the plot lib" OFF
    DEPENDS ("${QEXT_QT_VERSION}" VERSION_LESS "6")
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_LIB_LOGGING "Enable this to build the logging lib" OFF
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_LIB_PATTERNS "Enable this to build the patterns lib" OFF
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_LIB_BLUEPRINT "Enable this to build the blueprint lib" OFF
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_LIB_BREAKPAD "Enable this to build the breakpad lib" OFF
    DEPENDS WIN32 OR UNIX OR APPLE
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_LIB_MEDIA "Enable this to build the media lib" OFF
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_LIB_OPENSSL "Enable this to build the openssl lib" OFF
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_LIB_WIDGETS "Enable this to build the widgets lib" OFF
    DEPENDS QEXT_ENABLE_LIB_GUI AND ("${QEXT_QT_VERSION}" VERSION_LESS "6")
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_LIB_DAVIEW "Enable this to build the daview lib" OFF
    DEPENDS QEXT_ENABLE_LIB_PLOT AND QEXT_ENABLE_LIB_WIDGETS
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_LIB_FONTICON "Enable this to build the fonticon lib" OFF
    DEPENDS ("${QEXT_QT_VERSION}" VERSION_GREATER_EQUAL "5")
    OR_CONDITION QEXT_BUILD_ALL OR QEXT_QT_HAS_QML)
qext_option(QEXT_ENABLE_LIB_KEYBOARD "Enable this to build the keyboard lib" OFF
    DEPENDS ("${QEXT_QT_VERSION}" VERSION_LESS "6")
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_LIB_GRAPHICS "Enable this to build the graphics lib" OFF
    DEPENDS ("${QEXT_QT_VERSION}" VERSION_LESS "6")
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_LIB_SERIALPORT "Enable this to build the serialport lib" OFF
    DEPENDS (NOT CMAKE_CROSSCOMPILING)
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_LIB_SINGLEAPP "Enable this to build the singleapp lib" OFF
    DEPENDS (NOT CMAKE_CROSSCOMPILING) AND ("${QEXT_QT_VERSION}" VERSION_GREATER_EQUAL "5")
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_LIB_DEVICEWATCHER "Enable this to build the devicewatcher lib" OFF
    DEPENDS (NOT ANDROID) AND ("${QEXT_QT_VERSION}" VERSION_LESS "6")
    OR_CONDITION QEXT_BUILD_ALL)

qext_option(QEXT_ENABLE_3RDPARTY_QWT "Enable this to build the 3rdparty Qwt lib" OFF
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_3RDPARTY_QCUSTOMPLOT "Enable this to build the 3rdparty qcustomplot lib" OFF
    DEPENDS (NOT CMAKE_CROSSCOMPILING)
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ENABLE_3RDPARTY_QTADS "Enable this to build the 3rdparty Qt Advanced Docking System lib" OFF
    DEPENDS (NOT CMAKE_CROSSCOMPILING)
    OR_CONDITION QEXT_BUILD_ALL)

qext_option(QEXT_ADD_SUBDIRECTORY_QWT "Enable this to add the 3rdparty Qwt subdirectory" OFF
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ADD_SUBDIRECTORY_QCUSTOMPLOT "Enable this to add the 3rdparty qcustomplot subdirectory" OFF
    DEPENDS (NOT CMAKE_CROSSCOMPILING)
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ADD_SUBDIRECTORY_SINGLEAPP "Enable this to add the 3rdparty SingleApplication subdirectory" OFF
    DEPENDS (NOT CMAKE_CROSSCOMPILING) AND ("${QEXT_QT_VERSION}" VERSION_GREATER_EQUAL "5")
    OR_CONDITION QEXT_BUILD_ALL)
qext_option(QEXT_ADD_SUBDIRECTORY_QTADS "Enable this to add the 3rdparty Qt Advanced Docking System subdirectory" OFF
    DEPENDS (NOT CMAKE_CROSSCOMPILING)
    OR_CONDITION QEXT_BUILD_ALL)


#-----------------------------------------------------------------------------------------------------------------------
# Set install and paths
#-----------------------------------------------------------------------------------------------------------------------
# Install locations:
qext_configure_process_path(QEXT_INSTALL_LIBDIR "lib" "Libraries [PREFIX/lib]")
qext_configure_process_path(QEXT_INSTALL_BINDIR "bin" "Executables [PREFIX/bin]")
qext_configure_process_path(QEXT_INSTALL_TOOLDIR "tool" "Executables [PREFIX/tool]")
qext_configure_process_path(QEXT_INSTALL_INCLUDEDIR "include" "Header files [PREFIX/include]")
qext_configure_process_path(QEXT_INSTALL_ARCHDATADIR "." "Arch-dependent data [PREFIX]")
qext_configure_process_path(QEXT_INSTALL_PLUGINSDIR
    "${QEXT_INSTALL_ARCHDATADIR}/plugins" "Plugins [ARCHDATADIR/plugins]")

if(WIN32)
    set(QEXT_DEFAULT_DLLDIR "bin")
    set(QEXT_DEFAULT_TESTSDIR "bin")
    set(QEXT_DEFAULT_EXAMPLESDIR "bin")
    set(QEXT_DEFAULT_LIBEXEC "${QEXT_INSTALL_ARCHDATADIR}/bin")
else()
    set(QEXT_DEFAULT_DLLDIR "lib")
    set(QEXT_DEFAULT_TESTSDIR "tests")
    set(QEXT_DEFAULT_EXAMPLESDIR "examples")
    set(QEXT_DEFAULT_LIBEXEC "${QEXT_INSTALL_ARCHDATADIR}/libexec")
endif()

qext_configure_process_path(QEXT_INSTALL_DLLDIR
    "${QEXT_DEFAULT_DLLDIR}" "[PREFIX/bin] on Windows, [PREFIX/lib] otherwise")
qext_configure_process_path(QEXT_INSTALL_TESTSDIR
    "${QEXT_DEFAULT_TESTSDIR}" "[PREFIX/bin] on Windows, [PREFIX/tests] otherwise")
qext_configure_process_path(QEXT_INSTALL_EXAMPLESDIR
    "${QEXT_DEFAULT_EXAMPLESDIR}" "[PREFIX/bin] on Windows, [PREFIX/examples] otherwise")
qext_configure_process_path(QEXT_INSTALL_LIBEXECDIR
    "${QEXT_DEFAULT_LIBEXEC}" "Helper programs [ARCHDATADIR/bin on Windows, ARCHDATADIR/libexec otherwise]")
qext_configure_process_path(QEXT_INSTALL_QMLDIR
    "${QEXT_INSTALL_ARCHDATADIR}/qml" "QML imports [ARCHDATADIR/qml]")
qext_configure_process_path(QEXT_INSTALL_DATADIR "." "Arch-independent data [PREFIX]")
qext_configure_process_path(QEXT_INSTALL_DOCDIR "${QEXT_INSTALL_DATADIR}/doc" "Documentation [DATADIR/doc]")
qext_configure_process_path(QEXT_INSTALL_TRANSLATIONSDIR
    "${QEXT_INSTALL_DATADIR}/translations" "Translations [DATADIR/translations]")

if(APPLE)
    set(QEXT_DEFAULT_SYS_CONF_DIR "/Library/Preferences/QExt")
else()
    set(QEXT_DEFAULT_SYS_CONF_DIR "etc/xdg")
endif()
qext_configure_process_path(QEXT_INSTALL_SYSCONFDIR
    "${QEXT_DEFAULT_SYS_CONF_DIR}" "Settings used by QExt programs [PREFIX/etc/xdg]/[/Library/Preferences/QExt]")
qext_configure_process_path(QEXT_INSTALL_EXAMPLESDIR "examples" "Examples [PREFIX/examples]")
qext_configure_process_path(QEXT_INSTALL_TESTSDIR "tests" "Tests [PREFIX/tests]")
qext_configure_process_path(QEXT_INSTALL_DESCRIPTIONSDIR
    "${QEXT_INSTALL_DATADIR}/modules" "Module description files directory")

function(qext_internal_set_up_global_paths)
    # Compute the values of QEXT_BUILD_DIR, QEXT_INSTALL_DIR, QEXT_CONFIG_BUILD_DIR, QEXT_CONFIG_INSTALL_DIR
    # taking into account whether the current build is a prefix build or a non-prefix build,
    # and whether it is a superbuild or non-superbuild.
    # A third case is when another module or standalone tests are built against a super-built QExt.
    # The layout for the third case is the same as for non-superbuilds.
    #
    # These values should be prepended to file paths in commands or properties,
    # in order to correctly place generated Config files, generated Targets files,
    # executables / libraries, when copying / installing files, etc.
    #
    # The build dir variables will always be absolute paths.
    # The QEXT_INSTALL_DIR variable will have a relative path in a prefix build,
    # which means that it can be empty, so use qext_join_path to prevent accidental absolute paths.
    if(QEXT_SUPERBUILD)
        # In this case, we always copy all the build products in QEXT_BUILD_DIR/{bin,lib,...}
        if(QEXT_BUILD_INSTALL)
            set(QEXT_BUILD_DIR "${QEXT_BINARY_DIR}")
            set(QEXT_INSTALL_DIR "")
        else()
            if("${CMAKE_STAGING_PREFIX}" STREQUAL "")
                set(QEXT_BUILD_DIR "${QEXT_BINARY_DIR}")
                set(QEXT_INSTALL_DIR "${QEXT_BINARY_DIR}")
            else()
                set(QEXT_BUILD_DIR "${CMAKE_STAGING_PREFIX}")
                set(QEXT_INSTALL_DIR "${CMAKE_STAGING_PREFIX}")
            endif()
        endif()
    else()
        if(QEXT_BUILD_INSTALL)
            # In the usual prefix build case, the build dir is the current module build dir,
            # and the install dir is the prefix, so we don't set it.
            set(QEXT_BUILD_DIR "${CMAKE_BINARY_DIR}")
            set(QEXT_INSTALL_DIR "")
        else()
            # When doing a non-prefix build, both the build dir and install dir are the same, pointing to the
            # QExt build dir.
            set(QEXT_BUILD_DIR "${QEXT_STAGING_PREFIX}")
            set(QEXT_INSTALL_DIR "${QEXT_BUILD_DIR}")
        endif()
    endif()
    if(DEFINED INPUT_QEXT_BUILD_DIR)
        set(QEXT_BUILD_DIR "${INPUT_QEXT_BUILD_DIR}")
    endif()

    set(__config_path_part "${QEXT_INSTALL_LIBDIR}/cmake")
    set(QEXT_CONFIG_BUILD_DIR "${QEXT_BUILD_DIR}/${__config_path_part}")
    set(QEXT_CONFIG_INSTALL_DIR "${QEXT_INSTALL_DIR}")
    if(QEXT_CONFIG_INSTALL_DIR)
        string(APPEND QEXT_CONFIG_INSTALL_DIR "/")
    endif()
    string(APPEND QEXT_CONFIG_INSTALL_DIR ${__config_path_part})

    set(QEXT_BUILD_DIR "${QEXT_BUILD_DIR}" CACHE INTERNAL "" FORCE)
    set(QEXT_INSTALL_DIR "${QEXT_INSTALL_DIR}" CACHE INTERNAL "" FORCE)
    set(QEXT_CONFIG_BUILD_DIR "${QEXT_CONFIG_BUILD_DIR}" CACHE INTERNAL "" FORCE)
    set(QEXT_CONFIG_INSTALL_DIR "${QEXT_CONFIG_INSTALL_DIR}" CACHE INTERNAL "" FORCE)
    message(STATUS "QExt build dir set as '${QEXT_BUILD_DIR}'.")
    message(STATUS "QExt install dir set as '${QEXT_INSTALL_DIR}'.")
endfunction()
qext_internal_set_up_global_paths()

# the default RPATH to be used when installing, but only if it's not a system directory
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${QEXT_INSTALL_PREFIX}/${QEXT_INSTALL_LIBDIR}" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
    set(QEXT_DEFAULT_INSTALL_RPATH "${QEXT_INSTALL_PREFIX}/${QEXT_INSTALL_LIBDIR}")
endif("${isSystemDir}" STREQUAL "-1")

# The default rpath settings for installed targets is empty.
# The rpaths will instead be computed for each target separately using qext_apply_rpaths().
# Additional rpaths can be passed via QEXT_EXTRA_RPATHS.
# By default this will include $ORIGIN / @loader_path, so the installation is relocatable.
# Bottom line: No need to pass anything to CMAKE_INSTALL_RPATH.
set(CMAKE_INSTALL_RPATH "" CACHE STRING "RPATH for installed binaries" FORCE)
# message(QEXT_DEFAULT_INSTALL_RPATH=${QEXT_DEFAULT_INSTALL_RPATH})
# message(CMAKE_INSTALL_RPATH=${CMAKE_INSTALL_RPATH})
# By default, don't embed auto-determined RPATHs pointing to directories
# outside of the build tree, into the installed binaries.
# This ended up adding rpaths like ${QEXT_INSTALL_PREFIX}/lib (or /Users/qext/work/install/lib into
# the official libraries created by the CI) into the non-qextbase libraries, plugins, etc.
#
# It should not be necessary, given that qext_apply_rpaths() already adds the necessary rpaths, either
# relocatable ones or absolute ones, depending on what the platform supports.
if(NOT QEXT_NO_DISABLE_CMAKE_INSTALL_RPATH_USE_LINK_PATH)
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
endif()

# Ensure that GNUInstallDirs's CMAKE_INSTALL_LIBDIR points to the same lib dir that QExt was
# configured with. Currently this is important for QML plugins, which embed an rpath based
# on that value.
set(CMAKE_INSTALL_LIBDIR "${QEXT_INSTALL_LIBDIR}")

function(qext_setup_tool_path_command)
    if(NOT CMAKE_HOST_WIN32)
        return()
    endif()
    set(bindir "${QEXT_BUILD_INTERNALS_RELOCATABLE_INSTALL_PREFIX}/${QEXT_INSTALL_BINDIR}")
    file(TO_NATIVE_PATH "${bindir}" bindir)
    list(APPEND command COMMAND)
    list(APPEND command set PATH=${bindir}$<SEMICOLON>%PATH%)
    set(QEXT_TOOL_PATH_SETUP_COMMAND "${command}" CACHE INTERNAL "internal command prefix for tool invocations" FORCE)
    # QEXT_TOOL_PATH_SETUP_COMMAND is deprecated. Please use _qext_internal_get_wrap_tool_script_path instead.
endfunction()
qext_setup_tool_path_command()

list(APPEND QEXT_QML_IMPORT_PATH ${QML_IMPORT_PATH} "${QEXT_BUILD_DIR}/${QEXT_INSTALL_QMLDIR}")
list(REMOVE_DUPLICATES QEXT_QML_IMPORT_PATH)
set(QML_IMPORT_PATH ${QEXT_QML_IMPORT_PATH} CACHE INTERNAL "Qt Creator extra qml import paths" FORCE)


#-----------------------------------------------------------------------------------------------------------------------
# Set platform and mkspecs define
#-----------------------------------------------------------------------------------------------------------------------
include(QExtPlatformSupport)


#-----------------------------------------------------------------------------------------------------------------------
# Set namespace and separator
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_NAMESPACE_VERSION ${QEXT_VERSION_MAJOR})
set(QEXT_NAMESPACE "" CACHE STRING "QExt Namespace")
if(NOT QEXT_CMAKE_INSTALL_NAMESPACE)
    set(QEXT_CMAKE_INSTALL_NAMESPACE "QExt${QEXT_NAMESPACE_VERSION}" CACHE STRING "CMake namespace [QExt${QEXT_NAMESPACE_VERSION}]")
endif()
if(NOT QEXT_CMAKE_EXPORT_NAMESPACE)
    set(QEXT_CMAKE_EXPORT_NAMESPACE "QExt${QEXT_NAMESPACE_VERSION}"
        CACHE STRING "CMake namespace used when exporting targets [QExt${QEXT_NAMESPACE_VERSION}]")
endif()

set(QEXT_KNOWN_LIBRARIES_WITH_TOOLS "" CACHE INTERNAL "Known QExt modules with tools" FORCE)

# For adjusting variables when running tests, we need to know what
# the correct variable is for separating entries in PATH-alike
# variables.
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(QEXT_PATH_SEPARATOR "\\;")
else()
    set(QEXT_PATH_SEPARATOR ":")
endif()

# Save tQEXT_DEFAULT_INSTALL_RPATHt first project source dir.
# This will be /path/to/QExtCore for QExtCore both in a super-build and a non super-build.
# This will be /path/to/QExtCore/tests when building standalone tests.
set(QEXT_TOP_LEVEL_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(QEXT_INSTALL_COMPONENT_NAME "${QEXT_CMAKE_INSTALL_NAMESPACE}SDK")


#-----------------------------------------------------------------------------------------------------------------------
# Prevent warnings about object files without any symbols. This is a common thing in QExt as we tend to build files
# unconditionally, and then use ifdefs to compile out parts that are not relevant.
#-----------------------------------------------------------------------------------------------------------------------
if(CMAKE_HOST_APPLE AND APPLE)
    foreach(lang ASM C CXX)
        # We have to tell 'ar' to not run ranlib by itself, by passing the 'S' option
        set(CMAKE_${lang}_ARCHIVE_CREATE "<CMAKE_AR> qcS <TARGET> <LINK_FLAGS> <OBJECTS>")
        set(CMAKE_${lang}_ARCHIVE_APPEND "<CMAKE_AR> qS <TARGET> <LINK_FLAGS> <OBJECTS>")
        set(CMAKE_${lang}_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols <TARGET>")
    endforeach()
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Build directory check
#-----------------------------------------------------------------------------------------------------------------------
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run "
        "CMake from there. You may need to remove CMakeCache.txt.")
endif()
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(QEXT_IN_SUBMODULE OFF)
else()
    set(QEXT_IN_SUBMODULE ON)
endif()

if(CMAKE_CROSSCOMPILING AND NOT IS_DIRECTORY "${QT_HOST_PATH}")
    message(WARNING "You need to set QT_HOST_PATH to cross compile QEXT.")
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Set default param args
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_DEFAULT_PRIVATE_ARGS
    DEFINES
    SOURCES
    LIBRARIES
    INCLUDE_DIRECTORIES
    FEATURE_DEPENDENCIES
    COMPILE_OPTIONS
    LINK_OPTIONS
    MOC_OPTIONS
    DISABLE_AUTOGEN_TOOLS
    ENABLE_AUTOGEN_TOOLS
    PLUGIN_TYPES)
set(QEXT_DEFAULT_PUBLIC_ARGS
    PUBLIC_DEFINES
    PUBLIC_LIBRARIES
    PUBLIC_INCLUDE_DIRECTORIES
    PUBLIC_COMPILE_OPTIONS
    PUBLIC_LINK_OPTIONS)
set(QEXT_DEFAULT_TARGET_INFO_ARGS
    TARGET_VERSION
    TARGET_PRODUCT
    TARGET_DESCRIPTION
    TARGET_COMPANY
    TARGET_COPYRIGHT)
set(QEXT_DEFAULT_TARGET_SINGLE_ARGS
    CXX_STANDARD)
set(QEXT_DEFAULT_PRIVATE_LIBRARY_ARGS
    PRIVATE_LIBRARY_INTERFACE)

# Collection of arguments so they can be shared across qext_internal_add_executable and qext_internal_add_test_helper.
set(QEXT_INTERNAL_ADD_EXECUTABLE_OPTIONAL_ARGS
    GUI
    NO_INSTALL
    EXCEPTIONS
    DELAY_RC
    DELAY_TARGET_INFO
    QEXT_APP)
set(QEXT_INTERNAL_ADD_EXECUTABLE_SINGLE_ARGS
    VERSION
    OUTPUT_NAME
    CORE_LIBRARY
    OUTPUT_SUBDIR
    OUTPUT_DIRECTORY
    INSTALL_DIRECTORY
    ${QEXT_DEFAULT_TARGET_INFO_ARGS}
    ${QEXT_DEFAULT_TARGET_SINGLE_ARGS})
set(QEXT_INTERNAL_ADD_EXECUTABLE_MULTI_ARGS
    ${QEXT_DEFAULT_PRIVATE_ARGS}
    ${QEXT_DEFAULT_PUBLIC_ARGS})


#-----------------------------------------------------------------------------------------------------------------------
# Add 3rdparty subdirectory
#-----------------------------------------------------------------------------------------------------------------------
set(QWT_VERSION 6.3.0)
if(QEXT_ADD_SUBDIRECTORY_QWT)
    set(QExtWrapQwt_DIR_NAME "qwt-${QWT_VERSION}")
    set(QExtWrapQwt_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapQwt_DIR_NAME}")
    qext_fetch_3rdparty(QExtWrapQwt URL "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapQwt_DIR_NAME}.7z")
    add_subdirectory(${QExtWrapQwt_ROOT_DIR}/source ${QExtWrapQwt_ROOT_DIR}/subbuild)
endif()
if(QEXT_ENABLE_3RDPARTY_QWT)
    qext_find_package(WrapQwt PROVIDED_TARGETS QExt3rdparty::WrapQwt)
endif()

if(QEXT_ADD_SUBDIRECTORY_QTADS)
    set(ADS_VERSION "4.4.0")
    set(ADS_BUILD_INSTALL OFF)
    set(QExtWrapQtADS_DIR_NAME "QtADS-${ADS_VERSION}")
    set(QExtWrapQtADS_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapQtADS_DIR_NAME}")
    qext_fetch_3rdparty(QExtWrapQtADS URL "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapQtADS_DIR_NAME}.7z")
    add_subdirectory(${QExtWrapQtADS_ROOT_DIR}/source ${QExtWrapQtADS_ROOT_DIR}/subbuild)
endif()
if(QEXT_ENABLE_3RDPARTY_QTADS)
    qext_find_package(WrapQtADS PROVIDED_TARGETS QExt3rdparty::WrapQtADS)
endif()

if(QEXT_ADD_SUBDIRECTORY_SINGLEAPP)
    set(QExtWrapSingleApp_DIR_NAME "SingleApplication-3.5.4")
    set(QExtWrapSingleApp_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapSingleApp_DIR_NAME}")
    qext_fetch_3rdparty(QExtWrapSingleApp URL "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapSingleApp_DIR_NAME}.tar.gz")
    add_subdirectory(${QExtWrapSingleApp_ROOT_DIR}/source ${QExtWrapSingleApp_ROOT_DIR}/subbuild)
endif()

if(QEXT_ADD_SUBDIRECTORY_QCUSTOMPLOT)
    set(QCUSTOMPLOT_BUILD_ALL ON)
    set(QExtWrapQCustomPlot_DIR_NAME "qcustomplot-2.1.1")
    set(QExtWrapQCustomPlot_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapQCustomPlot_DIR_NAME}")
    qext_fetch_3rdparty(QExtWrapQCustomPlot URL "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapQCustomPlot_DIR_NAME}.7z")
    add_subdirectory(${QExtWrapQCustomPlot_ROOT_DIR}/source ${QExtWrapQCustomPlot_ROOT_DIR}/subbuild)
endif()
if(QEXT_ENABLE_3RDPARTY_QCUSTOMPLOT)
    qext_find_package(WrapQCustomPlot PROVIDED_TARGETS QExt3rdparty::WrapQCustomPlot)
endif()

qext_add_subdirectory(3rdparty/PinyinIME QEXT_ENABLE_LIB_KEYBOARD)

if(QEXT_BUILD_TESTS)
    include(CTest)
    enable_testing()
endif()

if(QEXT_BUILD_DOCS)
    message(STATUS "Project build documentation")
    #    qext_build_doxygen()
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Add subdirectory
#-----------------------------------------------------------------------------------------------------------------------
add_subdirectory(src/libs)
add_subdirectory(src/apps)
add_subdirectory(src/tools)
add_subdirectory(src/plugins)
qext_add_subdirectory(src/qmls QEXT_BUILD_QMLS)
message(STATUS "QExt Configuring Generating Done")
