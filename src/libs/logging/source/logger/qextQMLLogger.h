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

#ifndef _QEXTLOGQMLLOGGER_H
#define _QEXTLOGQMLLOGGER_H

#include <qextLogger.h>
#include <qextLogLevel.h>

#include <QObject>
#if QT_VERSION >= 0x060500
#include <QtQml/qqmlregistration.h>
#endif

/*!
 * \brief A  qml wapper on top of the log4qt logger for passing logger calls from qml to Log4Qt's logger.
 *
 * Resister qml wrapper:
 * \code qmlRegisterType<QExtQmlLogger>("org.log4qt", 1, 0, "QExtLogger"); \endcode
 *
 * Use in QML:
 * \code
 * property QExtLogger logger: QExtLogger {}
 *
 * Component.onCompleted:  {
 *  logger.trace("Component completed.")
 * }
 * \endcode
 * \note The default logger name is the parents object name. The logger name can also be set:
 *       property QExtLogger logger: QExtLogger { name: "MyLogger" }
 *
 * \note The default logger context is Qml. The QExtLogger name is put together from context and name (context.name)
 */
class QEXT_LOGGING_API QExtQmlLogger : public QObject
{
    Q_OBJECT
    QEXT_DISABLE_COPY_MOVE(QExtQmlLogger)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString context READ context WRITE setContext NOTIFY contextChanged)
    Q_PROPERTY(LevelEnum level READ level WRITE setLevel NOTIFY levelChanged)
#if QT_VERSION >= 0x060500
    QML_NAMED_ELEMENT(QExtLogger)
#endif


public:
    enum LevelEnum
    {
        Null = QExtLogLevel::Null,
        All = QExtLogLevel::All,
        Trace = QExtLogLevel::Trace,
        Debug = QExtLogLevel::Debug,
        Info  = QExtLogLevel::Info,
        Warn  = QExtLogLevel::Warn,
        Error = QExtLogLevel::Error,
        Fatal = QExtLogLevel::Fatal,
        Off = QExtLogLevel::Off
    };
    Q_ENUM(LevelEnum)

    explicit QExtQmlLogger(QObject *parent = nullptr);

    // String might be enough as in JavaScript logs concatenation is natural anyway
    Q_INVOKABLE void trace(const QString &message) const;
    Q_INVOKABLE void debug(const QString &message) const;
    Q_INVOKABLE void info(const QString &message) const;
    Q_INVOKABLE void error(const QString &message) const;
    Q_INVOKABLE void fatal(const QString &message) const;
    Q_INVOKABLE void log(QExtQmlLogger::LevelEnum level, const QString &message) const;

    QString name() const;
    QString context() const;
    QExtQmlLogger::LevelEnum level() const;

public Q_SLOTS:
    void setName(const QString &name);
    void setContext(const QString &context);
    void setLevel(QExtQmlLogger::LevelEnum level);

Q_SIGNALS:
    void nameChanged(const QString &name);
    void contextChanged(const QString &context);
    void levelChanged(QExtQmlLogger::LevelEnum level);

private:
    QString mContext;
    mutable QString mName;
    mutable QPointer<QExtLogger> mLogger;

    QString loggename() const;
    QExtLogger *logger() const;
};

#endif // _QEXTLOGQMLLOGGER_H
