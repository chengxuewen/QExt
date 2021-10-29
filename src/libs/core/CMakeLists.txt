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
# Set lib base name and out put path
#--------------------------------------------------------------------------------
set(qext_lib_base_name QEXTCore)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(qext_lib_public_headers
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
    include/invoke/qextSlot.h
    include/invoke/qextTrackObjectFunctor.h
    include/invoke/qextVisitor.h

    include/tools/qextId.h
    include/tools/qextPreprocessor.h
    include/tools/qextTypeInfo.h
    include/tools/qextTypeTrait.h
    include/tools/qextUniquePointer.h
    )

set(qext_lib_private_headers
    )

set(qext_lib_sources
    source/invoke/qextConnection.cpp
    source/invoke/qextSignal.cpp
    source/invoke/qextSlot.cpp

    source/tools/qextId.cpp
    source/tools/qextLinearFunction.cpp
    )

set(qext_lib_forms

    )

set(qext_lib_resources

    )



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(qext_lib_link_libraries)

if(UNIX)
    list(APPEND qext_lib_link_libraries ${CMAKE_DL_LIBS})
endif()

if(WIN32)
    list(APPEND qext_lib_link_libraries shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND qext_lib_link_libraries ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND qext_lib_link_libraries Qt4::QtCore)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND qext_lib_link_libraries Qt${QEXT_QT_VERSION_MAJOR}::Core Qt${QEXT_QT_VERSION_MAJOR}::Gui)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()



#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
add_library(${qext_lib_base_name}
    ${qext_lib_public_headers}
    ${qext_lib_private_headers}
    ${qext_lib_sources}
    ${qext_lib_forms}
    ${qext_lib_resources}
    ${QEXT_CONFIG_HPP_FILE_PATH}
    )
if (QEXT_BUILD_COMPILER_WARNING)
    qextFunctionSetCompilerWarnings(${qext_lib_base_name})
endif()
target_link_libraries(${qext_lib_base_name} PUBLIC ${qext_lib_link_libraries})
target_include_directories(${qext_lib_base_name} PUBLIC
    $<BUILD_INTERFACE:${QEXT_CONFIG_HPP_FILE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/invoke>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/global>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/tools>
    $<INSTALL_INTERFACE:include>
    )
set(${qext_lib_base_name}_PRIVATE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/private
    ${CMAKE_CURRENT_SOURCE_DIR}/private/invoke
    ${CMAKE_CURRENT_SOURCE_DIR}/private/global
    ${CMAKE_CURRENT_SOURCE_DIR}/private/tools
    CACHE INTERNAL "${qext_lib_base_name} private include dirs"
    )
target_include_directories(${qext_lib_base_name} PRIVATE
    $<BUILD_INTERFACE:${${qext_lib_base_name}_PRIVATE_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:private>
    )
target_compile_definitions(${qext_lib_base_name} PRIVATE QEXT_BUILD_CORE_LIB)


# set target properties
set_target_properties(${qext_lib_base_name} PROPERTIES
    VERSION ${QEXT_VERSION} SOVERSION ${QEXT_SO_VERSION}
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    DEBUG_POSTFIX ${QEXT_DEBUG_POSTFIX}
    )
if (QEXT_BUILD_SHARED_LIBS)
    set_target_properties(${qext_lib_base_name} PROPERTIES
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
