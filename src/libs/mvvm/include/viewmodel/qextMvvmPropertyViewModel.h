#ifndef _QEXTMVVMPROPERTYVIEWMODEL_H
#define _QEXTMVVMPROPERTYVIEWMODEL_H

#include <qextMvvmGlobal.h>
#include <qextMvvmViewModel.h>

#include <QObject>

//! View model to show content of QEXTMvvmModel in Qt widgets.
//! Only property items are shown, also hides inactive items of GroupProperty.

class QEXT_MVVM_API QEXTMvvmPropertyViewModel : public QEXTMvvmViewModel
{
    Q_OBJECT
public:
    QEXTMvvmPropertyViewModel(QEXTMvvmModel *model, QObject *parent = QEXT_DECL_NULLPTR);
};

#endif // _QEXTMVVMPROPERTYVIEWMODEL_H
