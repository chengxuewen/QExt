#ifndef _QEXTPEPROPERTY_P_H
#define _QEXTPEPROPERTY_P_H

#include <qextPEProperty.h>

#include <QSet>

class QExtPEPropertyPrivate
{
    QExtPEProperty * const q_ptr;
    QEXT_DECLARE_PUBLIC(QExtPEProperty)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEPropertyPrivate)
public:
    QExtPEPropertyPrivate(QExtPEProperty *q, QExtPEAbstractPropertyManager *manager);
    virtual ~QExtPEPropertyPrivate() {}

    QExtPEAbstractPropertyManager * const mManager;

    QSet<QExtPEProperty *> mParentItems;
    QList<QExtPEProperty *> mSubItems;

    QString mWhatsThis;
    QString mStatusTip;
    QString mToolTip;
    QString mName;

    bool mStyleChanged;
    bool mModified;
    bool mEnabled;
};

class QExtPEPropertyItemPrivate
{
    QExtPEPropertyItem * const q_ptr;
    QEXT_DECLARE_PUBLIC(QExtPEPropertyItem)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEPropertyItemPrivate)
public:
    QExtPEPropertyItemPrivate(QExtPEPropertyItem *q,
                              QExtPEAbstractPropertyEditor *browser,
                              QExtPEPropertyItem *parent,
                              QExtPEProperty *property)
        : q_ptr(q)
        , mBrowser(browser)
        , mParent(parent)
        , mProperty(property)
    {
    }

    void addChild(QExtPEPropertyItem *index, QExtPEPropertyItem *after);
    void removeChild(QExtPEPropertyItem *index);

    QExtPEAbstractPropertyEditor * const mBrowser;
    QList<QExtPEPropertyItem *> mChildren;
    QExtPEPropertyItem *mParent;
    QExtPEProperty *mProperty;
};

#endif // _QEXTPEPROPERTY_P_H
