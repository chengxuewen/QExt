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

#ifndef _QEXTLOGBINARYLOGGER_H
#define _QEXTLOGBINARYLOGGER_H

#include <qextLogger.h>
#include <qextBinaryLogStream.h>
#include <qextLogBinaryClassLogger.h>

class QByteArray;

class QExtLogAppender;
class QExtBinaryLoggingEvent;
class QExtLoggerRepository;
class QExtLogHierarchy;

#define LOG4QT_DECLARE_STATIC_BINARYLOGGER(FUNCTION, CLASS) \
    static QExtBinaryLogger *FUNCTION() \
    { \
        static QExtLogger * p_logger(QExtLogger::logger(#CLASS"@@binary@@" )); \
        return qobject_cast<QExtBinaryLogger*>(p_logger); \
    }

#define LOG4QT_DECLARE_QCLASS_BINARYLOGGER \
    private: \
        mutable QExtBinaryClassLogger mClassLogger; \
    public: \
        inline QExtBinaryLogger *logger() const \
        { \
            return mClassLogger.logger(this); \
        } \
    private:

class QEXT_LOGGING_API QExtBinaryLogger : public QExtLogger
{
    Q_OBJECT
public:
    QExtLogBinaryStream debug() const {return log(QExtLogLevel::Debug);}
    void debug(const QByteArray &message) const {log(QExtLogLevel::Debug, message);}
    QExtLogBinaryStream error() const {return log(QExtLogLevel::Error);}
    void error(const QByteArray &message) const {log(QExtLogLevel::Error, message);}
    QExtLogBinaryStream fatal() const {return log(QExtLogLevel::Fatal);}
    void fatal(const QByteArray &message) const {log(QExtLogLevel::Fatal, message);}
    QExtLogBinaryStream info() const {return log(QExtLogLevel::Info);}
    void info(const QByteArray &message) const {log(QExtLogLevel::Info, message);}
    QExtLogBinaryStream trace() const {return log(QExtLogLevel::Trace);}
    void trace(const QByteArray &message) const {log(QExtLogLevel::Trace, message);}
    QExtLogBinaryStream warn() const {return log(QExtLogLevel::Warn);}
    void warn(const QByteArray &message) const {log(QExtLogLevel::Warn, message);}

    QExtLogBinaryStream log(QExtLogLevel level) const;
    void log(QExtLogLevel level, const QByteArray &message) const;
    void log(QExtLogLevel level, const QByteArray &message, QDateTime timeStamp) const;

protected:
    QExtBinaryLogger(QExtLoggerRepository *loggerRepository, QExtLogLevel level, const QString &name, QExtLogger *parent = nullptr);
    virtual ~QExtBinaryLogger();

    void forcedLog(QExtLogLevel level, const QByteArray &message) const;

private:
    QExtBinaryLogger(const QExtBinaryLogger &other); // Not implemented
    QExtBinaryLogger &operator=(const QExtBinaryLogger &other); // Not implemented
    // Needs to be friend to create QExtBinaryLogger objects
    friend class QExtLogHierarchy;
};

#endif // _QEXTLOGBINARYLOGGER_H
