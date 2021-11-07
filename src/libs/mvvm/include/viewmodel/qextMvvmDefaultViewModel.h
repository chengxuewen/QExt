#ifndef _QEXTMVVMDEFAULTVIEWMODEL_H
#define _QEXTMVVMDEFAULTVIEWMODEL_H

#include <qextMvvmGlobal.h>
#include <qextMvvmViewModel.h>

#include <QObject>

//! View model to show content of QEXTMvvmModel in Qt widgets: two column tree with label/data.

//! Provides two column tree with label/data, with one-to-one child/parent
//! correspondence as in the original QEXTMvvmModel.

class QEXT_MVVM_API QEXTMvvmDefaultViewModel : public QEXTMvvmViewModel
{
    Q_OBJECT
public:
    QEXTMvvmDefaultViewModel(QEXTMvvmModel *model, QObject *parent = QEXT_DECL_NULLPTR);
};

#endif // _QEXTMVVMDEFAULTVIEWMODEL_H
