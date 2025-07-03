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

#ifndef _QEXTLOGGINGEVENT_H
#define _QEXTLOGGINGEVENT_H

#include <qextLogLevel.h>

#include <QStringList>
#include <QEvent>
#include <QHash>

#include <atomic>

class QExtLogger;

struct QExtLogMessageContext
{
    explicit QExtLogMessageContext()
        : file(nullptr), line(-1), function(nullptr) {}
    explicit QExtLogMessageContext(const char *fileName, int lineNumber, const char *functionName)
        : file(fileName), line(lineNumber), function(functionName) {}

    int line;
    const char *file;
    const char *function;
};

/*!
 * \brief The class QExtLoggingEvent is the internal representation of a
 *        logging event.
 *
 * The class uses milliseconds since 1970-01-01T00:00:00, Coordinated
 * Universal Time for time values. For converstion from and to QDateTime
 * use QExtLogDateTime.
 */
class QEXT_LOGGING_API QExtLoggingEvent : public QEvent
{
public:
    static const QEvent::Type eventId;
    QExtLoggingEvent();
    virtual ~QExtLoggingEvent();

    QExtLoggingEvent(const QExtLogger *logger,
                     QExtLogLevel level,
                     const QString &message);
    QExtLoggingEvent(const QExtLogger *logger,
                     QExtLogLevel level,
                     const QString &message,
                     const QExtLogMessageContext &context,
                     const QString &categoryName);
    QExtLoggingEvent(const QExtLogger *logger,
                     QExtLogLevel level,
                     const QString &message,
                     qint64 timeStamp);
    QExtLoggingEvent(const QExtLogger *logger,
                     QExtLogLevel level,
                     const QString &message,
                     const QString &ndc,
                     const QHash<QString, QString> &properties,
                     const QString &threadName,
                     qint64 timeStamp);
    QExtLoggingEvent(const QExtLogger *logger,
                     QExtLogLevel level,
                     const QString &message,
                     const QString &ndc,
                     const QHash<QString, QString> &properties,
                     qint64 timeStamp,
                     const QExtLogMessageContext &context,
                     const QString &categoryName);
    QExtLoggingEvent(const QExtLogger *logger,
                     QExtLogLevel level,
                     const QString &message,
                     const QString &ndc,
                     const QHash<QString, QString> &properties,
                     const QString &threadName,
                     qint64 timeStamp,
                     const QExtLogMessageContext &context,
                     const QString &categoryName);

    QExtLogLevel level() const;
    // LocationInformation locationInformation() const;
    const QExtLogger *logger() const;
    QString message() const;
    QHash<QString, QString> mdc() const;
    QString ndc() const;
    QHash<QString, QString> properties() const;
    qint64 sequenceNumber() const;
    QString threadName() const;
    qint64 timeStamp() const;

    QString loggename() const;
    QString property(const QString &key) const;
    QStringList propertyKeys() const;
    void setProperty(const QString &key, const QString &value);
    QString toString() const;
    static qint64 sequenceCount();
    static qint64 startTime();

    int lineNumber() const;
    void setLineNumber(int lineNumber);
    QString fileName() const;
    void setFileName(const QString &fileName);
    QString functionName() const;
    void setMethodName(const QString &functionName);
    QString categoryName() const;
    void setCategoryName(const QString &categoryName);
    QExtLogMessageContext context() const;
    void setContext(const QExtLogMessageContext &context);

private:
    void setThreadNameToCurrent();
    static qint64 nextSequenceNumber();

private:
    QExtLogLevel mLevel;
    const QExtLogger *mLogger;
    QString mMessage;
    QString mNdc;
    QHash<QString, QString> mProperties;
    qint64 mSequenceNumber;
    QString mThreadName;
    qint64 mTimeStamp;
    QExtLogMessageContext mContext;
    QString mCategoryName;

    static std::atomic<qint64> msSequenceCount;

#ifndef QT_NO_DATASTREAM
    // Needs to be friend to stream objects
    friend QEXT_LOGGING_API QDataStream &operator<<(QDataStream &out, const QExtLoggingEvent &loggingEvent);
    friend QEXT_LOGGING_API QDataStream &operator>>(QDataStream &in, QExtLoggingEvent &loggingEvent);
#endif // QT_NO_DATASTREAM
};

#ifndef QT_NO_DATASTREAM
/*!
 * \relates QExtLoggingEvent
 *
 * Writes the given error \a rLoggingEvent to the given stream \a rStream,
 * and returns a reference to the stream.
 */
QEXT_LOGGING_API QDataStream &operator<<(QDataStream &out, const QExtLoggingEvent &loggingEvent);

/*!
 * \relates QExtLoggingEvent
 *
 * Reads an error from the given stream \a rStream into the given
 * error \a rLoggingEvent, and returns a reference to the stream.
 */
QEXT_LOGGING_API QDataStream &operator>>(QDataStream &in, QExtLoggingEvent &loggingEvent);
#endif // QT_NO_DATASTREAM

inline QExtLogLevel QExtLoggingEvent::level() const
{
    return mLevel;
}

inline const QExtLogger *QExtLoggingEvent::logger() const
{
    return mLogger;
}

inline QString QExtLoggingEvent::message() const
{
    return mMessage;
}

inline QHash<QString, QString> QExtLoggingEvent::mdc() const
{
    return mProperties;
}

inline QString QExtLoggingEvent::ndc() const
{
    return mNdc;
}

inline QHash<QString, QString> QExtLoggingEvent::properties() const
{
    return mProperties;
}

inline qint64 QExtLoggingEvent::sequenceNumber() const
{
    return mSequenceNumber;
}

inline QString QExtLoggingEvent::threadName() const
{
    return mThreadName;
}

inline qint64 QExtLoggingEvent::timeStamp() const
{
    return mTimeStamp;
}

inline QString QExtLoggingEvent::property(const QString &key) const
{
    return mProperties.value(key);
}

inline QStringList QExtLoggingEvent::propertyKeys() const
{
    return QStringList(mProperties.keys());
}

inline void QExtLoggingEvent::setProperty(const QString &key, const QString &value)
{
    mProperties.insert(key, value);
}

Q_DECLARE_METATYPE(QExtLoggingEvent)
Q_DECLARE_TYPEINFO(QExtLoggingEvent, Q_MOVABLE_TYPE);

#endif // _QEXTLOGGINGEVENT_H
