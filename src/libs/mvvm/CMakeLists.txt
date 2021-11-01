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
    include/model/core/qextMvvmFileSystem.h
    include/model/core/qextMvvmTypes.h
    include/model/core/qextMvvmUniqueIdGenerator.h
    include/model/core/qextMvvmVariant.h
    include/model/core/qextMvvmVersion.h
    include/model/factories/qextMvvmItemCatalogueFactory.h
    include/model/factories/qextMvvmItemConverterFactory.h
    include/model/factories/qextMvvmModeIDocumentFactory.h
    include/model/factories/qextMvvmModelConverterFactory.h
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
    include/model/model/qextMvvmConstants.h
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
    include/model/standarditems/qextMvvmData1dItem.h
    include/model/standarditems/qextMvvmData2dItem.h
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
    include/model/utils/qextMvvmUtilsFactory.h
    include/model/utils/qextMvvmMathConstants.h
    include/model/utils/qextMvvmNumericUtils.h
    include/model/utils/qextMvvmProgressHandler.h
    include/model/utils/qextMvvmRealLimits.h
    include/model/utils/qextMvvmStringUtils.h
    include/model/utils/qextMvvmThreadSafeStack.h

    include/view/plotting/axistitlecontroller.h
    include/view/plotting/colormapcanvas.h
    include/view/plotting/colormapinfoformatter.h
    include/view/plotting/colormapplotcontroller.h
    include/view/plotting/colormapviewportplotcontroller.h
    include/view/plotting/colorscaleplotcontroller.h
    include/view/plotting/customplotproxywidget.h
    include/view/plotting/customplotsceneadapter.h
    include/view/plotting/customplotutils.h
    include/view/plotting/data1dplotcontroller.h
    include/view/plotting/data2dplotcontroller.h
    include/view/plotting/graphcanvas.h
    include/view/plotting/graphinfoformatter.h
    include/view/plotting/graphplotcontroller.h
    include/view/plotting/graphviewportplotcontroller.h
    include/view/plotting/mousemovereporter.h
    include/view/plotting/mouseposinfo.h
    include/view/plotting/pencontroller.h
    include/view/plotting/sceneadapterinterface.h
    include/view/plotting/statusstringformatterinterface.h
    include/view/plotting/statusstringreporter.h
    include/view/plotting/statusstringreporterfactory.h
    include/view/plotting/viewportaxisplotcontroller.h
    include/view/widgets/adjustingscrollarea.h
    include/view/widgets/allitemstreeview.h
    include/view/widgets/collapsiblebar.h
    include/view/widgets/collapsiblelistwidget.h
    include/view/widgets/itemstreeview.h
    include/view/widgets/itemstreeviewinterface.h
    include/view/widgets/layoututils.h
    include/view/widgets/propertyflatview.h
    include/view/widgets/propertytreeview.h
    include/view/widgets/standardtreeviews.h
    include/view/widgets/statuslabel.h
    include/view/widgets/topitemstreeview.h
    include/view/widgets/widgetutils.h

    include/viewmodel/editors/booleditor.h
    include/viewmodel/editors/coloreditor.h
    include/viewmodel/editors/combopropertyeditor.h
    include/viewmodel/editors/customeditor.h
    include/viewmodel/editors/customeventfilters.h
    include/viewmodel/editors/defaulteditorfactory.h
    include/viewmodel/editors/doubleeditor.h
    include/viewmodel/editors/editor_constants.h
    include/viewmodel/editors/editorbuilders.h
    include/viewmodel/editors/externalpropertycomboeditor.h
    include/viewmodel/editors/externalpropertyeditor.h
    include/viewmodel/editors/integereditor.h
    include/viewmodel/editors/scientificdoubleeditor.h
    include/viewmodel/editors/scientificspinbox.h
    include/viewmodel/editors/scientificspinboxeditor.h
    include/viewmodel/editors/selectablecomboboxeditor.h
    include/viewmodel/editors/styleutils.h
    include/viewmodel/factories/viewmodelcontrollerbuilder.h
    include/viewmodel/factories/viewmodelcontrollerfactory.h
    include/viewmodel/factories/viewmodelfactory.h
    include/viewmodel/interfaces/celldecoratorinterface.h
    include/viewmodel/interfaces/childrenstrategyinterface.h
    include/viewmodel/interfaces/editorfactoryinterface.h
    include/viewmodel/interfaces/rowstrategyinterface.h
    include/viewmodel/viewmodel/defaultcelldecorator.h
    include/viewmodel/viewmodel/defaultviewmodel.h
    include/viewmodel/viewmodel/labeldatarowstrategy.h
    include/viewmodel/viewmodel/propertiesrowstrategy.h
    include/viewmodel/viewmodel/propertyflatviewmodel.h
    include/viewmodel/viewmodel/propertytableviewmodel.h
    include/viewmodel/viewmodel/propertyviewmodel.h
    include/viewmodel/viewmodel/standardchildrenstrategies.h
    include/viewmodel/viewmodel/standardviewitems.h
    include/viewmodel/viewmodel/standardviewmodelcontrollers.h
    include/viewmodel/viewmodel/topitemsviewmodel.h
    include/viewmodel/viewmodel/viewitem.h
    include/viewmodel/viewmodel/viewmodel.h
    include/viewmodel/viewmodel/viewmodelbase.h
    include/viewmodel/viewmodel/viewmodelcontroller.h
    include/viewmodel/viewmodel/viewmodeldelegate.h
    include/viewmodel/viewmodel/viewmodelutils.h

    include/qextMvvm.h
    include/qextMvvmGlobal.h
    )

set(qext_lib_private_headers
    )

set(qext_lib_sources
    source/model/commands/qextMvvmAbstractItemCommand.cpp
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
    source/model/standarditems/qextMvvmData1dItem.cpp
    source/model/standarditems/qextMvvmData2dItem.cpp
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

    source/view/plotting/axistitlecontroller.cpp
    source/view/plotting/colormapcanvas.cpp
    source/view/plotting/colormapinfoformatter.cpp
    source/view/plotting/colormapplotcontroller.cpp
    source/view/plotting/colormapviewportplotcontroller.cpp
    source/view/plotting/colorscaleplotcontroller.cpp
    source/view/plotting/customplotproxywidget.cpp
    source/view/plotting/customplotsceneadapter.cpp
    source/view/plotting/customplotutils.cpp
    source/view/plotting/data1dplotcontroller.cpp
    source/view/plotting/data2dplotcontroller.cpp
    source/view/plotting/graphcanvas.cpp
    source/view/plotting/graphinfoformatter.cpp
    source/view/plotting/graphplotcontroller.cpp
    source/view/plotting/graphviewportplotcontroller.cpp
    source/view/plotting/mousemovereporter.cpp
    source/view/plotting/pencontroller.cpp
    source/view/plotting/statusstringreporter.cpp
    source/view/plotting/statusstringreporterfactory.cpp
    source/view/plotting/viewportaxisplotcontroller.cpp
    source/view/widgets/adjustingscrollarea.cpp
    source/view/widgets/allitemstreeview.cpp
    source/view/widgets/collapsiblebar.cpp
    source/view/widgets/collapsiblelistwidget.cpp
    source/view/widgets/itemstreeview.cpp
    source/view/widgets/layoututils.cpp
    source/view/widgets/propertyflatview.cpp
    source/view/widgets/propertytreeview.cpp
    source/view/widgets/statuslabel.cpp
    source/view/widgets/topitemstreeview.cpp
    source/view/widgets/widgetutils.cpp

    source/viewmodel/editors/booleditor.cpp
    source/viewmodel/editors/coloreditor.cpp
    source/viewmodel/editors/combopropertyeditor.cpp
    source/viewmodel/editors/customeditor.cpp
    source/viewmodel/editors/customeventfilters.cpp
    source/viewmodel/editors/defaulteditorfactory.cpp
    source/viewmodel/editors/doubleeditor.cpp
    source/viewmodel/editors/editorbuilders.cpp
    source/viewmodel/editors/externalpropertycomboeditor.cpp
    source/viewmodel/editors/externalpropertyeditor.cpp
    source/viewmodel/editors/integereditor.cpp
    source/viewmodel/editors/scientificdoubleeditor.cpp
    source/viewmodel/editors/scientificspinbox.cpp
    source/viewmodel/editors/scientificspinboxeditor.cpp
    source/viewmodel/editors/selectablecomboboxeditor.cpp
    source/viewmodel/editors/styleutils.cpp
    source/viewmodel/factories/viewmodelcontrollerbuilder.cpp
    source/viewmodel/factories/viewmodelfactory.cpp
    source/viewmodel/viewmodel/defaultcelldecorator.cpp
    source/viewmodel/viewmodel/defaultviewmodel.cpp
    source/viewmodel/viewmodel/labeldatarowstrategy.cpp
    source/viewmodel/viewmodel/propertiesrowstrategy.cpp
    source/viewmodel/viewmodel/propertyflatviewmodel.cpp
    source/viewmodel/viewmodel/propertytableviewmodel.cpp
    source/viewmodel/viewmodel/propertyviewmodel.cpp
    source/viewmodel/viewmodel/standardchildrenstrategies.cpp
    source/viewmodel/viewmodel/standardviewitems.cpp
    source/viewmodel/viewmodel/standardviewmodelcontrollers.cpp
    source/viewmodel/viewmodel/topitemsviewmodel.cpp
    source/viewmodel/viewmodel/viewitem.cpp
    source/viewmodel/viewmodel/viewmodel.cpp
    source/viewmodel/viewmodel/viewmodelbase.cpp
    source/viewmodel/viewmodel/viewmodelcontroller.cpp
    source/viewmodel/viewmodel/viewmodeldelegate.cpp
    source/viewmodel/viewmodel/viewmodelutils.cpp

    source/qextMvvm.cpp
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
