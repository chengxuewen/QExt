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
# Set lib base name
#--------------------------------------------------------------------------------
set(_lib_base_name QEXTWidgwts)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(_lib_public_headers
    include/qextstyle.h
    include/qextstyleoption.h
)

set(_lib_private_headers

)

set(_lib_sources
    source/qextstyle.cpp
    source/qextstyleoption.cpp
)

set(_lib_forms

)

set(_lib_resources

)



#--------------------------------------------------------------------------------
# Set lib name and version
#--------------------------------------------------------------------------------
set(_lib_link_libraries)

if(QEXT_QT_VERSION VERSION_EQUAL "4")
    list(APPEND _lib_link_libraries ${QT_LIBRARIES} Qt4::QtCore)
elseif(QEXT_QT_VERSION VERSION_EQUAL "5")
    list(APPEND _lib_link_libraries Qt5::Core Qt5::Gui Qt5::Widgets)
endif()

list(APPEND _lib_link_libraries QEXTCore QEXTGui)



#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
add_library(${_lib_base_name}
    ${_lib_public_headers}
    ${_lib_private_headers}
    ${_lib_sources}
    ${_lib_forms}
    ${_lib_resources}
    )
#qextFunctionSetCompilerWarnings(${_lib_base_name})
target_link_libraries(${_lib_base_name} PUBLIC ${_lib_link_libraries})
target_include_directories(${_lib_base_name} PUBLIC
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                            $<INSTALL_INTERFACE:include>
                            )
target_include_directories(${_lib_base_name} PRIVATE
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
                            )

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

#add_library(${_lib_base_name}-private INTERFACE
#            ${_lib_private_headers}
#            )
#target_include_directories(${_lib_base_name}-private INTERFACE
#                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
#                            )



#--------------------------------------------------------------------------------
# Add lib tests and examples
#--------------------------------------------------------------------------------
if (QEXT_BUILD_TESTS OR QEXT_BUILD_ALL)
    add_subdirectory(tests)
endif()

if (QEXT_BUILD_EXAMPLES OR QEXT_BUILD_ALL)
    add_subdirectory(examples)
endif()

