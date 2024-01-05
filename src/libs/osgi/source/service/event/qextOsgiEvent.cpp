/*=============================================================================

  Library: CTK

  Copyright (c) German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#include <qext/osgi/service/event/qextOsgiEvent.h>
#include <qext/osgi/service/event/qextOsgiEventConstants.h>
#include <qextException.h>

class QExtOsgiEventData : public QSharedData
{

public:
    QExtOsgiEventData(const QString& topic, const QExtOsgiDictionary& properties)
        : topic(topic), properties(properties)
    {
        validateTopicName(topic);
        this->properties.insert(QExtOsgiEventConstants::EVENT_TOPIC, topic);
    }

    static void validateTopicName(const QString& topic)
    {
        if (topic.isEmpty())
        {
            throw QExtInvalidArgumentException("empty topic");
        }

        // Can't start or end with a '/' but anywhere else is okay
        // Can't have "//" as that implies empty token
        if (topic.startsWith("/") || topic.endsWith("/") ||
            topic.contains("//"))
        {
            throw QExtInvalidArgumentException(QString("invalid topic: %1").arg(topic));
        }

        QString::const_iterator topicEnd = topic.end();
        QChar A('A'), Z('Z'), a('a'), z('z'), zero('0'), nine('9');
        QChar dash('-'), slash('/'), underscore('_');
        for (QString::const_iterator i = topic.begin(); i < topicEnd; ++i)
        {
            QChar c(*i);
            if ((A <= c) && (c <= Z)) continue;
            if ((a <= c) && (c <= z)) continue;
            if ((zero <= c) && (c <= nine)) continue;
            if ((c == underscore) || (c == dash) || (c == slash)) continue;
            throw QExtInvalidArgumentException(QString("invalid topic: %1").arg(topic));
        }
    }

    const QString topic;
    QExtOsgiDictionary properties;

};

//----------------------------------------------------------------------------
QExtOsgiEvent::QExtOsgiEvent()
    : d(0)
{

}

//----------------------------------------------------------------------------
QExtOsgiEvent::QExtOsgiEvent(const QString& topic, const QExtOsgiDictionary& properties)
    : d(new QExtOsgiEventData(topic, properties))
{

}

//----------------------------------------------------------------------------
// This is fast thanks to implicit sharing
QExtOsgiEvent::QExtOsgiEvent(const QExtOsgiEvent &event)
    : d(event.d)
{

}

//----------------------------------------------------------------------------
QExtOsgiEvent::~QExtOsgiEvent()
{
}

//----------------------------------------------------------------------------
bool QExtOsgiEvent::isNull() const
{
    return !d;
}

//----------------------------------------------------------------------------
QExtOsgiEvent& QExtOsgiEvent::operator=(const QExtOsgiEvent& other)
{
    d = other.d;
    return *this;
}

//----------------------------------------------------------------------------
bool QExtOsgiEvent::operator==(const QExtOsgiEvent& other) const
{
    if (d == other.d)
        return true;

    if (d->topic == other.d->topic &&
        d->properties == other.d->properties)
        return true;

    return false;
}

//----------------------------------------------------------------------------
QVariant QExtOsgiEvent::getProperty(const QString& name) const
{
    return d->properties[name];
}

//----------------------------------------------------------------------------
bool QExtOsgiEvent::containsProperty(const QString& name) const
{
    if (QExtOsgiEventConstants::EVENT_TOPIC == name)
    {
        return true;
    }
    return d->properties.contains(name);
}

//----------------------------------------------------------------------------
QStringList QExtOsgiEvent::getPropertyNames() const
{
    return d->properties.keys();
}

//----------------------------------------------------------------------------
const QString& QExtOsgiEvent::getTopic() const
{
    return d->topic;
}

//----------------------------------------------------------------------------
bool QExtOsgiEvent::matches(const QExtOsgiLDAPSearchFilter& filter) const
{
    return filter.matchCase(d->properties);
}
