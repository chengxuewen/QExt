#ifndef QTKEATHREADFACTORYUSER_P_H
#define QTKEATHREADFACTORYUSER_P_H

#include "qtkeathreadfactory_p.h"
#include "qtkeainterruptiblethread_p.h"

#include <QMutex>

class QTKEAThreadFactoryUser
{
protected:
    class DefaultThread : public QTKEAInterruptibleThread
    {
    public:
        DefaultThread(QTKEARunnable *pCommand);

        void run();

    private:
        QTKEARunnable *m_pCommand;
        bool m_bDeleteCmd;
    };

    class DefaultThreadFactory : public QTKEAThreadFactory
    {
    public:
        QTKEAInterruptibleThread *newThread(QTKEARunnable *pCommand);
    };

    QTKEAThreadFactoryUser();
    ~QTKEAThreadFactoryUser();

    QTKEAThreadFactory *setThreadFactory(QTKEAThreadFactory *pFactory);

    QTKEAThreadFactory *getThreadFactory();

    mutable QMutex m_mutex;
    QTKEAThreadFactory *m_pThreadFactory;
};

#endif // QTKEATHREADFACTORYUSER_P_H
