#ifndef _QEXTMVVMVIEWMODELPROPERTYFLATVIEWMODEL_H
#define _QEXTMVVMVIEWMODELPROPERTYFLATVIEWMODEL_H

#include <qextMvvmViewModel.h>

namespace ModelView
{

//! View model to show content of SessionModel in Qt widgets.
//! Only property items are shown, also hides inactive items of GroupProperty.

class QEXT_MVVM_API QEXTMvvmPropertyFlatViewModel : public QEXTMvvmViewModel
{
    Q_OBJECT
public:
    QEXTMvvmPropertyFlatViewModel(QEXTMvvmSessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // _QEXTMVVMVIEWMODELPROPERTYFLATVIEWMODEL_H
