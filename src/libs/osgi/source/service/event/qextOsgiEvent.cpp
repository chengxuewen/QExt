/****************************************************************************
** Library: QTK
**
** Copyright (c) German Cancer Research Center,
**     Division of Medical and Biological Informatics
** Copyright (c) chengxuewen <1398831004@qq.com>
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
** http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
****************************************************************************/

#include "qtkevent.h"
#include "qtkeventconstants.h"

#include <QTKCore/QTKException>

QTK_CORE_USE_NAMESPACE

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKEventData : public QSharedData
{
public:
    QTKEventData(const QString &strTopic, const QTKDictionary &properties)
        : m_strTopic(strTopic),
          m_properties(properties)
    {
        this->validateTopicName(strTopic);
        m_properties.insert(QTKEventConstants::EVENT_TOPICS, strTopic);
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

        QString::const_iterator topicEndIter = strTopic.end();
        QChar A('A'), Z('Z'), a('a'), z('z'), zero('0'), nine('9');
        QChar dash('-'), slash('/'), underscore('_');
        for (QString::const_iterator iter = strTopic.begin(); iter < topicEndIter; ++iter) {
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

QTKEvent::QTKEvent()
    : d(0)
{

}

QTKEvent::QTKEvent(const QString &strTopic, const QTKDictionary &properties)
    : d(new QTKEventData(strTopic, properties))
{

}

QTKEvent::QTKEvent(const QTKEvent &event)
    : d(event.d)
{

}

QTKEvent::~QTKEvent()
{

}

bool QTKEvent::isNull() const
{
    return !d;
}

QVariant QTKEvent::getProperty(const QString &strName) const
{
    return d->m_properties[strName];
}

bool QTKEvent::containsProperty(const QString &strName) const
{
    if (QTKEventConstants::EVENT_TOPICS == strName) {
        return true;
    }
    return d->m_properties.contains(strName);
}

QStringList QTKEvent::getPropertyNames() const
{
    return d->m_properties.keys();
}

const QString &QTKEvent::getTopic() const
{
    return d->m_strTopic;
}

bool QTKEvent::matches(const QTKLDAPSearchFilter &filter) const
{
    return filter.matchCase(d->m_properties);
}

QTKEvent &QTKEvent::operator=(const QTKEvent &other)
{
    d = other.d;
    return *this;
}

bool QTKEvent::operator==(const QTKEvent &other) const
{
    if (d == other.d) {
        return true;
    }

    if (d->m_strTopic == other.d->m_strTopic && d->m_properties == other.d->m_properties) {
        return true;
    }

    return false;
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
