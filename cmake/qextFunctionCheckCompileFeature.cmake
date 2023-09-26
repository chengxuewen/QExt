#################################################################################
#
# Library: QEXT
#
# Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
#
# License: MIT License
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
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
# Check compile features
#--------------------------------------------------------------------------------
function(qextFunctionCheckCompileFeature VARIABLE DESCRIPTION SOURCE)
    if(MSVC)
        # Force warning as error to detect "noexcept" warning when exceptions are disabled:
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
    endif()
    string(MD5 hashInputs "${CMAKE_CXX_FLAGS}${SOURCE}")
    if(NOT DEFINED ${VARIABLE} OR NOT "${${VARIABLE}_HASH}" STREQUAL "${hashInputs}")
        file(WRITE ${CMAKE_BINARY_DIR}/CMakeTmp/qextCompileCheck.cpp "${SOURCE}\nint main() { return 0; };")
        try_compile(${VARIABLE} ${CMAKE_BINARY_DIR}/CMakeTmp ${CMAKE_BINARY_DIR}/CMakeTmp/qextCompileCheck.cpp
        OUTPUT_VARIABLE output
        CXX_STANDARD ${CMAKE_CXX_STANDARD}
        )
        if(${VARIABLE})
            message("${DESCRIPTION} -- yes")
            set(${VARIABLE} 1 CACHE INTERNAL "${DESCRIPTION}")
        else()
            message("${DESCRIPTION} -- no")
            set(${VARIABLE} 0 CACHE INTERNAL "${DESCRIPTION}")
        endif()
       set("${VARIABLE}_HASH" "${hashInputs}" CACHE INTERNAL "${DESCRIPTION} (hashed inputs)")
    endif()
endfunction(qextFunctionCheckCompileFeature)
