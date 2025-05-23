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

#include <qextDesignerExtraInfoExtension.h>

QT_BEGIN_NAMESPACE

/*!
    \class QExtDesignerExtraInfoExtension
    \brief The QExtDesignerExtraInfoExtension class provides extra information about a widget in
    Qt Designer.
    \inmodule QtDesigner
    \internal
*/

/*!
    Returns the path to the working directory used by this extension.*/
QString QExtDesignerExtraInfoExtension::workingDirectory() const
{
    return m_workingDirectory;
}

/*!
    Sets the path to the working directory used by the extension to \a workingDirectory.*/
void QExtDesignerExtraInfoExtension::setWorkingDirectory(const QString &workingDirectory)
{
    m_workingDirectory = workingDirectory;
}

/*!
    \fn virtual QExtDesignerExtraInfoExtension::~QExtDesignerExtraInfoExtension()

    Destroys the extension.
*/

/*!
    \fn virtual QExtDesignerAbstractFormEditor *QExtDesignerExtraInfoExtension::core() const = 0

    \omit
    ### Description required
    \endomit
*/

/*!
    \fn virtual QWidget *QExtDesignerExtraInfoExtension::widget() const = 0

    Returns the widget described by this extension.
*/

/*!
    \fn virtual bool QExtDesignerExtraInfoExtension::saveUiExtraInfo(DomUI *ui) = 0

    Saves the information about the user interface specified by \a ui, and returns true if
    successful; otherwise returns false.
*/

/*!
    \fn virtual bool QExtDesignerExtraInfoExtension::loadUiExtraInfo(DomUI *ui) = 0

    Loads extra information about the user interface specified by \a ui, and returns true if
    successful; otherwise returns false.
*/

/*!
    \fn virtual bool QExtDesignerExtraInfoExtension::saveWidgetExtraInfo(DomWidget *widget) = 0

    Saves the information about the specified \a widget, and returns true if successful;
    otherwise returns false.
*/

/*!
    \fn virtual bool QExtDesignerExtraInfoExtension::loadWidgetExtraInfo(DomWidget *widget) = 0

    Loads extra information about the specified \a widget, and returns true if successful;
    otherwise returns false.
*/

QT_END_NAMESPACE
