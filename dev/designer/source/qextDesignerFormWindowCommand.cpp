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


#include <private/qextDesignerFormWindowCommand_p.h>
#include <private/qextDesignerObjectInspector_p.h>
#include <private/qextDesignerLayout_p.h>

#include <qextDesignerAbstractFormEditor.h>
#include <qextDesignerAbstractFormWindow.h>
#include <qextDesignerAbstractActionEditor.h>
#include <qextDesignerAbstractMetaDataBase.h>
#include <qextDesignerAbstractObjectInspector.h>
#include <qextDesignerPropertySheetExtension.h>
#include <qextDesignerAbstractPropertyEditor.h>
#include <qextDesignerExtensionManager.h>

#include <QtCore/qvariant.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>

QT_BEGIN_NAMESPACE

namespace qdesigner_internal {

// ---- QDesignerFormWindowCommand ----
QDesignerFormWindowCommand::QDesignerFormWindowCommand(const QString &description,
                                                       QExtDesignerAbstractFormWindow *formWindow,
                                                       QUndoCommand *parent)
    : QUndoCommand(description, parent),
      m_formWindow(formWindow)
{
}

QExtDesignerAbstractFormWindow *QDesignerFormWindowCommand::formWindow() const
{
    return m_formWindow;
}

QExtDesignerAbstractFormEditor *QDesignerFormWindowCommand::core() const
{
    if (QExtDesignerAbstractFormWindow *fw = formWindow())
        return fw->core();

    return nullptr;
}

void QDesignerFormWindowCommand::undo()
{
    cheapUpdate();
}

void QDesignerFormWindowCommand::redo()
{
    cheapUpdate();
}

void QDesignerFormWindowCommand::cheapUpdate()
{
    if (core()->objectInspector())
        core()->objectInspector()->setFormWindow(formWindow());

    if (core()->actionEditor())
        core()->actionEditor()->setFormWindow(formWindow());
}

QExtDesignerPropertySheetExtension* QDesignerFormWindowCommand::propertySheet(QObject *object) const
{
    return  qt_extension<QExtDesignerPropertySheetExtension*>(formWindow()->core()->extensionManager(), object);
}

void QDesignerFormWindowCommand::updateBuddies(QExtDesignerAbstractFormWindow *form,
                                               const QString &old_name,
                                               const QString &new_name)
{
    QExtensionManager* extensionManager = form->core()->extensionManager();

    const auto label_list = form->findChildren<QLabel*>();
    if (label_list.isEmpty())
        return;

    const QString buddyProperty = QStringLiteral("buddy");
    const QByteArray oldNameU8 = old_name.toUtf8();
    const QByteArray newNameU8 = new_name.toUtf8();

    for (QLabel *label : label_list) {
        if (QExtDesignerPropertySheetExtension* sheet =
                qt_extension<QExtDesignerPropertySheetExtension*>(extensionManager, label)) {
            const int idx = sheet->indexOf(buddyProperty);
            if (idx != -1) {
                const QByteArray oldBuddy = sheet->property(idx).toByteArray();
                if (oldBuddy == oldNameU8)
                    sheet->setProperty(idx, newNameU8);
            }
        }
    }
}

void QDesignerFormWindowCommand::selectUnmanagedObject(QObject *unmanagedObject)
{
    // Keep selection in sync
    if (QDesignerObjectInspector *oi = qobject_cast<QDesignerObjectInspector *>(core()->objectInspector())) {
        oi->clearSelection();
        oi->selectObject(unmanagedObject);
    }
    core()->propertyEditor()->setObject(unmanagedObject);
}

} // namespace qdesigner_internal

QT_END_NAMESPACE
