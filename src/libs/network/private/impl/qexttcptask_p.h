#ifndef QEXTTCPTASK_P_H
#define QEXTTCPTASK_P_H

#include <qextnetworkglobal.h>
#include <qexttcptaskbase_p.h>

class QEXTTcpTask;
class QEXT_NETWORK_API QEXTTcpTaskPrivate : public QEXTTcpTaskBasePrivate
{
public:
    explicit QEXTTcpTaskPrivate(QEXTTcpTask *qq);
    ~QEXTTcpTaskPrivate();

    QScopedPointer<QEXTTcpPacketBase> m_packet;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpTask)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskPrivate)
};

#endif // QEXTTCPTASK_P_H
