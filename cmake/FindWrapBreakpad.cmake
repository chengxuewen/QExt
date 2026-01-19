########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
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

# We can't create the same interface imported target multiple times, CMake will complain if we do
# that. This can happen if the find_package call is done in multiple different subdirectories.
if(TARGET QExt3rdparty::WrapBreakpad)
    set(QExtWrapBreakpad_FOUND ON)
    return()
endif()

include(InstallVcpkg)
qext_vcpkg_install_package(breakpad
    NOT_IMPORT
    TARGET
    QExt3rdparty::WrapBreakpad
    PREFIX
    QExtWrapBreakpad)
set(unofficial-breakpad_DIR ${QExtWrapBreakpad_INSTALL_DIR}/share/unofficial-breakpad)
find_package(unofficial-breakpad REQUIRED)
get_target_property(QExtWrapBreakpad_IMPORTED_LOCATION_RELEASE unofficial::breakpad::libbreakpad_client IMPORTED_LOCATION_RELEASE)
set_target_properties(unofficial::breakpad::libbreakpad_client PROPERTIES IMPORTED_LOCATION_MINSIZEREL ${QExtWrapBreakpad_IMPORTED_LOCATION_RELEASE})
set_target_properties(unofficial::breakpad::libbreakpad_client PROPERTIES IMPORTED_LOCATION_RELWITHDEBINFO ${QExtWrapBreakpad_IMPORTED_LOCATION_RELEASE})
target_link_libraries(QExt3rdparty::WrapBreakpad INTERFACE unofficial::breakpad::libbreakpad_client)
target_include_directories(QExt3rdparty::WrapBreakpad INTERFACE "${QExtWrapBreakpad_INSTALL_DIR}/include")
set(QExtWrapBreakpad_FOUND ON)
