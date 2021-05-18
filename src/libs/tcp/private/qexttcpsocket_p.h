#ifndef QEXTTCPSOCKET_P_H
#define QEXTTCPSOCKET_P_H

#include <qextobject_p.h>
#include <qextid.h>

#include <qexttcpglobal.h>



class QEXTTcpSocket;
class QEXT_TCP_API QEXTTcpSocketPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpSocketPrivate(QEXTTcpSocket *qq);
    ~QEXTTcpSocketPrivate();

    QEXTId m_identityId;
    static int sm_id;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpSocket)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpSocketPrivate)
};



#endif // QEXTTCPSOCKET_P_H
