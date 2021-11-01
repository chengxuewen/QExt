#ifndef QTKEACHANNEL_P_H
#define QTKEACHANNEL_P_H

class QTKEARunnable;

struct QTKEAChannel
{
    virtual ~QTKEAChannel() {}

    virtual void put(QTKEARunnable *pItem) = 0;

    virtual bool offer(QTKEARunnable *pItem, long lMsecs) = 0;

    virtual QTKEARunnable *take() = 0;

    virtual QTKEARunnable *poll(long lMsecs) = 0;

    virtual QTKEARunnable *peek() const = 0;

};

#endif // QTKEACHANNEL_P_H
