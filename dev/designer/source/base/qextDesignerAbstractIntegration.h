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

#ifndef _QEXTDESIGNERABSTRACTINTEGRATION_H
#define _QEXTDESIGNERABSTRACTINTEGRATION_H

#include <qextDesignerGlobal.h>

#include <QtCore/qobject.h>
#include <QtCore/qscopedpointer.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qflags.h>

QT_BEGIN_NAMESPACE

class QExtDesignerAbstractFormWindow;
class QExtDesignerAbstractFormEditor;
class QExtDesignerAbstractIntegrationPrivate;
class QExtDesignerAbstractResourceBrowser;
class QVariant;
class QWidget;

namespace qdesigner_internal {
class QExtDesignerIntegrationPrivate;
}

class QEXT_DESIGNER_API QExtDesignerAbstractIntegration: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString headerSuffix READ headerSuffix WRITE setHeaderSuffix)
    Q_PROPERTY(bool headerLowercase READ isHeaderLowercase WRITE setHeaderLowercase)

public:
    enum ResourceFileWatcherBehaviour
    {
        NoResourceFileWatcher,
        ReloadResourceFileSilently,
        PromptToReloadResourceFile // Default
    };

    enum FeatureFlag
    {
        ResourceEditorFeature = 0x1,
        SlotNavigationFeature = 0x2,
        DefaultWidgetActionFeature = 0x4,
        DefaultFeature = ResourceEditorFeature | DefaultWidgetActionFeature
    };
    Q_DECLARE_FLAGS(Feature, FeatureFlag)

    explicit QExtDesignerAbstractIntegration(QExtDesignerAbstractFormEditor *core, QObject *parent = nullptr);
    virtual ~QExtDesignerAbstractIntegration();

    QExtDesignerAbstractFormEditor *core() const;

    virtual QWidget *containerWindow(QWidget *widget) const = 0;

    // Create a resource browser specific to integration. Language integration takes precedence
    virtual QExtDesignerAbstractResourceBrowser *createResourceBrowser(QWidget *parent = nullptr) = 0;
    virtual QString headerSuffix() const = 0;
    virtual void setHeaderSuffix(const QString &headerSuffix) = 0;

    virtual bool isHeaderLowercase() const = 0;
    virtual void setHeaderLowercase(bool headerLowerCase) = 0;

    virtual Feature features() const = 0;
    bool hasFeature(Feature f) const;

    virtual ResourceFileWatcherBehaviour resourceFileWatcherBehaviour() const = 0;
    virtual void setResourceFileWatcherBehaviour(ResourceFileWatcherBehaviour behaviour) = 0;

    virtual QString contextHelpId() const = 0;

    void emitObjectNameChanged(QExtDesignerAbstractFormWindow *formWindow, QObject *object,
                               const QString &newName, const QString &oldName);
    void emitNavigateToSlot(const QString &objectName, const QString &signalSignature, const QStringList &parameterNames);
    void emitNavigateToSlot(const QString &slotSignature);
    void emitHelpRequested(const QString &manual, const QString &document);

Q_SIGNALS:
    void propertyChanged(QExtDesignerAbstractFormWindow *formWindow, const QString &name, const QVariant &value);
    void objectNameChanged(QExtDesignerAbstractFormWindow *formWindow, QObject *object, const QString &newName, const QString &oldName);
    void helpRequested(const QString &manual, const QString &document);

    void navigateToSlot(const QString &objectName, const QString &signalSignature, const QStringList &parameterNames);
    void navigateToSlot(const QString &slotSignature);

public Q_SLOTS:
    virtual void setFeatures(Feature f) = 0;
    virtual void updateProperty(const QString &name, const QVariant &value, bool enableSubPropertyHandling) = 0;
    virtual void updateProperty(const QString &name, const QVariant &value) = 0;
    // Additional signals of designer property editor
    virtual void resetProperty(const QString &name) = 0;
    virtual void addDynamicProperty(const QString &name, const QVariant &value) = 0;
    virtual void removeDynamicProperty(const QString &name) = 0;

    virtual void updateActiveFormWindow(QExtDesignerAbstractFormWindow *formWindow) = 0;
    virtual void setupFormWindow(QExtDesignerAbstractFormWindow *formWindow) = 0;
    virtual void updateSelection() = 0;
    virtual void updateCustomWidgetPlugins() = 0;

private:
    QScopedPointer<QExtDesignerAbstractIntegrationPrivate> d;
};

class QEXT_DESIGNER_API QExtDesignerIntegration: public QExtDesignerAbstractIntegration
{
    Q_OBJECT
public:
    explicit QExtDesignerIntegration(QExtDesignerAbstractFormEditor *core, QObject *parent = nullptr);
    virtual ~QExtDesignerIntegration();

    QString headerSuffix() const override;
    void setHeaderSuffix(const QString &headerSuffix) override;

    bool isHeaderLowercase() const override;
    void setHeaderLowercase(bool headerLowerCase) override;

    Feature features() const override;
    virtual void setFeatures(Feature f) override;

    ResourceFileWatcherBehaviour resourceFileWatcherBehaviour() const override;
    void setResourceFileWatcherBehaviour(ResourceFileWatcherBehaviour behaviour) override;

    virtual QWidget *containerWindow(QWidget *widget) const override;

    // Load plugins into widget database and factory.
    static void initializePlugins(QExtDesignerAbstractFormEditor *formEditor);

    // Create a resource browser specific to integration. Language integration takes precedence
    QExtDesignerAbstractResourceBrowser *createResourceBrowser(QWidget *parent = nullptr) override;

    QString contextHelpId() const override;

    void updateProperty(const QString &name, const QVariant &value, bool enableSubPropertyHandling) override;
    void updateProperty(const QString &name, const QVariant &value) override;
    // Additional signals of designer property editor
    void resetProperty(const QString &name) override;
    void addDynamicProperty(const QString &name, const QVariant &value) override;
    void removeDynamicProperty(const QString &name) override;

    void updateActiveFormWindow(QExtDesignerAbstractFormWindow *formWindow) override;
    void setupFormWindow(QExtDesignerAbstractFormWindow *formWindow) override;
    void updateSelection() override;
    void updateCustomWidgetPlugins() override;

private:
    QScopedPointer<qdesigner_internal::QExtDesignerIntegrationPrivate> d;
};

QT_END_NAMESPACE

#endif // _QEXTDESIGNERABSTRACTINTEGRATION_H
