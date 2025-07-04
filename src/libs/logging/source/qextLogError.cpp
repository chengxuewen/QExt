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

#include <qextLogError.h>
#include <qextLogInitialisationHelper.h>

#include <QBuffer>
#include <QByteArray>
#include <QDataStream>
#include <QCoreApplication>
#include <QThreadStorage>

#if (__cplusplus >= 201703L) // C++17 or later
#   include <utility>
#endif

typedef QThreadStorage<QExtLogError *> QExtThreadLogError;

Q_GLOBAL_STATIC(QExtThreadLogError, qextThreadLogError)

QExtLogError::QExtLogError()
    : mCode(0)
{
}

QExtLogError::QExtLogError(const QString &message,
                           int code,
                           const QString &symbol,
                           const QString &context)
    : mCode(code)
    , mContext(context)
    , mMessage(cleanMessage(message))
    , mSymbol(symbol)
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
    {
        mSymbol.clear();
    }
}

QString QExtLogError::translatedMessage() const
{
    return QCoreApplication::translate(mContext.toLatin1().constData(), mMessage.toUtf8().constData(), QEXT_NULLPTR);
}

QExtLogError QExtLogError::lastError()
{
    if (!qextThreadLogError()->hasLocalData())
    {
        return QExtLogError();
    }

    return *qextThreadLogError()->localData();
}

void QExtLogError::setLastError(const QExtLogError &logError)
{
    if (!qextThreadLogError()->hasLocalData())
    {
        qextThreadLogError()->setLocalData(new QExtLogError);
    }

    *qextThreadLogError()->localData() = logError;
}

QString QExtLogError::toString() const
{
    QString result = messageWithArgs();

    QString contextSymbol = mContext;
    if (!contextSymbol.isEmpty() && !mSymbol.isEmpty())
    {
        contextSymbol.append(QStringLiteral("::"));
    }
    contextSymbol.append(mSymbol);

    if (!contextSymbol.isEmpty() || mCode)
    {
        result.append(QStringLiteral(" ("));
        if (!contextSymbol.isEmpty())
        {
            result.append(contextSymbol);
        }
        if (!contextSymbol.isEmpty() && mCode)
        {
            result.append(QStringLiteral(", "));
        }
        if (mCode)
        {
            result.append(QString::number(mCode));
        }
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
    QString result = message;
#if (__cplusplus >= 201703L)
    for (const auto &arg : std::as_const(mArgs))
#else
    for (const auto &arg : qAsConst(mArgs))
#endif
    {
        result = result.arg(arg.toString());
    }
    return result;
}

QString QExtLogError::cleanMessage(const QString &message)
{
    if (message.isEmpty())
    {
        return message;
    }

    QString result = message;
    if (message.at(message.size() - 1) == QLatin1Char('.'))
    {
        result = message.left(message.size() - 1);
    }
    return result;
}

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &out, const QExtLogError &logError)
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

QDataStream &operator>>(QDataStream &in, QExtLogError &logError)
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

