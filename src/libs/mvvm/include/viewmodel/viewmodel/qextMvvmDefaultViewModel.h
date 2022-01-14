#ifndef _QEXTMVVMVIEWMODELDEFAULTVIEWMODEL_H
#define _QEXTMVVMVIEWMODELDEFAULTVIEWMODEL_H

#include <qextMvvmViewModel.h>

namespace ModelView
{

//! View model to show content of SessionModel in Qt widgets: two column tree with label/data.

//! Provides two column tree with label/data, with one-to-one child/parent
//! correspondence as in the original SessionModel.

class QEXT_MVVM_API QEXTMvvmDefaultViewModel : public QEXTMvvmViewModel
{
    Q_OBJECT
public:
    QEXTMvvmDefaultViewModel(QEXTMvvmSessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // _QEXTMVVMVIEWMODELDEFAULTVIEWMODEL_H
