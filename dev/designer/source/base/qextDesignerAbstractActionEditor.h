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

#ifndef _QEXTDESIGNERABSTRACTACTIONEDITOR_H
#define _QEXTDESIGNERABSTRACTACTIONEDITOR_H

#include <qextDesignerGlobal.h>

#include <QWidget>

class QExtDesignerAbstractFormEditor;
class QExtDesignerAbstractFormWindow;

class QEXT_DESIGNER_API QExtDesignerAbstractActionEditor: public QWidget
{
    Q_OBJECT
public:
    explicit QExtDesignerAbstractActionEditor(QWidget *parent, Qt::WindowFlags flags = Qt::WindowFlags());
    ~QExtDesignerAbstractActionEditor() QEXT_OVERRIDE;

    virtual QExtDesignerAbstractFormEditor *core() const;

    virtual void manageAction(QAction *action) = 0;
    virtual void unmanageAction(QAction *action) = 0;

public Q_SLOTS:
    virtual void setFormWindow(QExtDesignerAbstractFormWindow *formWindow) = 0;
};

#endif // _QEXTDESIGNERABSTRACTACTIONEDITOR_H
