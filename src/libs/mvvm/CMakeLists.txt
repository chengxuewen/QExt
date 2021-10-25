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
set(qext_lib_base_name QEXTMvvm)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(qext_lib_public_headers
    include/viewmodel/editors/qextMvvmBoolEditor.h
    include/viewmodel/editors/qextMvvmColorEditor.h
    include/viewmodel/editors/qextMvvmComboPropertyEditor.h
    include/viewmodel/editors/qextMvvmCustomEditor.h
    include/viewmodel/editors/qextMvvmCustomEventFilters.h
    include/viewmodel/editors/qextMvvmDefaultEditorFactory.h
    include/viewmodel/editors/qextMvvmDoubleEditor.h
    include/viewmodel/editors/qextMvvmEditorBuilders.h
    include/viewmodel/editors/qextMvvmExternalPropertyComboEditor.h
    include/viewmodel/editors/qextMvvmExternalPropertyEditor.h
    include/viewmodel/editors/qextMvvmIntegerEditor.h
    include/viewmodel/editors/qextMvvmScientificDoubleEditor.h
    include/viewmodel/editors/qextMvvmScientificSpinBox.h
    include/viewmodel/editors/qextMvvmScientificSpinBoxEditor.h
    include/viewmodel/editors/qextMvvmSelectableComboBoxEditor.h
    include/viewmodel/interface/qextMvvmCellDecoratorInterface.h
    include/viewmodel/interface/qextMvvmEditorFactoryInterface.h
    include/viewmodel/qextMvvmDefaultCellDecorator.h
    include/viewmodel/qextMvvmDefaultViewModel.h
    include/viewmodel/qextMvvmLabelDataRowStrategy.h
    include/viewmodel/qextMvvmPropertiesRowStrategy.h
    include/viewmodel/qextMvvmStandardChildrenStrategies.h
    include/viewmodel/qextMvvmStandardViewItems.h
    include/viewmodel/qextMvvmStandardViewModelControllers.h
    include/viewmodel/qextMvvmViewModel.h
    include/viewmodel/qextMvvmViewModelDelegate.h

    include/qextMvvmConstants.h
    include/qextMvvmGlobal.h
    include/qextMvvmUtils.h
    )

set(qext_lib_private_headers
    private/viewmodel/qextMvvmViewModel_p.h
    )

set(qext_lib_sources
    source/viewmodel/editors/qextMvvmBoolEditor.cpp
    source/viewmodel/editors/qextMvvmColorEditor.cpp
    source/viewmodel/editors/qextMvvmComboPropertyEditor.cpp
    source/viewmodel/editors/qextMvvmCustomEditor.cpp
    source/viewmodel/editors/qextMvvmCustomEventFilters.cpp
    source/viewmodel/editors/qextMvvmDefaultEditorFactory.cpp
    source/viewmodel/editors/qextMvvmDoubleEditor.cpp
    source/viewmodel/editors/qextMvvmEditorBuilders.cpp
    source/viewmodel/editors/qextMvvmExternalPropertyComboEditor.cpp
    source/viewmodel/editors/qextMvvmExternalPropertyEditor.cpp
    source/viewmodel/editors/qextMvvmIntegerEditor.cpp
    source/viewmodel/editors/qextMvvmScientificDoubleEditor.cpp
    source/viewmodel/editors/qextMvvmScientificSpinBox.cpp
    source/viewmodel/editors/qextMvvmScientificSpinBoxEditor.cpp
    source/viewmodel/editors/qextMvvmSelectableComboBoxEditor.cpp
    source/viewmodel/qextMvvmDefaultCellDecorator.cpp
    source/viewmodel/qextMvvmDefaultViewModel.cpp
    source/viewmodel/qextMvvmLabelDataRowStrategy.cpp
    source/viewmodel/qextMvvmPropertiesRowStrategy.cpp
    source/viewmodel/qextMvvmStandardChildrenStrategies.cpp
    source/viewmodel/qextMvvmStandardViewItems.cpp
    source/viewmodel/qextMvvmStandardViewModelControllers.cpp
    source/viewmodel/qextMvvmViewModel.cpp
    source/viewmodel/qextMvvmViewModelDelegate.cpp

    source/qextMvvmConstants.cpp
    source/qextMvvmUtils.cpp
    )

set(qext_lib_forms

    )

set(qext_lib_resources
    resource/QEXTMvvm.qrc
    )



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(qext_lib_link_libraries)
set(qext_lib_include_directories)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND qext_lib_link_libraries Qt4::QtCore Qt4::QtGui Qt4::QtSvg)
    list(APPEND qext_lib_include_directories
        ${Qt4Gui_PRIVATE_INCLUDE_DIRS}
        ${Qt4Widgets_PRIVATE_INCLUDE_DIRS}
        )
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND qext_lib_link_libraries
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Svg
        )
    list(APPEND qext_lib_include_directories
        ${Qt${QEXT_QT_VERSION_MAJOR}Gui_PRIVATE_INCLUDE_DIRS}
        ${Qt${QEXT_QT_VERSION_MAJOR}Widgets_PRIVATE_INCLUDE_DIRS}
        )
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND qext_lib_link_libraries QEXTCore CFCore CFMvvm)
list(APPEND qext_lib_include_directories
    ${CFCore_PRIVATE_INCLUDE_DIRS}
    ${CFMvvm_PRIVATE_INCLUDE_DIRS}
    )


#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
add_library(${qext_lib_base_name}
    ${qext_lib_public_headers}
    ${qext_lib_private_headers}
    ${qext_lib_sources}
    ${qext_lib_forms}
    ${qext_lib_resources}
    )
if (QEXT_BUILD_COMPILER_WARNING)
    qextFunctionSetCompilerWarnings(${qext_lib_base_name})
endif()
target_link_libraries(${qext_lib_base_name} PUBLIC ${qext_lib_link_libraries})
target_include_directories(${qext_lib_base_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/viewmodel>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/viewmodel/editors>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/viewmodel/interface>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private/viewmodel>
    $<BUILD_INTERFACE:${qext_lib_include_directories}>
    $<INSTALL_INTERFACE:include>
    )
target_compile_definitions(${qext_lib_base_name} PRIVATE QEXT_BUILD_MVVM_LIB)


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
