/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
** Copyright (C) 2007 - 2020 Log4Qt contributors
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#ifndef _QEXTBINARYLOGGINGEVENT_H
#define _QEXTBINARYLOGGINGEVENT_H

#include <qextLoggingEvent.h>

class QEXT_LOGGING_API QExtBinaryLoggingEvent : public QExtLoggingEvent
{
public:
    QExtBinaryLoggingEvent();
    QExtBinaryLoggingEvent(const QExtLogger *logger,
                       QExtLogLevel level,
                       const QByteArray &message);
    QExtBinaryLoggingEvent(const QExtLogger *logger,
                       QExtLogLevel level,
                       const QByteArray &message,
                       qint64 timeStamp);
    QExtBinaryLoggingEvent(const QExtLogger *logger,
                       QExtLogLevel level,
                       const QByteArray &message,
                       const QString &ndc,
                       const QHash<QString, QString> &properties,
                       const QString &threadName,
                       qint64 timeStamp);
    QByteArray binaryMessage() const;

    QString toString() const;

    static QString binaryMarker();

private:
    QByteArray mBinaryMessage;

#ifndef QT_NO_DATASTREAM
    // Needs to be friend to stream objects
    friend QEXT_LOGGING_API QDataStream &operator<<(QDataStream &out, const QExtBinaryLoggingEvent &loggingEvent);
    friend QEXT_LOGGING_API QDataStream &operator>>(QDataStream &in, QExtBinaryLoggingEvent &loggingEvent);
#endif // QT_NO_DATASTREAM
};

#ifndef QT_NO_DATASTREAM
QEXT_LOGGING_API QDataStream &operator<<(QDataStream &out, const QExtBinaryLoggingEvent &loggingEvent);
QEXT_LOGGING_API QDataStream &operator>>(QDataStream &in, QExtBinaryLoggingEvent &loggingEvent);
#endif // QT_NO_DATASTREAM

Q_DECLARE_METATYPE(QExtBinaryLoggingEvent)
Q_DECLARE_TYPEINFO(QExtBinaryLoggingEvent, Q_MOVABLE_TYPE);

#endif // _QEXTBINARYLOGGINGEVENT_H
