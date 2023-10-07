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
# Set cmake min version and policy
#--------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0075 NEW) # use CMAKE_REQUIRED_LIBRARIES
cmake_policy(SET CMP0083 NEW) # use check_pie_supported


#--------------------------------------------------------------------------------
# Set project name and version
#--------------------------------------------------------------------------------
project(QEXT VERSION 1.1.1.1 LANGUAGES CXX C)
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
set(QEXT_LICENSE "MIT License")
set(QEXT_PRODUCT_NAME "QEXT")
set(QEXT_CXX_STANDARD 11)
math(EXPR QEXT_VERSION_CALC "${QEXT_VERSION_MAJOR}*1000 + ${QEXT_VERSION_MINOR}*100 + ${QEXT_VERSION_PATCH}")
message(STATUS "=====================================QEXT=========================================")
message(STATUS "Project version: ${QEXT_VERSION}")
message(STATUS "Project copyright: ${QEXT_COPYRIGHT}")
message(STATUS "Project license: ${QEXT_LICENSE}")


#--------------------------------------------------------------------------------
# find qt and include path, set cmake moc uic rcc on
#--------------------------------------------------------------------------------
if (CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif ()

set(CMAKE_PREFIX_PATH "/Users/cxw/Qt/5.15.2/clang_64")
set(QEXT_QT_HAS_QJSON OFF)
set(QEXT_QT_HAS_QML OFF)
find_package(Qt4 QUIET COMPONENTS QtCore QUIET)
if (NOT QT_FOUND)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core QUIET)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core QUIET)
endif ()
set(QEXT_QT_VERSION_MAJOR ${QT_VERSION_MAJOR})
set(QEXT_QT_VERSION_MINOR ${QT_VERSION_MINOR})
set(QEXT_QT_VERSION_PATCH ${QT_VERSION_PATCH})
set(QEXT_QT_VERSION "${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
if (QEXT_QT_VERSION_MAJOR EQUAL 4)
    if (QEXT_QT_VERSION_MINOR LESS 8)
        message(FATAL_ERROR "Expected Qt4 version must greater than or equal to Qt4.8")
    endif ()
    message(STATUS "Expected Qt version is Qt${QEXT_QT_VERSION}")
    find_package(Qt4 REQUIRED QtCore QtGui QtTest QtNetwork)
    include(${QT_USE_FILE})
    add_definitions(${QT_DEFINITIONS})
    find_package(Qt4 COMPONENTS QtOpenGL)
    set(QEXT_QT_OPENGL_FOUND ${QT_QTOPENGL_FOUND})
    set(QEXT_CXX_STANDARD 98)
elseif (QEXT_QT_VERSION_MAJOR EQUAL 5)
    message(STATUS "Expected Qt version is Qt${QEXT_QT_VERSION}")
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS Core Widgets Network Quick Test PrintSupport Svg REQUIRED)
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS OpenGL)
    set(QEXT_QT_OPENGL_FOUND ${Qt${QEXT_QT_VERSION_MAJOR}OpenGL_FOUND})
    if (QEXT_QT_VERSION_MAJOR EQUAL 5 AND QEXT_QT_VERSION_MINOR GREATER_EQUAL 12)
        find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS Qml QuickControls2 REQUIRED)
        set(QEXT_QT_HAS_QML ON)
    else ()
        set(QEXT_QT_HAS_QML OFF)
    endif ()
    set(QEXT_QT_HAS_QJSON ON)
    set(QEXT_CXX_STANDARD 11)
elseif (QEXT_QT_VERSION_MAJOR EQUAL 6)
    message(STATUS "Expected Qt version is Qt${QEXT_QT_VERSION}")
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS Core Widgets Network Quick Test PrintSupport Svg REQUIRED)
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS Qml QuickControls2 Core5Compat REQUIRED)
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS Core5Compat REQUIRED)
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS OpenGLWidgets OpenGL)
    set(QEXT_QT_OPENGL_FOUND ${Qt${QEXT_QT_VERSION_MAJOR}OpenGL_FOUND})
    set(QEXT_QT_HAS_QML ON)
    set(QEXT_QT_HAS_QJSON ON)
    set(QEXT_CXX_STANDARD 17)
else ()
    message(FATAL_ERROR "Not find Qt package")
endif ()

get_filename_component(QEXT_QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
get_filename_component(QEXT_QT_KIT_DIR "${QEXT_QT_BIN_DIR}" DIRECTORY)
set(QEXT_QT_LIB_DIR ${QEXT_QT_KIT_DIR}/lib)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


#-----------------------------------------------------------------------------------------------------------------------
# Detect prefix and install
#-----------------------------------------------------------------------------------------------------------------------
# Pre-calculate the developer_build feature if it's set by the user via INPUT_QEXT_FEATURE_DEV_BUILD
if (NOT QEXT_FEATURE_DEV_BUILD AND NOT INPUT_QEXT_FEATURE_DEV_BUILD AND NOT "${INPUT_QEXT_FEATURE_DEV_BUILD}" STREQUAL "undefined")
    set(QEXT_FEATURE_DEV_BUILD ON)
endif ()


# Pre-calculate the no_prefix feature if it's set by configure via INPUT_QEXT_FEATURE_NO_PREFIX.
# This needs to be done before configure.cmake is processed.
if (NOT QEXT_FEATURE_NO_PREFIX AND INPUT_QEXT_FEATURE_NO_PREFIX AND NOT "${INPUT_QEXT_FEATURE_NO_PREFIX}" STREQUAL "undefined")
    set(QEXT_FEATURE_NO_PREFIX ON)
endif ()

if (NOT QEXT_BUILD_STANDALONE_TESTS)
    if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        # Handle both FEATURE_ and QEXT_FEATURE_ cases when they are specified on the command line explicitly.
        # It's possible for one to be set, but not the other, because core/configure.cmake is not processed by this point.
        if ((QEXT_FEATURE_DEV_BUILD OR QEXT_FEATURE_NO_PREFIX) AND NOT CMAKE_STAGING_PREFIX)
            # Handle non-prefix builds by setting the CMake install prefix to point to QEXT's build dir.
            set(QEXT_DEFAULT_PREFIX "${QEXT_BINARY_DIR}")
        else ()
            if (CMAKE_HOST_WIN32)
                set(QEXT_DEFAULT_PREFIX "C:/QEXT/")
            else ()
                set(QEXT_DEFAULT_PREFIX "/usr/local/")
            endif ()
            string(APPEND QEXT_DEFAULT_PREFIX "QEXT-${QEXT_VERSION}")
        endif ()
        set(CMAKE_INSTALL_PREFIX ${QEXT_DEFAULT_PREFIX} CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
    endif ()
    if (CMAKE_STAGING_PREFIX)
        set(QEXT_PREFIX "${CMAKE_STAGING_PREFIX}")
    else ()
        set(QEXT_PREFIX "${CMAKE_INSTALL_PREFIX}")
    endif ()
    if (QEXT_PREFIX STREQUAL QEXT_BINARY_DIR)
        set(QEXT_WILL_INSTALL_VALUE OFF)
    else ()
        set(QEXT_WILL_INSTALL_VALUE ON)
    endif ()
    set(QEXT_WILL_INSTALL ${QEXT_WILL_INSTALL_VALUE} CACHE BOOL "Boolean indicating if doing a QEXT prefix build (vs non-prefix build)." FORCE)
endif ()

if (QEXT_FEATURE_DEV_BUILD)
    if (DEFINED QEXT_CMAKE_EXPORT_COMPILE_COMMANDS)
        set(CMAKE_EXPORT_COMPILE_COMMANDS ${QEXT_CMAKE_EXPORT_COMPILE_COMMANDS})
    else ()
        set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    endif ()
    set(__qext_build_warnings_as_errors ON)
    set(__qext_build_tests_default ON)
    set(__qext_build_benchmarks ON)

    # Tests are not built by default with qmake for iOS and friends, and thus the overall build
    # tends to fail. Disable them by default when targeting uikit.
    if (UIKIT OR ANDROID)
        set(__qext_build_tests_default OFF)
    endif ()

    # Disable benchmarks for single configuration generators which do not build
    # with release configuration.
    if (CMAKE_BUILD_TYPE AND CMAKE_BUILD_TYPE STREQUAL Debug)
        set(__qext_build_benchmarks OFF)
    endif ()
else ()
    set(__qext_build_warnings_as_errors OFF)
    set(__qext_build_tests_default OFF)
    set(__qext_build_benchmarks OFF)
endif ()

# When cross-building, we don't build tools by default. Sometimes this also covers qext apps as well.
set(__qext_build_tools_default ON)
if (CMAKE_CROSSCOMPILING AND NOT QEXT_FORCE_BUILD_TOOLS)
    set(__qext_build_tools_default OFF)
endif ()


#-----------------------------------------------------------------------------------------------------------------------
# Decide whether output should be verbose or not. # Default to verbose (--log-level=STATUS) in a developer-build and
# non-verbose (--log-level=NOTICE) otherwise. If a custom CMAKE_MESSAGE_LOG_LEVEL was specified, it takes priority.
# Passing an explicit --log-level=Foo has the highest priority.
#-----------------------------------------------------------------------------------------------------------------------
if (NOT CMAKE_MESSAGE_LOG_LEVEL)
    if (QEXT_FEATURE_DEV_BUILD)
        set(CMAKE_MESSAGE_LOG_LEVEL "STATUS")
    else ()
        set(CMAKE_MESSAGE_LOG_LEVEL "NOTICE")
    endif ()
endif ()


#-----------------------------------------------------------------------------------------------------------------------
# Set build type
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_DEFAULT_BUILD_TYPE "Release")
if (QEXT_FEATURE_DEV_BUILD)
    set(QEXT_DEFAULT_BUILD_TYPE "Debug")
endif ()
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${QEXT_DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${QEXT_DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE
            PROPERTY STRINGS
            "Debug" "Release" "MinSizeRel" "RelWithDebInfo") # Set the possible values for cmake-gui.
elseif (CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Building for multiple configurations: ${CMAKE_CONFIGURATION_TYPES}.")
    message(STATUS "Main configuration is: ${QEXT_MULTI_CONFIG_FIRST_CONFIG}.")
    if (CMAKE_NINJA_MULTI_DEFAULT_BUILD_TYPE)
        message(STATUS "Default build configuration set to '${CMAKE_NINJA_MULTI_DEFAULT_BUILD_TYPE}'.")
    endif ()
    if (CMAKE_GENERATOR STREQUAL "Ninja")
        message(FATAL_ERROR
                "It's not possible to build multiple configurations with the single config Ninja "
                "generator. Consider configuring with -G\"Ninja Multi-Config\" instead of -GNinja.")
    endif ()
else ()
    message(STATUS "CMAKE_BUILD_TYPE was set to: '${CMAKE_BUILD_TYPE}'")
endif ()


#-----------------------------------------------------------------------------------------------------------------------
# Set multi-config
# Append a config-specific postfix to library names to ensure distinct names in a multi-config build. e.g.
# lib/libqext_core_relwithdebinfo.0.1.1.dylib
# Don't apply the postfix to the first encountered release-like config, so we have at least one config without a postifx.
#-----------------------------------------------------------------------------------------------------------------------
# Save the global property in a variable to make it available to feature conditions.
get_property(QEXT_GENERATOR_IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if (QEXT_GENERATOR_IS_MULTI_CONFIG AND CMAKE_CONFIGURATION_TYPES)
    set(__qext_setup_release_configs Release RelWithDebInfo MinSizeRel)
    set(__qext_setup_found_first_release_config FALSE)
    foreach (__qext_setup_config_type IN LISTS CMAKE_CONFIGURATION_TYPES)
        # Skip assigning postfix for the first release-like config.
        if (NOT __qext_setup_found_first_release_config AND __qext_setup_config_type IN_LIST __qext_setup_release_configs)
            set(__qext_setup_found_first_release_config TRUE)
            continue()
        endif ()

        string(TOLOWER "${__qext_setup_config_type}" __qext_setup_config_type_lower)
        string(TOUPPER "${__qext_setup_config_type}" __qext_setup_config_type_upper)
        set(CMAKE_${__qext_setup_config_type_upper}_POSTFIX "_${__qext_setup_config_type_lower}")
        if (APPLE)
            set(CMAKE_FRAMEWORK_MULTI_CONFIG_POSTFIX_${__qext_setup_config_type_upper} "_${__qext_setup_config_type_lower}")
        endif ()
    endforeach ()
endif ()

# Override the generic debug postfixes above with custom debug postfixes (even in a single config build) to follow the
# conventions we had. lib/libqext_core_debug.6.3.0.dylib
if (WIN32)
    if (MINGW)
        # On MinGW we don't have "d" suffix for debug libraries like on Linux, unless we're building debug and release
        # libraries in one go.
        if (QEXT_GENERATOR_IS_MULTI_CONFIG)
            set(CMAKE_DEBUG_POSTFIX "d")
        endif ()
    else ()
        set(CMAKE_DEBUG_POSTFIX "d")
    endif ()
elseif (APPLE)
    set(CMAKE_DEBUG_POSTFIX "_debug")
    set(CMAKE_FRAMEWORK_MULTI_CONFIG_POSTFIX_DEBUG "_debug")
endif ()

## Position independent code:
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Does the linker support position independent code?
include(CheckPIESupported)
check_pie_supported()

# Do not relink dependent libraries when no header has changed:
set(CMAKE_LINK_DEPENDS_NO_SHARED ON)


#--------------------------------------------------------------------------------
# Specify the C++ standard and flags
#--------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD ${QEXT_CXX_STANDARD})
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "Using C++: ${QEXT_CXX_STANDARD}")
message(STATUS "Set C++ extensions: ${CMAKE_CXX_EXTENSIONS}")

if (WIN32)
    if (CMAKE_CXX_COMPILER_ID MATCHES MSVC)
        # open bigobj flags in msvc compiler(bigobj)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
    elseif (CMAKE_CXX_COMPILER_ID MATCHES GNU)
        # open bigobj flags in gnu/mingw compiler(File too big/too many sections)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
    endif ()
endif ()


#--------------------------------------------------------------------------------
# specify the host info
#--------------------------------------------------------------------------------
set(QEXT_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})
set(QEXT_SYSTEM_VERSION ${CMAKE_SYSTEM_VERSION})
set(QEXT_SYSTEM_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR})
set(QEXT_CXX_COMPILER_ID ${CMAKE_CXX_COMPILER_ID})

# specify system
if (CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(QEXT_SYSTEM_LINUX ON)
elseif (CMAKE_SYSTEM_NAME STREQUAL Darwin)
    set(QEXT_SYSTEM_MAC ON)
    set(QEXT_SYSTEM_DARWIN ON)
elseif (CMAKE_SYSTEM_NAME STREQUAL Windows)
    set(QEXT_SYSTEM_WIN ON)
elseif (CMAKE_SYSTEM_NAME STREQUAL WindowsCE)
    set(QEXT_SYSTEM_WIN ON)
    set(QEXT_SYSTEM_WINCE ON)
elseif (CMAKE_SYSTEM_NAME STREQUAL QNX)
    set(QEXT_SYSTEM_QNX ON)
else ()
    set(QEXT_SYSTEM_UNKNOWN ON)
endif ()

# specify compiler
if (CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(QEXT_CXX_COMPILER_MSVC ON)
elseif (CMAKE_CXX_COMPILER_ID MATCHES Intel)
    set(QEXT_CXX_COMPILER_INTEL ON)
elseif (CMAKE_CXX_COMPILER_ID MATCHES AppleClang)
    set(QEXT_CXX_COMPILER_CLANG_APPLE ON)
    set(QEXT_CXX_COMPILER_CLANG ON)
elseif (CMAKE_CXX_COMPILER_ID MATCHES Clang)
    set(QEXT_CXX_COMPILER_CLANG ON)
elseif (CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(QEXT_CXX_COMPILER_GNU ON)
else ()
    set(QEXT_CXX_COMPILER_UNKNOWN Unknown)
endif ()

# specify arch bit
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(QEXT_ARCH_64 ON)
else ()
    set(QEXT_ARCH_32 ON)
endif ()

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
# Add CMake function(s) and macro(s)
#--------------------------------------------------------------------------------
set(QEXT_CMAKE_DIR "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_MODULE_PATH ${QEXT_CMAKE_DIR} ${CMAKE_MODULE_PATH})
include(qextFunctionActivatePrecompiledHeaders)
include(qextFunctionCopyDependencyExternal)
include(qextFunctionCopyDependencyInternal)
include(qextFunctionCheckCompileFeature)
include(qextFunctionSetCompilerWarnings)
include(qextFunctionQmlPlugin)
include(qextMacroEnsureDefineCacheVariable)
include(qextMacroEnsureDefineVariable)
include(qextMacroFindQmlPluginDump)
include(qextMacroFindReadline)
include(qextMacroBuildDoxygen)
include(qextMacroFindLibVLC)

include(QExtScopeFinalizerHelpers)
include(QExtGlobalStateHelpers)
include(QExtSyncIncludeHelpers)
include(QExtFindPackageHelpers)
include(QExtPrecompiledHelpers)
include(QExtPublicTargetHelpers)
include(QExtFlagHandlingHelpers)
include(QExtCMakeVersionHelpers)
include(QExtExecutableHelpers)
include(QExtSeparateDebugInfo)
include(QExtConfigureHelpers)
include(QExtFrameworkHelpers)
include(QExtPkgConfigHelpers)
include(QExtLibraryHelpers)
include(QExtInstallHelpers)
include(QExtModuleHelpers)
include(QExtTargetHelpers)
include(QExtCMakeHelpers)
include(QExtTestHelpers)
include(QExtRpathHelpers)
include(QExtOptionHelpers)

#
##--------------------------------------------------------------------------------
## Set option
##--------------------------------------------------------------------------------
#qextMacroEnsureDefineVariable(BUILD_QEXT_SHARED ON)
#qextMacroEnsureDefineVariable(BUILD_QEXT_USE_PCH ON)
#qextMacroEnsureDefineVariable(BUILD_QEXT_COMPILER_WARNING OFF)
#
#qextMacroEnsureDefineVariable(USE_QEXT_ALL ON)
#qextMacroEnsureDefineVariable(USE_QEXT_DEVICEWATCHER ${USE_QEXT_ALL})
#qextMacroEnsureDefineVariable(USE_QEXT_FRAMELESSHELPER ${USE_QEXT_ALL})
#qextMacroEnsureDefineVariable(USE_QEXT_GOOGLEPINYIN ${USE_QEXT_ALL})
#qextMacroEnsureDefineVariable(USE_QEXT_ICONFONT ${USE_QEXT_ALL})
#qextMacroEnsureDefineVariable(USE_QEXT_SERIALPORT ${USE_QEXT_ALL})
#qextMacroEnsureDefineVariable(USE_QEXT_SINGLEAPP ${USE_QEXT_ALL})
#qextMacroEnsureDefineVariable(USE_QEXT_STYLETHEME ${USE_QEXT_ALL})
#qextMacroEnsureDefineVariable(USE_QEXT_TCP ${USE_QEXT_ALL})
#qextMacroEnsureDefineVariable(USE_QEXT_UTILS ${USE_QEXT_ALL})
#qextMacroEnsureDefineVariable(USE_QEXT_VLC ${USE_QEXT_ALL})
#qextMacroEnsureDefineVariable(USE_QEXT_WIDGETS ${USE_QEXT_ALL})
#
#qextMacroEnsureDefineVariable(USE_QEXT_QML_FRAMELESSHELPER ${USE_QEXT_ALL})
#qextMacroEnsureDefineVariable(USE_QEXT_QML_QUICK ${USE_QEXT_ALL})
#qextMacroEnsureDefineVariable(USE_QEXT_QML_THEME ${USE_QEXT_ALL})
#qextMacroEnsureDefineVariable(USE_QEXT_QML_VLC ${USE_QEXT_ALL})
#
#qextMacroEnsureDefineVariable(USE_QEXT_QWT ${USE_QEXT_ALL})
#qextMacroEnsureDefineVariable(USE_QEXT_QCUSTOMPLOT ${USE_QEXT_ALL})
#
#option(QEXT_BUILD_QMLS "Build qmls" ON)
#option(QEXT_BUILD_TESTS "Build tests" OFF)
#option(QEXT_BUILD_PLUGINS "Build plugins" ON)
#option(QEXT_BUILD_EXAMPLES "Build examples" OFF)
#option(QEXT_BUILD_INSTALL "Build install" OFF)
#option(QEXT_BUILD_DOCUMENTATION "Enable this to build the documentation" OFF)
#option(QEXT_BUILD_SHARED_LIBS "Build shared library" ${BUILD_QEXT_SHARED})
#option(QEXT_BUILD_COMPILER_WARNING "Build target with compiler warnings" ${BUILD_QEXT_COMPILER_WARNING})
#option(QEXT_BUILD_USE_PCH "Enable this to build use precompiled header files for compilation" ${BUILD_QEXT_USE_PCH})
#
#
#option(QEXT_BUILD_LIB_DEVICEWATCHER "Enable this to build the devicewatcher lib" ${USE_QEXT_DEVICEWATCHER})
#option(QEXT_BUILD_LIB_FRAMELESSHELPER "Enable this to build the framelesshelper lib" ${USE_QEXT_FRAMELESSHELPER})
#option(QEXT_BUILD_LIB_GOOGLEPINYIN "Enable this to build the googlepinyin lib" ${USE_QEXT_GOOGLEPINYIN})
#option(QEXT_BUILD_LIB_ICONFONT "Enable this to build the iconfont lib" ${USE_QEXT_ICONFONT})
#option(QEXT_BUILD_LIB_SERIALPORT "Enable this to build the serialport lib" ${USE_QEXT_SERIALPORT})
#option(QEXT_BUILD_LIB_SINGLEAPP "Enable this to build the singleapp lib" ${USE_QEXT_SINGLEAPP})
#option(QEXT_BUILD_LIB_STYLETHEME "Enable this to build the styletheme lib" ${USE_QEXT_STYLETHEME})
#option(QEXT_BUILD_LIB_TCP "Enable this to build the tcp lib" ${USE_QEXT_TCP})
#option(QEXT_BUILD_LIB_UTILS "Enable this to build the utils lib" ${USE_QEXT_UTILS})
#option(QEXT_BUILD_LIB_VLC "Enable this to build the VLC lib" ${USE_QEXT_VLC})
#option(QEXT_BUILD_LIB_WIDGETS "Enable this to build the widgets lib" ${USE_QEXT_WIDGETS})
#
#option(QEXT_BUILD_LIB_QML_FRAMELESSHELPER "Enable this to build the qml framelesshelper lib" ${USE_QEXT_QML_FRAMELESSHELPER})
#option(QEXT_BUILD_LIB_QML_QUICK "Enable this to build the qml quick lib" ${USE_QEXT_QML_QUICK})
#option(QEXT_BUILD_LIB_QML_THEME "Enable this to build the qml theme lib" ${USE_QEXT_QML_THEME})
#option(QEXT_BUILD_LIB_QML_VLC "Enable this to build the qml VLC lib" ${USE_QEXT_QML_VLC})
#
#option(QEXT_BUILD_LIB_QWT "Enable this to build the qwt lib" ${USE_QEXT_QWT})
#option(QEXT_BUILD_LIB_QCUSTOMPLOT "Enable this to build the qcustomplot lib" ${USE_QEXT_QCUSTOMPLOT})
#
#
#if(QEXT_BUILD_SHARED_LIBS)
#    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build as shared libraries")
#    message(STATUS "Build as shared libraries")
#else()
#    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build as static libraries")
#    message(STATUS "Build as static libraries")
#endif()
#
#if(QEXT_BUILD_USE_PCH)
#    if(NOT ${QEXT_BUILD_SHARED_LIBS})
#        set(QEXT_BUILD_USE_PCH FALSE)
#        message(STATUS "Do not build use pch, becase QEXT build shared library.")
#    endif()
#endif()
#
#if(QEXT_BUILD_DOCUMENTATION)
#    qextMacroBuildDoxygen()
#    message(STATUS "Build with the documentation")
#else()
#    message(STATUS "Build with no documentation")
#endif()
#
#
#if(QEXT_BUILD_LIB_TCP)
#    set(QEXT_BUILD_LIB_UTILS ON)
#endif()
#
#if(QEXT_BUILD_LIB_FRAMELESSHELPER)
#    if(QEXT_QT_VERSION_MAJOR LESS 5)
#        message(STATUS "Do not build framelesshelper lib, becase Qt major version must greater than 5.")
#        set(QEXT_BUILD_LIB_FRAMELESSHELPER OFF)
#    endif()
#    if(NOT WIN32)
#        message(STATUS "Do not build framelesshelper lib, becase framelesshelper only support windows platform.")
#        set(QEXT_BUILD_LIB_FRAMELESSHELPER OFF)
#    endif()
#endif()
#
#if(QEXT_BUILD_LIB_VLC)
#    if(QEXT_QT_VERSION LESS 5.0)
#        set(QEXT_BUILD_LIB_VLC OFF)
#        message(STATUS "Do not build the vlc lib, becase Qt major version must greater than 5.0.")
#    endif()
#    qextMacroFindLibVLC()
#    if(NOT QEXT_LIBVLC_FOUND)
#        set(QEXT_BUILD_LIB_VLC OFF)
#        message(STATUS "Do not build the vlc lib, becase not found vlc lib.")
#    endif()
#    if(APPLE)
#        set(QEXT_BUILD_LIB_VLC OFF)
#        message(STATUS "Do not build the vlc lib, becase macos platform not support.")
#    endif()
#endif()
#
#if(QEXT_BUILD_LIB_WIDGETS)
#    set(QEXT_BUILD_LIB_ICONS ON)
#    set(QEXT_BUILD_LIB_GOOGLEPINYIN ON)
#endif()
#
#if(NOT QEXT_QT_HAS_QML)
#    set(QEXT_BUILD_QMLS OFF)
#    message(STATUS "Do not build the qml lib, becase Qt version must greater equal than 5.9.")
#endif()
#
#if(QEXT_BUILD_LIB_QCUSTOMPLOT)
#    if(NOT QEXT_QT_VERSION_MAJOR EQUAL 5)
#        set(QEXT_BUILD_LIB_QCUSTOMPLOT OFF)
#        message(STATUS "Do not build the qcustomplot lib, becase Qt major version must equal 5.")
#    endif()
#endif()
#
#if(QEXT_BUILD_LIB_QWT)
#    if(QEXT_QT_VERSION_MAJOR GREATER_EQUAL 6)
#        set(QEXT_BUILD_LIB_QWT OFF)
#        message(STATUS "Do not build the Qwt lib, becase Qt major version must less than 6.")
#    endif()
#endif()
#
#if(QEXT_BUILD_TESTS)
#    enable_testing()
#endif()


#-----------------------------------------------------------------------------------------------------------------------
# Set the output dir
#-----------------------------------------------------------------------------------------------------------------------
qext_ensure_define_variable(QEXT_OUTPUT_APP_DIR "${PROJECT_BINARY_DIR}/bin")
qext_ensure_define_variable(QEXT_OUTPUT_LIB_DIR "${PROJECT_BINARY_DIR}/lib")
qext_ensure_define_variable(QEXT_OUTPUT_LIBEXEC_DIR "${PROJECT_BINARY_DIR}/libexec")
qext_ensure_define_variable(QEXT_OUTPUT_PLUGIN_DIR "${PROJECT_BINARY_DIR}/plugin")
qext_ensure_define_variable(QEXT_OUTPUT_EXAMPLE_DIR "${PROJECT_BINARY_DIR}/example")
qext_ensure_define_variable(QEXT_OUTPUT_TEST_DIR "${PROJECT_BINARY_DIR}/test")
qext_ensure_define_variable(QEXT_OUTPUT_INCLUDE_DIR "${PROJECT_BINARY_DIR}/include")
qext_ensure_define_variable(QEXT_OUTPUT_DOC_DIR "${PROJECT_BINARY_DIR}/doc")


#-----------------------------------------------------------------------------------------------------------------------
# Set build options
#-----------------------------------------------------------------------------------------------------------------------
qext_option(QEXT_BUILD_ALL "Enable this to build all artifacts" OFF)
qext_option(QEXT_BUILD_SHARED_LIBS "Enable this to build as dynamically" ON
        SET BUILD_SHARED_LIBS)
qext_option(QEXT_BUILD_USE_PCH "Enable this to build use precompiled header files for compilation" ON
        DEPENDS QEXT_BUILD_SHARED_LIBS)
qext_option(QEXT_BUILD_COMPILER_WARNING "Enable this to build target with compiler warnings" OFF)
qext_option(QEXT_BUILD_WARNINGS_ARE_ERRORS "Build UTK with warnings as errors" ${__qext_build_warnings_as_errors})
qext_option(QEXT_BUILD_BENCHMARKS "Enable this to build the benchmarks" ${__qext_build_benchmarks}
        SET __qext_build_tests_default)
qext_option(QEXT_BUILD_EXAMPLES "Enable this to build examples" ON)
qext_option(QEXT_BUILD_TESTS "Enable this to build tests" ON)
qext_option(QEXT_BUILD_PLUGINS "Enable this to build the plugins." ON)
qext_option(QEXT_BUILD_TOOLS "Enable this to build the tools." "${__qext_build_tools_default}")
qext_option(QEXT_BUILD_APPS "Enable this to build apps" ON)
qext_option(QEXT_BUILD_DOCS "Enable this to build the documentation" OFF)
qext_option(QEXT_BUILD_INSTALL "Enable this to build the installer" ON)


#-----------------------------------------------------------------------------------------------------------------------
# Set doxygen build config
#-----------------------------------------------------------------------------------------------------------------------
if (QEXT_BUILD_DOCS)
    message(STATUS "Project build documentation")
    qext_build_doxygen()
endif ()


#-----------------------------------------------------------------------------------------------------------------------
# Set install and paths
#-----------------------------------------------------------------------------------------------------------------------
# Install locations:
qext_configure_process_path(INSTALL_BINDIR "bin" "Executables [PREFIX/bin]")
qext_configure_process_path(INSTALL_INCLUDEDIR "include" "Header files [PREFIX/include]")
qext_configure_process_path(INSTALL_LIBDIR "lib" "Libraries [PREFIX/lib]")
qext_configure_process_path(INSTALL_MKSPECSDIR "mkspecs" "Mkspecs files [PREFIX/mkspecs]")
qext_configure_process_path(INSTALL_ARCHDATADIR "." "Arch-dependent data [PREFIX]")
qext_configure_process_path(INSTALL_PLUGINSDIR "${INSTALL_ARCHDATADIR}/plugins" "Plugins [ARCHDATADIR/plugins]")

if (NOT INSTALL_MKSPECSDIR MATCHES "(^|/)mkspecs")
    message(FATAL_ERROR "INSTALL_MKSPECSDIR must end with '/mkspecs'")
endif ()

if (WIN32)
    set(_default_libexec "${INSTALL_ARCHDATADIR}/bin")
else ()
    set(_default_libexec "${INSTALL_ARCHDATADIR}/libexec")
endif ()

qext_configure_process_path(INSTALL_LIBEXECDIR
        "${_default_libexec}" "Helper programs [ARCHDATADIR/bin on Windows, ARCHDATADIR/libexec otherwise]")
qext_configure_process_path(INSTALL_DATADIR "." "Arch-independent data [PREFIX]")
qext_configure_process_path(INSTALL_DOCDIR "${INSTALL_DATADIR}/doc" "Documentation [DATADIR/doc]")
qext_configure_process_path(INSTALL_TRANSLATIONSDIR "${INSTALL_DATADIR}/translations" "Translations [DATADIR/translations]")
if (APPLE)
    set(QEXT_DEFAULT_SYS_CONF_DIR "/Library/Preferences/QEXT")
else ()
    set(QEXT_DEFAULT_SYS_CONF_DIR "etc/xdg")
endif ()
qext_configure_process_path(INSTALL_SYSCONFDIR
        "${QEXT_DEFAULT_SYS_CONF_DIR}" "Settings used by QEXT programs [PREFIX/etc/xdg]/[/Library/Preferences/QEXT]")
qext_configure_process_path(INSTALL_EXAMPLESDIR "examples" "Examples [PREFIX/examples]")
qext_configure_process_path(INSTALL_TESTSDIR "tests" "Tests [PREFIX/tests]")
qext_configure_process_path(INSTALL_DESCRIPTIONSDIR
        "${INSTALL_DATADIR}/modules" "Module description files directory")

if (NOT "${CMAKE_STAGING_PREFIX}" STREQUAL "")
    set(QEXT_STAGING_PREFIX "${CMAKE_STAGING_PREFIX}")
else ()
    set(QEXT_STAGING_PREFIX "${CMAKE_INSTALL_PREFIX}")
endif ()

function(qext_internal_set_up_global_paths)
    # Compute the values of QEXT_BUILD_DIR, QEXT_INSTALL_DIR, QEXT_CONFIG_BUILD_DIR, QEXT_CONFIG_INSTALL_DIR
    # taking into account whether the current build is a prefix build or a non-prefix build,
    # and whether it is a superbuild or non-superbuild.
    # A third case is when another module or standalone tests are built against a super-built QEXT.
    # The layout for the third case is the same as for non-superbuilds.
    #
    # These values should be prepended to file paths in commands or properties,
    # in order to correctly place generated Config files, generated Targets files,
    # executables / libraries, when copying / installing files, etc.
    #
    # The build dir variables will always be absolute paths.
    # The QEXT_INSTALL_DIR variable will have a relative path in a prefix build,
    # which means that it can be empty, so use qext_join_path to prevent accidental absolute paths.
    if (QEXT_SUPERBUILD)
        # In this case, we always copy all the build products in QEXT_BUILD_DIR/{bin,lib,...}
        if (QEXT_WILL_INSTALL)
            set(QEXT_BUILD_DIR "${QEXT_BINARY_DIR}")
            set(QEXT_INSTALL_DIR "")
        else ()
            if ("${CMAKE_STAGING_PREFIX}" STREQUAL "")
                set(QEXT_BUILD_DIR "${QEXT_BINARY_DIR}")
                set(QEXT_INSTALL_DIR "${QEXT_BINARY_DIR}")
            else ()
                set(QEXT_BUILD_DIR "${CMAKE_STAGING_PREFIX}")
                set(QEXT_INSTALL_DIR "${CMAKE_STAGING_PREFIX}")
            endif ()
        endif ()
    else ()
        if (QEXT_WILL_INSTALL)
            # In the usual prefix build case, the build dir is the current module build dir,
            # and the install dir is the prefix, so we don't set it.
            set(QEXT_BUILD_DIR "${CMAKE_BINARY_DIR}")
            set(QEXT_INSTALL_DIR "")
        else ()
            # When doing a non-prefix build, both the build dir and install dir are the same, pointing to the QEXT build dir.
            set(QEXT_BUILD_DIR "${QEXT_STAGING_PREFIX}")
            set(QEXT_INSTALL_DIR "${QEXT_BUILD_DIR}")
        endif ()
    endif ()

    set(__config_path_part "${INSTALL_LIBDIR}/cmake")
    set(QEXT_CONFIG_BUILD_DIR "${QEXT_BUILD_DIR}/${__config_path_part}")
    set(QEXT_CONFIG_INSTALL_DIR "${QEXT_INSTALL_DIR}")
    if (QEXT_CONFIG_INSTALL_DIR)
        string(APPEND QEXT_CONFIG_INSTALL_DIR "/")
    endif ()
    string(APPEND QEXT_CONFIG_INSTALL_DIR ${__config_path_part})

    set(QEXT_BUILD_DIR "${QEXT_BUILD_DIR}" PARENT_SCOPE)
    set(QEXT_INSTALL_DIR "${QEXT_INSTALL_DIR}" PARENT_SCOPE)
    set(QEXT_CONFIG_BUILD_DIR "${QEXT_CONFIG_BUILD_DIR}" PARENT_SCOPE)
    set(QEXT_CONFIG_INSTALL_DIR "${QEXT_CONFIG_INSTALL_DIR}" PARENT_SCOPE)
endfunction()
qext_internal_set_up_global_paths()


###TODO:del
## Find the path to mkspecs/, depending on whether we are building as part of a standard qextbuild,
## or a module against an already installed version of qext.
#if(NOT QEXT_MKSPECS_DIR)
#    if("${QEXT_BUILD_INTERNALS_PATH}" STREQUAL "")
#        get_filename_component(QEXT_MKSPECS_DIR "${CMAKE_CURRENT_LIST_DIR}/../mkspecs" ABSOLUTE)
#    else()
#        # We can rely on QEXT_BUILD_INTERNALS_RELOCATABLE_INSTALL_PREFIX being set by
#        # QEXTBuildInternalsExtra.cmake.
#        get_filename_component(QEXT_MKSPECS_DIR
#            "${QEXT_BUILD_INTERNALS_RELOCATABLE_INSTALL_PREFIX}/${INSTALL_MKSPECSDIR}" ABSOLUTE)
#    endif()
#    set(QEXT_MKSPECS_DIR "${QEXT_MKSPECS_DIR}" CACHE INTERNAL "")
#endif()

# the default RPATH to be used when installing, but only if it's not a system directory
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/${INSTALL_LIBDIR}" isSystemDir)
if ("${isSystemDir}" STREQUAL "-1")
    set(_default_install_rpath "${CMAKE_INSTALL_PREFIX}/${INSTALL_LIBDIR}")
endif ("${isSystemDir}" STREQUAL "-1")

# The default rpath settings for installed targets is empty.
# The rpaths will instead be computed for each target separately using qext_apply_rpaths().
# Additional rpaths can be passed via QEXT_EXTRA_RPATHS.
# By default this will include $ORIGIN / @loader_path, so the installation is relocatable.
# Bottom line: No need to pass anything to CMAKE_INSTALL_RPATH.
set(CMAKE_INSTALL_RPATH "" CACHE STRING "RPATH for installed binaries")

# By default, don't embed auto-determined RPATHs pointing to directories
# outside of the build tree, into the installed binaries.
# This ended up adding rpaths like ${CMAKE_INSTALL_PREFIX}/lib (or /Users/qext/work/install/lib into
# the official libraries created by the CI) into the non-qextbase libraries, plugins, etc.
#
# It should not be necessary, given that qext_apply_rpaths() already adds the necessary rpaths, either
# relocatable ones or absolute ones, depending on what the platform supports.
if (NOT QEXT_NO_DISABLE_CMAKE_INSTALL_RPATH_USE_LINK_PATH)
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
endif ()

# Ensure that GNUInstallDirs's CMAKE_INSTALL_LIBDIR points to the same lib dir that QEXT was
# configured with. Currently this is important for QML plugins, which embed an rpath based
# on that value.
set(CMAKE_INSTALL_LIBDIR "${INSTALL_LIBDIR}")

function(qext_setup_tool_path_command)
    if (NOT CMAKE_HOST_WIN32)
        return()
    endif ()
    set(bindir "${QEXT_BUILD_INTERNALS_RELOCATABLE_INSTALL_PREFIX}/${INSTALL_BINDIR}")
    file(TO_NATIVE_PATH "${bindir}" bindir)
    list(APPEND command COMMAND)
    list(APPEND command set PATH=${bindir}$<SEMICOLON>%PATH%)
    set(QEXT_TOOL_PATH_SETUP_COMMAND "${command}" CACHE INTERNAL "internal command prefix for tool invocations" FORCE)
    # QEXT_TOOL_PATH_SETUP_COMMAND is deprecated. Please use _qext_internal_get_wrap_tool_script_path
    # instead.
endfunction()
qext_setup_tool_path_command()

if (QEXT_BUILD_TESTS)
    include(CTest)
    enable_testing()
endif ()


#-----------------------------------------------------------------------------------------------------------------------
# Set namespace and separator
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_NAMESPACE_VERSION ${QEXT_VERSION_MAJOR})
set(QEXT_NAMESPACE "" CACHE STRING "QExt Namespace")
if (NOT INSTALL_CMAKE_NAMESPACE)
    set(INSTALL_CMAKE_NAMESPACE "QExt${QEXT_NAMESPACE_VERSION}" CACHE STRING "CMake namespace [QExt${QEXT_NAMESPACE_VERSION}]")
endif ()
if (NOT QEXT_CMAKE_EXPORT_NAMESPACE)
    set(QEXT_CMAKE_EXPORT_NAMESPACE "QExt${QEXT_NAMESPACE_VERSION}"
            CACHE STRING "CMake namespace used when exporting targets [QExt${QEXT_NAMESPACE_VERSION}]")
endif ()

set(QEXT_KNOWN_LIBRARIES_WITH_TOOLS "" CACHE INTERNAL "Known QExt modules with tools" FORCE)

# For adjusting variables when running tests, we need to know what
# the correct variable is for separating entries in PATH-alike
# variables.
if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(QEXT_PATH_SEPARATOR "\\;")
else ()
    set(QEXT_PATH_SEPARATOR ":")
endif ()

# Save the value of the current first project source dir.
# This will be /path/to/QEXTCore for QEXTCore both in a super-build and a non super-build.
# This will be /path/to/QEXTCore/tests when building standalone tests.
set(QEXT_TOP_LEVEL_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")


#-----------------------------------------------------------------------------------------------------------------------
# Prevent warnings about object files without any symbols. This is a common thing in QEXT as we tend to build files
# unconditionally, and then use ifdefs to compile out parts that are not relevant.
#-----------------------------------------------------------------------------------------------------------------------
if (CMAKE_HOST_APPLE AND APPLE)
    foreach (lang ASM C CXX)
        # We have to tell 'ar' to not run ranlib by itself, by passing the 'S' option
        set(CMAKE_${lang}_ARCHIVE_CREATE "<CMAKE_AR> qcS <TARGET> <LINK_FLAGS> <OBJECTS>")
        set(CMAKE_${lang}_ARCHIVE_APPEND "<CMAKE_AR> qS <TARGET> <LINK_FLAGS> <OBJECTS>")
        set(CMAKE_${lang}_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols <TARGET>")
    endforeach ()
endif ()


#-----------------------------------------------------------------------------------------------------------------------
# build directory check
#-----------------------------------------------------------------------------------------------------------------------
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run "
            "CMake from there. You may need to remove CMakeCache.txt.")
endif ()

if (CMAKE_CROSSCOMPILING AND NOT IS_DIRECTORY "${QEXT_HOST_PATH}")
    message(FATAL_ERROR "You need to set QEXT_HOST_PATH to cross compile QEXT.")
endif ()


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
        PLUGIN_TYPES)
set(QEXT_DEFAULT_PUBLIC_ARGS
        PUBLIC_DEFINES
        PUBLIC_LIBRARIES
        PUBLIC_INCLUDE_DIRECTORIES
        PUBLIC_COMPILE_OPTIONS
        PUBLIC_LINK_OPTIONS)
set(QEXT_DEFAULT_PRIVATE_LIBRARY_ARGS
        PRIVATE_LIBRARY_INTERFACE)
set(QEXT_DEFAULT_TARGET_INFO_ARGS
        TARGET_VERSION
        TARGET_PRODUCT
        TARGET_DESCRIPTION
        TARGET_COMPANY
        TARGET_COPYRIGHT)


# Collection of arguments so they can be shared across qext_internal_add_executable and qext_internal_add_test_helper.
set(QEXT_INTERNAL_ADD_EXECUTABLE_OPTIONAL_ARGS
        GUI
        NO_INSTALL
        EXCEPTIONS
        DELAY_RC
        DELAY_TARGET_INFO
        QEXT_APP)
set(QEXT_INTERNAL_ADD_EXECUTABLE_SINGLE_ARGS
        CORE_LIBRARY
        OUTPUT_DIRECTORY
        INSTALL_DIRECTORY
        VERSION
        ${QEXT_DEFAULT_TARGET_INFO_ARGS})
set(QEXT_INTERNAL_ADD_EXECUTABLE_MULTI_ARGS
        ${QEXT_DEFAULT_PRIVATE_ARGS}
        ${QEXT_DEFAULT_PUBLIC_ARGS})


#--------------------------------------------------------------------------------
# add subdirectory
#--------------------------------------------------------------------------------
add_subdirectory(src/libs)
#add_subdirectory(src/apps)
#add_subdirectory(src/plugins)
#add_subdirectory(src/qml)


#--------------------------------------------------------------------------------
# add 3rdparty subdirectory
#--------------------------------------------------------------------------------
#if(QEXT_BUILD_LIB_QWT)
#    add_subdirectory(3rdparty/qwt-6.1.3)
#endif()

#if(QEXT_BUILD_LIB_QCUSTOMPLOT)
#    add_subdirectory(3rdparty/qcustomplot)
#endif()


#--------------------------------------------------------------------------------
# Set install
#--------------------------------------------------------------------------------
if (QEXT_BUILD_INSTALL)
    include(CPackComponent)
    include(InstallRequiredSystemLibraries)
    set(CPACK_PACKAGE_NAME ${QEXT_PRODUCT_NAME})
    set(CPACK_PACKAGE_FILE_NAME ${QEXT_PRODUCT_NAME})
    set(CPACK_PACKAGE_VENDOR ${QEXT_PRODUCT_NAME})
    set(CPACK_PACKAGE_INSTALL_DIRECTORY @ApplicationsDir@)    # Installation directory on the target system.
    set(CPACK_SOURCE_GENERATOR ";")
    set(CPACK_CREATE_DESKTOP_LINKS ${QEXT_PRODUCT_NAME})
    include(CPack REQUIRED)

    install(
            DIRECTORY ${QEXT_OUTPUT_APP_DIR}
            DESTINATION ./bin
            COMPONENT Apps
            PATTERN bin/* PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ
    )
    install(
            DIRECTORY ${QEXT_OUTPUT_LIB_DIR}
            DESTINATION ./lib
            COMPONENT Libs
    )
    install(
            DIRECTORY ${QEXT_OUTPUT_QML_DIR}
            DESTINATION ./qml
            COMPONENT Qml
    )
    install(
            DIRECTORY ${QEXT_OUTPUT_EXAMPLE_DIR}
            DESTINATION ./example
            COMPONENT Example
            PATTERN bin/* PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ
    )
    install(
            DIRECTORY ${QEXT_OUTPUT_INCLUDE_DIR}
            DESTINATION ./include
            COMPONENT Include
    )
endif ()
