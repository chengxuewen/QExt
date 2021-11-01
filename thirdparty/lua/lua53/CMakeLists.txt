#--------------------------------------------------------------------------------
# Set lib base name and out put path
#--------------------------------------------------------------------------------
set(luacf_lib_base_name lua)
set(lua_lib_version_major 5)
set(lua_lib_version_minor 3)
set(lua_lib_version_patch 6)
set(lua_lib_version ${lua_lib_version_major}${lua_lib_version_minor})
set(lua_lib_name lib${luacf_lib_base_name}${lua_lib_version})
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Configure a header file to pass some of the CMake settings to the source code
#--------------------------------------------------------------------------------
set(lua_lib_include_files_dir ${LUA_INCLUDE_OUTPUT_DIR}/${lua_lib_name})
set(lua_lib_config_header_file_path ${lua_lib_include_files_dir}/lua${lua_lib_version}conf.h)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lua${lua_lib_version}conf.h.in"
    "${lua_lib_config_header_file_path}"
    )



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(lua_lib_headers
    src/lapi.h
    src/lauxlib53.h
    src/lcode.h
    src/lctype.h
    src/ldebug.h
    src/ldo.h
    src/lfunc.h
    src/lgc.h
    src/llex.h
    src/llimits.h
    src/lmem.h
    src/lobject.h
    src/lopcodes.h
    src/lparser.h
    src/lprefix.h
    src/lstate.h
    src/lstring.h
    src/ltable.h
    src/ltm.h
    src/lua53.h
    src/lualib53.h
    src/lundump.h
    src/lvm.h
    src/lzio.h
    src/lua${lua_lib_version}.hpp
    ${lua_lib_config_header_file_path}
    )
set(luacf_lib_sources
    src/lapi.c
    src/lauxlib.c
    src/lbaselib.c
    src/lbitlib.c
    src/lcode.c
    src/lcorolib.c
    src/lctype.c
    src/ldblib.c
    src/ldebug.c
    src/ldo.c
    src/ldump.c
    src/lfunc.c
    src/lgc.c
    src/linit.c
    src/liolib.c
    src/llex.c
    src/lmathlib.c
    src/lmem.c
    src/loadlib.c
    src/lobject.c
    src/lopcodes.c
    src/loslib.c
    src/lparser.c
    src/lstate.c
    src/lstring.c
    src/lstrlib.c
    src/ltable.c
    src/ltablib.c
    src/ltm.c
    src/lundump.c
    src/lutf8lib.c
    src/lvm.c
    src/lzio.c
    )

set(lua_source
    src/lua53.c
    )
set(luac_source
    src/luac.c
    )



#--------------------------------------------------------------------------------
# Add target
#--------------------------------------------------------------------------------
set(lua_lib_include_directories
    $<BUILD_INTERFACE:${lua_lib_include_files_dir}>
    $<INSTALL_INTERFACE:include/lua/${lua_lib_name}>
    )
# Create lua library
add_library(${lua_lib_name} SHARED ${lua_lib_headers} ${luacf_lib_sources})
target_link_libraries(${lua_lib_name} PUBLIC ${LUA_LINK_LIBS})
target_include_directories(${lua_lib_name} PUBLIC ${lua_lib_include_directories})
add_library(${lua_lib_name}_a STATIC ${lua_lib_headers} ${luacf_lib_sources})
target_link_libraries(${lua_lib_name}_a PUBLIC ${LUA_LINK_LIBS})
target_include_directories(${lua_lib_name}_a PUBLIC ${lua_lib_include_directories})

if(LUA_BUILD_AS_DLL)
    set_target_properties(${lua_lib_name} PROPERTIES COMPILE_DEFINITIONS LUA_BUILD_AS_DLL)
endif()

# set target properties
set_target_properties(${lua_lib_name} PROPERTIES
    DEBUG_POSTFIX ${LUA_DEBUG_POSTFIX}
    OUTPUT_NAME ${luacf_lib_base_name}${lua_lib_version}
    CLEAN_DIRECT_OUTPUT 1
    )

# set include copy custom command
add_custom_command(
    TARGET ${lua_lib_name}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/src/lua53.h ${lua_lib_include_files_dir}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/src/lualib53.h ${lua_lib_include_files_dir}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/src/lauxlib53.h ${lua_lib_include_files_dir}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/src/lua${lua_lib_version}.hpp ${lua_lib_include_files_dir}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${lua_lib_config_header_file_path} ${lua_lib_include_files_dir}
    COMMENT "Copy ${lua_lib_name} include file to include dir"
    PRE_BUILD
    )



#--------------------------------------------------------------------------------
# Add tool apps
#--------------------------------------------------------------------------------
# add lua app
add_executable(lua${lua_lib_version}
    ${lua_source}
    )
target_link_libraries(lua${lua_lib_version} ${lua_lib_name})

# add luac app
add_executable(luac${lua_lib_version}
    ${lua_lib_headers}
    ${luacf_lib_sources}
    ${luac_source}
    )
target_link_libraries(luac${lua_lib_version} ${LUA_LINK_LIBS})
target_include_directories(luac${lua_lib_version} PRIVATE
    ${lua_lib_include_files_dir}
    )


## On windows a variant of the lua interpreter without console output needs to be built
#if(LUA_BUILD_WLUA)
#    add_executable(wlua${lua_lib_version} WIN32
#        src/wmain.c
#        ${lua_source}
#        )
#    target_link_libraries(wlua${lua_lib_version} ${lua_lib_name})
#endif()
