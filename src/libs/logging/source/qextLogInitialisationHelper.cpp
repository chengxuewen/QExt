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

#include <qextLogInitialisationHelper.h>
#include <qextLoggingEvent.h>
#include <qextLogDatetime.h>
#include <qextLogError.h>

#include <QCoreApplication>
#include <QSettings>
#include <QProcess>
#include <QMutex>

#ifndef QT_NO_DATASTREAM
#include <QDataStream>
#endif

#if (__cplusplus >= 201703L) // C++17 or later
#include <utility>
#endif

QExtLogInitialisationHelper::QExtLogInitialisationHelper() :
    mStartTime(QDateTime::currentMSecsSinceEpoch())
{
    doRegisterTypes();
    doInitialiseEnvironmentSettings();
}

QExtLogInitialisationHelper::~QExtLogInitialisationHelper()
{
    Q_ASSERT_X(false, "QExtLogInitialisationHelper::~QExtLogInitialisationHelper()", "Unexpected destruction of singleton object");
}

LOG4QT_IMPLEMENT_INSTANCE(QExtLogInitialisationHelper)

void QExtLogInitialisationHelper::doInitialiseEnvironmentSettings()
{
    // Is Process::systemEnvironment() safe to be used before a QCoreApplication
    // object has been created?

    QStringList setting_keys;
    setting_keys << QStringLiteral("Debug");
    setting_keys << QStringLiteral("DefaultInitOverride");
    setting_keys << QStringLiteral("Configuration");

    QHash<QString, QString> env_keys;
#if (__cplusplus >= 201703L)
    for (const auto &entry : std::as_const(setting_keys))
#else
    for (const auto &entry : qAsConst(setting_keys))
#endif
        env_keys.insert(QStringLiteral("log4qt_").append(entry).toUpper(), entry);

    QStringList sys_env = QProcess::systemEnvironment();
#if (__cplusplus >= 201703L)
    for (const auto &entry : std::as_const(sys_env))
#else
    for (const auto &entry : qAsConst(sys_env))
#endif
    {
        int i = entry.indexOf(QLatin1Char('='));
        if (i == -1)
            continue;
        QString key = entry.left(i);
        QString value = entry.mid(i + 1).trimmed();
        if (env_keys.contains(key))
            mEnvironmentSettings.insert(env_keys.value(key), value);
    }
}

void QExtLogInitialisationHelper::doRegisterTypes()
{
    qRegisterMetaType<QExtLogError>("QExtLogError");
    qRegisterMetaType<QExtLogLevel>("QExtLogLevel");
    qRegisterMetaType<QExtLoggingEvent>("QExtLoggingEvent");

#ifndef QT_NO_DATASTREAM
#if QT_VERSION < 0x060000
    qRegisterMetaTypeStreamOperators<QExtLogError>("QExtLogError");
    qRegisterMetaTypeStreamOperators<QExtLogLevel>("QExtLogLevel");
    qRegisterMetaTypeStreamOperators<QExtLoggingEvent>("QExtLoggingEvent");
#endif
#endif

}

QString QExtLogInitialisationHelper::doSetting(const QString &key,
                                        const QString &defaultValue) const
{
    if (mEnvironmentSettings.contains(key))
        return mEnvironmentSettings.value(key);

    if (QCoreApplication::instance() != nullptr)
    {
        QSettings s;
        s.beginGroup(QStringLiteral("Log4Qt"));
        return s.value(key, defaultValue).toString().trimmed();
    }
    return defaultValue;
}

bool QExtLogInitialisationHelper::staticInitialisation()
{
    instance();
    return true;
}

bool QExtLogInitialisationHelper::mStaticInitialisation = staticInitialisation();
