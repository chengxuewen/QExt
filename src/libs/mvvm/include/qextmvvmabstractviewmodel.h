#ifndef QEXTMVVMABSTRACTVIEWMODEL_H
#define QEXTMVVMABSTRACTVIEWMODEL_H

#include <qextmvvmglobal.h>

#include <QAbstractItemModel>



class QEXT_MVVM_API QEXTMvvmAbstractViewModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    QEXTMvvmAbstractViewModel();
};



#endif // QEXTMVVMABSTRACTVIEWMODEL_H
