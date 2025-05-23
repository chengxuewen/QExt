/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Designer of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qextDesignerAbstractFormEditor.h>
#include <private/qextDesignerAbstractDialogGui_p.h>
#include <private/qextDesignerAbstractIntrospection_p.h>

#include <qextDesignerExtensionManager.h>

#include <qextDesignerAbstractSettings.h>
#include <qextDesignerAbstractWidgetBox.h>
#include <qextDesignerAbstractIntegration.h>
#include <qextDesignerAbstractOptionsPage.h>
#include <qextDesignerAbstractActionEditor.h>
#include <qextDesignerAbstractMetaDataBase.h>
#include <qextDesignerAbstractWidgetFactory.h>
#include <qextDesignerAbstractWidgetDataBase.h>
#include <qextDesignerAbstractPropertyEditor.h>
#include <qextDesignerAbstractObjectInspector.h>
#include <qextDesignerAbstractFormWindowManager.h>
#include <qextDesignerAbstractPromotion.h>

#include "../shared/actioneditor_p.h"
#include "../shared/pluginmanager_p.h"
#include "../shared/qtresourcemodel_p.h"
#include "../../qtgradienteditor/qtgradientmanager.h"
#include "../shared/widgetfactory_p.h"
#include "../shared/shared_settings_p.h"
#include "../shared/formwindowbase_p.h"
#include "../shared/grid_p.h"
#include "../shared/iconloader_p.h"

#include <QtGui/qicon.h>

// Must be done outside of the Qt namespace
static void initResources()
{
    Q_INIT_RESOURCE(shared);
    Q_INIT_RESOURCE(ClamshellPhone);
    Q_INIT_RESOURCE(PortableMedia);
    Q_INIT_RESOURCE(S60_nHD_Touchscreen);
    Q_INIT_RESOURCE(S60_QVGA_Candybar);
    Q_INIT_RESOURCE(SmartPhone2);
    Q_INIT_RESOURCE(SmartPhone);
    Q_INIT_RESOURCE(SmartPhoneWithButtons);
    Q_INIT_RESOURCE(TouchscreenPhone);
}

QT_BEGIN_NAMESPACE

class QExtDesignerAbstractFormEditorPrivate {
public:
    QExtDesignerAbstractFormEditorPrivate();
    ~QExtDesignerAbstractFormEditorPrivate();


    QPointer<QWidget> m_topLevel;
    QPointer<QExtDesignerAbstractWidgetBox> m_widgetBox;
    QPointer<QExtDesignerAbstractPropertyEditor> m_propertyEditor;
    QPointer<QExtDesignerAbstractFormWindowManager> m_formWindowManager;
    QPointer<QExtensionManager> m_extensionManager;
    QPointer<QExtDesignerAbstractMetaDataBase> m_metaDataBase;
    QPointer<QDesignerWidgetDataBaseInterface> m_widgetDataBase;
    QPointer<QExtDesignerAbstractWidgetFactory> m_widgetFactory;
    QPointer<QExtDesignerAbstractObjectInspector> m_objectInspector;
    QPointer<QExtDesignerAbstractIntegration> m_integration;
    QPointer<QExtDesignerAbstractActionEditor> m_actionEditor;
    QExtDesignerSettingsInterface *m_settingsManager = nullptr;
    QDesignerPluginManager *m_pluginManager = nullptr;
    QExtDesignerPromotionInterface *m_promotion = nullptr;
    QExtDesignerIntrospectionInterface *m_introspection = nullptr;
    QExtDesignerAbstractDialogGui *m_dialogGui = nullptr;
    QPointer<QtResourceModel> m_resourceModel;
    QPointer<QtGradientManager> m_gradientManager; // instantiated and deleted by designer_integration
    QList<QExtDesignerOptionsPageInterface*> m_optionsPages;
};

QExtDesignerAbstractFormEditorPrivate::QExtDesignerAbstractFormEditorPrivate() = default;

QExtDesignerAbstractFormEditorPrivate::~QExtDesignerAbstractFormEditorPrivate()
{
    delete m_settingsManager;
    delete m_formWindowManager;
    delete m_promotion;
    delete m_introspection;
    delete m_dialogGui;
    delete m_resourceModel;
    qDeleteAll(m_optionsPages);
}

/*!
    \class QExtDesignerAbstractFormEditor

    \brief The QExtDesignerAbstractFormEditor class allows you to access
    Qt Designer's various components.

    \inmodule QtDesigner

    \QD's current QExtDesignerAbstractFormEditor object holds
    information about all \QD's components: The action editor, the
    object inspector, the property editor, the widget box, and the
    extension and form window managers. QExtDesignerAbstractFormEditor
    contains a collection of functions that provides interfaces to all
    these components. They are typically used to query (and
    manipulate) the respective component. For example:

    \snippet lib/tools_designer_src_lib_sdk_abstractformeditor.cpp 0

    QExtDesignerAbstractFormEditor is not intended to be instantiated
    directly. A pointer to \QD's current QExtDesignerAbstractFormEditor
    object (\c formEditor in the example above) is provided by the
    QDesignerCustomWidgetInterface::initialize() function's
    parameter. When implementing a custom widget plugin, you must
    subclass the QDesignerCustomWidgetInterface to expose your plugin
    to \QD.

    QExtDesignerAbstractFormEditor also provides functions that can set
    the action editor, property editor, object inspector and widget
    box. These are only useful if you want to provide your own custom
    components.

    If designer is embedded in another program, one could to provide its
    own settings manager. The manager is used by the components of \QD
    to store/retrieve persistent configuration settings. The default
    manager uses QSettings as the backend.

    Finally, QExtDesignerAbstractFormEditor provides the topLevel()
    function that returns \QD's top-level widget.

    \sa QDesignerCustomWidgetInterface
*/

/*!
    Constructs a QExtDesignerAbstractFormEditor object with the given \a
    parent.
*/

QExtDesignerAbstractFormEditor::QExtDesignerAbstractFormEditor(QObject *parent)
    : QObject(parent),
    d(new QExtDesignerAbstractFormEditorPrivate())
{
    initResources();
}

/*!
    Destroys the QExtDesignerAbstractFormEditor object.
*/
QExtDesignerAbstractFormEditor::~QExtDesignerAbstractFormEditor() = default;

/*!
    Returns an interface to \QD's widget box.

    \sa setWidgetBox()
*/
QExtDesignerAbstractWidgetBox *QExtDesignerAbstractFormEditor::widgetBox() const
{
    return d->m_widgetBox;
}

/*!
    Sets \QD's widget box to be the specified \a widgetBox.

    \sa widgetBox()
*/
void QExtDesignerAbstractFormEditor::setWidgetBox(QExtDesignerAbstractWidgetBox *widgetBox)
{
    d->m_widgetBox = widgetBox;
}

/*!
    Returns an interface to \QD's property editor.

    \sa setPropertyEditor()
*/
QExtDesignerAbstractPropertyEditor *QExtDesignerAbstractFormEditor::propertyEditor() const
{
    return d->m_propertyEditor;
}

/*!
    Sets \QD's property editor to be the specified \a propertyEditor.

    \sa propertyEditor()
*/
void QExtDesignerAbstractFormEditor::setPropertyEditor(QExtDesignerAbstractPropertyEditor *propertyEditor)
{
    d->m_propertyEditor = propertyEditor;
}

/*!
    Returns an interface to \QD's action editor.

    \sa setActionEditor()
*/
QExtDesignerAbstractActionEditor *QExtDesignerAbstractFormEditor::actionEditor() const
{
    return d->m_actionEditor;
}

/*!
    Sets \QD's action editor to be the specified \a actionEditor.

    \sa actionEditor()
*/
void QExtDesignerAbstractFormEditor::setActionEditor(QExtDesignerAbstractActionEditor *actionEditor)
{
    d->m_actionEditor = actionEditor;
}

/*!
    Returns \QD's top-level widget.
*/
QWidget *QExtDesignerAbstractFormEditor::topLevel() const
{
    return d->m_topLevel;
}

/*!
    \internal
*/
void QExtDesignerAbstractFormEditor::setTopLevel(QWidget *topLevel)
{
    d->m_topLevel = topLevel;
}

/*!
    Returns an interface to \QD's form window manager.
*/
QExtDesignerAbstractFormWindowManager *QExtDesignerAbstractFormEditor::formWindowManager() const
{
    return d->m_formWindowManager;
}

/*!
    \internal
*/
void QExtDesignerAbstractFormEditor::setFormManager(QExtDesignerAbstractFormWindowManager *formWindowManager)
{
    d->m_formWindowManager = formWindowManager;
}

/*!
    Returns an interface to \QD's extension manager.
*/
QExtensionManager *QExtDesignerAbstractFormEditor::extensionManager() const
{
    return d->m_extensionManager;
}

/*!
    \internal
*/
void QExtDesignerAbstractFormEditor::setExtensionManager(QExtensionManager *extensionManager)
{
    d->m_extensionManager = extensionManager;
}

/*!
    \internal

    Returns an interface to the meta database used by the form editor.
*/
QExtDesignerAbstractMetaDataBase *QExtDesignerAbstractFormEditor::metaDataBase() const
{
    return d->m_metaDataBase;
}

/*!
    \internal
*/
void QExtDesignerAbstractFormEditor::setMetaDataBase(QExtDesignerAbstractMetaDataBase *metaDataBase)
{
    d->m_metaDataBase = metaDataBase;
}

/*!
    \internal

    Returns an interface to the widget database used by the form editor.
*/
QDesignerWidgetDataBaseInterface *QExtDesignerAbstractFormEditor::widgetDataBase() const
{
    return d->m_widgetDataBase;
}

/*!
    \internal
*/
void QExtDesignerAbstractFormEditor::setWidgetDataBase(QDesignerWidgetDataBaseInterface *widgetDataBase)
{
    d->m_widgetDataBase = widgetDataBase;
}

/*!
    \internal

    Returns an interface to the designer promotion handler.
*/

QExtDesignerPromotionInterface *QExtDesignerAbstractFormEditor::promotion() const
{
    return d->m_promotion;
}

/*!
    \internal

    Sets the designer promotion handler.
*/

void QExtDesignerAbstractFormEditor::setPromotion(QExtDesignerPromotionInterface *promotion)
{
    delete d->m_promotion;
    d->m_promotion = promotion;
}

/*!
    \internal

    Returns an interface to the widget factory used by the form editor
    to create widgets for the form.
*/
QExtDesignerAbstractWidgetFactory *QExtDesignerAbstractFormEditor::widgetFactory() const
{
    return d->m_widgetFactory;
}

/*!
    \internal
*/
void QExtDesignerAbstractFormEditor::setWidgetFactory(QExtDesignerAbstractWidgetFactory *widgetFactory)
{
    d->m_widgetFactory = widgetFactory;
}

/*!
    Returns an interface to \QD's object inspector.
*/
QExtDesignerAbstractObjectInspector *QExtDesignerAbstractFormEditor::objectInspector() const
{
    return d->m_objectInspector;
}

/*!
    Sets \QD's object inspector to be the specified \a
    objectInspector.

    \sa objectInspector()
*/
void QExtDesignerAbstractFormEditor::setObjectInspector(QExtDesignerAbstractObjectInspector *objectInspector)
{
    d->m_objectInspector = objectInspector;
}

/*!
    \internal

    Returns an interface to the integration.
*/
QExtDesignerAbstractIntegration *QExtDesignerAbstractFormEditor::integration() const
{
    return d->m_integration;
}

/*!
    \internal
*/
void QExtDesignerAbstractFormEditor::setIntegration(QExtDesignerAbstractIntegration *integration)
{
    d->m_integration = integration;
}

/*!
    \internal
    \since 4.5
    Returns the list of options pages that allow the user to configure \QD components.
*/
QList<QExtDesignerOptionsPageInterface*> QExtDesignerAbstractFormEditor::optionsPages() const
{
    return d->m_optionsPages;
}

/*!
    \internal
    \since 4.5
    Sets the list of options pages that allow the user to configure \QD components.
*/
void QExtDesignerAbstractFormEditor::setOptionsPages(const QList<QExtDesignerOptionsPageInterface*> &optionsPages)
{
    d->m_optionsPages = optionsPages;
}


/*!
    \internal

    Returns the plugin manager used by the form editor.
*/
QDesignerPluginManager *QExtDesignerAbstractFormEditor::pluginManager() const
{
    return d->m_pluginManager;
}

/*!
    \internal

    Sets the plugin manager used by the form editor to the specified
    \a pluginManager.
*/
void QExtDesignerAbstractFormEditor::setPluginManager(QDesignerPluginManager *pluginManager)
{
    d->m_pluginManager = pluginManager;
}

/*!
    \internal
    \since 4.4
    Returns the resource model used by the form editor.
*/
QtResourceModel *QExtDesignerAbstractFormEditor::resourceModel() const
{
    return d->m_resourceModel;
}

/*!
    \internal

    Sets the resource model used by the form editor to the specified
    \a resourceModel.
*/
void QExtDesignerAbstractFormEditor::setResourceModel(QtResourceModel *resourceModel)
{
    d->m_resourceModel = resourceModel;
}

/*!
    \internal
    \since 4.4
    Returns the gradient manager used by the style sheet editor.
*/
QtGradientManager *QExtDesignerAbstractFormEditor::gradientManager() const
{
    return d->m_gradientManager;
}

/*!
    \internal

    Sets the gradient manager used by the style sheet editor to the specified
    \a gradientManager.
*/
void QExtDesignerAbstractFormEditor::setGradientManager(QtGradientManager *gradientManager)
{
    d->m_gradientManager = gradientManager;
}

/*!
    \internal
    \since 4.5
    Returns the settings manager used by the components to store persistent settings.
*/
QExtDesignerSettingsInterface *QExtDesignerAbstractFormEditor::settingsManager() const
{
    return d->m_settingsManager;
}

/*!
    \internal
    \since 4.5
    Sets the settings manager used to store/retrieve the persistent settings of the components.
*/
void QExtDesignerAbstractFormEditor::setSettingsManager(QExtDesignerSettingsInterface *settingsManager)
{
    if (d->m_settingsManager)
        delete d->m_settingsManager;
    d->m_settingsManager = settingsManager;

    // This is a (hopefully) safe place to perform settings-dependent
    // initializations.
    const qdesigner_internal::QDesignerSharedSettings settings(this);
    qdesigner_internal::FormWindowBase::setDefaultDesignerGrid(settings.defaultGrid());
    qdesigner_internal::ActionEditor::setObjectNamingMode(settings.objectNamingMode());
}

/*!
    \internal
    \since 4.4
    Returns the introspection used by the form editor.
*/
QExtDesignerIntrospectionInterface *QExtDesignerAbstractFormEditor::introspection() const
{
    return d->m_introspection;
}

/*!
    \internal
    \since 4.4

    Sets the introspection used by the form editor to the specified \a introspection.
*/
void QExtDesignerAbstractFormEditor::setIntrospection(QExtDesignerIntrospectionInterface *introspection)
{
    delete d->m_introspection;
    d->m_introspection = introspection;
}

/*!
    \internal

    Returns the path to the resources used by the form editor.
*/
QString QExtDesignerAbstractFormEditor::resourceLocation() const
{
#ifdef Q_OS_MACOS
    return QStringLiteral(":/qt-project.org/formeditor/images/mac");
#else
    return QStringLiteral(":/qt-project.org/formeditor/images/win");
#endif
}

/*!
    \internal

    Returns the dialog GUI used by the form editor.
*/

QExtDesignerAbstractDialogGui *QExtDesignerAbstractFormEditor::dialogGui() const
{
    return d->m_dialogGui;
}

/*!
    \internal

    Sets the dialog GUI used by the form editor to the specified \a dialogGui.
*/

void QExtDesignerAbstractFormEditor::setDialogGui(QExtDesignerAbstractDialogGui *dialogGui)
{
    delete  d->m_dialogGui;
    d->m_dialogGui = dialogGui;
}

/*!
    \internal

    \since 5.0

    Returns the plugin instances of QDesignerPluginManager.
*/

QObjectList QExtDesignerAbstractFormEditor::pluginInstances() const
{
    return d->m_pluginManager->instances();
}

/*!
    \internal

    \since 5.0

    Return icons for actions of \QD.
*/

QIcon QExtDesignerAbstractFormEditor::createIcon(const QString &name)
{
    return qdesigner_internal::createIconSet(name);
}

QT_END_NAMESPACE
