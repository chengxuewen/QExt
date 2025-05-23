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

// sdk
#include <qextDesignerAbstractMetaDataBase.h>

QT_BEGIN_NAMESPACE

/*!
    \class QExtDesignerAbstractMetaDataBase
    \brief The QExtDesignerAbstractMetaDataBase class provides an interface to Qt Designer's
    object meta database.
    \inmodule QtDesigner
    \internal
*/

/*!
    Constructs an interface to the meta database with the given \a parent.
*/
QExtDesignerAbstractMetaDataBase::QExtDesignerAbstractMetaDataBase(QObject *parent)
    : QObject(parent)
{
}

/*!
    Destroys the interface to the meta database.
*/
QExtDesignerAbstractMetaDataBase::~QExtDesignerAbstractMetaDataBase() = default;

/*!
    \fn QExtDesignerMetaDataBaseItemInterface *QExtDesignerAbstractMetaDataBase::item(QObject *object) const

    Returns the item in the meta database associated with the given \a object.
*/

/*!
    \fn void QExtDesignerAbstractMetaDataBase::add(QObject *object)

    Adds the specified \a object to the meta database.
*/

/*!
    \fn void QExtDesignerAbstractMetaDataBase::remove(QObject *object)

    Removes the specified \a object from the meta database.
*/

/*!
    \fn QList<QObject*> QExtDesignerAbstractMetaDataBase::objects() const

    Returns the list of objects that have corresponding items in the meta database.
*/

/*!
    \fn QExtDesignerAbstractFormEditor *QExtDesignerAbstractMetaDataBase::core() const

    Returns the core interface that is associated with the meta database.
*/


// Doc: Interface only

/*!
    \class QExtDesignerMetaDataBaseItemInterface
    \brief The QExtDesignerMetaDataBaseItemInterface class provides an interface to individual
    items in Qt Designer's meta database.
    \inmodule QtDesigner
    \internal

    This class allows individual items in \QD's meta-data database to be accessed and modified.
    Use the QExtDesignerAbstractMetaDataBase class to change the properties of the database itself.
*/

/*!
    \fn QExtDesignerMetaDataBaseItemInterface::~QExtDesignerMetaDataBaseItemInterface()

    Destroys the item interface to the meta-data database.
*/

/*!
    \fn QString QExtDesignerMetaDataBaseItemInterface::name() const

    Returns the name of the item in the database.

    \sa setName()
*/

/*!
    \fn void QExtDesignerMetaDataBaseItemInterface::setName(const QString &name)

    Sets the name of the item to the given \a name.

    \sa name()
*/

/*!
    \fn QList<QWidget*> QExtDesignerMetaDataBaseItemInterface::tabOrder() const

    Returns a list of widgets in the order defined by the form's tab order.

    \sa setTabOrder()
*/


/*!
    \fn void QExtDesignerMetaDataBaseItemInterface::setTabOrder(const QList<QWidget*> &tabOrder)

    Sets the tab order in the form using the list of widgets defined by \a tabOrder.

    \sa tabOrder()
*/


/*!
    \fn bool QExtDesignerMetaDataBaseItemInterface::enabled() const

    Returns whether the item is enabled.

    \sa setEnabled()
*/

/*!
    \fn void QExtDesignerMetaDataBaseItemInterface::setEnabled(bool enabled)

    If \a enabled is true, the item is enabled; otherwise it is disabled.

    \sa enabled()
*/

QT_END_NAMESPACE
