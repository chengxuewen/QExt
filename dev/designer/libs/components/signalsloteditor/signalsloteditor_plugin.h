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

#ifndef _SIGNALSLOTEDITOR_PLUGIN_H
#define _SIGNALSLOTEDITOR_PLUGIN_H

#include "signalsloteditor_global.h"

#include "../../sdk/abstractformeditorplugin.h"

#include <QtCore/qpointer.h>
#include <QtCore/qhash.h>

QT_BEGIN_NAMESPACE

class QExtDesignerAbstractFormWindow;

namespace qdesigner_internal {

class SignalSlotEditorTool;

class QT_SIGNALSLOTEDITOR_EXPORT SignalSlotEditorPlugin: public QObject, public QExtDesignerFormEditorPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QExtDesignerFormEditorPluginInterface" FILE "signalsloteditor.json")
    Q_INTERFACES(QExtDesignerFormEditorPluginInterface)
public:
    SignalSlotEditorPlugin();
    ~SignalSlotEditorPlugin() override;

    bool isInitialized() const override;
    void initialize(QExtDesignerAbstractFormEditor *core) override;
    QAction *action() const override;

    QExtDesignerAbstractFormEditor *core() const override;

public slots:
    void activeFormWindowChanged(QExtDesignerAbstractFormWindow *formWindow);

private slots:
    void addFormWindow(QExtDesignerAbstractFormWindow *formWindow);
    void removeFormWindow(QExtDesignerAbstractFormWindow *formWindow);

private:
    QPointer<QExtDesignerAbstractFormEditor> m_core;
    QHash<QExtDesignerAbstractFormWindow*, SignalSlotEditorTool*> m_tools;
    bool m_initialized = false;
    QAction *m_action = nullptr;
};

}  // namespace qdesigner_internal

QT_END_NAMESPACE

#endif // _SIGNALSLOTEDITOR_PLUGIN_H
