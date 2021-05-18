#--------------------------------------------------------------------------------
# Set lib base name and out put path
#--------------------------------------------------------------------------------
set(_lib_base_name lua)
set(_lib_version_major 5)
set(_lib_version_minor 1)
set(_lib_version_patch 5)
set(_lib_version ${_lib_version_major}${_lib_version_minor})
set(_lib_name lib${_lib_base_name}${_lib_version})
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})
set(EXECUTABLE_OUTPUT_PATH ${QEXT_APP_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Configure a header file to pass some of the CMake settings to the source code
#--------------------------------------------------------------------------------
set(_lib_include_files_dir ${QEXT_LUA_INCLUDE_FILE_DIR}/${_lib_name})
set(_lib_config_header_file_path ${_lib_include_files_dir}/luaconf${_lib_version}.h)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/luaconf${_lib_version}.h.in"
    "${_lib_config_header_file_path}"
    )



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(_lib_headers
    src/lapi.h
    src/lauxlib.h
    src/lcode.h
#    src/lctype.h
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
    src/lstate.h
    src/lstring.h
    src/ltable.h
    src/ltm.h
    src/lua.h
    src/lualib.h
    src/lundump.h
    src/lvm.h
    src/lzio.h
    src/lua${_lib_version}.hpp
    ${_lib_config_header_file_path}
    )
set(_lib_sources
    src/lapi.c
    src/lauxlib.c
    src/lbaselib.c
    src/lcode.c
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
    src/lvm.c
    src/lzio.c
    )

set(_lua_source
    src/lua.c
    )
set(_luac_source
    src/luac.c
    src/print.c
    )



#--------------------------------------------------------------------------------
# Add target
#--------------------------------------------------------------------------------
# Create lua library
add_library(${_lib_name}
    ${_lib_headers}
    ${_lib_sources}
    )
target_link_libraries(${_lib_name} ${LUA_LINK_LIBS})
target_include_directories(${_lib_name} PUBLIC
    $<BUILD_INTERFACE:${_lib_include_files_dir}>
    $<INSTALL_INTERFACE:include>
    )
if(LUA_BUILD_AS_DLL)
    set_target_properties(${_lib_name} PROPERTIES COMPILE_DEFINITIONS LUA_BUILD_AS_DLL)
endif()

# set target properties
set_target_properties(${_lib_name} PROPERTIES
    DEBUG_POSTFIX ${QEXT_DEBUG_POSTFIX}
    OUTPUT_NAME ${_lib_base_name}${_lib_version}
    CLEAN_DIRECT_OUTPUT 1
    )

# set include copy custom command
add_custom_command(
    TARGET ${_lib_name}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/lua.h ${_lib_include_files_dir}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/lualib.h ${_lib_include_files_dir}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/lauxlib.h ${_lib_include_files_dir}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/lua${_lib_version}.hpp ${_lib_include_files_dir}
    COMMAND ${CMAKE_COMMAND} -E copy ${_lib_config_header_file_path} ${_lib_include_files_dir}
    COMMENT "Copy ${_lib_name} include file to include dir"
    PRE_BUILD
    )



#--------------------------------------------------------------------------------
# Add tool apps
#--------------------------------------------------------------------------------
# add lua app
add_executable(lua${_lib_version}
    ${_lua_source}
    )
target_link_libraries(lua${_lib_version} ${_lib_name})

# add luac app
add_executable(luac${_lib_version}
    ${_lib_headers}
    ${_lib_sources}
    ${_luac_source}
    )
target_link_libraries(luac${_lib_version} ${LUA_LINK_LIBS})
target_include_directories(luac${_lib_version} PRIVATE
    ${_lib_include_files_dir}
    )


# On windows a variant of the lua interpreter without console output needs to be built
if(LUA_BUILD_WLUA)
    add_executable(wlua${_lib_version} WIN32
        src/wmain.c
        ${_lua_source}
        )
    target_link_libraries(wlua${_lib_version} ${_lib_name})
endif()
