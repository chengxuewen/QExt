#ifndef _QEXTMVVMALLITEMSTREEVIEW_H
#define _QEXTMVVMALLITEMSTREEVIEW_H

#include <qextMvvmItemsTreeView.h>


class QEXTMvvmModel;

//! Widget holding standard QTreeView and intended for displaying all items of QEXTMvvmModel.

class QEXT_MVVM_API QEXTMvvmAllItemsTreeView : public QEXTMvvmItemsTreeView
{
    Q_OBJECT

public:
    QEXTMvvmAllItemsTreeView(QEXTMvvmModel* model, QWidget* parent = nullptr);
    ~QEXTMvvmAllItemsTreeView() QEXT_DECL_OVERRIDE;
};


#endif // _QEXTMVVMALLITEMSTREEVIEW_H
