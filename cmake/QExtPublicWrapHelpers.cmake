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
# Install third-party PUBLIC_LIBRARIES headers under the QExt namespace
#
# This function is called AFTER qext_add_library(). It:
#   1. Creates build tree symlinks: ${QEXT_BUILD_DIR}/include/QExt/3rdparty/<shortname>/
#   2. Adds install rules for headers to include/QExt/3rdparty/<shortname>/
#   3. Overrides INTERFACE_INCLUDE_DIRECTORIES for the wrap target
#
# Usage:
#   qext_install_public_wrap_headers(QExtCore
#       WRAPS
#       QExt3rdparty::WrapAnyLite|nonstd
#       QExt3rdparty::WrapOptionalLite|nonstd
#       QExt3rdparty::WrapStringViewLite|nonstd
#       ...)
#
# ARG_WRAPS: semicolon-separated list of wrap_target|shortname pairs.
#-----------------------------------------------------------------------------------------------------------------------
function(qext_install_public_wrap_headers target)
    cmake_parse_arguments(arg "" "" "WRAPS" ${ARGN})

    foreach(pair ${arg_WRAPS})
        # Parse wrap_target|shortname (using | as separator to avoid CMake list splitting)
        string(REPLACE "|" ";" pair_list ${pair})
        list(GET pair_list 0 wrap_target)
        list(GET pair_list 1 shortname)

        # Get wrap's install directory variable name from the target name
        # e.g., QExt3rdparty::WrapStringViewLite → variable: QExtWrapStringViewLite_INSTALL_DIR
        string(REGEX REPLACE "QExt3rdparty::Wrap([^|]+)" "\\1" wrap_name ${wrap_target})
        set(install_dir_var "QExtWrap${wrap_name}_INSTALL_DIR")
        if(NOT ${install_dir_var})
            message(WARNING "qext_install_public_wrap_headers: ${install_dir_var} not set for ${wrap_target}")
            continue()
        endif()

        set(wrap_install_dir "${${install_dir_var}}")
        set(wrap_include_dir "${wrap_install_dir}/include")
        set(install_dest_dir "include/QExt/3rdparty/${shortname}")

        if(EXISTS "${wrap_include_dir}")
            file(COPY "${wrap_include_dir}/" DESTINATION "${QEXT_BUILD_DIR}/include/QExt/3rdparty")
        else()
            file(MAKE_DIRECTORY "${QEXT_BUILD_DIR}/include/QExt/3rdparty")
        endif()

        # Install header files from wrap includes to QExt namespace
        # We take the wrap's include/ directory and install all subdirectories
        # Install header files to the unified namespace parent directory
        # Source: <wrap>/install/include/<lib>/header.h
        # Dest:  <prefix>/include/QExt/3rdparty/<lib>/header.h
        install(DIRECTORY "${wrap_include_dir}/"
            DESTINATION "include/QExt/3rdparty"
            FILES_MATCHING
            PATTERN "*.hpp"
            PATTERN "*.h"
            PATTERN "*.hh"
        )

        # Use target_include_directories (works with IMPORTED targets, appends to existing)
        # to add QExt-namespaced include paths for build and install interfaces.
        # This ensures consumers using find_package(QExtCore) get correct include paths.
        # Include path points to the ROOT, so <QExt/3rdparty/fmt/os.h> resolves correctly
        # -I build/include → build/include/QExt/3rdparty/fmt/os.h ✅
        # -I include/QExt/3rdparty/fmt → WRONG (doubles the path)
        target_include_directories(${wrap_target} INTERFACE
            "$<BUILD_INTERFACE:${QEXT_BUILD_DIR}/include>"
            "$<INSTALL_INTERFACE:include>"
        )
        # Bake into main target for find_package export
        target_include_directories(${target} INTERFACE
            "$<BUILD_INTERFACE:${QEXT_BUILD_DIR}/include>"
            "$<INSTALL_INTERFACE:include>")
    endforeach()
endfunction()
