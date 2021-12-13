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
# Set lib base name and out put path
#--------------------------------------------------------------------------------
set(QEXT_LIB_BASE_NAME QEXTCore)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(QEXT_LIB_PUBLIC_HEADERS
    include/global/qextCompiler.h
    include/global/qextGlobal.h
    include/global/qextProcessor.h
    include/global/qextSystem.h

    include/invoke/qextAdaptorTrait.h
    include/invoke/qextBindFunctor.h
    include/invoke/qextBindReturnFunctor.h
    include/invoke/qextBoundArgument.h
    include/invoke/qextComposeFunctor.h
    include/invoke/qextConnection.h
    include/invoke/qextFunction.h
    include/invoke/qextInPlace.h
    include/invoke/qextHideFunctor.h
    include/invoke/qextLambda.h
    include/invoke/qextLambdaBase.h
    include/invoke/qextLambdaGroup.h
    include/invoke/qextLambdaOperator.h
    include/invoke/qextLambdaSelect.h
    include/invoke/qextLimitReference.h
    include/invoke/qextLinearFunction.h
    include/invoke/qextMemberFunctor.h
    include/invoke/qextPointerFunctor.h
    include/invoke/qextReferenceWrapper.h
    include/invoke/qextReturnTypeDeduce.h
    include/invoke/qextRetypeFunctor.h
    include/invoke/qextRetypeReturnFunctor.h
    include/invoke/qextSignal.h
    include/invoke/qextTrackObjectFunctor.h
    include/invoke/qextVisitor.h
    include/invoke/qextEmitter.h

    include/tools/qextId.h
    include/tools/qextPreprocessor.h
    include/tools/qextTypeInfo.h
    include/tools/qextTypeTrait.h
    include/tools/qextUniquePointer.h

    include/qextPch.h
    )

set(QEXT_LIB_PRIVATE_HEADERS
    )

set(QEXT_LIB_SOURCES
    source/invoke/qextConnection.cpp
    source/invoke/qextSignal.cpp
    source/invoke/qextFunction.cpp

    source/tools/qextId.cpp
    source/tools/qextLinearFunction.cpp
    )

set(QEXT_LIB_FORMS

    )

set(QEXT_LIB_RESOURCES

    )



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(QEXT_LIB_LINK_LIBRARIES)

if(UNIX)
    list(APPEND QEXT_LIB_LINK_LIBRARIES ${CMAKE_DL_LIBS})
endif()

if(WIN32)
    list(APPEND QEXT_LIB_LINK_LIBRARIES shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND QEXT_LIB_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        )
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()



#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
add_library(${QEXT_LIB_BASE_NAME}
    ${QEXT_LIB_PUBLIC_HEADERS}
    ${QEXT_LIB_PRIVATE_HEADERS}
    ${QEXT_LIB_SOURCES}
    ${QEXT_LIB_FORMS}
    ${QEXT_LIB_RESOURCES}
    ${QEXT_CONFIG_HPP_FILE_PATH}
    )
if (QEXT_BUILD_COMPILER_WARNING)
    qextFunctionSetCompilerWarnings(${QEXT_LIB_BASE_NAME})
endif()
if (QEXT_BUILD_USE_PCH)
    qextFunctionActivatePrecompiledHeaders(${QEXT_LIB_BASE_NAME} PRIVATE include/qextPch.h)
endif()
target_link_libraries(${QEXT_LIB_BASE_NAME} PUBLIC ${QEXT_LIB_LINK_LIBRARIES})
target_include_directories(${QEXT_LIB_BASE_NAME} PUBLIC
    $<BUILD_INTERFACE:${QEXT_CONFIG_HPP_FILE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/invoke>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/global>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/tools>
    $<INSTALL_INTERFACE:include>
    )
set(${QEXT_LIB_BASE_NAME}_PRIVATE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/private
    ${CMAKE_CURRENT_SOURCE_DIR}/private/invoke
    ${CMAKE_CURRENT_SOURCE_DIR}/private/global
    ${CMAKE_CURRENT_SOURCE_DIR}/private/tools
    CACHE INTERNAL "${QEXT_LIB_BASE_NAME} private include dirs"
    )
target_include_directories(${QEXT_LIB_BASE_NAME} PRIVATE
    $<BUILD_INTERFACE:${${QEXT_LIB_BASE_NAME}_PRIVATE_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:private>
    )
if(QEXT_BUILD_SHARED_LIBS)
    target_compile_definitions(${QEXT_LIB_BASE_NAME} PUBLIC QEXT_BUILD_SHARED_LIBS)
endif()
target_compile_definitions(${QEXT_LIB_BASE_NAME} PRIVATE QEXT_BUILD_CORE_LIB)


# set target properties
set_target_properties(${QEXT_LIB_BASE_NAME} PROPERTIES
    VERSION ${QEXT_VERSION} SOVERSION ${QEXT_SO_VERSION}
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    DEBUG_POSTFIX ${QEXT_DEBUG_POSTFIX}
    )
if (QEXT_BUILD_SHARED_LIBS)
    set_target_properties(${QEXT_LIB_BASE_NAME} PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1)
endif()



#--------------------------------------------------------------------------------
# Add lib tests and examples
#--------------------------------------------------------------------------------
if (QEXT_BUILD_TESTS OR QEXT_BUILD_ALL)
    add_subdirectory(tests)
endif()

if (QEXT_BUILD_EXAMPLES OR QEXT_BUILD_ALL)
    add_subdirectory(examples)
endif()
