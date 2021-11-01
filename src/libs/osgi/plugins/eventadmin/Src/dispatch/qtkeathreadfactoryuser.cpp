#include "qtkeathreadfactoryuser_p.h"

#include <QRunnable>

QTKEAThreadFactoryUser::DefaultThread::DefaultThread(QTKEARunnable *pCommand)
    : m_pCommand(pCommand)
{
}

void QTKEAThreadFactoryUser::DefaultThread::run()
{
    const bool bAutoDelete = m_pCommand->autoDelete();
    m_pCommand->run();
    if (bAutoDelete && !--m_pCommand->m_iRef) {
        delete m_pCommand;
    }
}


QTKEAInterruptibleThread *QTKEAThreadFactoryUser::DefaultThreadFactory::newThread(QTKEARunnable *pCommand)
{
    return new DefaultThread(pCommand);
}


QTKEAThreadFactoryUser::QTKEAThreadFactoryUser()
    : m_mutex(QMutex::Recursive),
      m_pThreadFactory(new DefaultThreadFactory())
{

}

QTKEAThreadFactoryUser::~QTKEAThreadFactoryUser()
{
    delete m_pThreadFactory;
}

QTKEAThreadFactory *QTKEAThreadFactoryUser::setThreadFactory(QTKEAThreadFactory *pFactory)
{
    QMutexLocker lock(&m_mutex);
    QTKEAThreadFactory *pOld = m_pThreadFactory;
    m_pThreadFactory = pFactory;
    return pOld;
}

QTKEAThreadFactory *QTKEAThreadFactoryUser::getThreadFactory()
{
    return m_pThreadFactory;
}
