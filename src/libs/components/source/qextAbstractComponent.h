#ifndef _QEXTABSTRACTCOMPONENTS_H
#define _QEXTABSTRACTCOMPONENTS_H

#include <qextComponentsGlobal.h>

#include <QObject>

class QEXT_COMPONENTS_API QExtComponents : public QObject
{
    Q_OBJECT

public:
    explicit QExtComponents(QObject *parent = QEXT_NULLPTR);

signals:
};

#endif // _QEXTABSTRACTCOMPONENTS_H
