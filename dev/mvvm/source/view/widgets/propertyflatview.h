// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_WIDGETS_PROPERTYFLATVIEW_H
#define MVVM_WIDGETS_PROPERTYFLATVIEW_H

#include <qextMvvmGlobal.h>
#include <QWidget>
#include <memory>

namespace ModelView {

class QExtMvvmSessionItem;

//! Widget holding grid layout with editors and intended for displaying all properties of given
//! QExtMvvmSessionItem.

class QEXT_MVVM_API QExtMvvmPropertyFlatView : public QWidget {
    Q_OBJECT

public:
    QExtMvvmPropertyFlatView(QWidget* parent = nullptr);
    ~QExtMvvmPropertyFlatView();

    void setItem(QExtMvvmSessionItem* item);

private:
    struct PropertyFlatViewImpl;
    QExtUniquePointer<PropertyFlatViewImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_WIDGETS_PROPERTYFLATVIEW_H
