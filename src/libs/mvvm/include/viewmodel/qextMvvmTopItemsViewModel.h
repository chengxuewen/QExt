#ifndef _QEXTMVVMTOPITEMSVIEWMODEL_H
#define _QEXTMVVMTOPITEMSVIEWMODEL_H

#include <qextMvvmGlobal.h>
#include <qextMvvmViewModel.h>

#include <QObject>

//! View model to show top level items of QEXTMvvmModel in Qt trees and tables.
//! All property items (i.e. "thickness", "color" etc) will be filtered out, top level items
//! (i.e. Layer, MultiLayer, ...) will be presented as simple parent/child tree.

class QEXT_MVVM_API QEXTMvvmTopItemsViewModel : public QEXTMvvmViewModel
{
    Q_OBJECT
public:
    QEXTMvvmTopItemsViewModel(QEXTMvvmModel *model, QObject *parent = QEXT_DECL_NULLPTR);
};


#endif // _QEXTMVVMTOPITEMSVIEWMODEL_H
