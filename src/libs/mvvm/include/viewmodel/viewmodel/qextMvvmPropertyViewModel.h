#ifndef _QEXTMVVMVIEWMODELPROPERTYVIEWMODEL_H
#define _QEXTMVVMVIEWMODELPROPERTYVIEWMODEL_H

#include <qextMvvmViewModel.h>

namespace ModelView
{

//! View model to show content of SessionModel in Qt widgets.
//! Only property items are shown, also hides inactive items of GroupProperty.

class QEXT_MVVM_API QEXTMvvmPropertyViewModel : public QEXTMvvmViewModel
{
    Q_OBJECT
public:
    QEXTMvvmPropertyViewModel(QEXTMvvmSessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // _QEXTMVVMVIEWMODELPROPERTYVIEWMODEL_H
