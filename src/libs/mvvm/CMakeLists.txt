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
set(qext_lib_base_name QEXTMvvm)
set(LIBRARY_OUTPUT_PATH ${QEXT_LIB_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Set lib file list
#--------------------------------------------------------------------------------
set(qext_lib_public_headers
    include/model/commands/qextMvvmItemCommand.h
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
    include/model/core/qextMvvmFileSystem.h
    include/model/core/qextMvvmTypes.h
    include/model/core/qextMvvmUniqueIdGenerator.h
    include/model/core/qextMvvmVersion.h
    include/model/factories/qextMvvmItemCatalogueFactory.h
    include/model/factories/qextMvvmItemConverterFactory.h
    include/model/factories/qextMvvmModelConverterFactory.h
    include/model/factories/qextMvvmModelDocumentFactory.h
    include/model/factories/qextMvvmProjectManagerFactory.h
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
    include/model/model/qextMvvmComboProperty.h
    include/model/model/qextMvvmComparators.h
    include/model/model/qextMvvmCompoundItem.h
    include/model/model/qextMvvmCustomVariants.h
    include/model/model/qextMvvmDataRole.h
    include/model/model/qextMvvmExternalProperty.h
    include/model/model/qextMvvmFunctionTypes.h
    include/model/model/qextMvvmGroupItem.h
    include/model/model/qextMvvmItemCatalogue.h
    include/model/model/qextMvvmItemFactory.h
    include/model/model/qextMvvmItemManager.h
    include/model/model/qextMvvmItemPool.h
    include/model/model/qextMvvmItemUtils.h
    include/model/model/qextMvvmModelUtils.h
    include/model/model/qextMvvmConstantsTypes.h
    include/model/model/qextMvvmPath.h
    include/model/model/qextMvvmPropertyItem.h
    include/model/model/qextMvvmSessionItem.h
    include/model/model/qextMvvmSessionItemContainer.h
    include/model/model/qextMvvmSessionItemData.h
    include/model/model/qextMvvmSessionItemTags.h
    include/model/model/qextMvvmSessionModel.h
    include/model/model/qextMvvmTagInfo.h
    include/model/model/qextMvvmTagRow.h
    include/model/model/qextMvvmVariantConstants.h
    include/model/project/qextMvvmModelHasChangedController.h
    include/model/project/qextMvvmProject.h
    include/model/project/qextMvvmProjectTypes.h
    include/model/project/qextMvvmProjectChangeController.h
    include/model/project/qextMvvmProjectManager.h
    include/model/project/qextMvvmProjectManagerDecorator.h
    include/model/project/qextMvvmProjectUtils.h
    include/model/serialization/qextMvvmCompatibilityUtils.h
    include/model/serialization/qextMvvmJsonConverterInterfaces.h
    include/model/serialization/qextMvvmJsonDocument.h
    include/model/serialization/qextMvvmJsonItemTypes.h
    include/model/serialization/qextMvvmJsonItemBackupStrategy.h
    include/model/serialization/qextMvvmJsonItemContainerConverter.h
    include/model/serialization/qextMvvmJsonItemConverter.h
    include/model/serialization/qextMvvmJsonItemConverterInterface.h
    include/model/serialization/qextMvvmJsonItemCopyStrategy.h
    include/model/serialization/qextMvvmJsonItemDataConverter.h
    include/model/serialization/qextMvvmJsonItemDataConverterInterface.h
    include/model/serialization/qextMvvmJsonItemFormatAssistant.h
    include/model/serialization/qextMvvmJsonItemTagsConverter.h
    include/model/serialization/qextMvvmJsonModelConverter.h
    include/model/serialization/qextMvvmJsonModelConverterInterface.h
    include/model/serialization/qextMvvmJsonTagInfoConverter.h
    include/model/serialization/qextMvvmJsonTagInfoConverterInterface.h
    include/model/serialization/qextMvvmJsonUtils.h
    include/model/serialization/qextMvvmJsonVariantConverter.h
    include/model/serialization/qextMvvmJsonVariantConverterInterface.h
    include/model/signals/qextMvvmCallbackTypes.h
    include/model/signals/qextMvvmCallbackContainer.h
    include/model/signals/qextMvvmItemListener.h
    include/model/signals/qextMvvmItemListenerBase.h
    include/model/signals/qextMvvmItemMapper.h
    include/model/signals/qextMvvmModelListener.h
    include/model/signals/qextMvvmModelListenerBase.h
    include/model/signals/qextMvvmModelMapper.h
    include/model/standarditems/qextMvvmAxisItems.h
    include/model/standarditems/qextMvvmColorMapItem.h
    include/model/standarditems/qextMvvmColorMapViewPortItem.h
    include/model/standarditems/qextMvvmContainerItem.h
    include/model/standarditems/qextMvvmData1DItem.h
    include/model/standarditems/qextMvvmData2DItem.h
    include/model/standarditems/qextMvvmGraphItem.h
    include/model/standarditems/qextMvvmGraphViewPortItem.h
    include/model/standarditems/qextMvvmLinkedItem.h
    include/model/standarditems/qextMvvmPlotTableItems.h
    include/model/standarditems/qextMvvmStandardItemIncludes.h
    include/model/standarditems/qextMvvmVectorItem.h
    include/model/standarditems/qextMvvmViewPortItem.h
    include/model/utils/qextMvvmBinUtils.h
    include/model/utils/qextMvvmContainerUtils.h
    include/model/utils/qextMvvmFileUtils.h
    include/model/utils/qextMvvmIFactory.h
    include/model/utils/qextMvvmMathConstants.h
    include/model/utils/qextMvvmNumericUtils.h
    include/model/utils/qextMvvmProgressHandler.h
    include/model/utils/qextMvvmRealLimits.h
    include/model/utils/qextMvvmStringUtils.h
    include/model/utils/qextMvvmThreadSafeStack.h

    include/view/plotting/qextMvvmAxisTitleController.h
    include/view/plotting/qextMvvmColorMapCanvas.h
    include/view/plotting/qextMvvmColorMapInfoFormatter.h
    include/view/plotting/qextMvvmColorMapPlotController.h
    include/view/plotting/qextMvvmColorMapViewPortPlotController.h
    include/view/plotting/qextMvvmColorScalePlotController.h
    include/view/plotting/qextMvvmCustomPlotProxyWidget.h
    include/view/plotting/qextMvvmCustomPlotSceneAdapter.h
    include/view/plotting/qextMvvmCustomPlotUtils.h
    include/view/plotting/qextMvvmData1DPlotController.h
    include/view/plotting/qextMvvmData2DPlotController.h
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
    include/viewmodel/editors/qextMvvmScientificSpinBox.h
    include/viewmodel/editors/qextMvvmScientificSpinBoxEditor.h
    include/viewmodel/editors/qextMvvmSelectableComboBoxEditor.h
    include/viewmodel/editors/qextMvvmStyleUtils.h
    include/viewmodel/factories/qextMvvmViewModelControllerBuilder.h
    include/viewmodel/factories/qextMvvmViewModelControllerFactory.h
    include/viewmodel/factories/qextMvvmViewModelFactory.h
    include/viewmodel/interfaces/qextMvvmCellDecoratorInterface.h
    include/viewmodel/interfaces/qextMvvmChildrenStrategyInterface.h
    include/viewmodel/interfaces/qextMvvmEditorFactoryInterface.h
    include/viewmodel/interfaces/qextMvvmRowStrategyInterface.h
    include/viewmodel/viewmodel/qextMvvmDefaultCellDecorator.h
    include/viewmodel/viewmodel/qextMvvmDefaultViewModel.h
    include/viewmodel/viewmodel/qextMvvmLabelDataRowStrategy.h
    include/viewmodel/viewmodel/qextMvvmPropertiesRowStrategy.h
    include/viewmodel/viewmodel/qextMvvmPropertyFlatViewModel.h
    include/viewmodel/viewmodel/qextMvvmPropertyTableViewModel.h
    include/viewmodel/viewmodel/qextMvvmPropertyViewModel.h
    include/viewmodel/viewmodel/qextMvvmStandardChildrenStrategies.h
    include/viewmodel/viewmodel/qextMvvmStandardViewItems.h
    include/viewmodel/viewmodel/qextMvvmStandardViewModelControllers.h
    include/viewmodel/viewmodel/qextMvvmTopItemsViewModel.h
    include/viewmodel/viewmodel/qextMvvmViewItem.h
    include/viewmodel/viewmodel/qextMvvmViewModel.h
    include/viewmodel/viewmodel/qextMvvmViewModelBase.h
    include/viewmodel/viewmodel/qextMvvmViewModelController.h
    include/viewmodel/viewmodel/qextMvvmViewModelDelegate.h
    include/viewmodel/viewmodel/qextMvvmViewModelUtils.h

    include/qextMvvm.h
    include/qextMvvmPch.h
    include/qextMvvmGlobal.h
    )

set(qext_lib_private_headers
    )

set(qext_lib_sources
    source/model/commands/qextMvvmItemCommand.cpp
    source/model/commands/qextMvvmCommandAdapter.cpp
    source/model/commands/qextMvvmCommandService.cpp
    source/model/commands/qextMvvmCommandUtils.cpp
    source/model/commands/qextMvvmCopyItemCommand.cpp
    source/model/commands/qextMvvmInsertNewItemCommand.cpp
    source/model/commands/qextMvvmMoveItemCommand.cpp
    source/model/commands/qextMvvmRemoveItemCommand.cpp
    source/model/commands/qextMvvmSetValueCommand.cpp
    source/model/commands/qextMvvmUndoStack.cpp
    source/model/core/qextMvvmUniqueIdGenerator.cpp
    source/model/factories/qextMvvmItemCatalogueFactory.cpp
    source/model/factories/qextMvvmItemConverterFactory.cpp
    source/model/factories/qextMvvmModelConverterFactory.cpp
    source/model/factories/qextMvvmModelDocumentFactory.cpp
    source/model/factories/qextMvvmProjectManagerFactory.cpp
    source/model/model/qextMvvmComboProperty.cpp
    source/model/model/qextMvvmComparators.cpp
    source/model/model/qextMvvmCompoundItem.cpp
    source/model/model/qextMvvmCustomVariants.cpp
    source/model/model/qextMvvmDataRole.cpp
    source/model/model/qextMvvmExternalProperty.cpp
    source/model/model/qextMvvmGroupItem.cpp
    source/model/model/qextMvvmItemCatalogue.cpp
    source/model/model/qextMvvmItemFactory.cpp
    source/model/model/qextMvvmItemManager.cpp
    source/model/model/qextMvvmItemPool.cpp
    source/model/model/qextMvvmItemUtils.cpp
    source/model/model/qextMvvmModelUtils.cpp
    source/model/model/qextMvvmPath.cpp
    source/model/model/qextMvvmPropertyItem.cpp
    source/model/model/qextMvvmSessionItem.cpp
    source/model/model/qextMvvmSessionItemContainer.cpp
    source/model/model/qextMvvmSessionItemData.cpp
    source/model/model/qextMvvmSessionItemTags.cpp
    source/model/model/qextMvvmSessionModel.cpp
    source/model/model/qextMvvmTagInfo.cpp
    source/model/model/qextMvvmTagRow.cpp
    source/model/project/qextMvvmModelHasChangedController.cpp
    source/model/project/qextMvvmProject.cpp
    source/model/project/qextMvvmProjectChangeController.cpp
    source/model/project/qextMvvmProjectManager.cpp
    source/model/project/qextMvvmProjectManagerDecorator.cpp
    source/model/project/qextMvvmProjectUtils.cpp
    source/model/serialization/qextMvvmCompatibilityUtils.cpp
    source/model/serialization/qextMvvmJsonDocument.cpp
    source/model/serialization/qextMvvmJsonItemBackupStrategy.cpp
    source/model/serialization/qextMvvmJsonItemContainerConverter.cpp
    source/model/serialization/qextMvvmJsonItemConverter.cpp
    source/model/serialization/qextMvvmJsonItemCopyStrategy.cpp
    source/model/serialization/qextMvvmJsonItemDataConverter.cpp
    source/model/serialization/qextMvvmJsonItemFormatAssistant.cpp
    source/model/serialization/qextMvvmJsonItemTagsConverter.cpp
    source/model/serialization/qextMvvmJsonModelConverter.cpp
    source/model/serialization/qextMvvmJsonTagInfoConverter.cpp
    source/model/serialization/qextMvvmJsonUtils.cpp
    source/model/serialization/qextMvvmJsonVariantConverter.cpp
    source/model/signals/qextMvvmItemListenerBase.cpp
    source/model/signals/qextMvvmItemMapper.cpp
    source/model/signals/qextMvvmModelListenerBase.cpp
    source/model/signals/qextMvvmModelMapper.cpp
    source/model/standarditems/qextMvvmAxisItems.cpp
    source/model/standarditems/qextMvvmColorMapItem.cpp
    source/model/standarditems/qextMvvmColorMapViewPortItem.cpp
    source/model/standarditems/qextMvvmContainerItem.cpp
    source/model/standarditems/qextMvvmData1DItem.cpp
    source/model/standarditems/qextMvvmData2DItem.cpp
    source/model/standarditems/qextMvvmGraphItem.cpp
    source/model/standarditems/qextMvvmGraphViewPortItem.cpp
    source/model/standarditems/qextMvvmLinkedItem.cpp
    source/model/standarditems/qextMvvmPlotTableItems.cpp
    source/model/standarditems/qextMvvmVectorItem.cpp
    source/model/standarditems/qextMvvmViewPortItem.cpp
    source/model/utils/qextMvvmBinUtils.cpp
    source/model/utils/qextMvvmContainerUtils.cpp
    source/model/utils/qextMvvmFileUtils.cpp
    source/model/utils/qextMvvmNumericUtils.cpp
    source/model/utils/qextMvvmProgressHandler.cpp
    source/model/utils/qextMvvmRealLimits.cpp
    source/model/utils/qextMvvmStringUtils.cpp

    source/view/plotting/qextMvvmAxisTitleController.cpp
    source/view/plotting/qextMvvmColorMapCanvas.cpp
    source/view/plotting/qextMvvmColorMapInfoFormatter.cpp
    source/view/plotting/qextMvvmColorMapPlotController.cpp
    source/view/plotting/qextMvvmColorMapViewPortPlotController.cpp
    source/view/plotting/qextMvvmColorScalePlotController.cpp
    source/view/plotting/qextMvvmCustomPlotProxyWidget.cpp
    source/view/plotting/qextMvvmCustomPlotSceneAdapter.cpp
    source/view/plotting/qextMvvmCustomPlotUtils.cpp
    source/view/plotting/qextMvvmData1DPlotController.cpp
    source/view/plotting/qextMvvmData2DPlotController.cpp
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
    source/viewmodel/editors/qextMvvmScientificSpinBox.cpp
    source/viewmodel/editors/qextMvvmScientificSpinBoxEditor.cpp
    source/viewmodel/editors/qextMvvmSelectableComboBoxEditor.cpp
    source/viewmodel/editors/qextMvvmStyleUtils.cpp
    source/viewmodel/factories/qextMvvmViewModelControllerBuilder.cpp
    source/viewmodel/factories/qextMvvmViewModelFactory.cpp
    source/viewmodel/viewmodel/qextMvvmDefaultCellDecorator.cpp
    source/viewmodel/viewmodel/qextMvvmDefaultViewModel.cpp
    source/viewmodel/viewmodel/qextMvvmLabelDataRowStrategy.cpp
    source/viewmodel/viewmodel/qextMvvmPropertiesRowStrategy.cpp
    source/viewmodel/viewmodel/qextMvvmPropertyFlatViewModel.cpp
    source/viewmodel/viewmodel/qextMvvmPropertyTableViewModel.cpp
    source/viewmodel/viewmodel/qextMvvmPropertyViewModel.cpp
    source/viewmodel/viewmodel/qextMvvmStandardChildrenStrategies.cpp
    source/viewmodel/viewmodel/qextMvvmStandardViewItems.cpp
    source/viewmodel/viewmodel/qextMvvmStandardViewModelControllers.cpp
    source/viewmodel/viewmodel/qextMvvmTopItemsViewModel.cpp
    source/viewmodel/viewmodel/qextMvvmViewItem.cpp
    source/viewmodel/viewmodel/qextMvvmViewModel.cpp
    source/viewmodel/viewmodel/qextMvvmViewModelBase.cpp
    source/viewmodel/viewmodel/qextMvvmViewModelController.cpp
    source/viewmodel/viewmodel/qextMvvmViewModelDelegate.cpp
    source/viewmodel/viewmodel/qextMvvmViewModelUtils.cpp

    source/qextMvvm.cpp
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
    list(APPEND qext_lib_link_libraries Qt4::QtCore Qt4::QtGui)
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
if (QEXT_BUILD_USE_PCH)
    qextFunctionActivatePrecompiledHeaders(${qext_lib_base_name} PRIVATE include/qextMvvmPch.h)
endif()
target_link_libraries(${qext_lib_base_name} PUBLIC ${qext_lib_link_libraries})
target_include_directories(${qext_lib_base_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
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
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
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
