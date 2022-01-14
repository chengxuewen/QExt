#ifndef _QEXTMVVMVIEWMODELTOPITEMSVIEWMODEL_H
#define _QEXTMVVMVIEWMODELTOPITEMSVIEWMODEL_H

#include <qextMvvmViewModel.h>

namespace ModelView
{

//! View model to show top level items of SessionModel in Qt trees and tables.
//! All property items (i.e. "thickness", "color" etc) will be filtered out, top level items
//! (i.e. Layer, MultiLayer, ...) will be presented as simple parent/child tree.

class QEXT_MVVM_API QEXTMvvmTopItemsViewModel : public QEXTMvvmViewModel
{
    Q_OBJECT
public:
    QEXTMvvmTopItemsViewModel(QEXTMvvmSessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // _QEXTMVVMVIEWMODELTOPITEMSVIEWMODEL_H
