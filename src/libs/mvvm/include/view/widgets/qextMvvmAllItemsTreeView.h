#ifndef _QEXTMVVMWIDGETSALLITEMSTREEVIEW_H
#define _QEXTMVVMWIDGETSALLITEMSTREEVIEW_H

#include <qextMvvmItemsTreeView.h>

namespace ModelView
{

class QEXTMvvmSessionModel;

//! Widget holding standard QTreeView and intended for displaying all items of SessionModel.

class QEXT_MVVM_API QEXTMvvmAllItemsTreeView : public QEXTMvvmItemsTreeView
{
    Q_OBJECT

public:
    QEXTMvvmAllItemsTreeView(QEXTMvvmSessionModel* model, QWidget* parent = nullptr);
    ~QEXTMvvmAllItemsTreeView() override;
};

} // namespace ModelView

#endif // _QEXTMVVMWIDGETSALLITEMSTREEVIEW_H
