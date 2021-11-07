#################################################################################
#
# Library: QEXT
#
# Copyright (c) ChengXueWen. Contact: 1398831004@qq.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
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

if(QEXT_BUILD_LIB_GOOGLEPINYIN)
add_subdirectory(googlepinyin)
endif()

if(QEXT_BUILD_LIB_GUI)
add_subdirectory(gui)
endif()

if(QEXT_BUILD_LIB_ICONS)
add_subdirectory(icons)
endif()

if(QEXT_BUILD_LIB_LUA)
add_subdirectory(lua)
endif()

if(QEXT_BUILD_LIB_OSGI)
add_subdirectory(osgi)
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

if(QEXT_BUILD_LIB_STYLESHEET)
add_subdirectory(stylesheet)
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
