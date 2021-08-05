#################################################################################
#
# Library: QEXT
#
# Copyright (c) 2021 ChengXueWen 1398831004@qq.com
# Copyright (c) 2014 - 2018 Axel Menzel <info@rttr.org>
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
# Adds warnings compiler options to the target depending on the category target Target name
#--------------------------------------------------------------------------------
function(qextFunctionSetCompilerWarnings target)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(WARNINGS "-Werror" "-Wall")
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(WARNINGS "-Werror" "-Wall")
    elseif(MSVC)
        set(WARNINGS "/WX" "/W4")
    endif()
    target_compile_options(${target} PRIVATE ${WARNINGS})
endfunction()
