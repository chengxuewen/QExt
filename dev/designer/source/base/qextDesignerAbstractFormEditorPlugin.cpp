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

#include <qextDesignerAbstractFormEditorPlugin.h>

QT_BEGIN_NAMESPACE

/*!
    \internal
    \class QExtDesignerFormEditorPluginInterface
    \brief The QExtDesignerFormEditorPluginInterface class provides an interface that is used to
    manage plugins for Qt Designer's form editor component.
    \inmodule QtDesigner

    \sa QExtDesignerAbstractFormEditor
*/

/*!
    \fn virtual QExtDesignerFormEditorPluginInterface::~QExtDesignerFormEditorPluginInterface()

    Destroys the plugin interface.
*/

/*!
    \fn virtual bool QExtDesignerFormEditorPluginInterface::isInitialized() const = 0

    Returns true if the plugin interface is initialized; otherwise returns false.
*/

/*!
    \fn virtual void QExtDesignerFormEditorPluginInterface::initialize(QExtDesignerAbstractFormEditor *core) = 0

    Initializes the plugin interface for the specified \a core interface.
*/

/*!
    \fn virtual QAction *QExtDesignerFormEditorPluginInterface::action() const = 0

    Returns the action associated with this interface.
*/

/*!
    \fn virtual QExtDesignerAbstractFormEditor *QExtDesignerFormEditorPluginInterface::core() const = 0

    Returns the core form editor interface associated with this component.
*/

QT_END_NAMESPACE
