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


#-----------------------------------------------------------------------------------------------------------------------
# Add lib link libraries
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_LIB_LINK_LIBRARIES)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QExt::Core)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_library(Mvvm
    EXCEPTIONS
    SOURCES
    source/model/commands/qextMvvmAbstractItemCommand.cpp
    source/model/commands/qextMvvmAbstractItemCommand.h
    source/model/commands/qextMvvmCommandAdapter.cpp
    source/model/commands/qextMvvmCommandAdapter.h
    source/model/commands/qextMvvmCommandResult.h
    source/model/commands/qextMvvmCommandService.cpp
    source/model/commands/qextMvvmCommandService.h
    source/model/commands/qextMvvmCommandUtils.cpp
    source/model/commands/qextMvvmCommandUtils.h
    source/model/commands/qextMvvmCommands.cpp
    source/model/commands/qextMvvmCommands.h
    # source/model/commands/insertnewitemcommand.cpp
    # source/model/commands/insertnewitemcommand.h
    # source/model/commands/moveitemcommand.cpp
    # source/model/commands/moveitemcommand.h
    # source/model/commands/removeitemcommand.cpp
    # source/model/commands/removeitemcommand.h
    # source/model/commands/setvaluecommand.cpp
    # source/model/commands/setvaluecommand.h
    source/model/commands/qextMvvmUndoStack.cpp
    source/model/commands/qextMvvmUndoStack.h
    source/model/core/filesystem.h
    source/model/core/types.h
    source/model/core/uniqueidgenerator.cpp
    source/model/core/uniqueidgenerator.h
    source/model/core/variant.h
    source/model/core/version.h
    source/model/factories/itemcataloguefactory.cpp
    source/model/factories/itemcataloguefactory.h
    source/model/factories/itemconverterfactory.cpp
    source/model/factories/itemconverterfactory.h
    source/model/factories/modelconverterfactory.cpp
    source/model/factories/modelconverterfactory.h
    source/model/factories/modeldocumentfactory.cpp
    source/model/factories/modeldocumentfactory.h
    source/model/factories/projectmanagerfactory.cpp
    source/model/factories/projectmanagerfactory.h
    source/model/interfaces/applicationmodelsinterface.h
    source/model/interfaces/itembackupstrategy.h
    source/model/interfaces/itemcopystrategy.h
    source/model/interfaces/itemfactoryinterface.h
    source/model/interfaces/itemlistenerinterface.h
    source/model/interfaces/modeldocumentinterface.h
    source/model/interfaces/modellistenerinterface.h
    source/model/interfaces/projectinterface.h
    source/model/interfaces/projectmanagerinterface.h
    source/model/interfaces/undostackinterface.h
    source/model/model/comboproperty.cpp
    source/model/model/comboproperty.h
    source/model/model/comparators.cpp
    source/model/model/comparators.h
    source/model/model/compounditem.cpp
    source/model/model/compounditem.h
    source/model/model/customvariants.cpp
    source/model/model/customvariants.h
    source/model/model/datarole.cpp
    source/model/model/datarole.h
    source/model/model/externalproperty.cpp
    source/model/model/externalproperty.h
    source/model/model/function_types.h
    source/model/model/groupitem.cpp
    source/model/model/groupitem.h
    source/model/model/itemcatalogue.cpp
    source/model/model/itemcatalogue.h
    source/model/model/itemfactory.cpp
    source/model/model/itemfactory.h
    source/model/model/itemmanager.cpp
    source/model/model/itemmanager.h
    source/model/model/itempool.cpp
    source/model/model/itempool.h
    source/model/model/itemutils.cpp
    source/model/model/itemutils.h
    source/model/model/modelutils.cpp
    source/model/model/modelutils.h
    source/model/model/mvvm_types.h
    source/model/model/path.cpp
    source/model/model/path.h
    source/model/model/propertyitem.cpp
    source/model/model/propertyitem.h
    source/model/model/sessionitem.cpp
    source/model/model/sessionitem.h
    source/model/model/sessionitemcontainer.cpp
    source/model/model/sessionitemcontainer.h
    source/model/model/sessionitemdata.cpp
    source/model/model/sessionitemdata.h
    source/model/model/sessionitemtags.cpp
    source/model/model/sessionitemtags.h
    source/model/model/sessionmodel.cpp
    source/model/model/sessionmodel.h
    source/model/model/taginfo.cpp
    source/model/model/taginfo.h
    source/model/model/tagrow.cpp
    source/model/model/tagrow.h
    source/model/model/variant_constants.h
    source/model/project/modelhaschangedcontroller.cpp
    source/model/project/modelhaschangedcontroller.h
    source/model/project/project.cpp
    source/model/project/project.h
    source/model/project/project_types.h
    source/model/project/projectchangecontroller.cpp
    source/model/project/projectchangecontroller.h
    source/model/project/projectmanager.cpp
    source/model/project/projectmanager.h
    source/model/project/projectmanagerdecorator.cpp
    source/model/project/projectmanagerdecorator.h
    source/model/project/projectutils.cpp
    source/model/project/projectutils.h
    source/model/serialization/compatibilityutils.cpp
    source/model/serialization/compatibilityutils.h
    source/model/serialization/jsonconverterinterfaces.h
    source/model/serialization/jsondocument.cpp
    source/model/serialization/jsondocument.h
    source/model/serialization/jsonitem_types.h
    source/model/serialization/jsonitembackupstrategy.cpp
    source/model/serialization/jsonitembackupstrategy.h
    source/model/serialization/jsonitemcontainerconverter.cpp
    source/model/serialization/jsonitemcontainerconverter.h
    source/model/serialization/jsonitemconverter.cpp
    source/model/serialization/jsonitemconverter.h
    source/model/serialization/jsonitemconverterinterface.h
    source/model/serialization/jsonitemcopystrategy.cpp
    source/model/serialization/jsonitemcopystrategy.h
    source/model/serialization/jsonitemdataconverter.cpp
    source/model/serialization/jsonitemdataconverter.h
    source/model/serialization/jsonitemdataconverterinterface.h
    source/model/serialization/jsonitemformatassistant.cpp
    source/model/serialization/jsonitemformatassistant.h
    source/model/serialization/jsonitemtagsconverter.cpp
    source/model/serialization/jsonitemtagsconverter.h
    source/model/serialization/jsonmodelconverter.cpp
    source/model/serialization/jsonmodelconverter.h
    source/model/serialization/jsonmodelconverterinterface.h
    source/model/serialization/jsontaginfoconverter.cpp
    source/model/serialization/jsontaginfoconverter.h
    source/model/serialization/jsontaginfoconverterinterface.h
    source/model/serialization/jsonutils.cpp
    source/model/serialization/jsonutils.h
    source/model/serialization/jsonvariantconverter.cpp
    source/model/serialization/jsonvariantconverter.h
    source/model/serialization/jsonvariantconverterinterface.h
    source/model/signals/callback_types.h
    source/model/signals/callbackcontainer.h
    source/model/signals/itemlistener.h
    source/model/signals/itemlistenerbase.cpp
    source/model/signals/itemlistenerbase.h
    source/model/signals/itemmapper.cpp
    source/model/signals/itemmapper.h
    source/model/signals/modellistener.h
    source/model/signals/modellistenerbase.cpp
    source/model/signals/modellistenerbase.h
    source/model/signals/modelmapper.cpp
    source/model/signals/modelmapper.h
    source/model/standarditems/axisitems.cpp
    source/model/standarditems/axisitems.h
    source/model/standarditems/colormapitem.cpp
    source/model/standarditems/colormapitem.h
    source/model/standarditems/colormapviewportitem.cpp
    source/model/standarditems/colormapviewportitem.h
    source/model/standarditems/containeritem.cpp
    source/model/standarditems/containeritem.h
    source/model/standarditems/data1ditem.cpp
    source/model/standarditems/data1ditem.h
    source/model/standarditems/data2ditem.cpp
    source/model/standarditems/data2ditem.h
    source/model/standarditems/graphitem.cpp
    source/model/standarditems/graphitem.h
    source/model/standarditems/graphviewportitem.cpp
    source/model/standarditems/graphviewportitem.h
    source/model/standarditems/linkeditem.cpp
    source/model/standarditems/linkeditem.h
    source/model/standarditems/plottableitems.cpp
    source/model/standarditems/plottableitems.h
    source/model/standarditems/standarditemincludes.h
    source/model/standarditems/vectoritem.cpp
    source/model/standarditems/vectoritem.h
    source/model/standarditems/viewportitem.cpp
    source/model/standarditems/viewportitem.h
    source/model/utils/binutils.cpp
    source/model/utils/binutils.h
    source/model/utils/containerutils.cpp
    source/model/utils/containerutils.h
    source/model/utils/fileutils.cpp
    source/model/utils/fileutils.h
    source/model/utils/ifactory.h
    source/model/utils/mathconstants.h
    source/model/utils/numericutils.cpp
    source/model/utils/numericutils.h
    source/model/utils/progresshandler.cpp
    source/model/utils/progresshandler.h
    source/model/utils/reallimits.cpp
    source/model/utils/reallimits.h
    source/model/utils/stringutils.cpp
    source/model/utils/stringutils.h
    source/model/utils/threadsafestack.h
    source/view/plotting/axistitlecontroller.cpp
    source/view/plotting/axistitlecontroller.h
    source/view/plotting/colormapcanvas.cpp
    source/view/plotting/colormapcanvas.h
    source/view/plotting/colormapinfoformatter.cpp
    source/view/plotting/colormapinfoformatter.h
    source/view/plotting/colormapplotcontroller.cpp
    source/view/plotting/colormapplotcontroller.h
    source/view/plotting/colormapviewportplotcontroller.cpp
    source/view/plotting/colormapviewportplotcontroller.h
    source/view/plotting/colorscaleplotcontroller.cpp
    source/view/plotting/colorscaleplotcontroller.h
    source/view/plotting/customplotproxywidget.cpp
    source/view/plotting/customplotproxywidget.h
    source/view/plotting/customplotsceneadapter.cpp
    source/view/plotting/customplotsceneadapter.h
    source/view/plotting/customplotutils.cpp
    source/view/plotting/customplotutils.h
    source/view/plotting/data1dplotcontroller.cpp
    source/view/plotting/data1dplotcontroller.h
    source/view/plotting/data2dplotcontroller.cpp
    source/view/plotting/data2dplotcontroller.h
    source/view/plotting/graphcanvas.cpp
    source/view/plotting/graphcanvas.h
    source/view/plotting/graphinfoformatter.cpp
    source/view/plotting/graphinfoformatter.h
    source/view/plotting/graphplotcontroller.cpp
    source/view/plotting/graphplotcontroller.h
    source/view/plotting/graphviewportplotcontroller.cpp
    source/view/plotting/graphviewportplotcontroller.h
    source/view/plotting/mousemovereporter.cpp
    source/view/plotting/mousemovereporter.h
    source/view/plotting/mouseposinfo.h
    source/view/plotting/pencontroller.cpp
    source/view/plotting/pencontroller.h
    source/view/plotting/sceneadapterinterface.h
    source/view/plotting/statusstringformatterinterface.h
    source/view/plotting/statusstringreporter.cpp
    source/view/plotting/statusstringreporter.h
    source/view/plotting/statusstringreporterfactory.cpp
    source/view/plotting/statusstringreporterfactory.h
    source/view/plotting/viewportaxisplotcontroller.cpp
    source/view/plotting/viewportaxisplotcontroller.h
    source/view/widgets/adjustingscrollarea.cpp
    source/view/widgets/adjustingscrollarea.h
    source/view/widgets/allitemstreeview.cpp
    source/view/widgets/allitemstreeview.h
    source/view/widgets/collapsiblebar.cpp
    source/view/widgets/collapsiblebar.h
    source/view/widgets/collapsiblelistwidget.cpp
    source/view/widgets/collapsiblelistwidget.h
    source/view/widgets/itemstreeview.cpp
    source/view/widgets/itemstreeview.h
    source/view/widgets/itemstreeviewinterface.h
    source/view/widgets/layoututils.cpp
    source/view/widgets/layoututils.h
    source/view/widgets/propertyflatview.cpp
    source/view/widgets/propertyflatview.h
    source/view/widgets/propertytreeview.cpp
    source/view/widgets/propertytreeview.h
    source/view/widgets/standardtreeviews.h
    source/view/widgets/statuslabel.cpp
    source/view/widgets/statuslabel.h
    source/view/widgets/topitemstreeview.cpp
    source/view/widgets/topitemstreeview.h
    source/view/widgets/widgetutils.cpp
    source/view/widgets/widgetutils.h
    source/viewmodel/editors/booleditor.cpp
    source/viewmodel/editors/booleditor.h
    source/viewmodel/editors/coloreditor.cpp
    source/viewmodel/editors/coloreditor.h
    source/viewmodel/editors/combopropertyeditor.cpp
    source/viewmodel/editors/combopropertyeditor.h
    source/viewmodel/editors/customeditor.cpp
    source/viewmodel/editors/customeditor.h
    source/viewmodel/editors/customeventfilters.cpp
    source/viewmodel/editors/customeventfilters.h
    source/viewmodel/editors/defaulteditorfactory.cpp
    source/viewmodel/editors/defaulteditorfactory.h
    source/viewmodel/editors/doubleeditor.cpp
    source/viewmodel/editors/doubleeditor.h
    source/viewmodel/editors/editor_constants.h
    source/viewmodel/editors/editorbuilders.cpp
    source/viewmodel/editors/editorbuilders.h
    source/viewmodel/editors/externalpropertycomboeditor.cpp
    source/viewmodel/editors/externalpropertycomboeditor.h
    source/viewmodel/editors/externalpropertyeditor.cpp
    source/viewmodel/editors/externalpropertyeditor.h
    source/viewmodel/editors/integereditor.cpp
    source/viewmodel/editors/integereditor.h
    source/viewmodel/editors/scientificdoubleeditor.cpp
    source/viewmodel/editors/scientificdoubleeditor.h
    source/viewmodel/editors/scientificspinbox.cpp
    source/viewmodel/editors/scientificspinbox.h
    source/viewmodel/editors/scientificspinboxeditor.cpp
    source/viewmodel/editors/scientificspinboxeditor.h
    source/viewmodel/editors/selectablecomboboxeditor.cpp
    source/viewmodel/editors/selectablecomboboxeditor.h
    source/viewmodel/editors/styleutils.cpp
    source/viewmodel/editors/styleutils.h
    source/viewmodel/factories/viewmodelcontrollerbuilder.cpp
    source/viewmodel/factories/viewmodelcontrollerbuilder.h
    source/viewmodel/factories/viewmodelcontrollerfactory.h
    source/viewmodel/factories/viewmodelfactory.cpp
    source/viewmodel/factories/viewmodelfactory.h
    source/viewmodel/interfaces/celldecoratorinterface.h
    source/viewmodel/interfaces/childrenstrategyinterface.h
    source/viewmodel/interfaces/editorfactoryinterface.h
    source/viewmodel/interfaces/rowstrategyinterface.h
    source/viewmodel/viewmodel/defaultcelldecorator.cpp
    source/viewmodel/viewmodel/defaultcelldecorator.h
    source/viewmodel/viewmodel/defaultviewmodel.cpp
    source/viewmodel/viewmodel/defaultviewmodel.h
    source/viewmodel/viewmodel/labeldatarowstrategy.cpp
    source/viewmodel/viewmodel/labeldatarowstrategy.h
    source/viewmodel/viewmodel/propertiesrowstrategy.cpp
    source/viewmodel/viewmodel/propertiesrowstrategy.h
    source/viewmodel/viewmodel/propertyflatviewmodel.cpp
    source/viewmodel/viewmodel/propertyflatviewmodel.h
    source/viewmodel/viewmodel/propertytableviewmodel.cpp
    source/viewmodel/viewmodel/propertytableviewmodel.h
    source/viewmodel/viewmodel/propertyviewmodel.cpp
    source/viewmodel/viewmodel/propertyviewmodel.h
    source/viewmodel/viewmodel/standardchildrenstrategies.cpp
    source/viewmodel/viewmodel/standardchildrenstrategies.h
    source/viewmodel/viewmodel/standardviewitems.cpp
    source/viewmodel/viewmodel/standardviewitems.h
    source/viewmodel/viewmodel/standardviewmodelcontrollers.cpp
    source/viewmodel/viewmodel/standardviewmodelcontrollers.h
    source/viewmodel/viewmodel/topitemsviewmodel.cpp
    source/viewmodel/viewmodel/topitemsviewmodel.h
    source/viewmodel/viewmodel/viewitem.cpp
    source/viewmodel/viewmodel/viewitem.h
    source/viewmodel/viewmodel/viewmodel.cpp
    source/viewmodel/viewmodel/viewmodel.h
    source/viewmodel/viewmodel/viewmodelbase.cpp
    source/viewmodel/viewmodel/viewmodelbase.h
    source/viewmodel/viewmodel/viewmodelcontroller.cpp
    source/viewmodel/viewmodel/viewmodelcontroller.h
    source/viewmodel/viewmodel/viewmodeldelegate.cpp
    source/viewmodel/viewmodel/viewmodeldelegate.h
    source/viewmodel/viewmodel/viewmodelutils.cpp
    source/viewmodel/viewmodel/viewmodelutils.h
    source/qextMvvmGlobal.h
    resource/qextMvvm.qrc
    PRECOMPILED_HEADER
    source/qextMvvmPch.h
    INCLUDE_DIRECTORIES
    "${CMAKE_CURRENT_SOURCE_DIR}/source"
    LIBRARIES
    qcustomplot
    PUBLIC_LIBRARIES
    ${QEXT_LIB_LINK_LIBRARIES})


#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
qext_add_subdirectory(tests QEXT_BUILD_TESTS)
