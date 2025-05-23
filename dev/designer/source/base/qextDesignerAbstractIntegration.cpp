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

#include <qextDesignerAbstractIntegration.h>
#include <qextDesignerAbstractFormWindow.h>
#include <qextDesignerAbstractFormWindowManager.h>
#include <qextDesignerAbstractFormWindowCursor.h>
#include <qextDesignerAbstractFormEditor.h>
#include <qextDesignerAbstractActionEditor.h>
#include <qextDesignerAbstractWidgetBox.h>
#include <qextDesignerAbstractResourceBrowser.h>
#include <qextDesignerAbstractPropertyEditor.h>

#include <qextDesignerPropertySheetExtension.h>

#include <qextDesignerExtensionManager.h>
#include "../shared/qtresourcemodel_p.h"
#include "../shared/qdesigner_propertycommand_p.h"
#include "../shared/qdesigner_propertyeditor_p.h"
#include "../shared/qdesigner_objectinspector_p.h"
#include "../shared/widgetdatabase_p.h"
#include "../shared/pluginmanager_p.h"
#include "../shared/widgetfactory_p.h"
#include "../shared/qdesigner_widgetbox_p.h"
#include "../qtgradienteditor/qtgradientmanager.h"
#include "../qtgradienteditor/qtgradientutils.h"
#include "../shared/qtresourcemodel_p.h"

#include <QtCore/qvariant.h>
#include <QtCore/qfile.h>
#include <QtCore/qdir.h>

#include <QtCore/qdebug.h>

QT_BEGIN_NAMESPACE

/*!
    \class QExtDesignerAbstractIntegration

    \brief The QExtDesignerAbstractIntegration glues together parts of \QD
    and allows for overwriting functionality for IDE integration.

    \internal

    \inmodule QtDesigner

    \sa QExtDesignerAbstractFormEditor
*/

/*!
    \enum QExtDesignerAbstractIntegration::ResourceFileWatcherBehaviour

    \internal

    This enum describes if and how resource files are watched.

    \value NoResourceFileWatcher        Do not watch for changes
    \value ReloadResourceFileSilently   Reload files silently.
    \value PromptToReloadResourceFile   Prompt the user to reload.
*/

/*!
    \enum QExtDesignerAbstractIntegration::FeatureFlag

    \internal

    This enum describes the features that are available and can be
    controlled by the integration.

    \value ResourceEditorFeature       The resource editor is enabled.
    \value SlotNavigationFeature       Provide context menu entry offering 'Go to slot'.
    \value DefaultWidgetActionFeature  Trigger the preferred action of
                                       QExtDesignerTaskMenuExtension when widget is activated.
    \value DefaultFeature              Default for \QD

    \sa hasFeature(), features()
*/

/*!
    \property QExtDesignerAbstractIntegration::headerSuffix

    Returns the suffix of the header of promoted widgets.
*/

/*!
    \property QExtDesignerAbstractIntegration::headerLowercase

    Returns whether headers of promoted widgets should be lower-cased (as the user types the class name).
*/

/*!
    \fn virtual void QExtDesignerAbstractIntegration::updateSelection()

    \brief Sets the selected widget of the form window in various components.

    \internal

    In IDE integrations, the method can be overwritten to move the selection handles
    of the form's main window, should it be selected.
*/

/*!
    \fn virtual QWidget *QExtDesignerAbstractIntegration::containerWindow(QWidget *widget) const

    \brief Returns the outer window containing a form for applying main container geometries.

    \internal

    Should be implemented by IDE integrations.
*/

/*!
    \fn virtual QExtDesignerAbstractResourceBrowser *QExtDesignerAbstractIntegration::createResourceBrowser(QWidget *parent = 0)

    \brief Creates a resource browser depending on IDE integration.

    \internal

    \note Language integration takes precedence.
*/

/*!
    \fn virtual void QExtDesignerAbstractIntegration::updateProperty(const QString &name, const QVariant &value, bool enableSubPropertyHandling)

    \brief Triggered by the property editor to update a property value.

    \internal

    If a different property editor is used, it should invoke this function.
*/

/*!
    \fn virtual void QExtDesignerAbstractIntegration::updateProperty(const QString &name, const QVariant &value)

    \brief Triggered by the property editor to update a property value without subproperty handling.

    \internal

    If a different property editor is used, it should invoke this function.
*/

/*!
    \fn virtual void QExtDesignerAbstractIntegration::resetProperty(const QString &name)

    \brief Triggered by the property editor to reset a property value.

    \internal

    If a different property editor is used, it should invoke this function.
*/

/*!
    \fn virtual void QExtDesignerAbstractIntegration::addDynamicProperty(const QString &name, const QVariant &value)

    \brief Triggered by the property editor to add a dynamic property value.

    \internal

    If a different property editor is used, it should invoke this function.
*/

/*!
    \fn virtual void QExtDesignerAbstractIntegration::removeDynamicProperty(const QString &name)

    \brief Triggered by the property editor to remove a dynamic property.

    \internal

    If a different property editor is used, it should invoke this function.
*/

/*!
    \fn virtual void QExtDesignerAbstractIntegration::updateActiveFormWindow(QExtDesignerAbstractFormWindow *formWindow)

    \brief Sets up the active form window.

    \internal
*/

/*!
    \fn virtual void QExtDesignerAbstractIntegration::setupFormWindow(QExtDesignerAbstractFormWindow *formWindow)

    \brief Sets up the new form window.

    \internal
*/

/*!
    \fn virtual void QExtDesignerAbstractIntegration::updateCustomWidgetPlugins()

    \brief Triggers a reload of the custom widget plugins.

    \internal
*/

class QExtDesignerAbstractIntegrationPrivate
{
public:
    QExtDesignerAbstractIntegrationPrivate(QExtDesignerAbstractFormEditor *core) :
        m_core(core) {}

    QExtDesignerAbstractFormEditor *m_core;
};

QExtDesignerAbstractIntegration::QExtDesignerAbstractIntegration(QExtDesignerAbstractFormEditor *core, QObject *parent)
    : QObject(parent), d(new QExtDesignerAbstractIntegrationPrivate(core))
{
    core->setIntegration(this);
}

QExtDesignerAbstractIntegration::~QExtDesignerAbstractIntegration() = default;

QExtDesignerAbstractFormEditor *QExtDesignerAbstractIntegration::core() const
{
    return d->m_core;
}

bool QExtDesignerAbstractIntegration::hasFeature(Feature f) const
{
    return (features() & f) != 0;
}

void QExtDesignerAbstractIntegration::emitObjectNameChanged(QExtDesignerAbstractFormWindow *formWindow, QObject *object, const QString &newName, const QString &oldName)
{
    emit objectNameChanged(formWindow, object, newName, oldName);
}

void QExtDesignerAbstractIntegration::emitNavigateToSlot(const QString &objectName,
                                                       const QString &signalSignature,
                                                       const QStringList &parameterNames)
{
    emit navigateToSlot(objectName, signalSignature, parameterNames);
}

void QExtDesignerAbstractIntegration::emitNavigateToSlot(const QString &slotSignature)
{
    emit navigateToSlot(slotSignature);
}

void QExtDesignerAbstractIntegration::emitHelpRequested(const QString &manual, const QString &document)
{
    emit helpRequested(manual, document);
}

/*!
    \class QExtDesignerIntegration

    \brief The QExtDesignerIntegration class is \QD's implementation of
    QExtDesignerAbstractIntegration.

    \internal

    \inmodule QtDesigner

    IDE integrations should register classes derived from QExtDesignerIntegration
    with QExtDesignerAbstractFormEditor.
*/

namespace qdesigner_internal {

class QExtDesignerIntegrationPrivate {
public:
    explicit QExtDesignerIntegrationPrivate(QExtDesignerIntegration *qq);

    QWidget *containerWindow(QWidget *widget) const;

    // Load plugins into widget database and factory.
    static void initializePlugins(QExtDesignerAbstractFormEditor *formEditor);

    QString contextHelpId() const;

    void updateProperty(const QString &name, const QVariant &value, bool enableSubPropertyHandling);
    void resetProperty(const QString &name);
    void addDynamicProperty(const QString &name, const QVariant &value);
    void removeDynamicProperty(const QString &name);

    void setupFormWindow(QExtDesignerAbstractFormWindow *formWindow);
    void updateSelection();
    void updateCustomWidgetPlugins();

    void updatePropertyPrivate(const QString &name, const QVariant &value);

    void initialize();
    void getSelection(qdesigner_internal::Selection &s);
    QObject *propertyEditorObject();

    QExtDesignerIntegration *q;
    QString headerSuffix;
    bool headerLowercase;
    QExtDesignerAbstractIntegration::Feature m_features;
    QExtDesignerAbstractIntegration::ResourceFileWatcherBehaviour m_resourceFileWatcherBehaviour;
    QString m_gradientsPath;
    QtGradientManager *m_gradientManager;
};

QExtDesignerIntegrationPrivate::QExtDesignerIntegrationPrivate(QExtDesignerIntegration *qq) :
    q(qq),
    headerSuffix(QStringLiteral(".h")),
    headerLowercase(true),
    m_features(QExtDesignerAbstractIntegration::DefaultFeature),
    m_resourceFileWatcherBehaviour(QExtDesignerAbstractIntegration::PromptToReloadResourceFile),
    m_gradientManager(nullptr)
{
}

void QExtDesignerIntegrationPrivate::initialize()
{
    //
    // integrate the `Form Editor component'
    //

    // Extensions
    QExtDesignerAbstractFormEditor *core = q->core();
    if (QDesignerPropertyEditor *designerPropertyEditor= qobject_cast<QDesignerPropertyEditor *>(core->propertyEditor())) {
        QObject::connect(designerPropertyEditor, &QDesignerPropertyEditor::propertyValueChanged,
                         q, QOverload<const QString &, const QVariant &, bool>::of(&QExtDesignerIntegration::updateProperty));
        QObject::connect(designerPropertyEditor, &QDesignerPropertyEditor::resetProperty,
                         q, &QExtDesignerIntegration::resetProperty);
        QObject::connect(designerPropertyEditor, &QDesignerPropertyEditor::addDynamicProperty,
                         q, &QExtDesignerIntegration::addDynamicProperty);
        QObject::connect(designerPropertyEditor, &QDesignerPropertyEditor::removeDynamicProperty,
                         q, &QExtDesignerIntegration::removeDynamicProperty);
    } else {
        QObject::connect(core->propertyEditor(), SIGNAL(propertyChanged(QString,QVariant)),
                         q, SLOT(updatePropertyPrivate(QString,QVariant))); // ### fixme: VS Integration leftover?
    }

    QObject::connect(core->formWindowManager(), &QExtDesignerAbstractFormWindowManager::formWindowAdded,
                     q, &QExtDesignerAbstractIntegration::setupFormWindow);

    QObject::connect(core->formWindowManager(), &QExtDesignerAbstractFormWindowManager::activeFormWindowChanged,
                     q, &QExtDesignerAbstractIntegration::updateActiveFormWindow);

    m_gradientManager = new QtGradientManager(q);
    core->setGradientManager(m_gradientManager);

    QString designerFolder = QDir::homePath();
    designerFolder += QDir::separator();
    designerFolder += QStringLiteral(".designer");
    m_gradientsPath = designerFolder;
    m_gradientsPath += QDir::separator();
    m_gradientsPath += QStringLiteral("gradients.xml");

    QFile f(m_gradientsPath);
    if (f.open(QIODevice::ReadOnly)) {
        QtGradientUtils::restoreState(m_gradientManager, QString::fromLatin1(f.readAll()));
        f.close();
    } else {
        QFile defaultGradients(QStringLiteral(":/qt-project.org/designer/defaultgradients.xml"));
        if (defaultGradients.open(QIODevice::ReadOnly)) {
            QtGradientUtils::restoreState(m_gradientManager, QString::fromLatin1(defaultGradients.readAll()));
            defaultGradients.close();
        }
    }

    if (WidgetDataBase *widgetDataBase = qobject_cast<WidgetDataBase*>(core->widgetDataBase()))
        widgetDataBase->grabStandardWidgetBoxIcons();
}

void QExtDesignerIntegrationPrivate::updateProperty(const QString &name, const QVariant &value, bool enableSubPropertyHandling)
{
    QExtDesignerAbstractFormWindow *formWindow = q->core()->formWindowManager()->activeFormWindow();
    if (!formWindow)
        return;

    Selection selection;
    getSelection(selection);
    if (selection.empty())
        return;

    SetPropertyCommand *cmd = new SetPropertyCommand(formWindow);
    // find a reference object to compare to and to find the right group
    if (cmd->init(selection.selection(), name, value, propertyEditorObject(), enableSubPropertyHandling)) {
        formWindow->commandHistory()->push(cmd);
    } else {
        delete cmd;
        qDebug() << "Unable to set  property " << name << '.';
    }
}

void QExtDesignerIntegrationPrivate::resetProperty(const QString &name)
{
    QExtDesignerAbstractFormWindow *formWindow = q->core()->formWindowManager()->activeFormWindow();
    if (!formWindow)
        return;

    Selection selection;
    getSelection(selection);
    if (selection.empty())
        return;

    ResetPropertyCommand *cmd = new ResetPropertyCommand(formWindow);
    // find a reference object to find the right group
    if (cmd->init(selection.selection(), name, propertyEditorObject())) {
        formWindow->commandHistory()->push(cmd);
    } else {
        delete cmd;
        qDebug() << "** WARNING Unable to reset property " << name << '.';
    }
}

void QExtDesignerIntegrationPrivate::addDynamicProperty(const QString &name, const QVariant &value)
{
    QExtDesignerAbstractFormWindow *formWindow = q->core()->formWindowManager()->activeFormWindow();
    if (!formWindow)
        return;

    Selection selection;
    getSelection(selection);
    if (selection.empty())
        return;

    AddDynamicPropertyCommand *cmd = new AddDynamicPropertyCommand(formWindow);
    if (cmd->init(selection.selection(), propertyEditorObject(), name, value)) {
        formWindow->commandHistory()->push(cmd);
    } else {
        delete cmd;
        qDebug() <<  "** WARNING Unable to add dynamic property " << name << '.';
    }
}

void QExtDesignerIntegrationPrivate::removeDynamicProperty(const QString &name)
{
    QExtDesignerAbstractFormWindow *formWindow = q->core()->formWindowManager()->activeFormWindow();
    if (!formWindow)
        return;

    Selection selection;
    getSelection(selection);
    if (selection.empty())
        return;

    RemoveDynamicPropertyCommand *cmd = new RemoveDynamicPropertyCommand(formWindow);
    if (cmd->init(selection.selection(), propertyEditorObject(), name)) {
        formWindow->commandHistory()->push(cmd);
    } else {
        delete cmd;
        qDebug() << "** WARNING Unable to remove dynamic property " << name << '.';
    }

}

void QExtDesignerIntegrationPrivate::setupFormWindow(QExtDesignerAbstractFormWindow *formWindow)
{
    QObject::connect(formWindow, &QExtDesignerAbstractFormWindow::selectionChanged,
                     q, &QExtDesignerAbstractIntegration::updateSelection);
}

void QExtDesignerIntegrationPrivate::updateSelection()
{
    QExtDesignerAbstractFormEditor *core = q->core();
    QExtDesignerAbstractFormWindow *formWindow = core->formWindowManager()->activeFormWindow();
    QWidget *selection = nullptr;

    if (formWindow) {
        selection = formWindow->cursor()->current();
    }

    if (QExtDesignerAbstractActionEditor *actionEditor = core->actionEditor())
        actionEditor->setFormWindow(formWindow);

    if (QExtDesignerAbstractPropertyEditor *propertyEditor = core->propertyEditor())
        propertyEditor->setObject(selection);

    if (QExtDesignerAbstractObjectInspector *objectInspector = core->objectInspector())
        objectInspector->setFormWindow(formWindow);

}

QWidget *QExtDesignerIntegrationPrivate::containerWindow(QWidget *widget) const
{
    // Find the parent window to apply a geometry to.
    while (widget) {
        if (widget->isWindow())
            break;
        if (!qstrcmp(widget->metaObject()->className(), "QMdiSubWindow"))
            break;

        widget = widget->parentWidget();
    }

    return widget;
}

void QExtDesignerIntegrationPrivate::getSelection(Selection &s)
{
    QExtDesignerAbstractFormEditor *core = q->core();
    // Get multiselection from object inspector
    if (QDesignerObjectInspector *designerObjectInspector = qobject_cast<QDesignerObjectInspector *>(core->objectInspector())) {
        designerObjectInspector->getSelection(s);
        // Action editor puts actions that are not on the form yet
        // into the property editor only.
        if (s.empty())
            if (QObject *object = core->propertyEditor()->object())
                s.objects.push_back(object);

    } else {
        // Just in case someone plugs in an old-style object inspector: Emulate selection
        s.clear();
        QExtDesignerAbstractFormWindow *formWindow = core->formWindowManager()->activeFormWindow();
        if (!formWindow)
            return;

        QObject *object = core->propertyEditor()->object();
        if (object->isWidgetType()) {
            QWidget *widget = static_cast<QWidget*>(object);
            QExtDesignerFormWindowCursorInterface *cursor = formWindow->cursor();
            if (cursor->isWidgetSelected(widget)) {
                s.managed.push_back(widget);
            } else {
                s.unmanaged.push_back(widget);
            }
        } else {
            s.objects.push_back(object);
        }
    }
}

QObject *QExtDesignerIntegrationPrivate::propertyEditorObject()
{
    if (QExtDesignerAbstractPropertyEditor *propertyEditor = q->core()->propertyEditor())
        return propertyEditor->object();
    return nullptr;
}

// Load plugins into widget database and factory.
void QExtDesignerIntegrationPrivate::initializePlugins(QExtDesignerAbstractFormEditor *formEditor)
{
    // load the plugins
    qdesigner_internal::WidgetDataBase *widgetDataBase = qobject_cast<qdesigner_internal::WidgetDataBase*>(formEditor->widgetDataBase());
    if (widgetDataBase) {
        widgetDataBase->loadPlugins();
    }

    if (qdesigner_internal::WidgetFactory *widgetFactory = qobject_cast<qdesigner_internal::WidgetFactory*>(formEditor->widgetFactory())) {
        widgetFactory->loadPlugins();
    }

    if (widgetDataBase) {
        widgetDataBase->grabDefaultPropertyValues();
    }
}

void QExtDesignerIntegrationPrivate::updateCustomWidgetPlugins()
{
    QExtDesignerAbstractFormEditor *formEditor = q->core();
    if (QDesignerPluginManager *pm = formEditor->pluginManager())
        pm->registerNewPlugins();

    initializePlugins(formEditor);

    // Do not just reload the last file as the WidgetBox merges the compiled-in resources
    // and $HOME/.designer/widgetbox.xml. This would also double the scratchpad.
    if (QDesignerWidgetBox *wb = qobject_cast<QDesignerWidgetBox*>(formEditor->widgetBox())) {
        const QDesignerWidgetBox::LoadMode oldLoadMode = wb->loadMode();
        wb->setLoadMode(QDesignerWidgetBox::LoadCustomWidgetsOnly);
        wb->load();
        wb->setLoadMode(oldLoadMode);
    }
}

static QString fixHelpClassName(const QString &className)
{
    // ### generalize using the Widget Data Base
    if (className == QStringLiteral("Line"))
        return QStringLiteral("QFrame");
    if (className == QStringLiteral("Spacer"))
        return QStringLiteral("QSpacerItem");
    if (className == QStringLiteral("QLayoutWidget"))
        return QStringLiteral("QLayout");
    return className;
}

// Return class in which the property is defined
static QString classForProperty(QExtDesignerAbstractFormEditor *core,
                                QObject *object,
                                const QString &property)
{
    if (const QExtDesignerPropertySheetExtension *ps = qt_extension<QExtDesignerPropertySheetExtension *>(core->extensionManager(), object)) {
        const int index = ps->indexOf(property);
        if (index >= 0)
            return ps->propertyGroup(index);
    }
    return QString();
}

QString QExtDesignerIntegrationPrivate::contextHelpId() const
{
    QExtDesignerAbstractFormEditor *core = q->core();
    QObject *currentObject = core->propertyEditor()->object();
    if (!currentObject)
        return QString();
    // Return a help index id consisting of "class::property"
    QString className;
    QString currentPropertyName = core->propertyEditor()->currentPropertyName();
    if (!currentPropertyName.isEmpty())
        className = classForProperty(core, currentObject, currentPropertyName);
    if (className.isEmpty()) {
        currentPropertyName.clear(); // We hit on some fake property.
        className = qdesigner_internal::WidgetFactory::classNameOf(core, currentObject);
    }
    QString helpId = fixHelpClassName(className);
    if (!currentPropertyName.isEmpty()) {
        helpId += QStringLiteral("::");
        helpId += currentPropertyName;
    }
    return helpId;
}

} // namespace qdesigner_internal

// -------------- QExtDesignerIntegration
// As of 4.4, the header will be distributed with the Eclipse plugin.

QExtDesignerIntegration::QExtDesignerIntegration(QExtDesignerAbstractFormEditor *core, QObject *parent) :
    QExtDesignerAbstractIntegration(core, parent),
    d(new qdesigner_internal::QExtDesignerIntegrationPrivate(this))
{
    d->initialize();
}

QExtDesignerIntegration::~QExtDesignerIntegration()
{
    QFile f(d->m_gradientsPath);
    if (f.open(QIODevice::WriteOnly)) {
        f.write(QtGradientUtils::saveState(d->m_gradientManager).toUtf8());
        f.close();
    }
}

QString QExtDesignerIntegration::headerSuffix() const
{
    return d->headerSuffix;
}

void QExtDesignerIntegration::setHeaderSuffix(const QString &headerSuffix)
{
    d->headerSuffix = headerSuffix;
}

bool QExtDesignerIntegration::isHeaderLowercase() const
{
    return d->headerLowercase;
}

void QExtDesignerIntegration::setHeaderLowercase(bool headerLowercase)
{
    d->headerLowercase = headerLowercase;
}

QExtDesignerAbstractIntegration::Feature QExtDesignerIntegration::features() const
{
    return d->m_features;
}

void QExtDesignerIntegration::setFeatures(Feature f)
{
    d->m_features = f;
}

QExtDesignerAbstractIntegration::ResourceFileWatcherBehaviour QExtDesignerIntegration::resourceFileWatcherBehaviour() const
{
    return d->m_resourceFileWatcherBehaviour;
}

void QExtDesignerIntegration::setResourceFileWatcherBehaviour(ResourceFileWatcherBehaviour behaviour)
{
    if (d->m_resourceFileWatcherBehaviour != behaviour) {
        d->m_resourceFileWatcherBehaviour = behaviour;
        core()->resourceModel()->setWatcherEnabled(behaviour != QExtDesignerAbstractIntegration::NoResourceFileWatcher);
    }
}

void QExtDesignerIntegration::updateProperty(const QString &name, const QVariant &value, bool enableSubPropertyHandling)
{
    d->updateProperty(name, value, enableSubPropertyHandling);
    emit propertyChanged(core()->formWindowManager()->activeFormWindow(), name, value);
}

void QExtDesignerIntegration::updateProperty(const QString &name, const QVariant &value)
{
    updateProperty(name, value, true);
}

void QExtDesignerIntegration::resetProperty(const QString &name)
{
    d->resetProperty(name);
}

void QExtDesignerIntegration::addDynamicProperty(const QString &name, const QVariant &value)
{
    d->addDynamicProperty(name, value);
}

void QExtDesignerIntegration::removeDynamicProperty(const QString &name)
{
    d->removeDynamicProperty(name);
}

void QExtDesignerIntegration::updateActiveFormWindow(QExtDesignerAbstractFormWindow *)
{
    d->updateSelection();
}

void QExtDesignerIntegration::setupFormWindow(QExtDesignerAbstractFormWindow *formWindow)
{
    d->setupFormWindow(formWindow);
    connect(formWindow, &QExtDesignerAbstractFormWindow::selectionChanged,
            this, &QExtDesignerAbstractIntegration::updateSelection);
}

void QExtDesignerIntegration::updateSelection()
{
    d->updateSelection();
}

QWidget *QExtDesignerIntegration::containerWindow(QWidget *widget) const
{
    return d->containerWindow(widget);
}

// Load plugins into widget database and factory.
void QExtDesignerIntegration::initializePlugins(QExtDesignerAbstractFormEditor *formEditor)
{
    qdesigner_internal::QExtDesignerIntegrationPrivate::initializePlugins(formEditor);
}

void QExtDesignerIntegration::updateCustomWidgetPlugins()
{
    d->updateCustomWidgetPlugins();
}

QExtDesignerAbstractResourceBrowser *QExtDesignerIntegration::createResourceBrowser(QWidget *)
{
    return nullptr;
}

QString QExtDesignerIntegration::contextHelpId() const
{
    return d->contextHelpId();
}

QT_END_NAMESPACE
