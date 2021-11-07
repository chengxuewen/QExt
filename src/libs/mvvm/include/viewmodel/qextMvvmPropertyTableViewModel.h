#ifndef _QEXTMVVMPROPERTYTABLEVIEWMODEL_H
#define _QEXTMVVMPROPERTYTABLEVIEWMODEL_H

#include <qextMvvmGlobal.h>
#include <qextMvvmViewModel.h>

#include <QObject>

//! View model to show content of QEXTMvvmModel in Qt widgets: all item properties as a table row.

//! Intended to show registered properties of items in table-like view.
//! Registered properties will form columns of the table, top level items will form table rows.

class QEXT_MVVM_API QEXTMvvmPropertyTableViewModel : public QEXTMvvmViewModel
{
    Q_OBJECT
public:
    QEXTMvvmPropertyTableViewModel(QEXTMvvmModel *model, QObject *parent = QEXT_DECL_NULLPTR);
};

#endif // _QEXTMVVMPROPERTYTABLEVIEWMODEL_H
