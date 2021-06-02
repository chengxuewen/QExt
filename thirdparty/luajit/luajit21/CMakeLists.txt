# This CMakeLists.txt has been first taken from LuaDist
# Copyright (C) 2007-2011 LuaDist.
# Created by Peter Drahoš
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# Debugged and (now seriously) modified by Ronan Collobert, for Torch7

#project(LuaJIT C ASM)

#if(APPLE)
#  CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12 FATAL_ERROR)
#  CMAKE_POLICY(VERSION 2.8.12)
#  set(CMAKE_MACOSX_RPATH TRUE) # @rpath in libs
#else()
#  CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)
#  CMAKE_POLICY(VERSION 2.8)
#endif()

#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
#                      "${CMAKE_MODULE_PATH}")

#OPTION(WITH_AMALG "Build eveything in one shot (needs memory)" ON)

#set(INSTALL_INCLUDE_SUBDIR "include" CACHE string "installation include subdirectory name")
#if(WIN32)
#  set(INSTALL_BIN_SUBDIR "." CACHE string "installation executable subdirectory name")
#  set(INSTALL_LIB_SUBDIR "." CACHE string "installation library subdirectory name")
#  set(INSTALL_LUA_PATH_SUBDIR "lua") # not editable
#  set(INSTALL_LUA_CPATH_SUBDIR ".") # not editable
#else()
#  set(INSTALL_BIN_SUBDIR "bin" CACHE string "installation executable subdirectory name")
#  set(INSTALL_LIB_SUBDIR "lib" CACHE string "installation library subdirectory name")
#  set(INSTALL_LUA_PATH_SUBDIR "share/lua/5.1/" CACHE string "lua path subdirectory name")
#  set(INSTALL_LUA_LIB_SUBDIR "lib" CACHE string "installation lua lib subdirectory name")
#  set(INSTALL_LUA_CPATH_SUBDIR "${INSTALL_LUA_LIB_SUBDIR}/lua/5.1/" CACHE string "lua cpath subdirectory name")
#endif()

#ADD_DEFINITIONS(-DLUA_MULTILIB="${INSTALL_LUA_LIB_SUBDIR}")

#if(UNIX)
#  if(NOT CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
#    ADD_DEFINITIONS(-DLUA_ROOT="${CMAKE_INSTALL_PREFIX}")
#  endif()
#endif()

## Ugly warnings
#if(MSVC)
#  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
#endif()

## Readline support
#FIND_PACKAGE(Readline)
#if(READLINE_FOUND)
#  ADD_DEFINITIONS("-DLUA_USE_READLINE")
#  list(APPEND LIBS ${READLINE_LIBRARIES})
#  INCLUDE_DIRECTORIES(${READLINE_INCLUDE_DIR})
#endif()

## Various includes
#INCLUDE(CheckLibraryExists)
#INCLUDE(CheckFunctionExists)
#INCLUDE(CheckCSourceCompiles)
#INCLUDE(CheckTypeSize)

## LuaJIT specific
#option ( LUAJIT_DISABLE_FFI "Disable FFI." OFF )
#option ( LUAJIT_ENABLE_LUA52COMPAT "Enable Lua 5.2 compatibility." ON )
#option ( LUAJIT_DISABLE_JIT "Disable JIT." OFF )
#option ( LUAJIT_CPU_SSE2 "Use SSE2 instead of x87 instructions." ON )
#option ( LUAJIT_CPU_NOCMOV "Disable NOCMOV." OFF )

#option ( LUAJIT_USE_SYSMALLOC "LuaJIT uses sysmalloc?" OFF )
#option ( LUAJIT_USE_VALGRIND "Luajit compatible with Valgrind?" OFF )
#option ( LUAJIT_USE_GDBJIT "Luajit uses GDBJIT?" OFF )
#option ( LUA_USE_APICHECK "LuaJIT does API checks?" OFF )
#option ( LUA_USE_ASSERT "LuaJIT does asserts?" OFF )

#option ( LUAJIT_ENABLE_GC64 "LuaJIT 64 bits support" ON )

#MARK_AS_ADVANCED(
#  LUAJIT_DISABLE_FFI
#  LUAJIT_ENABLE_LUA52COMPAT
#  LUAJIT_DISABLE_JIT
#  LUAJIT_CPU_SSE2
#  LUAJIT_CPU_NOCMOV
#  LUAJIT_USE_SYSMALLOC
#  LUAJIT_USE_VALGRIND
#  LUAJIT_USE_GDBJIT
#  LUA_USE_APICHECK
#  LUA_USE_ASSERT
#  LUAJIT_ENABLE_GC64
#  )

#macro(ADD_MANDATORY_DEFINITIONS stuff)
#  ADD_DEFINITIONS(${stuff})
#  set(CMAKE_REQUIRED_DEFINITIONS ${CMAKE_REQUIRED_DEFINITIONS} ${stuff})
#endmacro()

#if(LUAJIT_DISABLE_FFI)
#  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_DISABLE_FFI)
#endif()

#if(LUAJIT_ENABLE_LUA52COMPAT)
#  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_ENABLE_LUA52COMPAT)
#endif()

#if(LUAJIT_DISABLE_JIT)
#  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_DISABLE_JIT)
#endif()

#if(LUAJIT_CPU_SSE2)
#  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_CPU_SSE2)
#endif()

#if(LUAJIT_CPU_NOCMOV)
#  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_CPU_NOCMOV)
#endif()

#if(LUAJIT_USE_SYSMALLOC)
#  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_USE_SYSMALLOC)
#endif()

#if(LUAJIT_USE_VALGRIND)
#  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_USE_VALGRIND)
#endif()

#if(LUAJIT_USE_GDBJIT)
#  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_USE_GDBJIT)
#endif()

#if(LUA_USE_APICHECK)
#  ADD_MANDATORY_DEFINITIONS(-DLUA_USE_APICHECK)
#endif()

#if(LUA_USE_ASSERT)
#  ADD_MANDATORY_DEFINITIONS(-DLUA_USE_ASSERT)
#endif()

#if(LUAJIT_ENABLE_GC64)
#  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_ENABLE_GC64)
#endif()

#######

#CHECK_TYPE_SIZE("void*" SIZEOF_VOID_P)
#if(SIZEOF_VOID_P EQUAL 8)
#  ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE)
#endif()

#if ( WIN32 AND NOT CYGWIN )
#  set(LUA_BUILD_AS_DLL 1)
#  add_definitions ( -DLUA_BUILD_AS_DLL -DLUAJIT_OS=LUAJIT_OS_WINDOWS)
#  set ( LJVM_MODE peobj )
#elseif ( APPLE )
#  set ( LJVM_MODE machasm )
#else ()
#  set ( LJVM_MODE elfasm )
#endif ()

#if(NOT WIN32)
#  FIND_LIBRARY(DL_LIBRARY "dl")
#  if(DL_LIBRARY)
#    set(CMAKE_REQUIRED_LIBRARIES ${DL_LIBRARY})
#    list(APPEND LIBS ${DL_LIBRARY})
#  endif(DL_LIBRARY)
#  CHECK_FUNCTION_EXISTS(dlopen LUA_USE_DLOPEN)
#  if(NOT LUA_USE_DLOPEN)
#    message(FATAL_ERROR "Cannot compile a useful lua.
#Function dlopen() seems not to be supported on your platform.
#Apparently you are not on a Windows platform as well.
#So lua has no way to deal with shared libraries!")
#  endif(NOT LUA_USE_DLOPEN)
#endif(NOT WIN32)

#CHECK_LIBRARY_EXISTS(m sin "" LUA_USE_LIBM)
#if ( LUA_USE_LIBM )
#  list ( APPEND LIBS m )
#endif ()

#CHECK_LIBRARY_EXISTS(ncurses printw "" LUA_USE_LIBNCURSES)
#if ( LUA_USE_LIBNCURSES )
#  list ( APPEND LIBS ncurses )
#endif ()

#set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
#FIND_PACKAGE(Threads)
#if(THREADS_FOUND)
#  list(APPEND LIBS ${CMAKE_THREAD_LIBS_INIT})
#endif()

## SOURCES
install(FILES
    src/luaconf.h
    src/lua.h
    src/lauxlib.h
    src/lualib.h
    src/lua.hpp
    src/luajit.h
    DESTINATION "${INSTALL_INCLUDE_SUBDIR}"
    )

macro(LJ_TEST_ARCH stuff)
    CHECK_C_SOURCE_COMPILES("
        #undef ${stuff}
        #include \"lj_arch.h\"
        #if ${stuff}
        int main() { return 0; }
        #else
        #error \"not defined\"
        #endif
        " ${stuff})
endmacro()

macro(LJ_TEST_ARCH_VALUE stuff value)
    CHECK_C_SOURCE_COMPILES("
        #undef ${stuff}
        #include \"lj_arch.h\"
        #if ${stuff} == ${value}
        int main() { return 0; }
        #else
        #error \"not defined\"
        #endif
        " ${stuff}_${value})
endmacro()

set(CMAKE_REQUIRED_INCLUDES ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src)
foreach(arch X64 X86 ARM ARM64 PPC PPCSPE MIPS)
    LJ_TEST_ARCH(LJ_TARGET_${arch})
    if(LJ_TARGET_${arch})
        string(TOLOWER ${arch} TARGET_LJARCH)
        message(STATUS "LuaJIT Target: ${TARGET_LJARCH}")
        break()
    endif()
endforeach()

if(NOT TARGET_LJARCH)
    message(FATAL_ERROR "architecture not supported")
endif()

set(DASM_ARCH ${TARGET_LJARCH})
set(DASM_FLAGS)
set(TARGET_ARCH)
list(APPEND TARGET_ARCH "LUAJIT_TARGET=LUAJIT_ARCH_${TARGET_LJARCH}")
LJ_TEST_ARCH_VALUE(LJ_LE 1)
if(LJ_LE_1)
    set(DASM_FLAGS ${DASM_FLAGS} -D ENDIAN_LE)
elseif()
    set(DASM_FLAGS ${DASM_FLAGS} -D ENDIAN_BE)
endif()
LJ_TEST_ARCH_VALUE(LJ_ARCH_BITS 64)
if(LJ_ARCH_BITS_64)
    set(DASM_FLAGS ${DASM_FLAGS} -D P64)
endif()
LJ_TEST_ARCH_VALUE(LJ_HASJIT 1)
if(LJ_HASJIT_1)
    set(DASM_FLAGS ${DASM_FLAGS} -D JIT)
endif()
LJ_TEST_ARCH_VALUE(LJ_HASFFI 1)
if(LJ_HASFFI_1)
    set(DASM_FLAGS ${DASM_FLAGS} -D FFI)
endif()
LJ_TEST_ARCH_VALUE(LJ_DUALNUM 1)
if(LJ_DUALNUM_1)
    set(DASM_FLAGS ${DASM_FLAGS} -D DUALNUM)
endif()
LJ_TEST_ARCH_VALUE(LJ_ARCH_HASFPU 1)
if(LJ_ARCH_HASFPU_1)
    set(DASM_FLAGS ${DASM_FLAGS} -D FPU)
    list(APPEND TARGET_ARCH "LJ_ARCH_HASFPU=1")
else()
    list(APPEND TARGET_ARCH "LJ_ARCH_HASFPU=0")
endif()
LJ_TEST_ARCH_VALUE(LJ_ABI_SOFTFP 1)
if(NOT LJ_ABI_SOFTFP_1)
    set(DASM_FLAGS ${DASM_FLAGS} -D HFABI)
    list(APPEND TARGET_ARCH "LJ_ABI_SOFTFP=0")
else()
    list(APPEND TARGET_ARCH "LJ_ABI_SOFTFP=1")
endif()
LJ_TEST_ARCH_VALUE(LJ_NO_UNWIND 1)
if(LJ_NO_UNWIND_1)
    set(DASM_FLAGS ${DASM_FLAGS} -D NO_UNWIND)
    list(APPEND TARGET_ARCH "LUAJIT_NO_UNWIND")
endif()
if(WIN32)
    set(DASM_FLAGS ${DASM_FLAGS} -LN -D WIN)
endif()
if(TARGET_LJARCH STREQUAL "x64")
    if(APPLE)
        set ( CMAKE_EXE_LINKER_FLAGS "-pagezero_size 10000 -image_base 100000000 ${CMAKE_EXE_LINKER_FLAGS}" )
        set ( CMAKE_SHARED_LINKER_FLAGS "-image_base 7fff04c4a000" ${CMAKE_SHARED_LINKER_FLAGS})
    endif()

    LJ_TEST_ARCH_VALUE(LJ_FR2 1)
    if(NOT LJ_FR2_1)
        set(DASM_ARCH "x86")
    endif()
endif()
if(TARGET_LJARCH STREQUAL "ppc")
    LJ_TEST_ARCH_VALUE(LJ_ARCH_SQRT 1)
    if(NOT LJ_ARCH_SQRT_1)
        set(DASM_FLAGS ${DASM_FLAGS} -D SQRT)
    endif()
    LJ_TEST_ARCH_VALUE(LJ_ARCH_PPC64 1)
    if(NOT LJ_ARCH_PPC64_1)
        set(DASM_FLAGS ${DASM_FLAGS} -D GPR64)
    endif()
endif()

if(LUAJIT_SYSTEM_MINILUA)
    message(STATUS "Using system lua for generating dynasm via: ${LUAJIT_SYSTEM_MINILUA}")
    # set(LUAJIT_SYSTEM_MINILUA ${LUAJIT_SYSTEM_MINILUA} CACHE string "system minilua" FORCE)
    message(STATUS "Executing command: ${LUAJIT_SYSTEM_MINILUA} ${CMAKE_CURRENT_SOURCE_DIR}/dynasm/dynasm.lua ${DASM_FLAGS} -o ${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h ${CMAKE_CURRENT_SOURCE_DIR}/src/vm_${DASM_ARCH}.dasc")
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h
        COMMAND ${LUAJIT_SYSTEM_MINILUA} ${CMAKE_CURRENT_SOURCE_DIR}/dynasm/dynasm.lua ${DASM_FLAGS} -o ${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h ${CMAKE_CURRENT_SOURCE_DIR}/src/vm_${DASM_ARCH}.dasc)
else(LUAJIT_SYSTEM_MINILUA)
    add_executable(minilua21 src/host/minilua.c)
    set_target_properties(minilua21 PROPERTIES COMPILE_DEFINITIONS "${TARGET_ARCH}")
    CHECK_LIBRARY_EXISTS(m sin "" MINILUA_USE_LIBM)
    if(MINILUA_USE_LIBM)
        target_link_libraries(minilua21 m)
    endif()

    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h
        COMMAND minilua21 ${CMAKE_CURRENT_SOURCE_DIR}/dynasm/dynasm.lua ${DASM_FLAGS} -o ${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h ${CMAKE_CURRENT_SOURCE_DIR}/src/vm_${DASM_ARCH}.dasc
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/dynasm/dynasm.lua minilua21
        )
endif(LUAJIT_SYSTEM_MINILUA)

set(SRC_LJLIB
    src/lib_base.c
    src/lib_math.c
    src/lib_bit.c
    src/lib_string.c
    src/lib_table.c
    src/lib_io.c
    src/lib_os.c
    src/lib_package.c
    src/lib_debug.c
    src/lib_jit.c
    src/lib_ffi.c
    )

set(SRC_LJCORE
    src/lj_gc.c
    src/lj_err.c
    src/lj_char.c
    src/lj_bc.c
    src/lj_obj.c
    src/lj_str.c
    src/lj_tab.c
    src/lj_func.c
    src/lj_udata.c
    src/lj_meta.c
    src/lj_debug.c
    src/lj_state.c
    src/lj_dispatch.c
    src/lj_vmevent.c
    src/lj_vmmath.c
    src/lj_strscan.c
    src/lj_api.c
    src/lj_lex.c
    src/lj_parse.c
    src/lj_bcread.c
    src/lj_bcwrite.c
    src/lj_load.c
    src/lj_ir.c
    src/lj_opt_mem.c
    src/lj_opt_fold.c
    src/lj_opt_narrow.c
    src/lj_opt_dce.c
    src/lj_opt_loop.c
    src/lj_opt_split.c
    src/lj_opt_sink.c
    src/lj_mcode.c
    src/lj_snap.c
    src/lj_record.c
    src/lj_crecord.c
    src/lj_ffrecord.c
    src/lj_asm.c
    src/lj_trace.c
    src/lj_gdbjit.c
    src/lj_ctype.c
    src/lj_cdata.c
    src/lj_cconv.c
    src/lj_ccall.c
    src/lj_ccallback.c
    src/lj_carith.c
    src/lj_clib.c
    src/lj_cparse.c
    src/lj_lib.c
    src/lj_alloc.c
    src/lib_aux.c
    src/lib_init.c
    ${SRC_LJLIB}
    )

set(SRC_BUILDVM
    src/host/buildvm.c
    src/host/buildvm_asm.c
    src/host/buildvm_peobj.c
    src/host/buildvm_lib.c
    src/host/buildvm_fold.c
    ${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h
    )

## GENERATE
if(LUAJIT_SYSTEM_BUILDVM)
else(LUAJIT_SYSTEM_BUILDVM)
    add_executable(buildvm21 ${SRC_BUILDVM})
    set_target_properties(buildvm21 PROPERTIES COMPILE_DEFINITIONS "${TARGET_ARCH}")
endif(LUAJIT_SYSTEM_BUILDVM)

macro(add_buildvm_target _target _mode)
    if(LUAJIT_SYSTEM_BUILDVM)
        add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_target}
            COMMAND ${LUAJIT_SYSTEM_BUILDVM} ARGS -m ${_mode} -o ${CMAKE_CURRENT_BINARY_DIR}/${_target} ${ARGN}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            )
    else(LUAJIT_SYSTEM_BUILDVM)
        add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_target}
            COMMAND buildvm21 ARGS -m ${_mode} -o ${CMAKE_CURRENT_BINARY_DIR}/${_target} ${ARGN}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DEPENDS buildvm21 ${ARGN}
            )
    endif(LUAJIT_SYSTEM_BUILDVM)
endmacro(add_buildvm_target)

if (MSVC)
    add_buildvm_target(lj_vm.obj peobj)
    set(LJ_VM_SRC ${CMAKE_CURRENT_BINARY_DIR}/lj_vm.obj)
else()
    add_buildvm_target(lj_vm.S ${LJVM_MODE})
    set(LJ_VM_SRC ${CMAKE_CURRENT_BINARY_DIR}/lj_vm.S)
endif()
add_buildvm_target(lj_ffdef.h   ffdef   ${SRC_LJLIB})
add_buildvm_target(lj_bcdef.h  bcdef  ${SRC_LJLIB})
add_buildvm_target(lj_folddef.h folddef src/lj_opt_fold.c)
add_buildvm_target(lj_recdef.h  recdef  ${SRC_LJLIB})
add_buildvm_target(lj_libdef.h  libdef  ${SRC_LJLIB})
add_buildvm_target(vmdef.lua  vmdef  ${SRC_LJLIB})

set(DEPS
    ${LJ_VM_SRC}
    ${CMAKE_CURRENT_BINARY_DIR}/lj_ffdef.h
    ${CMAKE_CURRENT_BINARY_DIR}/lj_bcdef.h
    ${CMAKE_CURRENT_BINARY_DIR}/lj_libdef.h
    ${CMAKE_CURRENT_BINARY_DIR}/lj_recdef.h
    ${CMAKE_CURRENT_BINARY_DIR}/lj_folddef.h
    ${CMAKE_CURRENT_BINARY_DIR}/vmdef.lua
    )

## COMPILE
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR} dynasm src)

if(WITH_AMALG)
    add_library(libluajit21 SHARED src/ljamalg.c ${DEPS})
    add_library(luajit-static21 STATIC src/ljamalg.c ${DEPS})
    set_property(TARGET luajit-static21 PROPERTY POSITION_INDEPENDENT_CODE 1)
else()
    add_library(libluajit21 SHARED ${SRC_LJCORE} ${DEPS})
    add_library(luajit-static21 STATIC ${SRC_LJCORE} ${DEPS})
    set_property(TARGET luajit-static21 PROPERTY POSITION_INDEPENDENT_CODE 1)
endif()

target_link_libraries (libluajit21 ${LIBS})
set_target_properties(libluajit21 PROPERTIES
    PREFIX "lib"
    IMPORT_PREFIX "lib"
    OUTPUT_NAME "luajit21"
    )

if(WIN32)
    add_executable(luajit21 src/luajit.c)
    target_link_libraries(luajit21 libluajit21)
else()
    if(WITH_AMALG)
        add_executable(luajit21 src/luajit.c src/ljamalg.c ${DEPS})
    else()
        add_executable(luajit21 src/luajit.c ${SRC_LJCORE} ${DEPS})
    endif()
    target_link_libraries(luajit21 ${LIBS})
    set_target_properties(luajit21 PROPERTIES ENABLE_EXPORTS ON)
endif()

install(TARGETS libluajit21 luajit21
    EXPORT torch-exports
    RUNTIME DESTINATION "${INSTALL_BIN_SUBDIR}"
    LIBRARY DESTINATION "${INSTALL_LIB_SUBDIR}"
    ARCHIVE DESTINATION "${INSTALL_LIB_SUBDIR}")

install(FILES
    src/jit/bc.lua
    src/jit/v.lua
    src/jit/dump.lua
    src/jit/dis_x86.lua
    src/jit/dis_x64.lua
    src/jit/dis_arm.lua
    src/jit/dis_ppc.lua
    src/jit/dis_mips.lua
    src/jit/dis_mipsel.lua
    src/jit/bcsave.lua
    src/jit/bc.lua
    src/jit/p.lua
    src/jit/zone.lua
    ${CMAKE_CURRENT_BINARY_DIR}/vmdef.lua
    DESTINATION "${INSTALL_LUA_PATH_SUBDIR}/jit"
    )
