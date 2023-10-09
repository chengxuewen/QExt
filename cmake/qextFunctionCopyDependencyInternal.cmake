########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2021~Present ChengXueWen. Contact: 1398831004@qq.com.
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

function(qextFunctionCopyDependencyInternal)
    set(multiValueArgs LIBS)
    set(oneValueArgs TARGET DESTINATION)
    set(options PRE_BUILD PRE_LINK POST_BUILD VERBOSE MATCHING)
    cmake_parse_arguments(MY "${options}" "${oneValueArgs}" "${multiValueArgs}" "${ARGN}")

    set(HAPPENS)
    if(MY_PRE_BUILD)
        list(APPEND HAPPENS PRE_BUILD)
    endif()
    if(MY_PRE_LINK)
        list(APPEND HAPPENS PRE_LINK)
    endif()
    if(MY_POST_BUILD)
        list(APPEND HAPPENS POST_BUILD)
    endif()

    if(MY_VERBOSE)
        message(STATUS "----VERBOSE---- qextFunctionCopyDependencyInternal")
        message(STATUS MY_LIBS=${MY_LIBS})
        message(STATUS MY_TARGET=${MY_TARGET})
        message(STATUS MY_DESTINATION=${MY_DESTINATION})
        message(STATUS MY_PRE_BUILD=${MY_PRE_BUILD})
        message(STATUS MY_PRE_LINK=${MY_PRE_LINK})
        message(STATUS MY_POST_BUILD=${MY_POST_BUILD})
        message(STATUS HAPPENS=${HAPPENS})
    endif()

    foreach(child ${MY_LIBS})
        if(MY_MATCHING)
            add_custom_command(
                TARGET ${MY_TARGET}
                COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_LINKER_FILE:${child}>* ${MY_DESTINATION}
                COMMENT "copy the depends internal lib ${child} to the ${MY_DESTINATION} folder"
                ${HAPPENS}
                )
        else()
            add_custom_command(
                TARGET ${MY_TARGET}
                COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${child}> ${MY_DESTINATION}
                COMMENT "copy the depends internal lib ${child} to the ${MY_DESTINATION} folder"
                ${HAPPENS}
                )
        endif()
    endforeach()

endfunction(qextFunctionCopyDependencyInternal)
