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
# Add subdirectory
#--------------------------------------------------------------------------------
add_subdirectory(core)

if(QEXT_BUILD_LIB_DEVICEWATCHER)
    add_subdirectory(devicewatcher)
endif()

if(QEXT_BUILD_LIB_FONTS)
    add_subdirectory(fonts)
endif()

if(QEXT_BUILD_LIB_FRAMELESSHELPER)
    add_subdirectory(framelesshelper)
endif()

if(QEXT_BUILD_LIB_GOOGLEPINYIN)
    add_subdirectory(googlepinyin)
endif()

if(QEXT_BUILD_LIB_ICONS)
    add_subdirectory(icons)
endif()

if(QEXT_BUILD_LIB_QUICK)
    add_subdirectory(quick)
endif()

if(QEXT_BUILD_LIB_SERIALPORT)
    add_subdirectory(serialport)
endif()

if(QEXT_BUILD_LIB_SINGLEAPP)
    add_subdirectory(singleapp)
endif()

if(QEXT_BUILD_LIB_STYLETHEME)
    add_subdirectory(styletheme)
endif()

if(QEXT_BUILD_LIB_TCP)
    add_subdirectory(tcp)
endif()

if(QEXT_BUILD_LIB_UTILS)
    add_subdirectory(utils)
endif()

if(QEXT_BUILD_LIB_WIDGETS)
    add_subdirectory(widgets)
endif()

if(QEXT_BUILD_LIB_MVVM)
    add_subdirectory(mvvm)
endif()
