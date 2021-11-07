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
    include/model/commands/qextMvvmAbstractItemCommand.h
    include/model/commands/qextMvvmCommandAdapter.h
    include/model/commands/qextMvvmCommandResult.h
    include/model/commands/qextMvvmCommandService.h
    include/model/commands/qextMvvmCommandUtils.h
    include/model/commands/qextMvvmCopyItemCommand.h
    include/model/commands/qextMvvmInsertNewItemCommand.h
    include/model/commands/qextMvvmMoveItemCommand.h
    include/model/commands/qextMvvmRemoveItemCommand.h
    include/model/commands/qextMvvmSetValueCommand.h
    include/model/commands/qextMvvmUndoStack.h
    include/model/interfaces/qextMvvmApplicationModelsInterface.h
    include/model/interfaces/qextMvvmItemBackupStrategy.h
    include/model/interfaces/qextMvvmItemCopyStrategy.h
    include/model/interfaces/qextMvvmItemFactoryInterface.h
    include/model/interfaces/qextMvvmItemListenerInterface.h
    include/model/interfaces/qextMvvmModelDocumentInterface.h
    include/model/interfaces/qextMvvmModelListenerInterface.h
    include/model/interfaces/qextMvvmProjectInterface.h
    include/model/interfaces/qextMvvmProjectManagerInterface.h
    include/model/interfaces/qextMvvmUndoStackInterface.h
    include/model/interfaces/qextMvvmFactoryInterface.h
    include/model/project/qextMvvmModelHasChangedController.h
    include/model/project/qextMvvmProject.h
    include/model/project/qextMvvmProjectTypes.h
    include/model/project/qextMvvmProjectChangeController.h
    include/model/project/qextMvvmProjectManager.h
    include/model/project/qextMvvmProjectManagerDecorator.h
    include/model/project/qextMvvmProjectUtils.h
    include/model/standarditems/qextMvvmAxisItems.h
    include/model/standarditems/qextMvvmColorMapItem.h
    include/model/standarditems/qextMvvmColorMapViewPortItem.h
    include/model/standarditems/qextMvvmContainerItem.h
    include/model/standarditems/qextMvvmData1dItem.h
    include/model/standarditems/qextMvvmData2dItem.h
    include/model/standarditems/qextMvvmGraphItem.h
    include/model/standarditems/qextMvvmGraphViewPortItem.h
    include/model/standarditems/qextMvvmLinkedItem.h
    include/model/standarditems/qextMvvmPlotTableItems.h
    include/model/standarditems/qextMvvmStandardItemIncludes.h
    include/model/standarditems/qextMvvmVectorItem.h
    include/model/standarditems/qextMvvmViewPortItem.h
    include/model/qextMvvmComboProperty.h
    include/model/qextMvvmComparators.h
    include/model/qextMvvmCompoundItem.h
    include/model/qextMvvmDataRole.h
    include/model/qextMvvmExternalProperty.h
    include/model/qextMvvmFactory.h
    include/model/qextMvvmGroupItem.h
    include/model/qextMvvmItemCatalogue.h
    include/model/qextMvvmItemFactory.h
    include/model/qextMvvmItemManager.h
    include/model/qextMvvmItemPool.h
    include/model/qextMvvmPath.h
    include/model/qextMvvmPropertyItem.h
    include/model/qextMvvmItem.h
    include/model/qextMvvmItemContainer.h
    include/model/qextMvvmItemData.h
    include/model/qextMvvmItemTags.h
    include/model/qextMvvmModel.h
    include/model/qextMvvmTagInfo.h
    include/model/qextMvvmTagRow.h
    include/model/qextMvvmTypes.h
    include/model/qextMvvmUniqueIdGenerator.h
    include/model/qextMvvmProgressHandler.h
    include/model/qextMvvmRealLimits.h
    include/model/qextMvvmThreadSafeStack.h
    include/model/qextMvvmItemListener.h
    include/model/qextMvvmItemListenerBase.h
    include/model/qextMvvmItemMapper.h
    include/model/qextMvvmModelListener.h
    include/model/qextMvvmModelListenerBase.h
    include/model/qextMvvmModelMapper.h
    include/model/qextMvvmFunctionTypes.h

    include/view/plotting/qextMvvmAxisTitleController.h
    include/view/plotting/qextMvvmColorMapCanvas.h
    include/view/plotting/qextMvvmColorMapInfoFormatter.h
    include/view/plotting/qextMvvmColorMapPlotController.h
    include/view/plotting/qextMvvmColorMapViewPortPlotController.h
    include/view/plotting/qextMvvmColorScalePlotController.h
    include/view/plotting/qextMvvmCustomPlotProxyWidget.h
    include/view/plotting/qextMvvmCustomPlotSceneAdapter.h
    include/view/plotting/qextMvvmCustomPlotUtils.h
    include/view/plotting/qextMvvmData1dPlotController.h
    include/view/plotting/qextMvvmData2dPlotController.h
    include/view/plotting/qextMvvmGraphCanvas.h
    include/view/plotting/qextMvvmGraphInfoFormatter.h
    include/view/plotting/qextMvvmGraphPlotController.h
    include/view/plotting/qextMvvmGraphViewPortPlotController.h
    include/view/plotting/qextMvvmMouseMoveReporter.h
    include/view/plotting/qextMvvmMousePosInfo.h
    include/view/plotting/qextMvvmPenController.h
    include/view/plotting/qextMvvmSceneAdapterInterface.h
    include/view/plotting/qextMvvmStatusStringFormatterInterface.h
    include/view/plotting/qextMvvmStatusStringReporter.h
    include/view/plotting/qextMvvmStatusStringReporterFactory.h
    include/view/plotting/qextMvvmViewPortAxisPlotController.h
    include/view/widgets/qextMvvmAdjustingScrollArea.h
    include/view/widgets/qextMvvmAllItemsTreeView.h
    include/view/widgets/qextMvvmCollapsibleBar.h
    include/view/widgets/qextMvvmCollapsibleListWidget.h
    include/view/widgets/qextMvvmItemsTreeView.h
    include/view/widgets/qextMvvmItemsTreeViewInterface.h
    include/view/widgets/qextMvvmLayoutUtils.h
    include/view/widgets/qextMvvmPropertyFlatView.h
    include/view/widgets/qextMvvmPropertyTreeView.h
    include/view/widgets/qextMvvmStandardTreeViews.h
    include/view/widgets/qextMvvmStatusLabel.h
    include/view/widgets/qextMvvmTopItemsTreeView.h
    include/view/widgets/qextMvvmWidgetUtils.h

    include/viewmodel/editors/qextMvvmBoolEditor.h
    include/viewmodel/editors/qextMvvmColorEditor.h
    include/viewmodel/editors/qextMvvmComboPropertyEditor.h
    include/viewmodel/editors/qextMvvmCustomEditor.h
    include/viewmodel/editors/qextMvvmCustomEventFilters.h
    include/viewmodel/editors/qextMvvmDefaultEditorFactory.h
    include/viewmodel/editors/qextMvvmDoubleEditor.h
    include/viewmodel/editors/qextMvvmEditorConstants.h
    include/viewmodel/editors/qextMvvmEditorBuilders.h
    include/viewmodel/editors/qextMvvmExternalPropertyComboEditor.h
    include/viewmodel/editors/qextMvvmExternalPropertyEditor.h
    include/viewmodel/editors/qextMvvmIntegerEditor.h
    include/viewmodel/editors/qextMvvmScientificDoubleEditor.h
    include/viewmodel/editors/qextMvvmScientificSpinbox.h
    include/viewmodel/editors/qextMvvmScientificSpinboxEditor.h
    include/viewmodel/editors/qextMvvmSelectableComboboxEditor.h
    include/viewmodel/editors/qextMvvmStyleUtils.h
    include/viewmodel/interfaces/qextMvvmCellDecoratorInterface.h
    include/viewmodel/interfaces/qextMvvmChildrenStrategyInterface.h
    include/viewmodel/interfaces/qextMvvmEditorFactoryInterface.h
    include/viewmodel/interfaces/qextMvvmRowStrategyInterface.h
    include/viewmodel/qextMvvmDefaultCellDecorator.h
    include/viewmodel/qextMvvmDefaultViewModel.h
    include/viewmodel/qextMvvmLabelDataRowStrategy.h
    include/viewmodel/qextMvvmPropertiesRowStrategy.h
    include/viewmodel/qextMvvmPropertyFlatViewModel.h
    include/viewmodel/qextMvvmPropertyTableViewModel.h
    include/viewmodel/qextMvvmPropertyViewModel.h
    include/viewmodel/qextMvvmStandardChildrenStrategies.h
    include/viewmodel/qextMvvmStandardViewItems.h
    include/viewmodel/qextMvvmStandardViewModelControllers.h
    include/viewmodel/qextMvvmTopItemsViewModel.h
    include/viewmodel/qextMvvmViewItem.h
    include/viewmodel/qextMvvmViewModel.h
    include/viewmodel/qextMvvmViewModelBase.h
    include/viewmodel/qextMvvmViewModelController.h
    include/viewmodel/qextMvvmViewModelDelegate.h
    include/viewmodel/qextMvvmViewModelUtils.h
    include/viewmodel/qextMvvmViewModelControllerBuilder.h
    include/viewmodel/qextMvvmViewModelFactory.h

    include/qextMvvm.h
    include/qextMvvmConstants.h
    include/qextMvvmEvent.h
    include/qextMvvmGlobal.h
    include/qextMvvmUtils.h
    )

set(qext_lib_private_headers
    private/model/commands/qextMvvmAbstractItemCommand_p.h
    private/model/commands/qextMvvmCommandService_p.h
    private/model/commands/qextMvvmCopyItemCommand_p.h
    private/model/commands/qextMvvmInsertNewItemCommand_p.h
    private/model/commands/qextMvvmMoveItemCommand_p.h
    private/model/commands/qextMvvmRemoveItemCommand_p.h
    private/model/commands/qextMvvmSetValueCommand_p.h
    private/model/commands/qextMvvmUndoStack_p.h

    private/model/project/qextMvvmProject_p.h

    private/model/qextMvvmComboProperty_p.h
    private/model/qextMvvmExternalProperty_p.h
    private/model/qextMvvmItemCatalogue_p.h
    private/model/qextMvvmItemContainer_p.h
    private/model/qextMvvmItemManager_p.h
    private/model/qextMvvmItemMapper_p.h
    private/model/qextMvvmItemPool_p.h
    private/model/qextMvvmItemTags_p.h
    private/model/qextMvvmItem_p.h
    private/model/qextMvvmModelMapper_p.h
    private/model/qextMvvmModel_p.h

    private/viewmodel/qextMvvmViewItem_p.h

    private/view/widgets/qextMvvmPropertyFlatView_p.h
    )

set(qext_lib_sources
    source/model/commands/qextMvvmAbstractItemCommand.cpp
    source/model/commands/qextMvvmCommandAdapter.cpp
    source/model/commands/qextMvvmCommandService.cpp
    source/model/commands/qextMvvmCommandUtils.cpp
    source/model/commands/qextMvvmCommandResult.cpp
    source/model/commands/qextMvvmCopyItemCommand.cpp
    source/model/commands/qextMvvmInsertNewItemCommand.cpp
    source/model/commands/qextMvvmMoveItemCommand.cpp
    source/model/commands/qextMvvmRemoveItemCommand.cpp
    source/model/commands/qextMvvmSetValueCommand.cpp
    source/model/commands/qextMvvmUndoStack.cpp
    source/model/project/qextMvvmModelHasChangedController.cpp
    source/model/project/qextMvvmProject.cpp
    source/model/project/qextMvvmProjectChangeController.cpp
    source/model/project/qextMvvmProjectManager.cpp
    source/model/project/qextMvvmProjectManagerDecorator.cpp
    source/model/project/qextMvvmProjectUtils.cpp
    source/model/standarditems/qextMvvmAxisItems.cpp
    source/model/standarditems/qextMvvmColorMapItem.cpp
    source/model/standarditems/qextMvvmColorMapViewPortItem.cpp
    source/model/standarditems/qextMvvmContainerItem.cpp
    source/model/standarditems/qextMvvmData1dItem.cpp
    source/model/standarditems/qextMvvmData2dItem.cpp
    source/model/standarditems/qextMvvmGraphItem.cpp
    source/model/standarditems/qextMvvmGraphViewPortItem.cpp
    source/model/standarditems/qextMvvmLinkedItem.cpp
    source/model/standarditems/qextMvvmPlotTableItems.cpp
    source/model/standarditems/qextMvvmVectorItem.cpp
    source/model/standarditems/qextMvvmViewPortItem.cpp
    source/model/qextMvvmComboProperty.cpp
    source/model/qextMvvmComparators.cpp
    source/model/qextMvvmCompoundItem.cpp
    source/model/qextMvvmDataRole.cpp
    source/model/qextMvvmFactory.cpp
    source/model/qextMvvmExternalProperty.cpp
    source/model/qextMvvmGroupItem.cpp
    source/model/qextMvvmItemCatalogue.cpp
    source/model/qextMvvmItemFactory.cpp
    source/model/qextMvvmItemManager.cpp
    source/model/qextMvvmItemPool.cpp
    source/model/qextMvvmPath.cpp
    source/model/qextMvvmPropertyItem.cpp
    source/model/qextMvvmItem.cpp
    source/model/qextMvvmItemContainer.cpp
    source/model/qextMvvmItemData.cpp
    source/model/qextMvvmItemTags.cpp
    source/model/qextMvvmModel.cpp
    source/model/qextMvvmTagInfo.cpp
    source/model/qextMvvmTagRow.cpp
    source/model/qextMvvmUniqueIdGenerator.cpp
    source/model/qextMvvmProgressHandler.cpp
    source/model/qextMvvmRealLimits.cpp
    source/model/qextMvvmItemListenerBase.cpp
    source/model/qextMvvmItemMapper.cpp
    source/model/qextMvvmModelListenerBase.cpp
    source/model/qextMvvmModelMapper.cpp

    source/view/plotting/qextMvvmAxisTitleController.cpp
    source/view/plotting/qextMvvmColorMapCanvas.cpp
    source/view/plotting/qextMvvmColorMapInfoFormatter.cpp
    source/view/plotting/qextMvvmColorMapPlotController.cpp
    source/view/plotting/qextMvvmColorMapViewPortPlotController.cpp
    source/view/plotting/qextMvvmColorScalePlotController.cpp
    source/view/plotting/qextMvvmCustomPlotProxyWidget.cpp
    source/view/plotting/qextMvvmCustomPlotSceneAdapter.cpp
    source/view/plotting/qextMvvmCustomPlotUtils.cpp
    source/view/plotting/qextMvvmData1dPlotController.cpp
    source/view/plotting/qextMvvmData2dPlotController.cpp
    source/view/plotting/qextMvvmGraphCanvas.cpp
    source/view/plotting/qextMvvmGraphInfoFormatter.cpp
    source/view/plotting/qextMvvmGraphPlotController.cpp
    source/view/plotting/qextMvvmGraphViewPortPlotController.cpp
    source/view/plotting/qextMvvmMouseMoveReporter.cpp
    source/view/plotting/qextMvvmPenController.cpp
    source/view/plotting/qextMvvmStatusStringReporter.cpp
    source/view/plotting/qextMvvmStatusStringReporterFactory.cpp
    source/view/plotting/qextMvvmViewPortAxisPlotController.cpp
    source/view/widgets/qextMvvmAdjustingScrollArea.cpp
    source/view/widgets/qextMvvmAllItemsTreeView.cpp
    source/view/widgets/qextMvvmCollapsibleBar.cpp
    source/view/widgets/qextMvvmCollapsibleListWidget.cpp
    source/view/widgets/qextMvvmItemsTreeView.cpp
    source/view/widgets/qextMvvmLayoutUtils.cpp
    source/view/widgets/qextMvvmPropertyFlatView.cpp
    source/view/widgets/qextMvvmPropertyTreeView.cpp
    source/view/widgets/qextMvvmStatusLabel.cpp
    source/view/widgets/qextMvvmTopItemsTreeView.cpp
    source/view/widgets/qextMvvmWidgetUtils.cpp

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
    source/viewmodel/editors/qextMvvmScientificSpinbox.cpp
    source/viewmodel/editors/qextMvvmScientificSpinboxEditor.cpp
    source/viewmodel/editors/qextMvvmSelectableComboboxEditor.cpp
    source/viewmodel/editors/qextMvvmStyleUtils.cpp
    source/viewmodel/qextMvvmDefaultCellDecorator.cpp
    source/viewmodel/qextMvvmDefaultViewModel.cpp
    source/viewmodel/qextMvvmLabelDataRowStrategy.cpp
    source/viewmodel/qextMvvmPropertiesRowStrategy.cpp
    source/viewmodel/qextMvvmPropertyFlatViewModel.cpp
    source/viewmodel/qextMvvmPropertyTableViewModel.cpp
    source/viewmodel/qextMvvmPropertyViewModel.cpp
    source/viewmodel/qextMvvmStandardChildrenStrategies.cpp
    source/viewmodel/qextMvvmStandardViewItems.cpp
    source/viewmodel/qextMvvmStandardViewModelControllers.cpp
    source/viewmodel/qextMvvmTopItemsViewModel.cpp
    source/viewmodel/qextMvvmViewItem.cpp
    source/viewmodel/qextMvvmViewModel.cpp
    source/viewmodel/qextMvvmViewModelBase.cpp
    source/viewmodel/qextMvvmViewModelController.cpp
    source/viewmodel/qextMvvmViewModelDelegate.cpp
    source/viewmodel/qextMvvmViewModelUtils.cpp
    source/viewmodel/qextMvvmViewModelControllerBuilder.cpp
    source/viewmodel/qextMvvmViewModelFactory.cpp

    source/qextMvvm.cpp
    source/qextMvvmEvent.cpp
    source/qextMvvmUtils.cpp
    )

set(qext_lib_forms

    )

set(qext_lib_resources
    resource/QEXTMvvm.qrc
    )

list(APPEND qext_lib_link_libraries QEXTCore)


#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(qext_lib_link_libraries)
set(qext_lib_include_directories)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND qext_lib_link_libraries Qt4::QtCore Qt4::QtGui Qt4::QtWidgets)
    list(APPEND qext_lib_include_directories
        ${Qt4Gui_PRIVATE_INCLUDE_DIRS}
        ${Qt4Widgets_PRIVATE_INCLUDE_DIRS}
        )
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND qext_lib_link_libraries
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets
        )
    list(APPEND qext_lib_include_directories
        ${Qt${QEXT_QT_VERSION_MAJOR}Gui_PRIVATE_INCLUDE_DIRS}
        ${Qt${QEXT_QT_VERSION_MAJOR}Widgets_PRIVATE_INCLUDE_DIRS}
        )
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND qext_lib_link_libraries QEXTCore qcustomplot)



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
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/model>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/model/commands>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/model/core>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/model/factories>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/model/interfaces>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/model/model>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/model/project>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/model/serialization>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/model/signals>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/model/standarditems>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/model/utils>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/view>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/view/plotting>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/view/widgets>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/viewmodel>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/viewmodel/editors>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/viewmodel/factories>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/viewmodel/interfaces>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/viewmodel/viewmodel>
    $<BUILD_INTERFACE:${qext_lib_include_directories}>
    $<INSTALL_INTERFACE:include>
    )
set(${qext_lib_base_name}_PRIVATE_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/private
    ${CMAKE_CURRENT_SOURCE_DIR}/private/model
    ${CMAKE_CURRENT_SOURCE_DIR}/private/model/commands
    ${CMAKE_CURRENT_SOURCE_DIR}/private/model/core
    ${CMAKE_CURRENT_SOURCE_DIR}/private/model/factories
    ${CMAKE_CURRENT_SOURCE_DIR}/private/model/interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/private/model/model
    ${CMAKE_CURRENT_SOURCE_DIR}/private/model/project
    ${CMAKE_CURRENT_SOURCE_DIR}/private/model/serialization
    ${CMAKE_CURRENT_SOURCE_DIR}/private/model/signals
    ${CMAKE_CURRENT_SOURCE_DIR}/private/model/standarditems
    ${CMAKE_CURRENT_SOURCE_DIR}/private/view
    ${CMAKE_CURRENT_SOURCE_DIR}/private/view/plotting
    ${CMAKE_CURRENT_SOURCE_DIR}/private/view/widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/private/viewmodel
    ${CMAKE_CURRENT_SOURCE_DIR}/private/viewmodel/editors
    ${CMAKE_CURRENT_SOURCE_DIR}/private/viewmodel/factories
    ${CMAKE_CURRENT_SOURCE_DIR}/private/viewmodel/interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/private/viewmodel/viewmodel
    CACHE INTERNAL "${qext_lib_base_name} private include dirs"
    )
target_include_directories(${qext_lib_base_name} PRIVATE
    $<BUILD_INTERFACE:${${qext_lib_base_name}_PRIVATE_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:private>
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
