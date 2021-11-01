#include "qtktopicregistry.h"

using namespace qtkeventbus;

QTKTopicRegistry* QTKTopicRegistry::instance()
{
    static QTKTopicRegistry instanceTopicRegistry;
    return &instanceTopicRegistry;
}

QTKTopicRegistry::QTKTopicRegistry()
{
}

void QTKTopicRegistry::shutdown()
{
    m_mapTopic.clear();
}

bool QTKTopicRegistry::registerTopic(const QString strTopic, const QObject *pOwner)
{
    if(strTopic.isEmpty() || pOwner == nullptr) {
        return false;
    }
    if(m_mapTopic.contains(strTopic)) {
        //topic already registered
        const QObject *pObj = m_mapTopic.value(strTopic, nullptr);
        QString strClassName = pObj->metaObject()->className();
        qWarning() << QObject::tr("Topic %1 already owned by %2").arg(strTopic, strClassName);
        return false;
    }
    m_mapTopic.insert(strTopic,pOwner);
    return true;
}

bool QTKTopicRegistry::unregisterTopic(const QString strTopic)
{
    bool bResult = false;
    if(m_mapTopic.contains(strTopic)) {
        if (m_mapTopic.remove(strTopic) > 0) {
            bResult = true;
        }
    }
    return bResult;
}

const QObject *QTKTopicRegistry::owner(const QString strTopic) const
{
    return m_mapTopic.value(strTopic, nullptr);
}

bool QTKTopicRegistry::isTopicRegistered(const QString strTopic) const
{
    return m_mapTopic.contains(strTopic);
}

void QTKTopicRegistry::dump()
{
    QHash<QString, const QObject*>::const_iterator iter = m_mapTopic.constBegin();
    while (iter != m_mapTopic.constEnd()) {
        const QObject *pObj = iter.value();
        QString strKey =  iter.key();
        QString strName = pObj->metaObject()->className();
        qDebug() << "Topic: " << strKey << "   Owner: "  << strName;
        ++iter;
    }
}
