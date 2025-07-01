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

#ifndef LOG4QT_QMLLOGGER_H
#define LOG4QT_QMLLOGGER_H

// #include "log4qtshared.h"
#include <qextLogger.h>
#include <qextLogLevel.h>

#include <QObject>
#if QT_VERSION >= 0x060500
#include <QtQml/qqmlregistration.h>
#endif

namespace Log4Qt
{

/*!
 * \brief A  qml wapper on top of the log4qt logger for passing logger calls from qml to Log4Qt's logger.
 *
 * Resister qml wrapper:
 * \code qmlRegisterType<Log4Qt::QmlLogger>("org.log4qt", 1, 0, "Logger"); \endcode
 *
 * Use in QML:
 * \code
 * property Logger logger: Logger {}
 *
 * Component.onCompleted:  {
 *  logger.trace("Component completed.")
 * }
 * \endcode
 * \note The default logger name is the parents object name. The logger name can also be set:
 *       property Logger logger: Logger { name: "MyLogger" }
 *
 * \note The default logger context is Qml. The Logger name is put together from context and name (context.name)
 */
class QEXT_LOGGING_API QmlLogger : public QObject
{
    Q_OBJECT
    QEXT_DISABLE_COPY_MOVE(QmlLogger)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString context READ context WRITE setContext NOTIFY contextChanged)
    Q_PROPERTY(LevelEnum level READ level WRITE setLevel NOTIFY levelChanged)
#if QT_VERSION >= 0x060500
    QML_NAMED_ELEMENT(Logger)
#endif


public:
    enum LevelEnum
    {
        Null = QExtLogLevel::NULL_INT,
        All = QExtLogLevel::ALL_INT,
        Trace = QExtLogLevel::TRACE_INT,
        Debug = QExtLogLevel::DEBUG_INT,
        Info  = QExtLogLevel::INFO_INT,
        Warn  = QExtLogLevel::WARN_INT,
        Error = QExtLogLevel::ERROR_INT,
        Fatal = QExtLogLevel::FATAL_INT,
        Off = QExtLogLevel::OFF_INT
    };
    Q_ENUM(LevelEnum)

    explicit QmlLogger(QObject *parent = nullptr);

    // String might be enough as in JavaScript logs concatenation is natural anyway
    Q_INVOKABLE void trace(const QString &message) const;
    Q_INVOKABLE void debug(const QString &message) const;
    Q_INVOKABLE void info(const QString &message) const;
    Q_INVOKABLE void error(const QString &message) const;
    Q_INVOKABLE void fatal(const QString &message) const;
    Q_INVOKABLE void log(QmlLogger::LevelEnum level, const QString &message) const;

    QString name() const;
    QString context() const;
    QmlLogger::LevelEnum level() const;

public Q_SLOTS:
    void setName(const QString &name);
    void setContext(const QString &context);
    void setLevel(QmlLogger::LevelEnum level);

Q_SIGNALS:
    void nameChanged(const QString &name);
    void contextChanged(const QString &context);
    void levelChanged(QmlLogger::LevelEnum level);

private:
    QString mContext;
    mutable QString mName;
    mutable QPointer<Logger> mLogger;

    QString loggename() const;
    Logger *logger() const;
};

}


#endif // LOG4QT_QMLLOGGER_H
