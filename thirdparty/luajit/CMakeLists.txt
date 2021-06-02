#--------------------------------------------------------------------------------
# Set project name and version
#--------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
project(LuaJit C ASM)



#--------------------------------------------------------------------------------
# Set project name and version
#--------------------------------------------------------------------------------
set(QEXT_LUAJIT_INCLUDE_FILE_DIR ${QEXT_INCLUDE_OUTPUT_DIR}/luajit)



#--------------------------------------------------------------------------------
# Various includes
#--------------------------------------------------------------------------------
include(CheckLibraryExists)
include(CheckFunctionExists)
include(CheckCSourceCompiles)
include(CheckTypeSize)



#--------------------------------------------------------------------------------
# Set configuration
#--------------------------------------------------------------------------------
option(WITH_AMALG "Build eveything in one shot (needs memory)" ON)

set(INSTALL_INCLUDE_SUBDIR "include" CACHE STRING "installation include subdirectory name")
if(WIN32)
    set(INSTALL_BIN_SUBDIR "." CACHE STRING "installation executable subdirectory name")
    set(INSTALL_LIB_SUBDIR "." CACHE STRING "installation library subdirectory name")
    set(INSTALL_LUA_PATH_SUBDIR "lua") # not editable
    set(INSTALL_LUA_CPATH_SUBDIR ".") # not editable
else()
    set(INSTALL_BIN_SUBDIR "bin" CACHE STRING "installation executable subdirectory name")
    set(INSTALL_LIB_SUBDIR "lib" CACHE STRING "installation library subdirectory name")
    set(INSTALL_LUA_PATH_SUBDIR "share/lua/5.1/" CACHE STRING "lua path subdirectory name")
    set(INSTALL_LUA_LIB_SUBDIR "lib" CACHE STRING "installation lua lib subdirectory name")
    set(INSTALL_LUA_CPATH_SUBDIR "${INSTALL_LUA_LIB_SUBDIR}/lua/5.1/" CACHE STRING "lua cpath subdirectory name")
endif()

add_definitions(-DLUA_MULTILIB="${INSTALL_LUA_LIB_SUBDIR}")

if(UNIX)
    if(NOT CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
        add_definitions(-DLUA_ROOT="${CMAKE_INSTALL_PREFIX}")
    endif()
endif()

# Ugly warnings
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Readline support
find_package(Readline)
if(READLINE_FOUND)
    add_definitions("-DLUA_USE_READLINE")
    list(APPEND LIBS ${READLINE_LIBRARIES})
    include_directories(${READLINE_INCLUDE_DIR})
endif()

# LuaJIT specific
option(LUAJIT_DISABLE_FFI "Disable FFI." OFF)
option(LUAJIT_ENABLE_LUA52COMPAT "Enable Lua 5.2 compatibility." ON)
option(LUAJIT_DISABLE_JIT "Disable JIT." OFF)
option(LUAJIT_CPU_SSE2 "Use SSE2 instead of x87 instructions." ON)
option(LUAJIT_CPU_NOCMOV "Disable NOCMOV." OFF)

option(LUAJIT_USE_SYSMALLOC "LuaJIT uses sysmalloc?" OFF)
option(LUAJIT_USE_VALGRIND "Luajit compatible with Valgrind?" OFF)
option(LUAJIT_USE_GDBJIT "Luajit uses GDBJIT?" OFF)
option(LUA_USE_APICHECK "LuaJIT does API checks?" OFF)
option(LUA_USE_ASSERT "LuaJIT does asserts?" OFF)

mark_as_advanced(
    LUAJIT_DISABLE_FFI
    LUAJIT_ENABLE_LUA52COMPAT
    LUAJIT_DISABLE_JIT
    LUAJIT_CPU_SSE2
    LUAJIT_CPU_NOCMOV
    LUAJIT_USE_SYSMALLOC
    LUAJIT_USE_VALGRIND
    LUAJIT_USE_GDBJIT
    LUA_USE_APICHECK
    LUA_USE_ASSERT
    )

macro(ADD_MANDATORY_DEFINITIONS stuff)
    add_definitions(${stuff})
    set(CMAKE_REQUIRED_DEFINITIONS ${CMAKE_REQUIRED_DEFINITIONS} ${stuff})
endmacro()

if(LUAJIT_DISABLE_FFI)
    ADD_MANDATORY_DEFINITIONS(-DLUAJIT_DISABLE_FFI)
endif()

if(LUAJIT_ENABLE_LUA52COMPAT)
    ADD_MANDATORY_DEFINITIONS(-DLUAJIT_ENABLE_LUA52COMPAT)
endif()

if(LUAJIT_DISABLE_JIT)
    ADD_MANDATORY_DEFINITIONS(-DLUAJIT_DISABLE_JIT)
endif()

if(LUAJIT_CPU_SSE2)
    ADD_MANDATORY_DEFINITIONS(-DLUAJIT_CPU_SSE2)
endif()

if(LUAJIT_CPU_NOCMOV)
    ADD_MANDATORY_DEFINITIONS(-DLUAJIT_CPU_NOCMOV)
endif()

if(LUAJIT_USE_SYSMALLOC)
    ADD_MANDATORY_DEFINITIONS(-DLUAJIT_USE_SYSMALLOC)
endif()

if(LUAJIT_USE_VALGRIND)
    ADD_MANDATORY_DEFINITIONS(-DLUAJIT_USE_VALGRIND)
endif()

if(LUAJIT_USE_GDBJIT)
    ADD_MANDATORY_DEFINITIONS(-DLUAJIT_USE_GDBJIT)
endif()

if(LUA_USE_APICHECK)
    ADD_MANDATORY_DEFINITIONS(-DLUA_USE_APICHECK)
endif()

if(LUA_USE_ASSERT)
    ADD_MANDATORY_DEFINITIONS(-DLUA_USE_ASSERT)
endif()


CHECK_TYPE_SIZE("void*" SIZEOF_VOID_P)
if(SIZEOF_VOID_P EQUAL 8)
    add_definitions(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE)
endif()

if(WIN32 AND NOT CYGWIN)
    set(LUA_BUILD_AS_DLL 1)
    add_definitions( -DLUA_BUILD_AS_DLL -DLUAJIT_OS=LUAJIT_OS_WINDOWS)
    set(LJVM_MODE peobj)
elseif( APPLE )
    set(LJVM_MODE machasm)
else()
    set(LJVM_MODE elfasm)
endif()

if(NOT WIN32)
    find_library(DL_LIBRARY "dl")
    if(DL_LIBRARY)
        set(CMAKE_REQUIRED_LIBRARIES ${DL_LIBRARY})
        list(APPEND LIBS ${DL_LIBRARY})
    endif(DL_LIBRARY)
    CHECK_FUNCTION_EXISTS(dlopen LUA_USE_DLOPEN)
    if(NOT LUA_USE_DLOPEN)
        message(FATAL_ERROR "Cannot compile a useful lua.
            Function dlopen() seems not to be supported on your platform.
            Apparently you are not on a Windows platform as well.
            So lua has no way to deal with shared libraries!")
    endif(NOT LUA_USE_DLOPEN)
endif(NOT WIN32)

CHECK_LIBRARY_EXISTS(m sin "" LUA_USE_LIBM)
if (LUA_USE_LIBM)
    list(APPEND LIBS m)
endif()

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads)
if(THREADS_FOUND)
    list(APPEND LIBS ${CMAKE_THREAD_LIBS_INIT})
endif()



#--------------------------------------------------------------------------------
# Add subdirectory
#--------------------------------------------------------------------------------
add_subdirectory(luajit20)
add_subdirectory(luajit21)
