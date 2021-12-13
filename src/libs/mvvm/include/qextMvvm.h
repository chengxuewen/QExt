#ifndef _QEXTMVVM_H
#define _QEXTMVVM_H

#include <qextMvvmGlobal.h>

#include <QObject>

class QEXT_MVVM_API QEXTMvvm : public QObject
{
    Q_OBJECT
public:
    explicit QEXTMvvm(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvm();
};

#endif // _QEXTMVVM_H
