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
add_subdirectory(devicewatcher)
add_subdirectory(fontawesome)
add_subdirectory(googlepinyin)
add_subdirectory(serialport)
add_subdirectory(singleapp)
add_subdirectory(tcp)
#add_subdirectory(theme)
add_subdirectory(utils)
add_subdirectory(widget)

if(QEXT_BUILD_QML)
#    add_subdirectory(quick)
endif()
