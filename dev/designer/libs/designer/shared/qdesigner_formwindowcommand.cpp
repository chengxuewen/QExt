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


#include "qdesigner_formwindowcommand_p.h"
#include "qdesigner_objectinspector_p.h"
#include "layout_p.h"

#include <../sdk/abstractformeditor.h>
#include <../sdk/abstractformwindow.h>
#include <../sdk/abstractobjectinspector.h>
#include <../sdk/abstractactioneditor.h>
#include <../sdk/abstractmetadatabase.h>
#include <../sdk/propertysheet.h>
#include <../sdk/abstractpropertyeditor.h>
#include <../extension/qextensionmanager.h>

#include <QtCore/qvariant.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>

QT_BEGIN_NAMESPACE

namespace qdesigner_internal {

// ---- QDesignerFormWindowCommand ----
QDesignerFormWindowCommand::QDesignerFormWindowCommand(const QString &description,
                                                       QDesignerFormWindowInterface *formWindow,
                                                       QUndoCommand *parent)
    : QUndoCommand(description, parent),
      m_formWindow(formWindow)
{
}

QDesignerFormWindowInterface *QDesignerFormWindowCommand::formWindow() const
{
    return m_formWindow;
}

QDesignerFormEditorInterface *QDesignerFormWindowCommand::core() const
{
    if (QDesignerFormWindowInterface *fw = formWindow())
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

QDesignerPropertySheetExtension* QDesignerFormWindowCommand::propertySheet(QObject *object) const
{
    return  qt_extension<QDesignerPropertySheetExtension*>(formWindow()->core()->extensionManager(), object);
}

void QDesignerFormWindowCommand::updateBuddies(QDesignerFormWindowInterface *form,
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
        if (QDesignerPropertySheetExtension* sheet =
                qt_extension<QDesignerPropertySheetExtension*>(extensionManager, label)) {
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
