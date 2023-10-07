#################################################################################
#
# Library: QExt
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
# Creates a PreCompiled Header
# _TARGET target name
# _SCOPE INTERFACE|PUBLIC|PRIVATE
# _PCH_FILES The full path of the dependency incl. FileName
#--------------------------------------------------------------------------------
function(qextFunctionActivatePrecompiledHeaders _TARGET _SCOPE _PCH_FILES)
    if(COMMAND target_precompile_headers)
        target_precompile_headers(${_TARGET} ${_SCOPE} ${_PCH_FILES})
    else()
        set_target_properties(${_TARGET} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "${_PCH_FILES}")
        include(cotire)
        cotire(${_TARGET})
    endif()
endfunction(qextFunctionActivatePrecompiledHeaders)
