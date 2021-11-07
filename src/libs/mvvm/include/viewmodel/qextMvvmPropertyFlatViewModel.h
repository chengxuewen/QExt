#ifndef _QEXTMVVMPROPERTYFLATVIEWMODEL_H
#define _QEXTMVVMPROPERTYFLATVIEWMODEL_H

#include <qextMvvmGlobal.h>
#include <qextMvvmViewModel.h>

#include <QObject>

//! View model to show content of QEXTMvvmModel in Qt widgets.
//! Only property items are shown, also hides inactive items of GroupProperty.

class QEXT_MVVM_API QEXTMvvmPropertyFlatViewModel : public QEXTMvvmViewModel
{
    Q_OBJECT
public:
    QEXTMvvmPropertyFlatViewModel(QEXTMvvmModel *model, QObject *parent = QEXT_DECL_NULLPTR);
};

#endif // _QEXTMVVMPROPERTYFLATVIEWMODEL_H
