// Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
// SPDX-License-Identifier: BSD-3-Clause

#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include <QWidget>

#include <qextPropertyBrowser.h>

class ObjectControllerPrivate;
class ObjectController : public QWidget
{
    Q_OBJECT
public:
    ObjectController(QWidget *parent = 0);
    ~ObjectController();

    void setObject(QObject *object);
    QObject *object() const;

private Q_SLOTS:
    void onValueChanged(QExtProperty *property, const QVariant &value);

private:
    ObjectControllerPrivate *dd_ptr;
    Q_DECLARE_PRIVATE_D(dd_ptr, ObjectController)
    Q_DISABLE_COPY(ObjectController)
};

#endif
