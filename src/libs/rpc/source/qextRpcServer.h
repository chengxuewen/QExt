#ifndef _QEXTRPCSERVER_H
#define _QEXTRPCSERVER_H

#include <qextRpcGlobal.h>

#include <QObject>

class QEXT_RPC_API QExtRpcServer : public QObject
{
    Q_OBJECT
public:
    explicit QExtRpcServer(QObject *parent = QEXT_NULLPTR);

signals:

};

#endif // _QEXTRPCSERVER_H
