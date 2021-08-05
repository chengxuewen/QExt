#################################################################################
#
# Library: QEXT
#
# Copyright (c) 2021 ChengXueWen 1398831004@qq.com
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

macro(qextMacroCopyDependenceLib target dependence directory)
    add_custom_command(
        TARGET ${target}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${dependence}> ${directory}
        COMMENT "copy the .dll file to the same folder as the executable"
        POST_BUILD
        )
endmacro(qextMacroCopyLib)
