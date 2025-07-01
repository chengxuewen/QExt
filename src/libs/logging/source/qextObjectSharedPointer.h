/******************************************************************************
 *
 * This file is part of Log4Qt library.
 *
 * Copyright (C) 2007 - 2020 Log4Qt contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#ifndef LOG4QT_LOG4QTSHAREDPTR_H
#define LOG4QT_LOG4QTSHAREDPTR_H

#include <QSharedPointer>
#include <QObject>

#include <type_traits>

template<typename T>
class QExtObjectSharedPointer : public QSharedPointer<T>
{
public:
    QExtObjectSharedPointer(T *ptr)
        : QSharedPointer<T>(ptr, &T::deleteLater)
    {
        static_assert(std::is_base_of<QObject, T>::value, "Need a QObject derived class here");
    }

    QExtObjectSharedPointer() : QSharedPointer<T>() { }
    QExtObjectSharedPointer(const QSharedPointer<T> &other) : QSharedPointer<T>(other) { }
    QExtObjectSharedPointer(const QWeakPointer<T> &other) : QSharedPointer<T>(other) { }
};

#endif // LOG4QT_LOG4QTSHAREDPTR_H
