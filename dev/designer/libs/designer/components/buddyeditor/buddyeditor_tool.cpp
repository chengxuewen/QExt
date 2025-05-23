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

#include "buddyeditor_tool.h"
#include "buddyeditor.h"

#include <qextDesignerAbstractFormWindow.h>

#include <QtWidgets/qaction.h>

QT_BEGIN_NAMESPACE

using namespace qdesigner_internal;

BuddyEditorTool::BuddyEditorTool(QExtDesignerAbstractFormWindow *formWindow, QObject *parent)
    : QExtDesignerAbstractFormWindowTool(parent),
      m_formWindow(formWindow),
      m_action(new QAction(tr("Edit Buddies"), this))
{
}

BuddyEditorTool::~BuddyEditorTool() = default;

QExtDesignerAbstractFormEditor *BuddyEditorTool::core() const
{
    return m_formWindow->core();
}

QExtDesignerAbstractFormWindow *BuddyEditorTool::formWindow() const
{
    return m_formWindow;
}

bool BuddyEditorTool::handleEvent(QWidget *widget, QWidget *managedWidget, QEvent *event)
{
    Q_UNUSED(widget);
    Q_UNUSED(managedWidget);
    Q_UNUSED(event);

    return false;
}

QWidget *BuddyEditorTool::editor() const
{
    if (!m_editor) {
        Q_ASSERT(formWindow() != nullptr);
        m_editor = new BuddyEditor(formWindow(), nullptr);
        connect(formWindow(), &QExtDesignerAbstractFormWindow::mainContainerChanged,
                m_editor.data(), &BuddyEditor::setBackground);
        connect(formWindow(), &QExtDesignerAbstractFormWindow::changed,
                m_editor.data(), &BuddyEditor::updateBackground);
    }

    return m_editor;
}

void BuddyEditorTool::activated()
{
    m_editor->enableUpdateBackground(true);
}

void BuddyEditorTool::deactivated()
{
    m_editor->enableUpdateBackground(false);
}

QAction *BuddyEditorTool::action() const
{
    return m_action;
}

QT_END_NAMESPACE
