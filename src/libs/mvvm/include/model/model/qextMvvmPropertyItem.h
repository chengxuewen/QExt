#ifndef _QEXTMVVMMODELPROPERTYITEM_H
#define _QEXTMVVMMODELPROPERTYITEM_H

#include <qextMvvmSessionItem.h>

namespace ModelView
{

class QEXTMvvmRealLimits;

//! Item to carry concrete editable entity (e.g. 'double' value with limits).
//! Intended for use as a child or CompountItem, not expected to have own children.

class QEXT_MVVM_API QEXTMvvmPropertyItem : public QEXTMvvmSessionItem
{
public:
    QEXTMvvmPropertyItem();

    QEXTMvvmPropertyItem* setDisplayName(const std::string& name) override;

    QEXTMvvmPropertyItem* setLimits(const QEXTMvvmRealLimits& value);
};

} // namespace ModelView

#endif // _QEXTMVVMMODELPROPERTYITEM_H
