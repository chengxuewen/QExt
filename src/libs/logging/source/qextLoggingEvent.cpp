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

#include <qextLoggingEvent.h>
#include <qextLogDatetime.h>
#include <qextLogInitialisationHelper.h>
#include <qextLogger.h>
#include <qextLogMDC.h>
#include <qextLogNDC.h>

#include <QMutex>
#include <QBuffer>
#include <QThread>
#include <QByteArray>
#include <QDataStream>

QExtLoggingEvent::QExtLoggingEvent() :
    QEvent(eventId),
    mLevel(QExtLogLevel::Null),
    mLogger(nullptr),
    mMessage(),
    mNdc(QExtLogNDC::peek()),
    mProperties(QExtLogMDC::context()),
    mSequenceNumber(nextSequenceNumber()),
    mThreadName(),
    mTimeStamp(QDateTime::currentMSecsSinceEpoch())
{
    setThreadNameToCurrent();
}

QExtLoggingEvent::~QExtLoggingEvent() = default;

QExtLoggingEvent::QExtLoggingEvent(const QExtLogger *logger,
                                   QExtLogLevel level,
                                   const QString &message) :
    QEvent(eventId),
    mLevel(level),
    mLogger(logger),
    mMessage(message),
    mNdc(QExtLogNDC::peek()),
    mProperties(QExtLogMDC::context()),
    mSequenceNumber(nextSequenceNumber()),
    mThreadName(),
    mTimeStamp(QDateTime::currentMSecsSinceEpoch())
{
    setThreadNameToCurrent();
}

QExtLoggingEvent::QExtLoggingEvent(const QExtLogger *logger,
                                   QExtLogLevel level,
                                   const QString &message,
                                   const QExtLogMessageContext &context,
                                   const QString &categoryName) :
    QEvent(eventId),
    mLevel(level),
    mLogger(logger),
    mMessage(message),
    mNdc(QExtLogNDC::peek()),
    mProperties(QExtLogMDC::context()),
    mSequenceNumber(nextSequenceNumber()),
    mThreadName(),
    mTimeStamp(QDateTime::currentMSecsSinceEpoch()),
    mContext(context),
    mCategoryName(categoryName)
{
    setThreadNameToCurrent();
}


QExtLoggingEvent::QExtLoggingEvent(const QExtLogger *logger,
                                   QExtLogLevel level,
                                   const QString &message,
                                   qint64 timeStamp) :
    QEvent(eventId),
    mLevel(level),
    mLogger(logger),
    mMessage(message),
    mNdc(QExtLogNDC::peek()),
    mProperties(QExtLogMDC::context()),
    mSequenceNumber(nextSequenceNumber()),
    mThreadName(),
    mTimeStamp(timeStamp)
{
    setThreadNameToCurrent();
}


QExtLoggingEvent::QExtLoggingEvent(const QExtLogger *logger,
                                   QExtLogLevel level,
                                   const QString &message,
                                   const QString &ndc,
                                   const QHash<QString, QString> &properties,
                                   const QString &threadName,
                                   qint64 timeStamp) :
    QEvent(eventId),
    mLevel(level),
    mLogger(logger),
    mMessage(message),
    mNdc(ndc),
    mProperties(properties),
    mSequenceNumber(nextSequenceNumber()),
    mThreadName(threadName),
    mTimeStamp(timeStamp)
{
}

QExtLoggingEvent::QExtLoggingEvent(const QExtLogger *logger,
                                   QExtLogLevel level,
                                   const QString &message,
                                   const QString &ndc,
                                   const QHash<QString, QString> &properties,
                                   qint64 timeStamp,
                                   const QExtLogMessageContext &context,
                                   const QString &categoryName)
    :
    QEvent(eventId),
    mLevel(level),
    mLogger(logger),
    mMessage(message),
    mNdc(ndc),
    mProperties(properties),
    mSequenceNumber(nextSequenceNumber()),
    mThreadName(),
    mTimeStamp(timeStamp),
    mContext(context),
    mCategoryName(categoryName)
{
    setThreadNameToCurrent();
}

QExtLoggingEvent::QExtLoggingEvent(const QExtLogger *logger,
                                   QExtLogLevel level,
                                   const QString &message,
                                   const QString &ndc,
                                   const QHash<QString, QString> &properties,
                                   const QString &threadName,
                                   qint64 timeStamp,
                                   const QExtLogMessageContext &context,
                                   const QString &categoryName)
    :
    QEvent(eventId),
    mLevel(level),
    mLogger(logger),
    mMessage(message),
    mNdc(ndc),
    mProperties(properties),
    mSequenceNumber(nextSequenceNumber()),
    mThreadName(threadName),
    mTimeStamp(timeStamp),
    mContext(context),
    mCategoryName(categoryName)
{
}

QString QExtLoggingEvent::loggename() const
{
    if (mLogger)
        return mLogger->name();
    return QString();
}


QString QExtLoggingEvent::toString() const
{
    return level().toString() + QLatin1Char(':') + message();
}


qint64 QExtLoggingEvent::sequenceCount()
{
    return msSequenceCount;
}


qint64 QExtLoggingEvent::startTime()
{
    return QExtLogInitialisationHelper::startTime();
}


void QExtLoggingEvent::setThreadNameToCurrent()
{
    if (QThread::currentThread())
    {
        mThreadName = QThread::currentThread()->objectName();
        // if object name is not set use thread function address for thread identification
        if (mThreadName.isEmpty())
            mThreadName = QStringLiteral("0x%1").arg(reinterpret_cast<quintptr>(QThread::currentThread()), QT_POINTER_SIZE * 2, 16, QChar('0'));

    }
}


qint64 QExtLoggingEvent::nextSequenceNumber()
{
    return ++msSequenceCount;
}

QExtLogMessageContext QExtLoggingEvent::context() const
{
    return mContext;
}

void QExtLoggingEvent::setContext(const QExtLogMessageContext &context)
{
    mContext = context;
}

QString QExtLoggingEvent::categoryName() const
{
    return mCategoryName;
}

void QExtLoggingEvent::setCategoryName(const QString &categoryName)
{
    mCategoryName = categoryName;
}

std::atomic<qint64> QExtLoggingEvent::msSequenceCount {0};
const QEvent::Type QExtLoggingEvent::eventId = static_cast<QEvent::Type>(QEvent::registerEventType());

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &out, const QExtLoggingEvent &loggingEvent)
{
    // version
    quint16 version = 0;
    out << version;
    // version 0 data
    out << loggingEvent.mLevel
        << loggingEvent.loggename()
        << loggingEvent.mMessage
        << loggingEvent.mNdc
        << loggingEvent.mProperties
        << loggingEvent.mSequenceNumber
        << loggingEvent.mThreadName
        << loggingEvent.mTimeStamp;

    return out;
}


QDataStream &operator>>(QDataStream &in, QExtLoggingEvent &loggingEvent)
{
    // version
    quint16 version;
    in >> version;
    // Version 0 data
    QString logger;
    in >> loggingEvent.mLevel
        >> logger
        >> loggingEvent.mMessage
        >> loggingEvent.mNdc
        >> loggingEvent.mProperties
        >> loggingEvent.mSequenceNumber
        >> loggingEvent.mThreadName
        >> loggingEvent.mTimeStamp;
    if (logger.isEmpty())
        loggingEvent.mLogger = nullptr;
    else
        loggingEvent.mLogger = QExtLogger::logger(logger);

    return in;
}
#endif // QT_NO_DATASTREAM
