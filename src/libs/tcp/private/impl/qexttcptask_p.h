#ifndef QEXTTCPTASK_P_H
#define QEXTTCPTASK_P_H

#include <qexttcpglobal.h>
#include <qexttcpabstracttask_p.h>



class QEXTTcpTask;
class QEXT_TCP_API QEXTTcpTaskPrivate : public QEXTTcpAbstractTaskPrivate
{
public:
    explicit QEXTTcpTaskPrivate(QEXTTcpTask *qq);
    ~QEXTTcpTaskPrivate();

    QScopedPointer<QEXTTcpAbstractPacket> m_packet;

private:
    QEXT_DECL_PUBLIC(QEXTTcpTask)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskPrivate)
};



#endif // QEXTTCPTASK_P_H
