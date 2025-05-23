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

#ifndef _QEXTDESIGNEREXTENSIONMANAGER_H
#define _QEXTDESIGNEREXTENSIONMANAGER_H

#include <qextDesignerExtension.h>

#include <QtCore/qhash.h>

QT_BEGIN_NAMESPACE

class QObject; // Fool syncqt

class QEXT_DESIGNER_API QExtensionManager: public QObject, public QAbstractExtensionManager
{
    Q_OBJECT
    Q_INTERFACES(QAbstractExtensionManager)
public:
    explicit QExtensionManager(QObject *parent = nullptr);
    ~QExtensionManager();

    void registerExtensions(QAbstractExtensionFactory *factory, const QString &iid = QString()) override;
    void unregisterExtensions(QAbstractExtensionFactory *factory, const QString &iid = QString()) override;

    QObject *extension(QObject *object, const QString &iid) const override;

private:
    using FactoryList = QList<QAbstractExtensionFactory *>;
    typedef QHash<QString, FactoryList> FactoryMap;
    FactoryMap m_extensions;
    FactoryList m_globalExtension;
};

QT_END_NAMESPACE

#endif // _QEXTDESIGNEREXTENSIONMANAGER_H
