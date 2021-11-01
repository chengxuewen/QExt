#ifndef QTKEAINTERRUPTIBLETHREAD_P_H
#define QTKEAINTERRUPTIBLETHREAD_P_H

#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include <QAtomicInt>
#include <QRunnable>

class QTKEARunnable : public QRunnable
{
public:
    QTKEARunnable() : m_iRef(0) {}
    bool autoDelete() const { return m_iRef != -1; }
    void setAutoDelete(bool bAutoDelete) { m_iRef = bAutoDelete ? 0 : -1; }

    int m_iRef;
};

class QTKEAScopedRunnableReference
{
public:
    QTKEAScopedRunnableReference(QTKEARunnable* runnable)
        : m_pRunnable(runnable)
    {
        ++runnable->m_iRef;
    }

    ~QTKEAScopedRunnableReference()
    {
        if (!--m_pRunnable->m_iRef) {
            delete m_pRunnable;
        }
    }

private:
    QTKEARunnable *m_pRunnable;
};

/**
 * @brief The QTKEAInterruptibleThread class
 * A QThread subclass which can be interrupted when waiting on a wait condition.
 */
class QTKEAInterruptibleThread : public QThread, public QMutex
{
    Q_OBJECT

public:
    QTKEAInterruptibleThread(QTKEARunnable *pCommand = nullptr, QObject *pParent = nullptr);

    static QTKEAInterruptibleThread *currentThread();

    void wait(QMutex *pMutex, QWaitCondition *pWaitCond, unsigned long ulTime = ULONG_MAX);

    void join();

    void interrupt();

    static bool interrupted();

    bool isInterrupted() const;

    void run();

private:
    QTKEARunnable *m_pCommand;
    bool m_bDeleteCmd;

    QAtomicPointer<QWaitCondition> m_currWaitCond;
    mutable QAtomicInt m_interrupted;
    mutable QAtomicInt m_isWaiting;
};

#endif // QTKEAINTERRUPTIBLETHREAD_P_H
