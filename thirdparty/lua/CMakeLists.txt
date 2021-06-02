#--------------------------------------------------------------------------------
# Set project name and version
#--------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
project(Lua C ASM)



#--------------------------------------------------------------------------------
# Set project name and version
#--------------------------------------------------------------------------------
set(QEXT_LUA_INCLUDE_FILE_DIR ${QEXT_INCLUDE_OUTPUT_DIR}/lua)



#--------------------------------------------------------------------------------
# Set configuration
#--------------------------------------------------------------------------------
## CONFIGURATION
# Default configuration (we assume POSIX by default)
set(LUA_PATH "LUA_PATH" CACHE STRING "Environment variable to use as package.path.")
set(LUA_CPATH "LUA_CPATH" CACHE STRING "Environment variable to use as package.cpath.")
set(LUA_INIT "LUA_INIT" CACHE STRING "Environment variable for initial script.")


#option ( LUA_ANSI "Use only ansi features." OFF )
option(LUA_USE_C89 "Use only C89 features." OFF)
option(LUA_USE_RELATIVE_LOADLIB "Use modified loadlib.c with support for relative paths on posix systems." ON)
#option(LUA_COMPAT_5_1 "Enable backwards compatibility options with lua-5.1." ON)
#option(LUA_COMPAT_5_2 "Enable backwards compatibility options with lua-5.2." ON)
#option(LUA_COMPAT_5_3 "Enable backwards compatibility options with lua-5.3." ON)
option(LUA_COMPAT_ALL "Enable backwards compatibility options." ON)

set(LUA_ANSI LUA_USE_C89)
if (LUA_COMPAT_ALL)
    set(LUA_COMPAT_5_1 ON)
    set(LUA_COMPAT_5_2 ON)
    set(LUA_COMPAT_5_3 ON)
endif()


set(LUA_IDSIZE 60 CACHE STRING "gives the maximum size for the description of the source.")
set(LUA_PROMPT "> " CACHE STRING "Is the default prompt used by stand-alone Lua.")
set(LUA_PROMPT2 ">> " CACHE STRING "Is the default continuation prompt used by stand-alone Lua.")
set(LUA_MAXINPUT 512 CACHE STRING "Is the maximum length for an input line in the stand-alone interpreter.")

#LUAI_* and LUAL_* settings, for now defaults are used.
set(LUA_DIRSEP "/")
set(LUA_MODULE_SUFFIX ${CMAKE_SHARED_MODULE_SUFFIX})
set(LUA_LDIR ${INSTALL_LMOD})
set(LUA_CDIR ${INSTALL_CMOD})


if (LUA_USE_RELATIVE_LOADLIB)
    # This will set up relative paths to lib
    string(REGEX REPLACE "[^!/]+" ".." LUA_DIR "!/${INSTALL_BIN}/")
else()
    # Direct path to installation
    set(LUA_DIR ${CMAKE_INSTALL_PREFIX} CACHE STRING "Destination from which modules will be resolved. See INSTALL_LMOD and INSTALL_CMOD.")
endif()

set(LUA_PATH_DEFAULT "./?.lua;${LUA_DIR}${LUA_LDIR}/?.lua;${LUA_DIR}${LUA_LDIR}/?/init.lua")
set(LUA_CPATH_DEFAULT "./?${LUA_MODULE_SUFFIX};${LUA_DIR}${LUA_CDIR}/?${LUA_MODULE_SUFFIX};${LUA_DIR}${LUA_CDIR}/loadall${LUA_MODULE_SUFFIX}")

if(WIN32 AND NOT CYGWIN)
    # Windows systems
    option(LUA_USE_WINDOWS "Windows specific build." ON)
    option(LUA_BUILD_WLUA "Build wLua interpretter without console output." ON)
    option(LUA_BUILD_AS_DLL "Build Lua library as Dll." ${BUILD_SHARED_LIBS})

    # Paths (Double escapes needed)
    set(LUA_DIRSEP "\\\\")
    string(REPLACE " /" ${LUA_DIRSEP} LUA_DIR "${LUA_DIR}")
    string(REPLACE "/" ${LUA_DIRSEP} LUA_LDIR "${LUA_LDIR}")
    string(REPLACE "/" ${LUA_DIRSEP} LUA_CDIR "${LUA_CDIR}")
    string(REPLACE "/" ${LUA_DIRSEP} LUA_PATH_DEFAULT "${LUA_PATH_DEFAULT}")
    string(REPLACE "/" ${LUA_DIRSEP} LUA_CPATH_DEFAULT "${LUA_CPATH_DEFAULT}")
else()
    # Posix systems (incl. Cygwin)
    option(LUA_USE_POSIX "Use POSIX features." ON)
    option(LUA_USE_DLOPEN "Use dynamic linker to load modules." ON)
    option(LUA_USE_MKSTEMP "Use mkstep." ON)
    option(LUA_USE_ISATTY "Use tty." ON)
    option(LUA_USE_POPEN "Use popen." ON)
    option(LUA_USE_ULONGJMP "Use ulongjmp" ON)
    option(LUA_USE_GMTIME_R "Use GTIME_R" ON)
    # Apple and Linux specific
    if(LINUX OR APPLE)
        option(LUA_USE_AFORMAT "Assume 'printf' handles 'aA' specifiers" ON)
        option(LUA_USE_STRTODHEX "Assume 'strtod' handles hexa formats" ON)
        option(LUA_USE_LONGLONG "Assume support for long long" ON)
    endif()
endif()

## SETUP
# Optional libraries
find_package(Readline)
if(READLINE_FOUND)
    option(LUA_USE_READLINE "Use readline in the Lua CLI." ON)
endif()

find_package(Curses)
if (CURSES_FOUND)
    option(LUA_USE_CURSES "Use curses in the Lua CLI." ON)
endif()



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(LUA_LINK_LIBS)

# Setup needed variables and libraries
if (LUA_USE_POSIX)
    # On POSIX Lua links to standard math library "m"
    find_library(MATH_LIBRARY NAMES m)
    if (MATH_LIBRARY)
        list(APPEND LUA_LINK_LIBS ${MATH_LIBRARY})
    endif()
endif()

if(LUA_USE_DLOPEN)
    # Link to dynamic linker library "dl"
    find_library(DL_LIBRARY NAMES dl)
    if (DL_LIBRARY)
        list (APPEND LUA_LINK_LIBS ${DL_LIBRARY})
    endif()
endif()

if(LUA_USE_READLINE)
    # Add readline
    include_directories(${READLINE_INCLUDE_DIR})
    list(APPEND LUA_LINK_LIBS ${READLINE_LIBRARY})
endif()

if (LUA_USE_CURSES)
    # Add curses
    include_directories(${CURSES_INCLUDE_DIR})
    list(APPEND LUA_LINK_LIBS ${CURSES_LIBRARY})
endif()



#--------------------------------------------------------------------------------
# Add subdirectory
#--------------------------------------------------------------------------------
add_subdirectory(lua51)
add_subdirectory(lua52)
add_subdirectory(lua53)
