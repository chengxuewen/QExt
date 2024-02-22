#include <qextMVCView.h>
#include <qextMVCInterface.h>
#include <qextMVCMediator.h>

QExtMVCView *QExtMVCView::m_instance = QEXT_NULLPTR;

QExtMVCView::QExtMVCView()
{
}

QExtMVCView *QExtMVCView::instance()
{
    if (!m_instance)
    {
        m_instance = new QExtMVCView();
    }

    return m_instance;
}

void QExtMVCView::registerObserver(QExtMVCObserverInterface *observer, const QString &notificationName)
{
    if (observer == NULL)
    {
        return;
    }

    if (m_observerMap.contains(notificationName))
    {
        QList<QExtMVCObserverInterface *> observers = m_observerMap[notificationName];
        if (observers.contains(observer))
        {
            return;
        }

        observers.append(observer);

        m_observerMap[notificationName] = observers;
    }
    else
    {
        QList<QExtMVCObserverInterface *> observers;

        observers.append(observer);

        m_observerMap[notificationName] = observers;
    }
}

void QExtMVCView::removeObserver(const QString &notificationName)
{
    if (!m_observerMap.contains(notificationName))
    {
        return;
    }

    m_observerMap.remove(notificationName);
}

void QExtMVCView::notifyObservers(QExtMVCNotificationInterface *notification)
{
    if (!m_observerMap.contains(notification->getNotificationName()))
    {
        return;
    }

    QList<QExtMVCObserverInterface *> observers = m_observerMap[notification->getNotificationName()];

    int count = observers.size();
    for (int i = 0; i < count; i++)
    {
        observers.at(i)->notifyObserver(notification);
    }
}

void QExtMVCView::registerMediator(QExtMVCMediatorInterface *mediator)
{
    if (mediator == NULL)
    {
        return;
    }

    m_mediatorMap[mediator->getMediatorName()] = mediator;

    QList<QString> notificationInterests = mediator->getListNotificationInterests();

    int count = notificationInterests.size();
    for (int i = 0; i < count; i++)
    {
        registerObserver((QExtMVCObserverInterface *)((QExtMVCMediator *)mediator),
                         notificationInterests.at(i));
    }
}

QExtMVCMediatorInterface *QExtMVCView::retrieveMediator(const QString &mediatorName)
{
    if (!hasMediator(mediatorName))
    {
        return NULL;
    }

    return m_mediatorMap[mediatorName];
}

bool QExtMVCView::hasMediator(const QString &mediatorName)
{
    return m_mediatorMap.contains(mediatorName);
}

void QExtMVCView::removeMediator(const QString &mediatorName)
{
    m_mediatorMap.remove(mediatorName);
}
