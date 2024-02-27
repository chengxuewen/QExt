// Copyright (C) 2023-2024 Stdware Collections
// SPDX-License-Identifier: Apache-2.0

#ifndef _QEXTFRAMELESSCONTEXT_COCOA_P_H
#define _QEXTFRAMELESSCONTEXT_COCOA_P_H

#include <private/qextAbstractFramelessContext_p.h>

#include <QScopedPointer>

class QExtCocoaFramelessContext : public QExtAbstractFramelessContext
{
    Q_OBJECT
public:
    QExtCocoaFramelessContext();
    ~QExtCocoaFramelessContext() QEXT_OVERRIDE;

    QString key() const QEXT_OVERRIDE;
    void virtualHook(int id, void *data) QEXT_OVERRIDE;

    QVariant windowAttribute(const QString &key) const QEXT_OVERRIDE;

protected:
    void winIdChanged() QEXT_OVERRIDE;
    bool windowAttributeChanged(const QString &key, const QVariant &attribute,
                                const QVariant &oldAttribute) QEXT_OVERRIDE;

protected:
    WId windowId = 0;

    QScopedPointer<QExtFramelessSharedEventFilter> cocoaWindowEventFilter;
};

#endif // _QEXTFRAMELESSCONTEXT_COCOA_P_H
