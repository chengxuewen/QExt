########################################################################################################################
#
# Library: QEXT
#
# Copyright (C) 2022 ChengXueWen.
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
# qext_set01 finction
#-----------------------------------------------------------------------------------------------------------------------
function(qext_set01 result)
    if(${ARGN})
        set("${result}" 1 PARENT_SCOPE)
    else()
        set("${result}" 0 PARENT_SCOPE)
    endif()
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
# utk set system variable
#-----------------------------------------------------------------------------------------------------------------------
message(STATUS "Build in system: ${CMAKE_SYSTEM_NAME}")
set(QEXT_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})
set(QEXT_SYSTEM_VERSION ${CMAKE_SYSTEM_VERSION})
set(QEXT_SYSTEM_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR})
qext_set01(QEXT_SYSTEM_LINUX
    CMAKE_SYSTEM_NAME STREQUAL "Linux")
qext_set01(QEXT_SYSTEM_WINCE
    CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
qext_set01(QEXT_SYSTEM_WIN
    QEXT_SYSTEM_WINCE OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
qext_set01(QEXT_SYSTEM_HPUX
    CMAKE_SYSTEM_NAME STREQUAL "HPUX")
qext_set01(QEXT_SYSTEM_ANDROID
    CMAKE_SYSTEM_NAME STREQUAL "Android")
qext_set01(QEXT_SYSTEM_NACL
    CMAKE_SYSTEM_NAME STREQUAL "NaCl")
qext_set01(QEXT_SYSTEM_INTEGRITY
    CMAKE_SYSTEM_NAME STREQUAL "Integrity")
qext_set01(QEXT_SYSTEM_VXWORKS
    CMAKE_SYSTEM_NAME STREQUAL "VxWorks")
qext_set01(QEXT_SYSTEM_QNX
    CMAKE_SYSTEM_NAME STREQUAL "QNX")
qext_set01(QEXT_SYSTEM_OPENBSD
    CMAKE_SYSTEM_NAME STREQUAL "OpenBSD")
qext_set01(QEXT_SYSTEM_FREEBSD
    CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
qext_set01(QEXT_SYSTEM_NETBSD
    CMAKE_SYSTEM_NAME STREQUAL "NetBSD")
qext_set01(QEXT_SYSTEM_WASM
    CMAKE_SYSTEM_NAME STREQUAL "Emscripten" OR EMSCRIPTEN)
qext_set01(QEXT_SYSTEM_SOLARIS
    CMAKE_SYSTEM_NAME STREQUAL "SunOS")
qext_set01(QEXT_SYSTEM_HURD
    CMAKE_SYSTEM_NAME STREQUAL "GNU")
# This is the only reliable way we can determine the webOS platform as the yocto recipe adds this compile definition
# into its generated toolchain.cmake file
qext_set01(QEXT_SYSTEM_WEBOS
    CMAKE_CXX_FLAGS MATCHES "-D__WEBOS__")
qext_set01(QEXT_SYSTEM_BSD
    APPLE OR OPENBSD OR FREEBSD OR NETBSD)
qext_set01(QEXT_SYSTEM_DARWIN
    APPLE OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
qext_set01(QEXT_SYSTEM_IOS
    APPLE AND CMAKE_SYSTEM_NAME STREQUAL "iOS")
qext_set01(QEXT_SYSTEM_TVOS
    APPLE AND CMAKE_SYSTEM_NAME STREQUAL "tvOS")
qext_set01(QEXT_SYSTEM_WATCHOS
    APPLE AND CMAKE_SYSTEM_NAME STREQUAL "watchOS")
qext_set01(QEXT_SYSTEM_UIKIT
    APPLE AND (IOS OR TVOS OR WATCHOS))
qext_set01(QEXT_SYSTEM_MACOS
    APPLE AND NOT UIKIT)
qext_set01(QEXT_SYSTEM_UNIX UNIX)
qext_set01(QEXT_SYSTEM_WIN32 WIN32)
qext_set01(QEXT_SYSTEM_APPLE APPLE)


#-----------------------------------------------------------------------------------------------------------------------
# utk set processor variable
#-----------------------------------------------------------------------------------------------------------------------
message(STATUS "Build in processor: ${CMAKE_SYSTEM_PROCESSOR}")
set(QEXT_SYSTEM_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR})
qext_set01(QEXT_PROCESSOR_I386
    CMAKE_SYSTEM_PROCESSOR STREQUAL "i386")
qext_set01(QEXT_PROCESSOR_I686
    CMAKE_CXX_COMPILER_ID MATCHES "i686")
qext_set01(QEXT_PROCESSOR_X86_64
    CMAKE_CXX_COMPILER_ID MATCHES "x86_64")
qext_set01(QEXT_PROCESSOR_X86
    CMAKE_CXX_COMPILER_ID MATCHES "x86")
qext_set01(QEXT_PROCESSOR_AMD64
    CMAKE_CXX_COMPILER_ID STREQUAL "amd64")
qext_set01(QEXT_PROCESSOR_ARM64
    CMAKE_CXX_COMPILER_ID STREQUAL "arm64")
qext_set01(QEXT_PROCESSOR_ARM32
    CMAKE_CXX_COMPILER_ID STREQUAL "arm32")
qext_set01(QEXT_PROCESSOR_ARM
    QEXT_PROCESSOR_ARM64 OR QEXT_PROCESSOR_ARM32)


#-----------------------------------------------------------------------------------------------------------------------
# utk set cxx compiler variable
#-----------------------------------------------------------------------------------------------------------------------
message(STATUS "Build in cxx compiler: ${CMAKE_CXX_COMPILER_ID}")
set(QEXT_CXX_COMPILER_ID ${CMAKE_CXX_COMPILER_ID})
set(QEXT_CXX_COMPILER_VERSION ${CMAKE_CXX_COMPILER_VERSION})
qext_set01(QEXT_CXX_COMPILER_GNU
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
qext_set01(QEXT_CXX_COMPILER_MSVC
    MSVC OR CMAKE_CXX_COMPILER_ID STREQUAL "Msvc")
qext_set01(QEXT_CXX_COMPILER_MINGW
    MINGW OR CMAKE_CXX_COMPILER_ID STREQUAL "Mingw")
qext_set01(QEXT_CXX_COMPILER_CLANG
    CMAKE_CXX_COMPILER_ID MATCHES "Clang|IntelLLVM")
qext_set01(QEXT_CXX_COMPILER_APPLE_CLANG
    CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
qext_set01(QEXT_CXX_COMPILER_INTEL_LLVM
    CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
qext_set01(QEXT_CXX_COMPILER_QCC
    CMAKE_CXX_COMPILER_ID STREQUAL "QCC") # CMP0047


#-----------------------------------------------------------------------------------------------------------------------
# utk arch size variable
#-----------------------------------------------------------------------------------------------------------------------
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(QEXT_ARCH_64BIT TRUE)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(QEXT_ARCH_32BIT TRUE)
endif()


#-----------------------------------------------------------------------------------------------------------------------
# utk mkspecs version
#-----------------------------------------------------------------------------------------------------------------------
if(QEXT_SYSTEM_WIN32)
    set(QEXT_DEFAULT_PLATFORM_DEFINITIONS WIN32 _ENABLE_EXTENDED_ALIGNED_STORAGE)
    if(QEXT_ARCH_64BIT)
        list(APPEND QEXT_DEFAULT_PLATFORM_DEFINITIONS WIN64 _WIN64)
    endif()
    if(QEXT_CXX_COMPILER_MSVC)
        if(QEXT_CXX_COMPILER_CLANG)
            set(QEXT_DEFAULT_MKSPEC win32-clang-msvc)
        elseif(QEXT_PROCESSOR_ARM64)
            set(QEXT_DEFAULT_MKSPEC win32-arm64-msvc)
        else()
            set(QEXT_DEFAULT_MKSPEC win32-msvc)
        endif()
    elseif(QEXT_CXX_COMPILER_CLANG AND QEXT_CXX_COMPILER_MINGW)
        set(QEXT_DEFAULT_MKSPEC win32-clang-g++)
    elseif(QEXT_CXX_COMPILER_MINGW)
        set(QEXT_DEFAULT_MKSPEC win32-g++)
    endif()

    if(QEXT_CXX_COMPILER_MINGW)
        list(APPEND QEXT_DEFAULT_PLATFORM_DEFINITIONS MINGW_HAS_SECURE_API=1)
    endif()
elseif(QEXT_SYSTEM_LINUX)
    if(QEXT_CXX_COMPILER_GNU)
        set(QEXT_DEFAULT_MKSPEC linux-g++)
    elseif(QEXT_CXX_COMPILER_CLANG)
        set(QEXT_DEFAULT_MKSPEC linux-clang)
    endif()
elseif(QEXT_SYSTEM_ANDROID)
    if(QEXT_CXX_COMPILER_GNU)
        set(QEXT_DEFAULT_MKSPEC android-g++)
    elseif(QEXT_CXX_COMPILER_CLANG)
        set(QEXT_DEFAULT_MKSPEC android-clang)
    endif()
elseif(QEXT_SYSTEM_IOS)
    set(QEXT_DEFAULT_MKSPEC macx-ios-clang)
elseif(QEXT_SYSTEM_APPLE)
    set(QEXT_DEFAULT_MKSPEC macx-clang)
elseif(QEXT_SYSTEM_WASM)
    set(QEXT_DEFAULT_MKSPEC wasm-emscripten)
elseif(QEXT_SYSTEM_QNX)
    # Certain POSIX defines are not set if we don't compile with -std=gnuXX
    set(QEXT_ENABLE_CXX_EXTENSIONS ON)

    list(APPEND QEXT_DEFAULT_PLATFORM_DEFINITIONS _FORTIFY_SOURCE=2 _REENTRANT)

    set(compiler_aarch64le aarch64le)
    set(compiler_armle-v7 armv7le)
    set(compiler_x86-64 x86_64)
    set(compiler_x86 x86)
    foreach(arch aarch64le armle-v7 x86-64 x86)
        if(CMAKE_CXX_COMPILER_TARGET MATCHES "${compiler_${arch}}$")
            set(QEXT_DEFAULT_MKSPEC qnx-${arch}-qcc)
        endif()
    endforeach()
elseif(QEXT_SYSTEM_FREEBSD)
    if(QEXT_CXX_COMPILER_CLANG)
        set(QEXT_DEFAULT_MKSPEC freebsd-clang)
    elseif(QEXT_CXX_COMPILER_GNU)
        set(QEXT_DEFAULT_MKSPEC freebsd-g++)
    endif()
elseif(QEXT_SYSTEM_NETBSD)
    set(QEXT_DEFAULT_MKSPEC netbsd-g++)
elseif(QEXT_SYSTEM_OPENBSD)
    set(QEXT_DEFAULT_MKSPEC openbsd-g++)
elseif(QEXT_SYSTEM_SOLARIS)
    if(QEXT_CXX_COMPILER_GNU)
        if(QEXT_ARCH_64BIT)
            set(QEXT_DEFAULT_MKSPEC solaris-g++-64)
        else()
            set(QEXT_DEFAULT_MKSPEC solaris-g++)
        endif()
    else()
        if(QEXT_ARCH_64BIT)
            set(QEXT_DEFAULT_MKSPEC solaris-cc-64)
        else()
            set(QEXT_DEFAULT_MKSPEC solaris-cc)
        endif()
    endif()
elseif(QEXT_SYSTEM_HURD)
    set(QEXT_DEFAULT_MKSPEC hurd-g++)
endif()

if(NOT QEXT_DEFAULT_MKSPEC)
    message(FATAL_ERROR "mkspec not Detected!")
else()
    message(STATUS "Build in mkspec: ${QEXT_DEFAULT_MKSPEC}")
endif()

if(NOT DEFINED QEXT_DEFAULT_PLATFORM_DEFINITIONS)
    set(QEXT_DEFAULT_PLATFORM_DEFINITIONS "")
endif()

set(QEXT_PLATFORM_DEFINITIONS ${QEXT_DEFAULT_PLATFORM_DEFINITIONS} CACHE STRING "QEXT platform specific pre-processor defines")


#-----------------------------------------------------------------------------------------------------------------------
# utk parse version
#-----------------------------------------------------------------------------------------------------------------------
# Parses a version string like "xx.yy.zz" and sets the major, minor and patch variables.
function(qext_parse_version_string version_string out_var_prefix)
    string(REPLACE "." ";" version_list ${version_string})
    list(LENGTH version_list length)

    set(out_var "${out_var_prefix}_MAJOR")
    set(value "")
    if(length GREATER 0)
        list(GET version_list 0 value)
        list(REMOVE_AT version_list 0)
        math(EXPR length "${length}-1")
    endif()
    set(${out_var} "${value}" PARENT_SCOPE)

    set(out_var "${out_var_prefix}_MINOR")
    set(value "")
    if(length GREATER 0)
        list(GET version_list 0 value)
        set(${out_var} "${value}" PARENT_SCOPE)
        list(REMOVE_AT version_list 0)
        math(EXPR length "${length}-1")
    endif()
    set(${out_var} "${value}" PARENT_SCOPE)

    set(out_var "${out_var_prefix}_PATCH")
    set(value "")
    if(length GREATER 0)
        list(GET version_list 0 value)
        set(${out_var} "${value}" PARENT_SCOPE)
        list(REMOVE_AT version_list 0)
        math(EXPR length "${length}-1")
    endif()
    set(${out_var} "${value}" PARENT_SCOPE)
endfunction()

# Set up the separate version components for the compiler version, to allow mapping of qmake
# conditions like 'equals(QEXT_GCC_MAJOR_VERSION,5)'.
if(CMAKE_CXX_COMPILER_VERSION)
    qext_parse_version_string("${CMAKE_CXX_COMPILER_VERSION}" "QEXT_COMPILER_VERSION")
endif()
