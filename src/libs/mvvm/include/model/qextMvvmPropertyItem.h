#ifndef _QEXTMVVMPROPERTYITEM_H
#define _QEXTMVVMPROPERTYITEM_H

#include <qextMvvmItem.h>


class QEXTMvvmRealLimits;

//! Item to carry concrete editable entity (e.g. 'double' value with limits).
//! Intended for use as a child or CompountItem, not expected to have own children.

class QEXT_MVVM_API QEXTMvvmPropertyItem : public QEXTMvvmItem
{
public:
    QEXTMvvmPropertyItem();

    QEXTMvvmPropertyItem* setDisplayName(const QString& name) QEXT_DECL_OVERRIDE;

    QEXTMvvmPropertyItem* setLimits(const QEXTMvvmRealLimits& value);
};

#endif // _QEXTMVVMPROPERTYITEM_H
