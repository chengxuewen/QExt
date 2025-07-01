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

#include <qextLogError.h>
#include <qextLogInitialisationHelper.h>

#include <QBuffer>
#include <QByteArray>
#include <QDataStream>
#include <QCoreApplication>
#include <QThreadStorage>

#if (__cplusplus >= 201703L) // C++17 or later
#include <utility>
#endif

// namespace Log4Qt
// {

typedef QThreadStorage<QExtLogError *> ThreadError;

Q_GLOBAL_STATIC(ThreadError, thread_error)

QExtLogError::QExtLogError() :
    mCode(0)
{
}

QExtLogError::QExtLogError(const QString &message,
                   int code,
                   const QString &symbol,
                   const QString &context) :
    mCode(code),
    mContext(context),
    mMessage(cleanMessage(message)),
    mSymbol(symbol)
{
}

QExtLogError::QExtLogError(const char *message,
                   int code,
                   const char *symbol,
                   const char *context,
                   EncodingEnum encoding) :
    mCode(code),
    mContext(QString::fromLatin1(context)),
    mSymbol(QString::fromLatin1(symbol))
{
    switch (encoding)
    {
    case Encoding_Latin1:
        mMessage = QString::fromLatin1(message);
        break;
    case Encoding_UnicodeUtf8:
        mMessage = QString::fromUtf8(message);
        break;
    default:
        Q_ASSERT_X(false, "QExtLogError::QExtLogError", "Unknown encoding constant");
        mMessage = QString::fromLatin1(message);
    }
    mMessage = cleanMessage(mMessage);

    if (mSymbol == QString::number(mCode))
        mSymbol.clear();
}

QString QExtLogError::translatedMessage() const
{
    return QCoreApplication::translate(mContext.toLatin1().constData(), mMessage.toUtf8().constData(), nullptr);
}

QExtLogError QExtLogError::lastError()
{
    if (!thread_error()->hasLocalData())
        return QExtLogError();

    return *thread_error()->localData();
}

void QExtLogError::setLastError(const QExtLogError &logError)
{
    if (!thread_error()->hasLocalData())
        thread_error()->setLocalData(new QExtLogError);

    *thread_error()->localData() = logError;
}

QString QExtLogError::toString() const
{
    QString result = messageWithArgs();

    QString context_symbol = mContext;
    if (!context_symbol.isEmpty() && !mSymbol.isEmpty())
        context_symbol.append(QStringLiteral("::"));
    context_symbol.append(mSymbol);

    if (!context_symbol.isEmpty() || mCode)
    {
        result.append(QStringLiteral(" ("));
        if (!context_symbol.isEmpty())
            result.append(context_symbol);
        if (!context_symbol.isEmpty() && mCode)
            result.append(QStringLiteral(", "));
        if (mCode)
            result.append(QString::number(mCode));
        result.append(QStringLiteral(")"));
    }

    if (!mCausingErrors.isEmpty())
    {
        QString causing_errors_str = QStringLiteral(": ") + mCausingErrors.at(0).toString();
        int i = 1;
        while (i < mCausingErrors.count())
        {
            causing_errors_str.append(QStringLiteral(", ")).append(mCausingErrors.at(i).toString());
            i++;
        }
        result.append(causing_errors_str);
    }

    return result;
}

QString QExtLogError::insertArgs(const QString &message) const
{
    QString result;

    result = message;
#if (__cplusplus >= 201703L)
    for (const auto &arg : std::as_const(mArgs))
#else
    for (const auto &arg : qAsConst(mArgs))
#endif
        result = result.arg(arg.toString());
    return result;
}

QString QExtLogError::cleanMessage(const QString &message)
{
    if (message.isEmpty())
        return message;

    QString result = message;
    if (message.at(message.size() - 1) == QLatin1Char('.'))
        result = message.left(message.size() - 1);
    return result;
}

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &out,
                        const QExtLogError &logError)
{
    // version
    quint16 version = 0;
    out << version;
    // version 0 data
    out << logError.mCode
           << logError.mContext
           << logError.mMessage
           << logError.mSymbol
           << logError.mArgs
           << logError.mCausingErrors;

    return out;
}

QDataStream &operator>>(QDataStream &in,
                        QExtLogError &logError)
{
    // version
    quint16 version;
    in >> version;
    // Version 0 data
    in >> logError.mCode
           >> logError.mContext
           >> logError.mMessage
           >> logError.mSymbol
           >> logError.mArgs
           >> logError.mCausingErrors;

    return in;
}
#endif // QT_NO_DATASTREAM

// } // namespace Log4Qt
