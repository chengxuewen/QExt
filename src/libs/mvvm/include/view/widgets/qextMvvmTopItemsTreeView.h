#ifndef _QEXTMVVMTOPITEMSTREEVIEW_H
#define _QEXTMVVMTOPITEMSTREEVIEW_H

#include <qextMvvmItemsTreeView.h>

class QEXTMvvmModel;

//! Widget holding standard QTreeView and intended for displaying all top level
//! items of QEXTMvvmModel.

//! All property items (i.e. "thickness", "color" etc) will be filtered out, top level items
//! (i.e. Layer, MultiLayer, ...) will be presented as simple parent/child tree.

class QEXT_MVVM_API QEXTMvvmTopItemsTreeView : public QEXTMvvmItemsTreeView
{
    Q_OBJECT

public:
    QEXTMvvmTopItemsTreeView(QEXTMvvmModel *model, QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmTopItemsTreeView();
};

#endif // _QEXTMVVMTOPITEMSTREEVIEW_H
