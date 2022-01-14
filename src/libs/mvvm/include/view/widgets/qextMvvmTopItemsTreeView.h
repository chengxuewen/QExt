#ifndef _QEXTMVVMWIDGETSTOPITEMSTREEVIEW_H
#define _QEXTMVVMWIDGETSTOPITEMSTREEVIEW_H

#include <qextMvvmItemsTreeView.h>

namespace ModelView
{

class QEXTMvvmSessionModel;

//! Widget holding standard QTreeView and intended for displaying all top level
//! items of SessionModel.

//! All property items (i.e. "thickness", "color" etc) will be filtered out, top level items
//! (i.e. Layer, MultiLayer, ...) will be presented as simple parent/child tree.

class QEXT_MVVM_API QEXTMvvmTopItemsTreeView : public QEXTMvvmItemsTreeView
{
    Q_OBJECT

public:
    QEXTMvvmTopItemsTreeView(QEXTMvvmSessionModel* model, QWidget* parent = nullptr);
    ~QEXTMvvmTopItemsTreeView();
};

} // namespace ModelView

#endif // _QEXTMVVMWIDGETSTOPITEMSTREEVIEW_H
