#################################################################################
#
# Library: QExt
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

qext_add_subdirectory(core)
qext_add_subdirectory(serialport ON)

#if(QEXT_BUILD_LIB_DEVICEWATCHER)
#    message(STATUS "Build devicewatcher lib.")
#    add_subdirectory(devicewatcher)
#endif()

#if(QEXT_BUILD_LIB_FRAMELESSHELPER)
#    message(STATUS "Build framelesshelper lib.")
#    add_subdirectory(framelesshelper)
#endif()

#if(QEXT_BUILD_LIB_GOOGLEPINYIN)
#    message(STATUS "Build googlepinyin lib.")
#    add_subdirectory(googlepinyin)
#endif()

#if(QEXT_BUILD_LIB_ICONFONT)
#    message(STATUS "Build iconfont lib.")
#    add_subdirectory(iconfont)
#endif()

#if(QEXT_BUILD_LIB_SERIALPORT)
#    message(STATUS "Build serialport lib.")
#    add_subdirectory(serialport)
#endif()

#if(QEXT_BUILD_LIB_SINGLEAPP)
#    message(STATUS "Build singleapp lib.")
#    add_subdirectory(singleapp)
#endif()

#if(QEXT_BUILD_LIB_STYLETHEME)
#    message(STATUS "Build styletheme lib.")
#    add_subdirectory(styletheme)
#endif()

#if(QEXT_BUILD_LIB_TCP)
#    message(STATUS "Build tcp lib.")
#    add_subdirectory(tcp)
#endif()

#if(QEXT_BUILD_LIB_UTILS)
#    message(STATUS "Build utils lib.")
#    add_subdirectory(utils)
#endif()

#if(QEXT_BUILD_LIB_VLC)
#    message(STATUS "Build vlc lib.")
#    add_subdirectory(vlc)
#endif()

#if(QEXT_BUILD_LIB_WIDGETS)
#    message(STATUS "Build widgets lib.")
#    add_subdirectory(widgets)
#endif()
