// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_VECTORITEM_H
#define MVVM_STANDARDITEMS_VECTORITEM_H

#include <qextMvvmCompoundItem.h>

namespace ModelView {

//! Vector item with three x,y,z property items.

class QEXT_MVVM_API QExtMvvmVectorItem : public QExtMvvmCompoundItem {
public:
    static constexpr const char *P_X = "P_X";
    static constexpr const char *P_Y = "P_Y";
    static constexpr const char *P_Z = "P_Z";

    QExtMvvmVectorItem();

    void activate() override;

    double x() const;
    void setX(double value);

    double y() const;
    void setY(double value);

    double z() const;
    void setZ(double value);

private:
    void update_label();
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_VECTORITEM_H
