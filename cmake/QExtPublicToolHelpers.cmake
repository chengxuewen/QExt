########################################################################################################################
#
# Library: QEXT
#
# Copyright (C) 2025 ChengXueWen.
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
# The function returns location of the imported 'tool', returns an empty string if tool is not
# imported.
#-----------------------------------------------------------------------------------------------------------------------
function(_qext_internal_get_tool_imported_location out_var tool)
    unset(${out_var})
    if("${tool}" MATCHES "^Qt[0-9]?::.+$")
        # The tool target has namespace already
        set(target ${tool})
    else()
        set(target ${QT_CMAKE_EXPORT_NAMESPACE}::${tool})
    endif()

    if(NOT TARGET ${target})
        message(FATAL_ERROR "${target} is not a target.")
    endif()

    get_target_property(is_imported ${target} IMPORTED)
    if(NOT is_imported)
        set(${out_var} "" PARENT_SCOPE)
        return()
    endif()

    get_target_property(configs ${target} IMPORTED_CONFIGURATIONS)
    list(TRANSFORM configs PREPEND _)
    # Well-known configuration types
    list(APPEND configs
        _RELWITHDEBINFO
        _RELEASE
        _MINSIZEREL
        _DEBUG
    )
    list(REMOVE_DUPLICATES configs)
    # Look for the default empty configuration type at the first place.
    list(PREPEND configs "")

    foreach(config ${configs})
        get_target_property(${out_var} ${target} "IMPORTED_LOCATION${config}")
        if(${out_var})
            break()
        endif()
    endforeach()

    set(${out_var} "${${out_var}}" PARENT_SCOPE)
endfunction()