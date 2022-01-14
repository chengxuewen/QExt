#ifndef _QEXTMVVMWIDGETSPROPERTYFLATVIEW_H
#define _QEXTMVVMWIDGETSPROPERTYFLATVIEW_H

#include <qextMvvmGlobal.h>

#include <QWidget>

#include <memory>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Widget holding grid layout with editors and intended for displaying all properties of given
//! QEXTMvvmSessionItem.

class QEXT_MVVM_API QEXTMvvmPropertyFlatView : public QWidget
{
    Q_OBJECT

public:
    QEXTMvvmPropertyFlatView(QWidget* parent = nullptr);
    ~QEXTMvvmPropertyFlatView();

    void setItem(QEXTMvvmSessionItem* item);

private:
    struct PropertyFlatViewImpl;
    std::unique_ptr<PropertyFlatViewImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMWIDGETSPROPERTYFLATVIEW_H
