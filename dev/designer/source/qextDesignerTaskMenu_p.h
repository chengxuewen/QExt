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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of Qt Designer.  This header
// file may change from version to version without notice, or even be removed.
//
// We mean it.
//

#ifndef QDESIGNER_TASKMENU_H
#define QDESIGNER_TASKMENU_H

#include <qextDesignerGlobal.h>
#include <qextDesignerTaskMenuExtension.h>
#include <private/qextDesignerExtensionFactory_p.h>

#include <QtGui/qwindowdefs.h>

#include <QtCore/qobject.h>
#include <QtCore/qpointer.h>
#include <QtCore/qlist.h>

QT_BEGIN_NAMESPACE

class QExtDesignerAbstractFormWindow;
class QExtDesignerAbstractFormEditor;

namespace qdesigner_internal {
class QDesignerTaskMenuPrivate;

class QEXT_DESIGNER_API QDesignerTaskMenu: public QObject, public QExtDesignerTaskMenuExtension
{
    Q_OBJECT
    Q_INTERFACES(QExtDesignerTaskMenuExtension)
public:
    QDesignerTaskMenu(QWidget *widget, QObject *parent);
    ~QDesignerTaskMenu() override;

    QWidget *widget() const;

    QList<QAction*> taskActions() const override;

    enum PropertyMode { CurrentWidgetMode, MultiSelectionMode };

    static bool isSlotNavigationEnabled(const QExtDesignerAbstractFormEditor *core);
    static void navigateToSlot(QExtDesignerAbstractFormEditor *core, QObject *o,
                               const QString &defaultSignal = QString());

protected:

    QExtDesignerAbstractFormWindow *formWindow() const;
    void changeTextProperty(const QString &propertyName, const QString &windowTitle, PropertyMode pm, Qt::TextFormat desiredFormat);

    QAction *createSeparator();

    /* Retrieve the list of objects the task menu is supposed to act on. Note that a task menu can be invoked for
     * an unmanaged widget [as of 4.5], in which case it must not use the cursor selection,
     * but the unmanaged selection of the object inspector. */
    QObjectList applicableObjects(const QExtDesignerAbstractFormWindow *fw, PropertyMode pm) const;
    QWidgetList applicableWidgets(const QExtDesignerAbstractFormWindow *fw, PropertyMode pm) const;

    void setProperty(QExtDesignerAbstractFormWindow *fw, PropertyMode pm, const QString &name, const QVariant &newValue);

private slots:
    void changeObjectName();
    void changeToolTip();
    void changeWhatsThis();
    void changeStyleSheet();
    void createMenuBar();
    void addToolBar(Qt::ToolBarArea area);
    void createStatusBar();
    void removeStatusBar();
    void containerFakeMethods();
    void slotNavigateToSlot();
    void applySize(QAction *a);
    void slotLayoutAlignment();

private:
    QDesignerTaskMenuPrivate *d;
};

using QDesignerTaskMenuFactory = ExtensionFactory<QExtDesignerTaskMenuExtension, QWidget, QDesignerTaskMenu>;

} // namespace qdesigner_internal

QT_END_NAMESPACE

#endif // QDESIGNER_TASKMENU_H
