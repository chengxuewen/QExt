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



#--------------------------------------------------------------------------------
# Set project name and version
#--------------------------------------------------------------------------------
project(QEXT VERSION 0.15.1.3 LANGUAGES CXX C)
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

set(QEXT_QT_HAS_QJSON OFF)
set(QEXT_QT_HAS_QML OFF)
find_package(Qt4 QUIET COMPONENTS QtCore QUIET)
if (NOT QT_FOUND)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core QUIET)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core QUIET)
endif()
set(QEXT_QT_VERSION_MAJOR ${QT_VERSION_MAJOR})
set(QEXT_QT_VERSION_MINOR ${QT_VERSION_MINOR})
set(QEXT_QT_VERSION_PATCH ${QT_VERSION_PATCH})
set(QEXT_QT_VERSION "${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
if (QEXT_QT_VERSION_MAJOR EQUAL 4)
    if (QEXT_QT_VERSION_MINOR LESS 8)
        message(FATAL_ERROR "----QEXT---- Expected Qt4 version must greater than or equal to Qt4.8")
    endif()
    message(STATUS "----QEXT---- Expected Qt version is Qt${QEXT_QT_VERSION}")
    find_package(Qt4 REQUIRED QtCore QtGui QtTest QtNetwork)
    include(${QT_USE_FILE})
    add_definitions(${QT_DEFINITIONS})
    find_package(Qt4 COMPONENTS QtOpenGL)
    set(QEXT_QT_OPENGL_FOUND ${QT_QTOPENGL_FOUND})
    set(QEXT_CXX_STANDARD 98)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    message(STATUS "----QEXT---- Expected Qt version is Qt${QEXT_QT_VERSION}")
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS Core Widgets Network Quick Test PrintSupport Svg REQUIRED)
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS OpenGL)
    set(QEXT_QT_OPENGL_FOUND ${Qt${QEXT_QT_VERSION_MAJOR}OpenGL_FOUND})
    if(QEXT_QT_VERSION_MAJOR EQUAL 5 AND QEXT_QT_VERSION_MINOR GREATER_EQUAL 12)
        find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS Qml QuickControls2 REQUIRED)
        set(QEXT_QT_HAS_QML ON)
    else()
        set(QEXT_QT_HAS_QML OFF)
    endif()
    set(QEXT_QT_HAS_QJSON ON)
    set(QEXT_CXX_STANDARD 11)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 6)
    message(STATUS "----QEXT---- Expected Qt version is Qt${QEXT_QT_VERSION}")
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS Core Widgets Network Quick Test PrintSupport Svg REQUIRED)
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS Qml QuickControls2 Core5Compat REQUIRED)
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS Core5Compat REQUIRED)
    find_package(Qt${QEXT_QT_VERSION_MAJOR} COMPONENTS OpenGLWidgets OpenGL)
    set(QEXT_QT_OPENGL_FOUND ${Qt${QEXT_QT_VERSION_MAJOR}OpenGL_FOUND})
    set(QEXT_QT_HAS_QML ON)
    set(QEXT_QT_HAS_QJSON ON)
    set(QEXT_CXX_STANDARD 17)
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
# Specify the C++ standard and flags
#--------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD ${QEXT_CXX_STANDARD})
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "----QEXT---- Using C++: ${QEXT_CXX_STANDARD}")
message(STATUS "----QEXT---- Set C++ extensions: ${CMAKE_CXX_EXTENSIONS}")

if(WIN32)
    if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
        # open bigobj flags in msvc compiler(bigobj)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
    elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
        # open bigobj flags in gnu/mingw compiler(File too big/too many sections)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
    endif()
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
if(CMAKE_SYSTEM_PROCESSOR MATCHES i386)
    set(QEXT_SYSTEM_PROCESSOR_I386 ON)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES i686)
    set(QEXT_SYSTEM_PROCESSOR_I686 ON)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES x86_64)
    set(QEXT_SYSTEM_PROCESSOR_X86_64 ON)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES AMD64)
    set(QEXT_SYSTEM_PROCESSOR_AMD64 ON)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES ARM)
    set(QEXT_SYSTEM_PROCESSOR_ARM ON)
else()
    set(QEXT_SYSTEM_PROCESSOR_UNKNOWN Unknown)
endif()



#--------------------------------------------------------------------------------
# Add CMake function(s) and macro(s)
#--------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
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



#--------------------------------------------------------------------------------
# Specify the output dir
#--------------------------------------------------------------------------------
qextMacroEnsureDefineCacheVariable(QEXT_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR} STRING)
qextMacroEnsureDefineCacheVariable(QEXT_PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR} STRING)
qextMacroEnsureDefineCacheVariable(QEXT_OUTPUT_APP_DIR ${PROJECT_BINARY_DIR}/bin STRING)
qextMacroEnsureDefineCacheVariable(QEXT_OUTPUT_LIB_DIR ${PROJECT_BINARY_DIR}/lib STRING)
qextMacroEnsureDefineCacheVariable(QEXT_OUTPUT_PLUGIN_DIR ${PROJECT_BINARY_DIR}/plugin STRING)
qextMacroEnsureDefineCacheVariable(QEXT_OUTPUT_QML_DIR ${PROJECT_BINARY_DIR}/qml STRING)
qextMacroEnsureDefineCacheVariable(QEXT_OUTPUT_INCLUDE_DIR ${PROJECT_BINARY_DIR}/include STRING)
qextMacroEnsureDefineCacheVariable(QEXT_OUTPUT_EXAMPLE_DIR ${PROJECT_BINARY_DIR}/example STRING)
qextMacroEnsureDefineCacheVariable(QEXT_OUTPUT_TEST_DIR ${PROJECT_BINARY_DIR}/test STRING)



#--------------------------------------------------------------------------------
# Set option
#--------------------------------------------------------------------------------
qextMacroEnsureDefineVariable(BUILD_QEXT_SHARED ON)
qextMacroEnsureDefineVariable(BUILD_QEXT_USE_PCH ON)
qextMacroEnsureDefineVariable(BUILD_QEXT_COMPILER_WARNING OFF)

qextMacroEnsureDefineVariable(USE_QEXT_ALL ON)
qextMacroEnsureDefineVariable(USE_QEXT_DEVICEWATCHER ${USE_QEXT_ALL})
qextMacroEnsureDefineVariable(USE_QEXT_FRAMELESSHELPER ${USE_QEXT_ALL})
qextMacroEnsureDefineVariable(USE_QEXT_GOOGLEPINYIN ${USE_QEXT_ALL})
qextMacroEnsureDefineVariable(USE_QEXT_ICONFONT ${USE_QEXT_ALL})
qextMacroEnsureDefineVariable(USE_QEXT_SERIALPORT ${USE_QEXT_ALL})
qextMacroEnsureDefineVariable(USE_QEXT_SINGLEAPP ${USE_QEXT_ALL})
qextMacroEnsureDefineVariable(USE_QEXT_STYLETHEME ${USE_QEXT_ALL})
qextMacroEnsureDefineVariable(USE_QEXT_TCP ${USE_QEXT_ALL})
qextMacroEnsureDefineVariable(USE_QEXT_UTILS ${USE_QEXT_ALL})
qextMacroEnsureDefineVariable(USE_QEXT_VLC ${USE_QEXT_ALL})
qextMacroEnsureDefineVariable(USE_QEXT_WIDGETS ${USE_QEXT_ALL})

qextMacroEnsureDefineVariable(USE_QEXT_QML_FRAMELESSHELPER ${USE_QEXT_ALL})
qextMacroEnsureDefineVariable(USE_QEXT_QML_QUICK ${USE_QEXT_ALL})
qextMacroEnsureDefineVariable(USE_QEXT_QML_THEME ${USE_QEXT_ALL})
qextMacroEnsureDefineVariable(USE_QEXT_QML_VLC ${USE_QEXT_ALL})

qextMacroEnsureDefineVariable(USE_QEXT_QWT ${USE_QEXT_ALL})
qextMacroEnsureDefineVariable(USE_QEXT_QCUSTOMPLOT ${USE_QEXT_ALL})

option(QEXT_BUILD_QMLS "Build qmls" ON)
option(QEXT_BUILD_TESTS "Build tests" OFF)
option(QEXT_BUILD_PLUGINS "Build plugins" ON)
option(QEXT_BUILD_EXAMPLES "Build examples" OFF)
option(QEXT_BUILD_INSTALL "Build install" OFF)
option(QEXT_BUILD_DOCUMENTATION "Enable this to build the documentation" OFF)
option(QEXT_BUILD_SHARED_LIBS "Build shared library" ${BUILD_QEXT_SHARED})
option(QEXT_BUILD_COMPILER_WARNING "Build target with compiler warnings" ${BUILD_QEXT_COMPILER_WARNING})
option(QEXT_BUILD_USE_PCH "Enable this to build use precompiled header files for compilation" ${BUILD_QEXT_USE_PCH})


option(QEXT_BUILD_LIB_DEVICEWATCHER "Enable this to build the devicewatcher lib" ${USE_QEXT_DEVICEWATCHER})
option(QEXT_BUILD_LIB_FRAMELESSHELPER "Enable this to build the framelesshelper lib" ${USE_QEXT_FRAMELESSHELPER})
option(QEXT_BUILD_LIB_GOOGLEPINYIN "Enable this to build the googlepinyin lib" ${USE_QEXT_GOOGLEPINYIN})
option(QEXT_BUILD_LIB_ICONFONT "Enable this to build the iconfont lib" ${USE_QEXT_ICONFONT})
option(QEXT_BUILD_LIB_SERIALPORT "Enable this to build the serialport lib" ${USE_QEXT_SERIALPORT})
option(QEXT_BUILD_LIB_SINGLEAPP "Enable this to build the singleapp lib" ${USE_QEXT_SINGLEAPP})
option(QEXT_BUILD_LIB_STYLETHEME "Enable this to build the styletheme lib" ${USE_QEXT_STYLETHEME})
option(QEXT_BUILD_LIB_TCP "Enable this to build the tcp lib" ${USE_QEXT_TCP})
option(QEXT_BUILD_LIB_UTILS "Enable this to build the utils lib" ${USE_QEXT_UTILS})
option(QEXT_BUILD_LIB_VLC "Enable this to build the VLC lib" ${USE_QEXT_VLC})
option(QEXT_BUILD_LIB_WIDGETS "Enable this to build the widgets lib" ${USE_QEXT_WIDGETS})

option(QEXT_BUILD_LIB_QML_FRAMELESSHELPER "Enable this to build the qml framelesshelper lib" ${USE_QEXT_QML_FRAMELESSHELPER})
option(QEXT_BUILD_LIB_QML_QUICK "Enable this to build the qml quick lib" ${USE_QEXT_QML_QUICK})
option(QEXT_BUILD_LIB_QML_THEME "Enable this to build the qml theme lib" ${USE_QEXT_QML_THEME})
option(QEXT_BUILD_LIB_QML_VLC "Enable this to build the qml VLC lib" ${USE_QEXT_QML_VLC})

option(QEXT_BUILD_LIB_QWT "Enable this to build the qwt lib" ${USE_QEXT_QWT})
option(QEXT_BUILD_LIB_QCUSTOMPLOT "Enable this to build the qcustomplot lib" ${USE_QEXT_QCUSTOMPLOT})


if(QEXT_BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build as shared libraries")
    message(STATUS "----QEXT---- Build as shared libraries")
else()
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build as static libraries")
    message(STATUS "----QEXT---- Build as static libraries")
endif()

if(QEXT_BUILD_USE_PCH)
    if(NOT ${QEXT_BUILD_SHARED_LIBS})
        set(QEXT_BUILD_USE_PCH FALSE)
        message(STATUS "----QEXT---- Do not build use pch, becase QEXT build shared library.")
    endif()
endif()

if(QEXT_BUILD_DOCUMENTATION)
    qextMacroBuildDoxygen()
    message(STATUS "----QEXT---- Build with the documentation")
else()
    message(STATUS "----QEXT---- Build with no documentation")
endif()


if(QEXT_BUILD_LIB_TCP)
    set(QEXT_BUILD_LIB_UTILS ON)
endif()

if(QEXT_BUILD_LIB_FRAMELESSHELPER)
    if(QEXT_QT_VERSION_MAJOR LESS 5)
        message(STATUS "----QEXT---- Do not build framelesshelper lib, becase Qt major version must greater than 5.")
        set(QEXT_BUILD_LIB_FRAMELESSHELPER OFF)
    endif()
    if(NOT WIN32)
        message(STATUS "----QEXT---- Do not build framelesshelper lib, becase framelesshelper only support windows platform.")
        set(QEXT_BUILD_LIB_FRAMELESSHELPER OFF)
    endif()
endif()

if(QEXT_BUILD_LIB_VLC)
    if(QEXT_QT_VERSION LESS 5.0)
        set(QEXT_BUILD_LIB_VLC OFF)
        message(STATUS "----QEXT---- Do not build the vlc lib, becase Qt major version must greater than 5.0.")
    endif()
    qextMacroFindLibVLC()
    if(NOT QEXT_LIBVLC_FOUND)
        set(QEXT_BUILD_LIB_VLC OFF)
        message(STATUS "----QEXT---- Do not build the vlc lib, becase not found vlc lib.")
    endif()
    if(APPLE)
        set(QEXT_BUILD_LIB_VLC OFF)
        message(STATUS "----QEXT---- Do not build the vlc lib, becase macos platform not support.")
    endif()
endif()

if(QEXT_BUILD_LIB_WIDGETS)
    set(QEXT_BUILD_LIB_ICONS ON)
    set(QEXT_BUILD_LIB_GOOGLEPINYIN ON)
endif()

if(NOT QEXT_QT_HAS_QML)
    set(QEXT_BUILD_QMLS OFF)
    message(STATUS "----QEXT---- Do not build the qml lib, becase Qt version must greater equal than 5.9.")
endif()

if(QEXT_BUILD_LIB_QCUSTOMPLOT)
    if(NOT QEXT_QT_VERSION_MAJOR EQUAL 5)
        set(QEXT_BUILD_LIB_QCUSTOMPLOT OFF)
        message(STATUS "----QEXT---- Do not build the qcustomplot lib, becase Qt major version must equal 5.")
    endif()
endif()

if(QEXT_BUILD_LIB_QWT)
    if(QEXT_QT_VERSION_MAJOR GREATER_EQUAL 6)
        set(QEXT_BUILD_LIB_QWT OFF)
        message(STATUS "----QEXT---- Do not build the Qwt lib, becase Qt major version must less than 6.")
    endif()
endif()

if(QEXT_BUILD_TESTS)
    enable_testing()
endif()



#--------------------------------------------------------------------------------
# add subdirectory
#--------------------------------------------------------------------------------
add_subdirectory(src/libs)
add_subdirectory(src/apps)
add_subdirectory(src/plugins)
add_subdirectory(src/qml)



#--------------------------------------------------------------------------------
# add 3rdparty subdirectory
#--------------------------------------------------------------------------------
if(QEXT_BUILD_LIB_QWT)
    add_subdirectory(3rdparty/qwt-6.1.3)
endif()

if(QEXT_BUILD_LIB_QCUSTOMPLOT)
    add_subdirectory(3rdparty/qcustomplot)
endif()



#--------------------------------------------------------------------------------
# Set install
#--------------------------------------------------------------------------------
if(QEXT_BUILD_INSTALL)
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
endif()
