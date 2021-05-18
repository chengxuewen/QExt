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
set(_lib_base_name QEXTMvvm)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(_lib_public_headers
    include/qextmvvmabstractitemcommand.h
    include/qextmvvmabstractitemlistener.h
    include/qextmvvmabstractmodellistener.h
    include/qextmvvmabstractviewmodel.h
    include/qextmvvmcallback.h
    include/qextmvvmcommandadapter.h
    include/qextmvvmcommandservice.h
    include/qextmvvmglobal.h
    include/qextmvvmitem.h
    include/qextmvvmitemcatalogue.h
    include/qextmvvmitemcommand.h
    include/qextmvvmitemcontainer.h
    include/qextmvvmitemdata.h
    include/qextmvvmitemfactory.h
    include/qextmvvmitemfactoryinterface.h
    include/qextmvvmitemlistenerinterface.h
    include/qextmvvmitemmanager.h
    include/qextmvvmitemmapper.h
    include/qextmvvmitempool.h
    include/qextmvvmitemtags.h
    include/qextmvvmmodel.h
    include/qextmvvmmodellistener.h
    include/qextmvvmmodellistenerinterface.h
    include/qextmvvmmodelmapper.h
    include/qextmvvmtaginfo.h
    include/qextmvvmtagrow.h
    include/qextmvvmundostackinterface.h
    include/qextmvvmviewmodel.h
    include/qextmvvmviewmodelcontroller.h
    include/qextmvvmviewmodeldelegate.h
    )

set(_lib_private_headers
    private/qextmvvmabstractitemcommand_p.h
    private/qextmvvmabstractitemlistener_p.h
    private/qextmvvmitem_p.h
    private/qextmvvmitemcontainer_p.h
    private/qextmvvmitemmapper_p.h
    private/qextmvvmitemtags_p.h
    private/qextmvvmmodelmapper_p.h
    )

set(_lib_sources
    source/qextmvvmabstractitemcommand.cpp
    source/qextmvvmabstractitemlistener.cpp
    source/qextmvvmabstractmodellistener.cpp
    source/qextmvvmabstractviewmodel.cpp
    source/qextmvvmcommandadapter.cpp
    source/qextmvvmcommandservice.cpp
    source/qextmvvmitem.cpp
    source/qextmvvmitemcatalogue.cpp
    source/qextmvvmitemcommand.cpp
    source/qextmvvmitemcontainer.cpp
    source/qextmvvmitemdata.cpp
    source/qextmvvmitemfactory.cpp
    source/qextmvvmitemmanager.cpp
    source/qextmvvmitemmapper.cpp
    source/qextmvvmitempool.cpp
    source/qextmvvmitemtags.cpp
    source/qextmvvmmodel.cpp
    source/qextmvvmmodelmapper.cpp
    source/qextmvvmtaginfo.cpp
    source/qextmvvmtagrow.cpp
    source/qextmvvmviewmodel.cpp
    source/qextmvvmviewmodelcontroller.cpp
    source/qextmvvmviewmodeldelegate.cpp

    )

set(_lib_forms

    )

set(_lib_resources

    )



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(_lib_link_libraries)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _lib_link_libraries Qt4::QtCore Qt4::QtNetwork)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _lib_link_libraries Qt5::Core Qt5::Network)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND _lib_link_libraries QEXTCore)



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
if (QEXT_BUILD_COMPILER_WARNING)
    qextFunctionSetCompilerWarnings(${_lib_base_name})
endif()
target_link_libraries(${_lib_base_name} PUBLIC ${_lib_link_libraries})
target_include_directories(${_lib_base_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<INSTALL_INTERFACE:include>
    )
target_compile_definitions(${_lib_base_name} PRIVATE QEXT_BUILD_MVVM_LIB)


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
