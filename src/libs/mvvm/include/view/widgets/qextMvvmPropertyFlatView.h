#ifndef _QEXTMVVMPROPERTYFLATVIEW_H
#define _QEXTMVVMPROPERTYFLATVIEW_H

#include <qextMvvmGlobal.h>

#include <QWidget>
#include <QScopedPointer>

class QEXTMvvmItem;

//! Widget holding grid layout with editors and intended for displaying all properties of given
//! QEXTMvvmItem.
class QEXTMvvmPropertyFlatViewPrivate;
class QEXT_MVVM_API QEXTMvvmPropertyFlatView : public QWidget
{
    Q_OBJECT
public:
    QEXTMvvmPropertyFlatView(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmPropertyFlatView();

    void setItem(QEXTMvvmItem *item);

protected Q_SLOTS:
    void onDataChange(const QModelIndex &topLeft, const QModelIndex &, const QVector<int> &roles);
    void onRowInserted(const QModelIndex&, int, int);
    void onRowRemoved(const QModelIndex&, int, int);

protected:
    QScopedPointer<QEXTMvvmPropertyFlatViewPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmPropertyFlatView)
    QEXT_DECL_PRIVATE(QEXTMvvmPropertyFlatView)
};


#endif // _QEXTMVVMPROPERTYFLATVIEW_H
