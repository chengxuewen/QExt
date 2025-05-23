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
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui Qt4::QtXml)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Xml
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::WidgetsPrivate
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QExt::Core)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_library(Designer
    EXCEPTIONS
    SOURCES
    libs/deviceskin/skins/ClamshellPhone.qrc
    libs/deviceskin/skins/PortableMedia.qrc
    libs/deviceskin/skins/S60-nHD-Touchscreen.qrc
    libs/deviceskin/skins/S60-QVGA-Candybar.qrc
    libs/deviceskin/skins/SmartPhone.qrc
    libs/deviceskin/skins/SmartPhone2.qrc
    libs/deviceskin/skins/SmartPhoneWithButtons.qrc
    libs/deviceskin/skins/TouchscreenPhone.qrc
    libs/deviceskin/deviceskin.cpp
    libs/deviceskin/deviceskin.h
    libs/findwidget/abstractfindwidget.cpp
    libs/findwidget/abstractfindwidget.h
    libs/findwidget/findwidget.qrc
    libs/findwidget/itemviewfindwidget.cpp
    libs/findwidget/itemviewfindwidget.h
    libs/findwidget/texteditfindwidget.cpp
    libs/findwidget/texteditfindwidget.h
    libs/fontpanel/fontpanel.cpp
    libs/fontpanel/fontpanel.h
    libs/qtgradienteditor/qtcolorbutton.cpp
    libs/qtgradienteditor/qtcolorbutton.h
    libs/qtgradienteditor/qtcolorline.cpp
    libs/qtgradienteditor/qtcolorline.h
    libs/qtgradienteditor/qtgradientdialog.cpp
    libs/qtgradienteditor/qtgradientdialog.h
    libs/qtgradienteditor/qtgradientdialog.ui
    libs/qtgradienteditor/qtgradienteditor.cpp
    libs/qtgradienteditor/qtgradienteditor.h
    libs/qtgradienteditor/qtgradienteditor.qrc
    libs/qtgradienteditor/qtgradienteditor.ui
    libs/qtgradienteditor/qtgradientmanager.cpp
    libs/qtgradienteditor/qtgradientmanager.h
    libs/qtgradienteditor/qtgradientstopscontroller.cpp
    libs/qtgradienteditor/qtgradientstopscontroller.h
    libs/qtgradienteditor/qtgradientstopsmodel.cpp
    libs/qtgradienteditor/qtgradientstopsmodel.h
    libs/qtgradienteditor/qtgradientstopswidget.cpp
    libs/qtgradienteditor/qtgradientstopswidget.h
    libs/qtgradienteditor/qtgradientutils.cpp
    libs/qtgradienteditor/qtgradientutils.h
    libs/qtgradienteditor/qtgradientview.cpp
    libs/qtgradienteditor/qtgradientview.h
    libs/qtgradienteditor/qtgradientview.ui
    libs/qtgradienteditor/qtgradientviewdialog.cpp
    libs/qtgradienteditor/qtgradientviewdialog.h
    libs/qtgradienteditor/qtgradientviewdialog.ui
    libs/qtgradienteditor/qtgradientwidget.cpp
    libs/qtgradienteditor/qtgradientwidget.h
    libs/qtpropertybrowser/qtbuttonpropertybrowser.cpp
    libs/qtpropertybrowser/qtbuttonpropertybrowser.h
    libs/qtpropertybrowser/qteditorfactory.cpp
    libs/qtpropertybrowser/qteditorfactory.h
    libs/qtpropertybrowser/qtgroupboxpropertybrowser.cpp
    libs/qtpropertybrowser/qtgroupboxpropertybrowser.h
    libs/qtpropertybrowser/qtpropertybrowser.cpp
    libs/qtpropertybrowser/qtpropertybrowser.h
    libs/qtpropertybrowser/qtpropertybrowser.qrc
    libs/qtpropertybrowser/qtpropertybrowserutils.cpp
    libs/qtpropertybrowser/qtpropertybrowserutils_p.h
    libs/qtpropertybrowser/qtpropertymanager.cpp
    libs/qtpropertybrowser/qtpropertymanager.h
    libs/qtpropertybrowser/qttreepropertybrowser.cpp
    libs/qtpropertybrowser/qttreepropertybrowser.h
    libs/qtpropertybrowser/qtvariantproperty.cpp
    libs/qtpropertybrowser/qtvariantproperty.h
    libs/qttoolbardialog/qttoolbardialog.cpp
    libs/qttoolbardialog/qttoolbardialog.h
    libs/qttoolbardialog/qttoolbardialog.qrc
    libs/qttoolbardialog/qttoolbardialog.ui
    libs/uiplugin/customwidget.h
    libs/uiplugin/qdesignerexportwidget.h
    # ../uitools/quiloader.cpp
    # ../uitools/quiloader.h
    # ../uitools/quiloader_p.h
    # ../winutils/elfreader.cpp
    # ../winutils/elfreader.h
    # ../winutils/qmlutils.cpp
    # ../winutils/qmlutils.h
    # ../winutils/utils.cpp
    # ../winutils/utils.h
    libs/designer/components/buddyeditor/buddyeditor.cpp
    libs/designer/components/buddyeditor/buddyeditor.h
    libs/designer/components/buddyeditor/buddyeditor.json
    libs/designer/components/buddyeditor/buddyeditor_global.h
    # components/buddyeditor/buddyeditor_plugin.cpp
    # components/buddyeditor/buddyeditor_plugin.h
    libs/designer/components/buddyeditor/buddyeditor_tool.cpp
    libs/designer/components/buddyeditor/buddyeditor_tool.h
    libs/designer/components/formeditor/default_actionprovider.cpp
    libs/designer/components/formeditor/default_actionprovider.h
    libs/designer/components/formeditor/default_container.cpp
    libs/designer/components/formeditor/default_container.h
    libs/designer/components/formeditor/default_layoutdecoration.cpp
    libs/designer/components/formeditor/default_layoutdecoration.h
    libs/designer/components/formeditor/defaultbrushes.xml
    libs/designer/components/formeditor/deviceprofiledialog.cpp
    libs/designer/components/formeditor/deviceprofiledialog.h
    libs/designer/components/formeditor/deviceprofiledialog.ui
    libs/designer/components/formeditor/dpi_chooser.cpp
    libs/designer/components/formeditor/dpi_chooser.h
    libs/designer/components/formeditor/embeddedoptionspage.cpp
    libs/designer/components/formeditor/embeddedoptionspage.h
    libs/designer/components/formeditor/formeditor.cpp
    libs/designer/components/formeditor/formeditor.h
    libs/designer/components/formeditor/formeditor.qrc
    libs/designer/components/formeditor/formeditor_global.h
    libs/designer/components/formeditor/formeditor_optionspage.cpp
    libs/designer/components/formeditor/formeditor_optionspage.h
    libs/designer/components/formeditor/formwindow.cpp
    libs/designer/components/formeditor/formwindow.h
    libs/designer/components/formeditor/formwindow_dnditem.cpp
    libs/designer/components/formeditor/formwindow_dnditem.h
    libs/designer/components/formeditor/formwindow_widgetstack.cpp
    libs/designer/components/formeditor/formwindow_widgetstack.h
    libs/designer/components/formeditor/formwindowcursor.cpp
    libs/designer/components/formeditor/formwindowcursor.h
    libs/designer/components/formeditor/formwindowmanager.cpp
    libs/designer/components/formeditor/formwindowmanager.h
    libs/designer/components/formeditor/formwindowsettings.cpp
    libs/designer/components/formeditor/formwindowsettings.h
    libs/designer/components/formeditor/formwindowsettings.ui
    libs/designer/components/formeditor/itemview_propertysheet.cpp
    libs/designer/components/formeditor/itemview_propertysheet.h
    libs/designer/components/formeditor/layout_propertysheet.cpp
    libs/designer/components/formeditor/layout_propertysheet.h
    libs/designer/components/formeditor/line_propertysheet.cpp
    libs/designer/components/formeditor/line_propertysheet.h
    libs/designer/components/formeditor/previewactiongroup.cpp
    libs/designer/components/formeditor/previewactiongroup.h
    libs/designer/components/formeditor/qdesigner_resource.cpp
    libs/designer/components/formeditor/qdesigner_resource.h
    libs/designer/components/formeditor/qlayoutwidget_propertysheet.cpp
    libs/designer/components/formeditor/qlayoutwidget_propertysheet.h
    libs/designer/components/formeditor/qmainwindow_container.cpp
    libs/designer/components/formeditor/qmainwindow_container.h
    libs/designer/components/formeditor/qmdiarea_container.cpp
    libs/designer/components/formeditor/qmdiarea_container.h
    libs/designer/components/formeditor/qwizard_container.cpp
    libs/designer/components/formeditor/qwizard_container.h
    libs/designer/components/formeditor/spacer_propertysheet.cpp
    libs/designer/components/formeditor/spacer_propertysheet.h
    libs/designer/components/formeditor/templateoptionspage.cpp
    libs/designer/components/formeditor/templateoptionspage.h
    libs/designer/components/formeditor/templateoptionspage.ui
    libs/designer/components/formeditor/tool_widgeteditor.cpp
    libs/designer/components/formeditor/tool_widgeteditor.h
    libs/designer/components/formeditor/widgetselection.cpp
    libs/designer/components/formeditor/widgetselection.h
    libs/designer/components/objectinspector/objectinspector.cpp
    libs/designer/components/objectinspector/objectinspector.h
    libs/designer/components/objectinspector/objectinspector_global.h
    libs/designer/components/objectinspector/objectinspectormodel.cpp
    libs/designer/components/objectinspector/objectinspectormodel_p.h
    libs/designer/components/propertyeditor/brushpropertymanager.cpp
    libs/designer/components/propertyeditor/brushpropertymanager.h
    libs/designer/components/propertyeditor/designerpropertymanager.cpp
    libs/designer/components/propertyeditor/designerpropertymanager.h
    libs/designer/components/propertyeditor/fontmapping.xml
    libs/designer/components/propertyeditor/fontpropertymanager.cpp
    libs/designer/components/propertyeditor/fontpropertymanager.h
    libs/designer/components/propertyeditor/newdynamicpropertydialog.cpp
    libs/designer/components/propertyeditor/newdynamicpropertydialog.h
    libs/designer/components/propertyeditor/newdynamicpropertydialog.ui
    libs/designer/components/propertyeditor/paletteeditor.cpp
    libs/designer/components/propertyeditor/paletteeditor.h
    libs/designer/components/propertyeditor/paletteeditor.ui
    libs/designer/components/propertyeditor/paletteeditorbutton.cpp
    libs/designer/components/propertyeditor/paletteeditorbutton.h
    libs/designer/components/propertyeditor/previewframe.cpp
    libs/designer/components/propertyeditor/previewframe.h
    libs/designer/components/propertyeditor/previewwidget.cpp
    libs/designer/components/propertyeditor/previewwidget.h
    libs/designer/components/propertyeditor/previewwidget.ui
    libs/designer/components/propertyeditor/propertyeditor.cpp
    libs/designer/components/propertyeditor/propertyeditor.h
    libs/designer/components/propertyeditor/propertyeditor.qrc
    libs/designer/components/propertyeditor/propertyeditor_global.h
    libs/designer/components/propertyeditor/qlonglongvalidator.cpp
    libs/designer/components/propertyeditor/qlonglongvalidator.h
    libs/designer/components/propertyeditor/stringlisteditor.cpp
    libs/designer/components/propertyeditor/stringlisteditor.h
    libs/designer/components/propertyeditor/stringlisteditor.ui
    libs/designer/components/propertyeditor/stringlisteditorbutton.cpp
    libs/designer/components/propertyeditor/stringlisteditorbutton.h
    libs/designer/components/signalsloteditor/connectdialog.cpp
    libs/designer/components/signalsloteditor/connectdialog.ui
    libs/designer/components/signalsloteditor/connectdialog_p.h
    libs/designer/components/signalsloteditor/signalslot_utils.cpp
    libs/designer/components/signalsloteditor/signalslot_utils_p.h
    libs/designer/components/signalsloteditor/signalsloteditor.cpp
    libs/designer/components/signalsloteditor/signalsloteditor.h
    libs/designer/components/signalsloteditor/signalsloteditor.json
    libs/designer/components/signalsloteditor/signalsloteditor_global.h
    libs/designer/components/signalsloteditor/signalsloteditor_p.h
    # components/signalsloteditor/signalsloteditor_plugin.cpp
    # components/signalsloteditor/signalsloteditor_plugin.h
    libs/designer/components/signalsloteditor/signalsloteditor_tool.cpp
    libs/designer/components/signalsloteditor/signalsloteditor_tool.h
    libs/designer/components/signalsloteditor/signalsloteditorwindow.cpp
    libs/designer/components/signalsloteditor/signalsloteditorwindow.h
    libs/designer/components/tabordereditor/tabordereditor.cpp
    libs/designer/components/tabordereditor/tabordereditor.h
    libs/designer/components/tabordereditor/tabordereditor.json
    libs/designer/components/tabordereditor/tabordereditor_global.h
    # components/tabordereditor/tabordereditor_plugin.cpp
    # components/tabordereditor/tabordereditor_plugin.h
    libs/designer/components/tabordereditor/tabordereditor_tool.cpp
    libs/designer/components/tabordereditor/tabordereditor_tool.h
    libs/designer/components/taskmenu/button_taskmenu.cpp
    libs/designer/components/taskmenu/button_taskmenu.h
    libs/designer/components/taskmenu/combobox_taskmenu.cpp
    libs/designer/components/taskmenu/combobox_taskmenu.h
    libs/designer/components/taskmenu/containerwidget_taskmenu.cpp
    libs/designer/components/taskmenu/containerwidget_taskmenu.h
    libs/designer/components/taskmenu/groupbox_taskmenu.cpp
    libs/designer/components/taskmenu/groupbox_taskmenu.h
    libs/designer/components/taskmenu/inplace_editor.cpp
    libs/designer/components/taskmenu/inplace_editor.h
    libs/designer/components/taskmenu/inplace_widget_helper.cpp
    libs/designer/components/taskmenu/inplace_widget_helper.h
    libs/designer/components/taskmenu/itemlisteditor.cpp
    libs/designer/components/taskmenu/itemlisteditor.h
    libs/designer/components/taskmenu/itemlisteditor.ui
    libs/designer/components/taskmenu/label_taskmenu.cpp
    libs/designer/components/taskmenu/label_taskmenu.h
    libs/designer/components/taskmenu/layouttaskmenu.cpp
    libs/designer/components/taskmenu/layouttaskmenu.h
    libs/designer/components/taskmenu/lineedit_taskmenu.cpp
    libs/designer/components/taskmenu/lineedit_taskmenu.h
    libs/designer/components/taskmenu/listwidget_taskmenu.cpp
    libs/designer/components/taskmenu/listwidget_taskmenu.h
    libs/designer/components/taskmenu/listwidgeteditor.cpp
    libs/designer/components/taskmenu/listwidgeteditor.h
    libs/designer/components/taskmenu/menutaskmenu.cpp
    libs/designer/components/taskmenu/menutaskmenu.h
    libs/designer/components/taskmenu/tablewidget_taskmenu.cpp
    libs/designer/components/taskmenu/tablewidget_taskmenu.h
    libs/designer/components/taskmenu/tablewidgeteditor.cpp
    libs/designer/components/taskmenu/tablewidgeteditor.h
    libs/designer/components/taskmenu/tablewidgeteditor.ui
    libs/designer/components/taskmenu/taskmenu_component.cpp
    libs/designer/components/taskmenu/taskmenu_component.h
    libs/designer/components/taskmenu/taskmenu_global.h
    libs/designer/components/taskmenu/textedit_taskmenu.cpp
    libs/designer/components/taskmenu/textedit_taskmenu.h
    libs/designer/components/taskmenu/toolbar_taskmenu.cpp
    libs/designer/components/taskmenu/toolbar_taskmenu.h
    libs/designer/components/taskmenu/treewidget_taskmenu.cpp
    libs/designer/components/taskmenu/treewidget_taskmenu.h
    libs/designer/components/taskmenu/treewidgeteditor.cpp
    libs/designer/components/taskmenu/treewidgeteditor.h
    libs/designer/components/taskmenu/treewidgeteditor.ui
    libs/designer/components/widgetbox/widgetbox.cpp
    libs/designer/components/widgetbox/widgetbox.h
    libs/designer/components/widgetbox/widgetbox.qrc
    libs/designer/components/widgetbox/widgetbox.xml
    libs/designer/components/widgetbox/widgetbox_dnditem.cpp
    libs/designer/components/widgetbox/widgetbox_dnditem.h
    libs/designer/components/widgetbox/widgetbox_global.h
    libs/designer/components/widgetbox/widgetboxcategorylistview.cpp
    libs/designer/components/widgetbox/widgetboxcategorylistview.h
    libs/designer/components/widgetbox/widgetboxtreewidget.cpp
    libs/designer/components/widgetbox/widgetboxtreewidget.h
    libs/designer/components/qdesigner_components.cpp
    libs/designer/components/qdesigner_components.h
    libs/designer/components/qdesigner_components_global.h
    # libs/designer/extension/default_extensionfactory.cpp
    # libs/designer/extension/default_extensionfactory.h
    # libs/designer/extension/extension.cpp
    # libs/designer/extension/extension.h
    # libs/designer/extension/extension_global.h
    # libs/designer/extension/qextensionmanager.cpp
    # libs/designer/extension/qextensionmanager.h
    # libs/designer/sdk/abstractactioneditor.cpp
    # libs/designer/sdk/abstractactioneditor.h
    # libs/designer/sdk/abstractdialoggui.cpp
    # libs/designer/sdk/abstractdialoggui_p.h
    # libs/designer/sdk/abstractdnditem.h
    # libs/designer/sdk/abstractformeditor.cpp
    # libs/designer/sdk/abstractformeditor.h
    # libs/designer/sdk/abstractformeditorplugin.cpp
    # libs/designer/sdk/abstractformeditorplugin.h
    # libs/designer/sdk/abstractformwindow.cpp
    # libs/designer/sdk/abstractformwindow.h
    # libs/designer/sdk/abstractformwindowcursor.cpp
    # libs/designer/sdk/abstractformwindowcursor.h
    # libs/designer/sdk/abstractformwindowmanager.cpp
    # libs/designer/sdk/abstractformwindowmanager.h
    # libs/designer/sdk/abstractformwindowtool.cpp
    # libs/designer/sdk/abstractformwindowtool.h
    # libs/designer/sdk/abstractintegration.cpp
    # libs/designer/sdk/abstractintegration.h
    # libs/designer/sdk/abstractintrospection.cpp
    # libs/designer/sdk/abstractintrospection_p.h
    # libs/designer/sdk/abstractlanguage.h
    # libs/designer/sdk/abstractmetadatabase.cpp
    # libs/designer/sdk/abstractmetadatabase.h
    # libs/designer/sdk/abstractnewformwidget.cpp
    # libs/designer/sdk/abstractnewformwidget.h
    # libs/designer/sdk/abstractobjectinspector.cpp
    # libs/designer/sdk/abstractobjectinspector.h
    # libs/designer/sdk/abstractoptionspage.h
    # libs/designer/sdk/abstractpromotioninterface.cpp
    # libs/designer/sdk/abstractpromotioninterface.h
    # libs/designer/sdk/abstractpropertyeditor.cpp
    # libs/designer/sdk/abstractpropertyeditor.h
    # libs/designer/sdk/abstractresourcebrowser.cpp
    # libs/designer/sdk/abstractresourcebrowser.h
    # libs/designer/sdk/abstractsettings.h
    # libs/designer/sdk/abstractwidgetbox.cpp
    # libs/designer/sdk/abstractwidgetbox.h
    # libs/designer/sdk/abstractwidgetdatabase.cpp
    # libs/designer/sdk/abstractwidgetdatabase.h
    # libs/designer/sdk/abstractwidgetfactory.cpp
    # libs/designer/sdk/abstractwidgetfactory.h
    # libs/designer/sdk/container.h
    # libs/designer/sdk/dynamicpropertysheet.h
    # libs/designer/sdk/extrainfo.cpp
    # libs/designer/sdk/extrainfo.h
    # libs/designer/sdk/layoutdecoration.h
    # libs/designer/sdk/membersheet.h
    # libs/designer/sdk/propertysheet.h
    # libs/designer/sdk/sdk_global.h
    # libs/designer/sdk/taskmenu.h
    libs/designer/shared/templates/forms/240x320/Dialog_with_Buttons_Bottom.ui
    libs/designer/shared/templates/forms/240x320/Dialog_with_Buttons_Right.ui
    libs/designer/shared/templates/forms/320x240/Dialog_with_Buttons_Bottom.ui
    libs/designer/shared/templates/forms/320x240/Dialog_with_Buttons_Right.ui
    libs/designer/shared/templates/forms/480x640/Dialog_with_Buttons_Bottom.ui
    libs/designer/shared/templates/forms/480x640/Dialog_with_Buttons_Right.ui
    libs/designer/shared/templates/forms/640x480/Dialog_with_Buttons_Bottom.ui
    libs/designer/shared/templates/forms/640x480/Dialog_with_Buttons_Right.ui
    libs/designer/shared/templates/forms/Dialog_with_Buttons_Bottom.ui
    libs/designer/shared/templates/forms/Dialog_with_Buttons_Right.ui
    libs/designer/shared/templates/forms/Dialog_without_Buttons.ui
    libs/designer/shared/templates/forms/Main_Window.ui
    libs/designer/shared/templates/forms/Widget.ui
    libs/designer/shared/actioneditor.cpp
    libs/designer/shared/actioneditor_p.h
    libs/designer/shared/actionprovider_p.h
    libs/designer/shared/actionrepository.cpp
    libs/designer/shared/actionrepository_p.h
    libs/designer/shared/addlinkdialog.ui
    libs/designer/shared/codedialog.cpp
    libs/designer/shared/codedialog_p.h
    libs/designer/shared/connectionedit.cpp
    libs/designer/shared/connectionedit_p.h
    libs/designer/shared/csshighlighter.cpp
    libs/designer/shared/csshighlighter_p.h
    libs/designer/shared/deviceprofile.cpp
    libs/designer/shared/deviceprofile_p.h
    libs/designer/shared/dialoggui.cpp
    libs/designer/shared/dialoggui_p.h
    libs/designer/shared/extensionfactory_p.h
    libs/designer/shared/formlayoutmenu.cpp
    libs/designer/shared/formlayoutmenu_p.h
    libs/designer/shared/formlayoutrowdialog.ui
    libs/designer/shared/formwindowbase.cpp
    libs/designer/shared/formwindowbase_p.h
    libs/designer/shared/grid.cpp
    libs/designer/shared/grid_p.h
    libs/designer/shared/gridpanel.cpp
    libs/designer/shared/gridpanel.ui
    libs/designer/shared/gridpanel_p.h
    libs/designer/shared/htmlhighlighter.cpp
    libs/designer/shared/htmlhighlighter_p.h
    libs/designer/shared/iconloader.cpp
    libs/designer/shared/iconloader_p.h
    libs/designer/shared/iconselector.cpp
    libs/designer/shared/iconselector_p.h
    libs/designer/shared/invisible_widget.cpp
    libs/designer/shared/invisible_widget_p.h
    libs/designer/shared/layout.cpp
    libs/designer/shared/layout_p.h
    libs/designer/shared/layoutinfo.cpp
    libs/designer/shared/layoutinfo_p.h
    libs/designer/shared/metadatabase.cpp
    libs/designer/shared/metadatabase_p.h
    libs/designer/shared/morphmenu.cpp
    libs/designer/shared/morphmenu_p.h
    libs/designer/shared/newactiondialog.cpp
    libs/designer/shared/newactiondialog.ui
    libs/designer/shared/newactiondialog_p.h
    libs/designer/shared/newformwidget.cpp
    libs/designer/shared/newformwidget.ui
    libs/designer/shared/newformwidget_p.h
    libs/designer/shared/orderdialog.cpp
    libs/designer/shared/orderdialog.ui
    libs/designer/shared/orderdialog_p.h
    libs/designer/shared/plaintexteditor.cpp
    libs/designer/shared/plaintexteditor_p.h
    libs/designer/shared/plugindialog.cpp
    libs/designer/shared/plugindialog.ui
    libs/designer/shared/plugindialog_p.h
    libs/designer/shared/pluginmanager.cpp
    libs/designer/shared/pluginmanager_p.h
    libs/designer/shared/previewconfigurationwidget.cpp
    libs/designer/shared/previewconfigurationwidget.ui
    libs/designer/shared/previewconfigurationwidget_p.h
    libs/designer/shared/previewmanager.cpp
    libs/designer/shared/previewmanager_p.h
    libs/designer/shared/promotionmodel.cpp
    libs/designer/shared/promotionmodel_p.h
    libs/designer/shared/promotiontaskmenu.cpp
    libs/designer/shared/promotiontaskmenu_p.h
    libs/designer/shared/propertylineedit.cpp
    libs/designer/shared/propertylineedit_p.h
    libs/designer/shared/qdesigner_command.cpp
    libs/designer/shared/qdesigner_command2.cpp
    libs/designer/shared/qdesigner_command2_p.h
    libs/designer/shared/qdesigner_command_p.h
    libs/designer/shared/qdesigner_dnditem.cpp
    libs/designer/shared/qdesigner_dnditem_p.h
    libs/designer/shared/qdesigner_dockwidget.cpp
    libs/designer/shared/qdesigner_dockwidget_p.h
    libs/designer/shared/qdesigner_formbuilder.cpp
    libs/designer/shared/qdesigner_formbuilder_p.h
    libs/designer/shared/qdesigner_formeditorcommand.cpp
    libs/designer/shared/qdesigner_formeditorcommand_p.h
    libs/designer/shared/qdesigner_formwindowcommand.cpp
    libs/designer/shared/qdesigner_formwindowcommand_p.h
    libs/designer/shared/qdesigner_formwindowmanager.cpp
    libs/designer/shared/qdesigner_formwindowmanager_p.h
    libs/designer/shared/qdesigner_introspection.cpp
    libs/designer/shared/qdesigner_introspection_p.h
    libs/designer/shared/qdesigner_membersheet.cpp
    libs/designer/shared/qdesigner_membersheet_p.h
    libs/designer/shared/qdesigner_menu.cpp
    libs/designer/shared/qdesigner_menu_p.h
    libs/designer/shared/qdesigner_menubar.cpp
    libs/designer/shared/qdesigner_menubar_p.h
    libs/designer/shared/qdesigner_objectinspector.cpp
    libs/designer/shared/qdesigner_objectinspector_p.h
    libs/designer/shared/qdesigner_promotion.cpp
    libs/designer/shared/qdesigner_promotion_p.h
    libs/designer/shared/qdesigner_promotiondialog.cpp
    libs/designer/shared/qdesigner_promotiondialog_p.h
    libs/designer/shared/qdesigner_propertycommand.cpp
    libs/designer/shared/qdesigner_propertycommand_p.h
    libs/designer/shared/qdesigner_propertyeditor.cpp
    libs/designer/shared/qdesigner_propertyeditor_p.h
    libs/designer/shared/qdesigner_propertysheet.cpp
    libs/designer/shared/qdesigner_propertysheet_p.h
    libs/designer/shared/qdesigner_qsettings.cpp
    libs/designer/shared/qdesigner_qsettings_p.h
    libs/designer/shared/qdesigner_stackedbox.cpp
    libs/designer/shared/qdesigner_stackedbox_p.h
    libs/designer/shared/qdesigner_tabwidget.cpp
    libs/designer/shared/qdesigner_tabwidget_p.h
    libs/designer/shared/qdesigner_taskmenu.cpp
    libs/designer/shared/qdesigner_taskmenu_p.h
    libs/designer/shared/qdesigner_toolbar.cpp
    libs/designer/shared/qdesigner_toolbar_p.h
    libs/designer/shared/qdesigner_toolbox.cpp
    libs/designer/shared/qdesigner_toolbox_p.h
    libs/designer/shared/qdesigner_utils.cpp
    libs/designer/shared/qdesigner_utils_p.h
    libs/designer/shared/qdesigner_widget.cpp
    libs/designer/shared/qdesigner_widget_p.h
    libs/designer/shared/qdesigner_widgetbox.cpp
    libs/designer/shared/qdesigner_widgetbox_p.h
    libs/designer/shared/qdesigner_widgetitem.cpp
    libs/designer/shared/qdesigner_widgetitem_p.h
    libs/designer/shared/qlayout_widget.cpp
    libs/designer/shared/qlayout_widget_p.h
    libs/designer/shared/qsimpleresource.cpp
    libs/designer/shared/qsimpleresource_p.h
    libs/designer/shared/qtresourceeditordialog.cpp
    libs/designer/shared/qtresourceeditordialog.ui
    libs/designer/shared/qtresourceeditordialog_p.h
    libs/designer/shared/qtresourcemodel.cpp
    libs/designer/shared/qtresourcemodel_p.h
    libs/designer/shared/qtresourceview.cpp
    libs/designer/shared/qtresourceview_p.h
    libs/designer/shared/rcc.cpp
    libs/designer/shared/rcc_p.h
    libs/designer/shared/richtexteditor.cpp
    libs/designer/shared/richtexteditor_p.h
    libs/designer/shared/selectsignaldialog.cpp
    libs/designer/shared/selectsignaldialog.ui
    libs/designer/shared/selectsignaldialog_p.h
    libs/designer/shared/shared.qrc
    libs/designer/shared/shared_enums_p.h
    libs/designer/shared/shared_global_p.h
    libs/designer/shared/shared_settings.cpp
    libs/designer/shared/shared_settings_p.h
    libs/designer/shared/sheet_delegate.cpp
    libs/designer/shared/sheet_delegate_p.h
    libs/designer/shared/signalslotdialog.cpp
    libs/designer/shared/signalslotdialog.ui
    libs/designer/shared/signalslotdialog_p.h
    libs/designer/shared/spacer_widget.cpp
    libs/designer/shared/spacer_widget_p.h
    libs/designer/shared/stylesheeteditor.cpp
    libs/designer/shared/stylesheeteditor_p.h
    libs/designer/shared/textpropertyeditor.cpp
    libs/designer/shared/textpropertyeditor_p.h
    libs/designer/shared/widgetdatabase.cpp
    libs/designer/shared/widgetdatabase_p.h
    libs/designer/shared/widgetfactory.cpp
    libs/designer/shared/widgetfactory_p.h
    libs/designer/shared/zoomwidget.cpp
    libs/designer/shared/zoomwidget_p.h
    # libs/designer/uilib/abstractformbuilder.cpp
    # libs/designer/uilib/abstractformbuilder.h
    # libs/designer/uilib/formbuilder.cpp
    # libs/designer/uilib/formbuilder.h
    # libs/designer/uilib/formbuilderextra.cpp
    # libs/designer/uilib/formbuilderextra_p.h
    # libs/designer/uilib/properties.cpp
    # libs/designer/uilib/properties_p.h
    # libs/designer/uilib/resourcebuilder.cpp
    # libs/designer/uilib/resourcebuilder_p.h
    # libs/designer/uilib/textbuilder.cpp
    # libs/designer/uilib/textbuilder_p.h
    # libs/designer/uilib/ui4.cpp
    # libs/designer/uilib/ui4_p.h
    # libs/designer/uilib/uilib_global.h
    source/base/qextDesignerAbstractActionEditor.cpp
    source/base/qextDesignerAbstractActionEditor.h
    source/base/qextDesignerAbstractDialogGui.cpp
    source/base/qextDesignerAbstractDialogGui_p.h
    source/base/qextDesignerAbstractDnDItem.h
    source/base/qextDesignerAbstractFormEditor.cpp
    source/base/qextDesignerAbstractFormEditor.h
    source/base/qextDesignerAbstractFormEditorPlugin.cpp
    source/base/qextDesignerAbstractFormEditorPlugin.h
    source/base/qextDesignerAbstractFormWindow.cpp
    source/base/qextDesignerAbstractFormWindow.h
    source/base/qextDesignerAbstractFormWindowCursor.cpp
    source/base/qextDesignerAbstractFormWindowCursor.h
    source/base/qextDesignerAbstractFormWindowManager.cpp
    source/base/qextDesignerAbstractFormWindowManager.h
    source/base/qextDesignerAbstractFormWindowTool.cpp
    source/base/qextDesignerAbstractFormWindowTool.h
    source/base/qextDesignerAbstractIntegration.cpp
    source/base/qextDesignerAbstractIntegration.h
    source/base/qextDesignerAbstractIntrospection.cpp
    source/base/qextDesignerAbstractIntrospection_p.h
    source/base/qextDesignerAbstractMetaDataBase.cpp
    source/base/qextDesignerAbstractMetaDataBase.h
    source/base/qextDesignerAbstractNewFormWidget.cpp
    source/base/qextDesignerAbstractNewFormWidget.h
    source/base/qextDesignerAbstractObjectInspector.cpp
    source/base/qextDesignerAbstractObjectInspector.h
    source/base/qextDesignerAbstractOptionsPage.h
    source/base/qextDesignerAbstractPromotion.cpp
    source/base/qextDesignerAbstractPromotion.h
    source/base/qextDesignerAbstractPropertyEditor.cpp
    source/base/qextDesignerAbstractPropertyEditor.h
    source/base/qextDesignerAbstractResourceBrowser.cpp
    source/base/qextDesignerAbstractResourceBrowser.h
    source/base/qextDesignerAbstractSettings.h
    source/base/qextDesignerAbstractWidgetBox.cpp
    source/base/qextDesignerAbstractWidgetBox.h
    source/base/qextDesignerAbstractWidgetDataBase.cpp
    source/base/qextDesignerAbstractWidgetDataBase.h
    source/base/qextDesignerAbstractWidgetFactory.cpp
    source/base/qextDesignerAbstractWidgetFactory.h
    source/builder/qextDesignerAbstractFormBuilder.cpp
    source/builder/qextDesignerAbstractFormBuilder.h
    source/builder/qextDesignerDomUI.cpp
    source/builder/qextDesignerDomUI_p.h
    source/builder/qextDesignerFormBuilder.cpp
    source/builder/qextDesignerFormBuilder.h
    source/builder/qextDesignerFormBuilderExtra.cpp
    source/builder/qextDesignerFormBuilderExtra_p.h
    source/builder/qextDesignerFormBuilderUtils.cpp
    source/builder/qextDesignerFormBuilderUtils_p.h
    source/builder/qextDesignerResourceBuilder.cpp
    source/builder/qextDesignerResourceBuilder_p.h
    source/builder/qextDesignerTextBuilder.cpp
    source/builder/qextDesignerTextBuilder_p.h
    source/builder/qextDesignerWidgetsTable.h
    source/extension/qextDesignerContainerExtension.h
    source/extension/qextDesignerDynamicPropertySheetExtension.h
    source/extension/qextDesignerExtension.cpp
    source/extension/qextDesignerExtension.h
    source/extension/qextDesignerExtensionFactory.cpp
    source/extension/qextDesignerExtensionFactory.h
    source/extension/qextDesignerExtensionManager.cpp
    source/extension/qextDesignerExtensionManager.h
    source/extension/qextDesignerExtraInfoExtension.cpp
    source/extension/qextDesignerExtraInfoExtension.h
    source/extension/qextDesignerLanguageExtension.h
    source/extension/qextDesignerLayoutDecorationExtension.h
    source/extension/qextDesignerMemberSheetExtension.h
    source/extension/qextDesignerPropertySheetExtension.h
    source/extension/qextDesignerTaskMenuExtension.h
    source/qextDesignerConstant.h
    source/qextDesignerGlobal.h
    source/qextDesignerPch.h
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/dev/designer/
    ${PROJECT_SOURCE_DIR}/dev/designer/libs
    ${PROJECT_SOURCE_DIR}/dev/designer/libs/designer
    ${PROJECT_SOURCE_DIR}/dev/designer/libs/designer/components
    ${PROJECT_SOURCE_DIR}/dev/designer/libs/designer/extension
    ${PROJECT_SOURCE_DIR}/dev/designer/libs/designer/sdk
    ${PROJECT_SOURCE_DIR}/dev/designer/libs/designer/shared
    ${PROJECT_SOURCE_DIR}/dev/designer/libs/designer/uilib
    ${PROJECT_SOURCE_DIR}/dev/designer/libs/deviceskin
    ${PROJECT_SOURCE_DIR}/dev/designer/libs/findwidget
    ${PROJECT_SOURCE_DIR}/dev/designer/libs/fontpanel
    ${PROJECT_SOURCE_DIR}/dev/designer/libs/qtgradienteditor
    ${PROJECT_SOURCE_DIR}/dev/designer/libs/qtpropertybrowser
    ${PROJECT_SOURCE_DIR}/dev/designer/libs/qttoolbardialog
    ${PROJECT_SOURCE_DIR}/dev/designer/libs/uiplugin
    ${PROJECT_SOURCE_DIR}/dev/designer/libs/uitools
    ${PROJECT_SOURCE_DIR}/dev/designer/libs/winutils
    PRECOMPILED_HEADER
    source/qextDesignerPch.h
    PUBLIC_LIBRARIES
    ${QEXT_LIB_LINK_LIBRARIES})



#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
# qext_add_subdirectory(tests QEXT_BUILD_TESTS)
