#ifndef _QEXTMVVMVIEWMODELPROPERTYTABLEVIEWMODEL_H
#define _QEXTMVVMVIEWMODELPROPERTYTABLEVIEWMODEL_H

#include <qextMvvmViewModel.h>

namespace ModelView
{

//! View model to show content of SessionModel in Qt widgets: all item properties as a table row.

//! Intended to show registered properties of items in table-like view.
//! Registered properties will form columns of the table, top level items will form table rows.

class QEXT_MVVM_API QEXTMvvmPropertyTableViewModel : public QEXTMvvmViewModel
{
    Q_OBJECT
public:
    QEXTMvvmPropertyTableViewModel(QEXTMvvmSessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // _QEXTMVVMVIEWMODELPROPERTYTABLEVIEWMODEL_H
