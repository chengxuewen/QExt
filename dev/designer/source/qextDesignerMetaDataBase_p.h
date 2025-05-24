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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of Qt Designer.  This header
// file may change from version to version without notice, or even be removed.
//
// We mean it.
//

#ifndef METADATABASE_H
#define METADATABASE_H

#include <qextDesignerGlobal.h>

#include <qextDesignerAbstractMetaDataBase.h>

#include <QtCore/qhash.h>
#include <QtCore/qstringlist.h>
#include <QtGui/qcursor.h>

QT_BEGIN_NAMESPACE

namespace qdesigner_internal {

class QEXT_DESIGNER_API MetaDataBaseItem: public QExtDesignerMetaDataBaseItemInterface
{
public:
    explicit MetaDataBaseItem(QObject *object);
    ~MetaDataBaseItem() override;

    QString name() const override;
    void setName(const QString &name) override;

    QWidgetList tabOrder() const override;
    void setTabOrder(const QWidgetList &tabOrder) override;

    bool enabled() const override;
    void setEnabled(bool b) override;

    QString customClassName() const;
    void setCustomClassName(const QString &customClassName);

    QStringList fakeSlots() const;
    void setFakeSlots(const QStringList &);

    QStringList fakeSignals() const;
    void setFakeSignals(const QStringList &);

private:
    QObject *m_object;
    QWidgetList m_tabOrder;
    bool m_enabled;
    QString m_customClassName;
    QStringList m_fakeSlots;
    QStringList m_fakeSignals;
};

class QEXT_DESIGNER_API MetaDataBase: public QExtDesignerAbstractMetaDataBase
{
    Q_OBJECT
public:
    explicit MetaDataBase(QExtDesignerAbstractFormEditor *core, QObject *parent = nullptr);
    ~MetaDataBase() override;

    QExtDesignerAbstractFormEditor *core() const override;

    QExtDesignerMetaDataBaseItemInterface *item(QObject *object) const override { return metaDataBaseItem(object); }
    virtual MetaDataBaseItem *metaDataBaseItem(QObject *object) const;
    void add(QObject *object) override;
    void remove(QObject *object) override;

    QObjectList objects() const override;

private slots:
    void slotDestroyed(QObject *object);

private:
    QExtDesignerAbstractFormEditor *m_core;
    typedef QHash<QObject *, MetaDataBaseItem*> ItemMap;
    ItemMap m_items;
};

    // promotion convenience
    QEXT_DESIGNER_API bool promoteWidget(QExtDesignerAbstractFormEditor *core,QWidget *widget,const QString &customClassName);
    QEXT_DESIGNER_API void demoteWidget(QExtDesignerAbstractFormEditor *core,QWidget *widget);
    QEXT_DESIGNER_API bool isPromoted(QExtDesignerAbstractFormEditor *core, QWidget* w);
    QEXT_DESIGNER_API QString promotedCustomClassName(QExtDesignerAbstractFormEditor *core, QWidget* w);
    QEXT_DESIGNER_API QString promotedExtends(QExtDesignerAbstractFormEditor *core, QWidget* w);

} // namespace qdesigner_internal

QT_END_NAMESPACE

#endif // METADATABASE_H
