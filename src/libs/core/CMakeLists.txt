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
set(_lib_base_name QEXTCore)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(_lib_public_headers
    include/qextadaptortrait.h
    include/qextargument.h
    include/qextbind.h
    include/qextbindreturn.h
    include/qextboundargument.h
    include/qextfunctor.h
    include/qextfunctortrait.h
    include/qextglobal.h
    include/qextid.h
    include/qextlimitreference.h
    include/qextmemberfunctor.h
    include/qextobject.h
    include/qextreferencewrapper.h
    include/qextreturntypededuce.h
    include/qextsignal.h
    include/qextsignalbase.h
    include/qextsingleton.h
    include/qexttypetrait.h
    include/qextslot.h
    include/qextslotbase.h
    include/qexttrackable.h
    include/qextvisitor.h
    )

set(_lib_private_headers
    private/qextobject_p.h
    )

set(_lib_sources
    source/qextid.cpp
    source/qextobject.cpp
    source/qextsignalbase.cpp
    source/qextslotbase.cpp
    source/qexttrackable.cpp
    )

set(_lib_forms

    )

set(_lib_resources

    )



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(_lib_link_libraries)

if(UNIX)
    list(APPEND _lib_link_libraries ${CMAKE_DL_LIBS})
endif()

if(WIN32)
    list(APPEND _lib_link_libraries shlwapi.lib)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND _lib_link_libraries ${CMAKE_THREAD_LIBS_INIT})
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _lib_link_libraries Qt4::QtCore)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _lib_link_libraries Qt5::Core Qt5::Gui)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()



#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
add_library(${_lib_base_name}
    ${_lib_public_headers}
    ${_lib_private_headers}
    ${_lib_sources}
    ${_lib_forms}
    ${_lib_resources}
    ${QEXT_CONFIG_HPP_FILE_PATH}
    )
if (QEXT_BUILD_COMPILER_WARNING)
    qextFunctionSetCompilerWarnings(${_lib_base_name})
endif()
target_link_libraries(${_lib_base_name} PUBLIC ${_lib_link_libraries})
target_include_directories(${_lib_base_name} PUBLIC
    $<BUILD_INTERFACE:${QEXT_CONFIG_HPP_FILE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<INSTALL_INTERFACE:include>
    )
target_compile_definitions(${_lib_base_name} PRIVATE QEXT_BUILD_CORE_LIB)


# set target properties
set_target_properties(${_lib_base_name} PROPERTIES
    VERSION ${QEXT_VERSION} SOVERSION ${QEXT_SO_VERSION}
    CXX_STANDARD ${QEXT_CXX_STANDARD}
    DEBUG_POSTFIX ${QEXT_DEBUG_POSTFIX}
    )
if (QEXT_BUILD_SHARED_LIBS)
    set_target_properties(${_lib_base_name} PROPERTIES
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
