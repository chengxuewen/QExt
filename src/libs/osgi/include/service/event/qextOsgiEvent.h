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

#ifndef QTKEVENT_H
#define QTKEVENT_H

#include "../../qtkpluginframework_global.h"
#include "../../qtkldapsearchfilter.h"

#include <QMap>
#include <QVariant>
#include <QStringList>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKEventData;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKEvent class
 * A CTK event.
 *
 * <code>ctkEvent</code> objects are delivered to <code>ctkEventHandler</code>
 * or Qt slots which subscribe to the topic of the event.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKEvent
{
public:
    /**
     * @brief QTKEvent
     * Default constructor for use with the Qt meta object system.
     */
    QTKEvent();

    /**
     * @brief QTKEvent
     * Constructs an event.
     *
     * @param strTopic The topic of the event.
     * @param properties The event's properties (may be empty).
     * @throws ctkInvalidArgumentException If topic is not a valid topic name.
     */
    QTKEvent(const QString &strTopic, const QTKDictionary &properties = QTKDictionary());
    QTKEvent(const QTKEvent &event);
    ~QTKEvent();

    /**
     * @brief isNull
     * Can be used to check if this ctkEvent instance is valid,
     * or if it has been constructed using the default constructor.
     *
     * @return <code>true</code> if this event object is valid,
     *         <code>false</code> otherwise.
     */
    bool isNull() const;

    /**
     * @brief getProperty
     * Retrieve the value of an event property. The event topic may be retrieved
     * with the property name &quot;event.topics&quot;.
     *
     * @param strName the name of the property to retrieve
     * @return The value of the property, or an invalid QVariant if not found.
     */
    QVariant getProperty(const QString &strName) const;

    /**
     * @brief containsProperty
     * Indicate the presence of an event property. The event topic is present
     * using the property name &quot;event.topics&quot;.
     *
     * @param strName The name of the property.
     * @return <code>true</code> if a property with the specified name is in the
     *         event. This property may have an invalid QVariant value.
     *         <code>false</code> otherwise.
     */
    bool containsProperty(const QString &strName) const;

    /**
     * @brief getPropertyNames
     * Returns a list of this event's property names. The list will include the
     * event topic property name &quot;event.topics&quot;.
     *
     * @return A non-empty list with one element per property.
     */
    QStringList getPropertyNames() const;

    /**
     * @brief getTopic
     * Returns the topic of this event.
     *
     * @return The topic of this event.
     */
    const QString &getTopic() const;

    /**
     * @brief matches
     * Tests this event's properties against the given filter using a case
     * sensitive match.
     *
     * @param filter The filter to test.
     * @return true If this event's properties match the filter, false
     *         otherwise.
     */
    bool matches(const QTKLDAPSearchFilter &filter) const;

    QTKEvent &operator=(const QTKEvent &other);

    /**
     * @brief operator ==
     * Compares this <code>ctkEvent</code> object to another object.
     *
     * <p>
     * An event is considered to be <b>equal to</b> another event if the topic
     * is equal and the properties are equal.
     *
     * @param other The <code>ctkEvent</code> object to be compared.
     * @return <code>true</code> if <code>other</code> is equal to
     *         this object; <code>false</code> otherwise.
     */
    bool operator==(const QTKEvent &other) const;

private:
    QSharedDataPointer<QTKEventData> d;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

Q_DECLARE_METATYPE(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKEvent)

#endif // QTKEVENT_H
