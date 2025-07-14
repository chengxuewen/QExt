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

#include <qextLogFactory.h>
#include <qextLogConsoleAppender.h>
#include <qextLogDailyRollingFileAppender.h>
#include <qextLogFileAppender.h>
#include <qextLogInitialisationHelper.h>
#include <qextLogOptionConverter.h>
#include <qextLogError.h>
#include <qextLogPatternLayout.h>
#include <qextLogRollingFileAppender.h>
#include <qextLogSignalAppender.h>
#include <qextLogSimpleTimeLayout.h>
#include <qextLogSimpleLayout.h>
#include <qextLogTTCCLayout.h>
#include <qextLogBinaryLayout.h>
#include <qextLogBinaryToTextLayout.h>
#include <qextLogXMLLayout.h>

#if QEXT_FEATURE_USE_LOGGING_TELNET
#   include <qextLogTelnetAppender.h>
#endif

#if QEXT_FEATURE_USE_LOGGING_DATABASE
#   include <qextLogDatabaseAppender.h>
#   include <qextLogDatabaseLayout.h>
#endif

#include <qextLogAsyncAppender.h>
#include <qextLogMainThreadAppender.h>
#include <qextLogSyslogAppender.h>
#include <qextLogBinaryFileAppender.h>
#include <qextLogRollingBinaryFileAppender.h>
#include <qextLogDailyFileAppender.h>
#ifdef Q_OS_WIN
#   include <qextLogColorConsoleAppender.h>
#   include <qextLogWDCAppender.h>
#endif

#include <qextLogDebugAppender.h>
#include <qextLogDenyAllFilter.h>
#include <qextLogLevelMatchFilter.h>
#include <qextLogLevelRangeFilter.h>
#include <qextLogListAppender.h>
#include <qextLogNullAppender.h>
#include <qextLogStringMatchFilter.h>
#include <qextLogBinaryEventFilter.h>

#include <QMetaObject>
#include <QMetaProperty>

QEXT_DECLARE_STATIC_LOGGER(logger, QExtLogFactory)

// Appenders

QExtLogAppender *console_file_appender()
{
    return new QExtLogConsoleAppender;
}

QExtLogAppender *create_daily_rolling_file_appender()
{
    return new QExtLogDailyRollingFileAppender;
}

QExtLogAppender *create_debug_appender()
{
    return new QExtLogDebugAppender;
}

QExtLogAppender *create_file_appender()
{
    return new QExtLogFileAppender;
}

QExtLogAppender *create_list_appender()
{
    return new QExtLogListAppender;
}

QExtLogAppender *create_null_appender()
{
    return new QExtLogNullAppender;
}

QExtLogAppender *create_rolling_file_appender()
{
    return new QExtLogRollingFileAppender;
}

QExtLogAppender *create_signal_appender()
{
    return new QExtLogSignalAppender;
}

#if QEXT_FEATURE_USE_LOGGING_DATABASE
QExtLogAppender *create_database_appender()
{
    return new QExtLogDatabaseAppender;
}
#endif

#if QEXT_FEATURE_USE_LOGGING_TELNET
QExtLogAppender *create_telnet_appender()
{
    return new QExtLogTelnetAppender;
}
#endif

QExtLogAppender *create_async_appender()
{
    return new QExtLogAsyncAppender;
}

QExtLogAppender *create_mainthread_appender()
{
    return new QExtLogMainThreadAppender;
}

QExtLogAppender *create_systemlog_appender()
{
    return new QExtLogSystemLogAppender;
}

QExtLogAppender *create_binaryfile_appender()
{
    return new QExtLogBinaryFileAppender;
}

QExtLogAppender *create_rollingbinaryfile_appender()
{
    return new QExtLogRollingBinaryFileAppender;
}

QExtLogAppender *create_dailyrollingfile_appender()
{
    return new QExtLogDailyFileAppender;
}

#ifdef Q_OS_WIN
QExtLogAppender *create_wdc_appender()
{
    return new QExtLogWDCAppender;
}

QExtLogAppender *create_color_console_appender()
{
    return new QExtLogColorConsoleAppender;
}
#endif

// Filters

QExtLogFilter *create_deny_all_filter()
{
    return new QExtLogDenyAllFilter;
}

QExtLogFilter *create_level_match_filter()
{
    return new QExtLogLevelMatchFilter;
}

QExtLogFilter *create_level_range_filter()
{
    return new QExtLogLevelRangeFilter;
}

QExtLogFilter *create_string_match_filter()
{
    return new QExtLogStringMatchFilter;
}

QExtLogFilter *create_binaryevent_filter()
{
    return new QExtLogBinaryEventFilter;
}

// Layouts

QExtLogLayout *create_pattern_layout()
{
    return new QExtLogPatternLayout;
}

QExtLogLayout *create_simple_layout()
{
    return new QExtLogSimpleLayout;
}

QExtLogLayout *create_simple_time_layout()
{
    return new QExtLogSimpleTimeLayout;
}

#if QEXT_FEATURE_USE_LOGGING_DATABASE
QExtLogLayout *create_database_layout()
{
    return new QExtLogDatabaseLayout;
}
#endif

QExtLogLayout *create_ttcc_layout()
{
    return new QExtLogTTCCLayout;
}
QExtLogLayout *create_binary_layout()
{
    return new QExtLogBinaryLayout;
}

QExtLogLayout *create_binarytotext_layout()
{
    return new QExtLogBinaryToTextLayout;
}

QExtLogLayout *create_xml_layout()
{
    return new QExtLogXMLLayout;
}

QExtLogFactory::QExtLogFactory()
{
    registerDefaultAppenders();
    registerDefaultFilters();
    registerDefaultLayouts();
}

QEXT_IMPLEMENT_INSTANCE(QExtLogFactory)

QExtLogAppender *QExtLogFactory::doCreateAppender(const QString &appenderClassName)
{
    QMutexLocker locker(&mObjectGuard);

    if (!mAppenderRegistry.contains(appenderClassName))
    {
        logger()->warn(QStringLiteral("Request for the creation of QExtLogAppender with class '%1', "
                                      "which is not registered"), appenderClassName);
        return QEXT_NULLPTR;
    }
    return mAppenderRegistry.value(appenderClassName)();
}


QExtLogFilter *QExtLogFactory::doCreateFilter(const QString &filterClassName)
{
    QMutexLocker locker(&mObjectGuard);

    if (!mFilterRegistry.contains(filterClassName))
    {
        logger()->warn(QStringLiteral("Request for the creation of QExtLogFilter with class '%1', "
                                      "which is not registered"), filterClassName);
        return QEXT_NULLPTR;
    }
    return mFilterRegistry.value(filterClassName)();
}


QExtLogLayout *QExtLogFactory::doCreateLayout(const QString &layoutClassName)
{
    QMutexLocker locker(&mObjectGuard);

    if (!mLayoutRegistry.contains(layoutClassName))
    {
        logger()->warn(QStringLiteral("Request for the creation of QExtLogLayout with class '%1', "
                                      "which is not registered"), layoutClassName);
        return QEXT_NULLPTR;
    }
    return mLayoutRegistry.value(layoutClassName)();
}


void QExtLogFactory::doRegisterAppender(const QString &appenderClassName,
                                        AppenderFactoryFunc appenderFactoryFunc)
{
    QMutexLocker locker(&mObjectGuard);

    if (appenderClassName.isEmpty())
    {
        logger()->warn(QStringLiteral("Registering QExtLogAppender factory function with empty class name"));
        return;
    }
    mAppenderRegistry.insert(appenderClassName, appenderFactoryFunc);
}


void QExtLogFactory::doRegisterFilter(const QString &filterClassName,
                                      FilterFactoryFunc filterFactoryFunc)
{
    QMutexLocker locker(&mObjectGuard);

    if (filterClassName.isEmpty())
    {
        logger()->warn(QStringLiteral("Registering QExtLogFilter factory function with empty class name"));
        return;
    }
    mFilterRegistry.insert(filterClassName, filterFactoryFunc);
}


void QExtLogFactory::doRegisterLayout(const QString &layoutClassName,
                                      LayoutFactoryFunc layoutFactoryFunc)
{
    QMutexLocker locker(&mObjectGuard);

    if (layoutClassName.isEmpty())
    {
        logger()->warn(QStringLiteral("Registering QExtLogLayout factory function with empty class name"));
        return;
    }
    mLayoutRegistry.insert(layoutClassName, layoutFactoryFunc);
}


void QExtLogFactory::doSetObjectProperty(QObject *object,
                                         const QString &property,
                                         const QString &value)
{
    // - Validate property
    // - Get correct property name from meta object
    // - Find specific property setter
    // - If no specfifc propery setter can be found,
    //   find general property setter
    // - Call property setter

    QMetaProperty meta_property;
    if (!validateObjectProperty(meta_property, property, object))
    {
        return;
    }

    QString propertyString = QLatin1String(meta_property.name());
    QString type = QLatin1String(meta_property.typeName());
    logger()->debug(QStringLiteral("Setting property '%1' on object of class '%2' to value '%3'"),
                    propertyString,
                    QLatin1String(object->metaObject()->className()),
                    value);

    QVariant variant;
    bool ok = true;
    if (type == QStringLiteral("bool"))
    {
        variant = QExtLogOptionConverter::toBoolean(value, &ok);
    }
    else if (type == QStringLiteral("int"))
    {
        variant = QExtLogOptionConverter::toInt(value, &ok);
    }
    else if (type == QStringLiteral("QExtLogLevel"))
    {
        variant = QVariant::fromValue(QExtLogOptionConverter::toLevel(value, &ok));
    }
    else if (type == QStringLiteral("QString"))
    {
        variant = value;
    }
#if QT_VERSION < 0x060000
    else if (type == QStringLiteral("QTextCodec*"))
    {
        variant = QVariant::fromValue(QExtLogOptionConverter::toEncoding(value, &ok));
    }
#else
    else if (type == QStringLiteral("QStringConverter::Encoding"))
    {
        variant = QVariant::fromValue(QExtLogOptionConverter::toEncoding(value, &ok));
    }
#endif
    else
    {
        QExtLogError e = QEXT_LOG_ERROR(QT_TR_NOOP("Cannot convert to type '%1' for property '%2' on object of class '%3'"),
                                        QExtLogError::Error_ConfiguratorUnknownType,
                                        "QExtLogFactory");
        e << type
          << property
          << QString::fromLatin1(object->metaObject()->className());
        logger()->error(e);
        return;
    }
    if (!ok)
    {
        return;
    }

    // Everything is checked and the type is the one of the property.
    // Write should never return false
    if (!meta_property.write(object, variant))
    {
        logger()->warn(QStringLiteral("Unxpected error result from QMetaProperty.write()"));
    }
}


void QExtLogFactory::doUnregisterAppender(const QString &appenderClassName)
{
    QMutexLocker locker(&mObjectGuard);

    if (!mAppenderRegistry.contains(appenderClassName))
    {
        logger()->warn(QStringLiteral("Request to unregister not registered QExtLogAppender factory "
                                      "function for class '%1'"), appenderClassName);
        return;
    }
    mAppenderRegistry.remove(appenderClassName);
}


void QExtLogFactory::doUnregisterFilter(const QString &filterClassName)
{
    QMutexLocker locker(&mObjectGuard);

    if (!mFilterRegistry.contains(filterClassName))
    {
        logger()->warn(QStringLiteral("Request to unregister not registered QExtLogFilter factory "
                                      "function for class '%1'"), filterClassName);
        return;
    }
    mFilterRegistry.remove(filterClassName);
}


void QExtLogFactory::doUnregisterLayout(const QString &layoutClassName)
{
    QMutexLocker locker(&mObjectGuard);

    if (!mLayoutRegistry.contains(layoutClassName))
    {
        logger()->warn(QStringLiteral("Request to unregister not registered QExtLogLayout factory "
                                      "function for class '%1'"), layoutClassName);
        return;
    }
    mLayoutRegistry.remove(layoutClassName);
}


void QExtLogFactory::registerDefaultAppenders()
{
    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogConsoleAppender"),
                             console_file_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogConsoleAppender"),
                             console_file_appender);
    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogDailyRollingFileAppender"),
                             create_daily_rolling_file_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogDailyRollingFileAppender"),
                             create_daily_rolling_file_appender);
    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogDebugAppender"),
                             create_debug_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogDebugAppender"),
                             create_debug_appender);
    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogFileAppender"),
                             create_file_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogFileAppender"),
                             create_file_appender);
    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogListAppender"),
                             create_list_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogListAppender"),
                             create_list_appender);
    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogNullAppender"),
                             create_null_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogNullAppender"),
                             create_null_appender);
    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogRollingFileAppender"),
                             create_rolling_file_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogRollingFileAppender"),
                             create_rolling_file_appender);

    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogSignalAppender"),
                             create_signal_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogSignalAppender"),
                             create_signal_appender);
#ifdef Q_OS_WIN
    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogColorConsoleAppender"),
                             create_color_console_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogColorConsoleAppender"),
                             create_color_console_appender);
#endif

#if QEXT_FEATURE_USE_LOGGING_DATABASE
    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogDatabaseAppender"),
                             create_database_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogDatabaseAppender"),
                             create_database_appender);
#endif

#if QEXT_FEATURE_USE_LOGGING_TELNET
    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogTelnetAppender"),
                             create_telnet_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogTelnetAppender"),
                             create_telnet_appender);
#endif
    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogAsyncAppender"),
                             create_async_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogAsyncAppender"),
                             create_async_appender);

    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogMainThreadAppender"),
                             create_mainthread_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogMainThreadAppender"),
                             create_mainthread_appender);

    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogSystemLogAppender"),
                             create_systemlog_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogSystemLogAppender"),
                             create_systemlog_appender);

    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogBinaryFileAppender"),
                             create_binaryfile_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogBinaryFileAppender"),
                             create_binaryfile_appender);

    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogRollingBinaryFileAppender"),
                             create_rollingbinaryfile_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogRollingBinaryFileAppender"),
                             create_rollingbinaryfile_appender);

    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogDailyFileAppender"),
                             create_dailyrollingfile_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogDailyFileAppender"),
                             create_dailyrollingfile_appender);
#ifdef Q_OS_WIN
    mAppenderRegistry.insert(QStringLiteral("org.QExt.LogWDCAppender"),
                             create_wdc_appender);
    mAppenderRegistry.insert(QStringLiteral("QExtLogWDCAppender"),
                             create_wdc_appender);
#endif
}


void QExtLogFactory::registerDefaultFilters()
{
    mFilterRegistry.insert(QStringLiteral("org.QExt.LogDenyAllFilter"),
                           create_deny_all_filter);
    mFilterRegistry.insert(QStringLiteral("QExtLogDenyAllFilter"),
                           create_deny_all_filter);
    mFilterRegistry.insert(QStringLiteral("org.QExt.LogLevelMatchFilter"),
                           create_level_match_filter);
    mFilterRegistry.insert(QStringLiteral("QExtLogLevelMatchFilter"),
                           create_level_match_filter);
    mFilterRegistry.insert(QStringLiteral("org.QExt.LogLevelRangeFilter"),
                           create_level_range_filter);
    mFilterRegistry.insert(QStringLiteral("QExtLogLevelRangeFilter"),
                           create_level_range_filter);
    mFilterRegistry.insert(QStringLiteral("org.QExt.LogStringMatchFilter"),
                           create_string_match_filter);
    mFilterRegistry.insert(QStringLiteral("QExtLogStringMatchFilter"),
                           create_string_match_filter);
    mFilterRegistry.insert(QStringLiteral("org.QExt.LogBinaryEventFilter"),
                           create_binaryevent_filter);
    mFilterRegistry.insert(QStringLiteral("QExtLogBinaryEventFilter"),
                           create_binaryevent_filter);
}


void QExtLogFactory::registerDefaultLayouts()
{
    mLayoutRegistry.insert(QStringLiteral("org.QExt.LogPatternLayout"),
                           create_pattern_layout);
    mLayoutRegistry.insert(QStringLiteral("QExtLogPatternLayout"),
                           create_pattern_layout);
    mLayoutRegistry.insert(QStringLiteral("org.QExt.LogSimpleLayout"),
                           create_simple_layout);
    mLayoutRegistry.insert(QStringLiteral("QExtLogSimpleLayout"),
                           create_simple_layout);
    mLayoutRegistry.insert(QStringLiteral("org.QExt.LogTTCCLayout"),
                           create_ttcc_layout);
    mLayoutRegistry.insert(QStringLiteral("QExtLogTTCCLayout"),
                           create_ttcc_layout);

    mLayoutRegistry.insert(QStringLiteral("org.QExt.LogSimpleTimeLayout"),
                           create_simple_time_layout);
    mLayoutRegistry.insert(QStringLiteral("QExtLogSimpleTimeLayout"),
                           create_simple_time_layout);

#if QEXT_FEATURE_USE_LOGGING_DATABASE
    mLayoutRegistry.insert(QStringLiteral("org.QExt.LogDatabaseLayout"),
                           create_database_layout);
    mLayoutRegistry.insert(QStringLiteral("QExtLogDatabaseLayout"),
                           create_database_layout);
#endif

    mLayoutRegistry.insert(QStringLiteral("org.QExt.LogBinaryLayout"),
                           create_binary_layout);
    mLayoutRegistry.insert(QStringLiteral("QExtLogBinaryLayout"),
                           create_binary_layout);

    mLayoutRegistry.insert(QStringLiteral("org.QExt.LogBinaryToTextLayout"),
                           create_binarytotext_layout);
    mLayoutRegistry.insert(QStringLiteral("QExtLogBinaryToTextLayout"),
                           create_binarytotext_layout);

    mLayoutRegistry.insert(QStringLiteral("org.QExt.LogXMLLayout"),
                           create_xml_layout);
    mLayoutRegistry.insert(QStringLiteral("QExtLogXMLLayout"),
                           create_xml_layout);
}


bool QExtLogFactory::validateObjectProperty(QMetaProperty &metaProperty,
                                            const QString &property,
                                            QObject *object)
{
    // Validate:
    // - No null object pointer
    // - No empty property name
    // - Property exists on the object (QT or Java name)
    // - Property is readable
    // - Property is writable

    const char *context = "QExtLogFactory";
    QExtLogError e = QEXT_LOG_ERROR(QT_TR_NOOP("Unable to set property value on object"),
                                    QExtLogError::Error_ConfiguratorInvalidProperty,
                                    context);

    if (object == QEXT_NULLPTR)
    {
        QExtLogError ce = QEXT_LOG_ERROR(QT_TR_NOOP("Invalid null object pointer"),
                                         0,
                                         context);
        e.addCausingError(ce);
        logger()->error(e);
        return false;
    }
    if (property.isEmpty())
    {
        QExtLogError ce = QEXT_LOG_ERROR(QT_TR_NOOP("Invalid empty property name"),
                                         0,
                                         context);
        e.addCausingError(ce);
        logger()->error(e);
        return false;
    }
    const QMetaObject *p_meta_object = object->metaObject();
    QString propertyString = property;
    int i = p_meta_object->indexOfProperty(propertyString.toLatin1().constData());
    if (i < 0)
    {
        // Try name with lower case first character. Java properties names
        // start upper case
        propertyString[0] = propertyString[0].toLower();
        i = p_meta_object->indexOfProperty(propertyString.toLatin1().constData());
        if (i < 0)
        {
            QExtLogError ce = QEXT_LOG_ERROR(QT_TR_NOOP("Property '%1' does not exist in class '%2'"),
                                             0,
                                             context);
            ce << propertyString
               << QString::fromLatin1(object->metaObject()->className());
            e.addCausingError(ce);
            logger()->error(e);
            return false;
        }
    }
    metaProperty = p_meta_object->property(i);
    if (!metaProperty.isWritable())
    {
        QExtLogError ce = QEXT_LOG_ERROR(QT_TR_NOOP("Property '%1' is not writable in class '%2'"),
                                         0,
                                         context);
        ce << property
           << QString::fromLatin1(object->metaObject()->className());
        e.addCausingError(ce);
        logger()->error(e);
        return false;
    }

    return true;
}
