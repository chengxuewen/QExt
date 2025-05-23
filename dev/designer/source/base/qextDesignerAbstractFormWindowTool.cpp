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

#include <qextDesignerAbstractFormWindowTool.h>

QT_BEGIN_NAMESPACE

/*!
    \class QExtDesignerAbstractFormWindowTool

    \brief The QExtDesignerAbstractFormWindowTool class provides an
    interface that enables tools to be used on items in a form window.

    \inmodule QtDesigner

    \internal
*/

/*!
*/
QExtDesignerAbstractFormWindowTool::QExtDesignerAbstractFormWindowTool(QObject *parent)
    : QObject(parent)
{
}

/*!
*/
QExtDesignerAbstractFormWindowTool::~QExtDesignerAbstractFormWindowTool() = default;

/*!
    \fn virtual QExtDesignerAbstractFormEditor *QExtDesignerAbstractFormWindowTool::core() const = 0
*/

/*!
    \fn virtual QExtDesignerAbstractFormWindow *QExtDesignerAbstractFormWindowTool::formWindow() const = 0
*/

/*!
    \fn virtual QWidget *QExtDesignerAbstractFormWindowTool::editor() const = 0
*/

/*!
    \fn virtual QAction *QExtDesignerAbstractFormWindowTool::action() const = 0
*/

/*!
    \fn virtual void QExtDesignerAbstractFormWindowTool::activated() = 0
*/

/*!
    \fn virtual void QExtDesignerAbstractFormWindowTool::deactivated() = 0
*/

/*!
    \fn virtual void QExtDesignerAbstractFormWindowTool::saveToDom(DomUI*, QWidget*) {
*/

/*!
    \fn virtual void QExtDesignerAbstractFormWindowTool::loadFromDom(DomUI*, QWidget*) {
*/

/*!
    \fn virtual bool QExtDesignerAbstractFormWindowTool::handleEvent(QWidget *widget, QWidget *managedWidget, QEvent *event) = 0
*/

QT_END_NAMESPACE
