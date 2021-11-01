#include "qtkbusevent.h"
#include "qtkeventdefinitions.h"

#include <QTKCore/QTKException>

QTK_CORE_USE_NAMESPACE

class QTKBusEventData : public QSharedData
{
public:
    QTKBusEventData(const QString &strTopic, const QTKDictionary &properties)
        : m_strTopic(strTopic),
          m_properties(properties)
    {
        m_properties.insert(TOPIC, strTopic);
    }

    QTKBusEventData(QString strTopic, int iEventType, int iSignatureType, QObject *pObjectPointer, QString strSignature)
        : m_strTopic(strTopic)
    {
        m_properties.insert(TOPIC, strTopic);
        m_properties.insert(TYPE, static_cast<int>(iEventType));
        m_properties.insert(SIGTYPE, static_cast<int>(iSignatureType));
        QVariant var;
        var.setValue(pObjectPointer);
        m_properties.insert(OBJECT, var);
        m_properties.insert(SIGNATURE, strSignature);
    }

    static void validateTopicName(const QString &strTopic) {
        if (strTopic.isEmpty()) {
            throw QTKInvalidArgumentException("empty topic");
        }

        // Can't start or end with a '/' but anywhere else is okay
        // Can't have "//" as that implies empty token
        if (strTopic.startsWith("/") || strTopic.endsWith("/") || strTopic.contains("//")) {
            throw QTKInvalidArgumentException(QString("invalid topic: %1").arg(strTopic));
        }

        QString::const_iterator topicEnd = strTopic.end();
        QChar A('A'), Z('Z'), a('a'), z('z'), zero('0'), nine('9');
        QChar dash('-'), slash('/'), underscore('_');
        for (QString::const_iterator iter = strTopic.begin(); iter < topicEnd; ++iter) {
            QChar c(*iter);
            if ((A <= c) && (c <= Z)) {
                continue;
            }
            if ((a <= c) && (c <= z)) {
                continue;
            }
            if ((zero <= c) && (c <= nine)) {
                continue;
            }
            if ((c == underscore) || (c == dash) || (c == slash)) {
                continue;
            }
            throw QTKInvalidArgumentException(QString("invalid topic: %1").arg(strTopic));
        }
    }

    const QString m_strTopic;
    QTKDictionary m_properties;
};


QTKBusEvent::QTKBusEvent()
    : d(0)
{

}

QTKBusEvent::QTKBusEvent(const QString &strTopic, const QTKDictionary &properties)
    : d(new QTKBusEventData(strTopic, properties))
{

}

QTKBusEvent::QTKBusEvent(QString strTopic, int iEventType, int iSignatureType, QObject *pbjectPointer, QString strSignature)
    : d(new QTKBusEventData(strTopic, iEventType, iSignatureType, pbjectPointer, strSignature))
{

}

QTKBusEvent::QTKBusEvent(const QTKBusEvent &event)
    : QTKEvent(event),
      d(event.d)
{

}

QTKBusEvent::~QTKBusEvent()
{
}

QTKBusEvent& QTKBusEvent::operator=(const QTKBusEvent &event)
{
    d = event.d;
    return *this;
}

QVariant &QTKBusEvent::operator[](QString strKey)
{
    return (d->m_properties)[strKey];
}

int QTKBusEvent::eventType() const
{
    return static_cast<int>((d->m_properties).value("EventType").toInt());
}

QString QTKBusEvent::eventTopic() const
{
    return (d->m_properties).value(TOPIC).toString();
}

bool QTKBusEvent::isEventLocal() const
{
    int iEventType = (d->m_properties).value(TYPE).toInt();
    return iEventType == 0; //is local
}

void QTKBusEvent::setEventType(int iEventType)
{
    (d->m_properties).insert(TYPE, static_cast<int>(iEventType));
}

void QTKBusEvent::setEventTopic(QString strTopic)
{
    (d->m_properties).insert(TOPIC, strTopic);
}
