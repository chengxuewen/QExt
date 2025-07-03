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

#include <qextLogPropertyConfigurator.h>
#include <qextLogConfiguratorHelper.h>
#include <qextLogFactory.h>
#include <qextLogOptionConverter.h>
#include <qextLogProperties.h>
#include <qextLogAppender.h>
#include <qextLogLayout.h>
#include <qextLogger.h>
#include <qextLogManager.h>
#include <qextLoggerRepository.h>
#include <qextLogListAppender.h>

#include <QFile>

#if (__cplusplus >= 201703L) // C++17 or later
#include <utility>
#endif

QEXT_DECLARE_STATIC_LOGGER(staticLogger, QExtLogPropertyConfigurator)

bool QExtLogPropertyConfigurator::doConfigure(const QExtLogProperties &properties,
                                       QExtLoggerRepository *loggerRepository)
{
    startCaptureErrors();
    configureFromProperties(properties, loggerRepository);
    return stopCaptureErrors();
}


bool QExtLogPropertyConfigurator::doConfigure(const QString &configFileName,
                                       QExtLoggerRepository *loggerRepository)
{
    startCaptureErrors();
    configureFromFile(configFileName, loggerRepository);
    return stopCaptureErrors();
}


bool QExtLogPropertyConfigurator::doConfigure(const QSettings &settings,
                                       QExtLoggerRepository *loggerRepository)
{
    startCaptureErrors();
    configureFromSettings(settings, loggerRepository);
    return stopCaptureErrors();
}


bool QExtLogPropertyConfigurator::configure(const QExtLogProperties &properties)
{
    QExtLogPropertyConfigurator configurator;
    return configurator.doConfigure(properties);
}


bool QExtLogPropertyConfigurator::configure(const QString &configFilename)
{
    QExtLogPropertyConfigurator configurator;
    return configurator.doConfigure(configFilename);
}


bool QExtLogPropertyConfigurator::configure(const QSettings &settings)
{
    QExtLogPropertyConfigurator configurator;
    return configurator.doConfigure(settings);
}


bool QExtLogPropertyConfigurator::configureAndWatch(const QString &configFilename)
{
    // Stop an existing watch to avoid a possible concurrent configuration
    QExtLogConfiguratorHelper::setConfigurationFile();
    if (configFilename.isEmpty())
        return true;

    QExtLogPropertyConfigurator configurator;
    bool result = configurator.doConfigure(configFilename);
    QExtLogConfiguratorHelper::setConfigurationFile(configFilename, configure);
    return result;
}


void QExtLogPropertyConfigurator::configureFromFile(const QString &configFileName,
        QExtLoggerRepository *loggerRepository)
{
    QFile file(configFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QExtLogError e = QEXT_LOG_ERROR(QT_TR_NOOP("Unable to open property file '%1'"),
                                  QExtLogError::Error_ConfiguratorOpenFileFailed,
                                  "QExtLogPropertyConfigurator");
        e << configFileName;
        e.addCausingError(QExtLogError(file.errorString(), file.error()));
        staticLogger()->error(e);
        return;
    }
    QExtLogProperties properties;
    properties.load(&file);
    if (file.error())
    {
        QExtLogError e = QEXT_LOG_ERROR(QT_TR_NOOP("Unable to read property file '%1'"),
                                  QExtLogError::Error_ConfiguratorReadFileFailed,
                                  "QExtLogPropertyConfigurator");
        e << configFileName;
        e.addCausingError(QExtLogError(file.errorString(), file.error()));
        staticLogger()->error(e);
        return;
    }
    configureFromProperties(properties, loggerRepository);
}


void QExtLogPropertyConfigurator::configureFromProperties(const QExtLogProperties &properties,
        QExtLoggerRepository *loggerRepository)
{
    if (!loggerRepository)
        loggerRepository = QExtLogManager::loggerRepository();

    configureGlobalSettings(properties, loggerRepository);
    configureRootLogger(properties, loggerRepository);
    configureNonRootElements(properties, loggerRepository);
    mAppenderRegistry.clear();
}


void QExtLogPropertyConfigurator::configureFromSettings(const QSettings &settings,
        QExtLoggerRepository *loggerRepository)
{
    QExtLogProperties properties;
    properties.load(settings);
    configureFromProperties(properties, loggerRepository);
}


void QExtLogPropertyConfigurator::configureGlobalSettings(const QExtLogProperties &properties,
        QExtLoggerRepository *loggerRepository) const
{
    Q_ASSERT_X(loggerRepository, "QExtLogPropertyConfigurator::configureGlobalSettings()", "loggerRepository must not be null.");

    const QLatin1String key_reset("log4j.reset");
    const QLatin1String key_debug("log4j.Debug");
    const QLatin1String key_config_debug("log4j.configDebug");
    const QLatin1String key_threshold("log4j.threshold");
    const QLatin1String key_handle_qt_messages("log4j.handleQtMessages");
    const QLatin1String key_watch_this_file("log4j.watchThisFile");
    const QLatin1String key_filterRules("log4j.qtLogging.filterRules");
    const QLatin1String key_messagePattern("log4j.qtLogging.messagePattern");

    // Test each global setting and set it
    // - Reset: log4j.reset
    // - Debug: log4j.Debug, log4j.configDebug
    // - Threshold: log4j.threshold
    // - Handle Qt Messages: log4j.handleQtMessages
    // - Watch the properties file
    // - filterRules: QLoggingCategory::setFilterRules
    // - messagePattern: qSetMessagePattern

    // Reset
    QString value = properties.property(key_reset);
    if (!value.isEmpty() && QExtLogOptionConverter::toBoolean(value, false))
    {
        // Use QExtLogManager and not loggerRepository to reset internal
        // logging.
        QExtLogManager::resetConfiguration();
        staticLogger()->debug(QStringLiteral("Reset configuration"));
    }

    // Debug
    value = properties.property(key_debug);
    if (value.isNull())
    {
        value = properties.property(key_config_debug);
        if (!value.isNull())
            staticLogger()->warn(QStringLiteral("[%1] is deprecated. Use [%2] instead."), key_config_debug, key_debug);
    }
    if (!value.isNull())
    {
        // Don't use QExtLogOptionConverter::toLevel(). Invalid level string is a valid setting
        bool ok;
        QExtLogLevel level = QExtLogLevel::fromString(value, &ok);
        if (!ok)
            level = QExtLogLevel::Debug;
        QExtLogManager::logLogger()->setLevel(level);
        staticLogger()->debug(QStringLiteral("Set level for Log4Qt logging to %1"),
                        QExtLogManager::logLogger()->level().toString());
    }

    // Threshold
    value = properties.property(key_threshold);
    if (!value.isNull())
    {
        loggerRepository->setThreshold(QExtLogOptionConverter::toLevel(value, QExtLogLevel::All));
        staticLogger()->debug(QStringLiteral("Set threshold for QExtLoggerRepository to %1"),
                        loggerRepository->threshold().toString());
    }

    // Handle Qt messages
    value = properties.property(key_handle_qt_messages);
    if (!value.isNull())
    {
        QExtLogManager::setHandleQtMessages(QExtLogOptionConverter::toBoolean(value, false));
        staticLogger()->debug(QStringLiteral("Set handling of Qt messages QExtLoggerRepository to %1"),
                        QVariant(QExtLogManager::handleQtMessages()).toString());
    }

    // Watch this file
    value = properties.property(key_watch_this_file);
    if (!value.isNull())
    {
        QExtLogManager::setWatchThisFile(QExtLogOptionConverter::toBoolean(value, false));
        staticLogger()->debug(QStringLiteral("Set watching the properties file to %1"),
                        QVariant(QExtLogManager::watchThisFile()).toString());
    }

    value = properties.property(key_filterRules);
    if (!value.isNull())
    {
        value.replace(";", "\n");
        QExtLogManager::setFilterRules(value);
        staticLogger()->debug(QStringLiteral("Set filter rules to %1"), QExtLogManager::filterRules());
    }

    value = properties.property(key_messagePattern);
    if (!value.isNull())
    {
        QExtLogManager::setMessagePattern(value);
        staticLogger()->debug(QStringLiteral("Set message pattern to %1"), QExtLogManager::messagePattern());
    }
}


void QExtLogPropertyConfigurator::configureNonRootElements(const QExtLogProperties &properties,
        QExtLoggerRepository *loggerRepository)
{
    Q_ASSERT_X(loggerRepository, "QExtLogPropertyConfigurator::configureNonRootElements()", "loggerRepository must not be null.");

    const QString logger_prefix = QStringLiteral("log4j.logger.");
    const QString category_prefix = QStringLiteral("log4j.category.");

    // Iterate through all entries:
    // - Test for the logger/category prefix
    // - Convert JAVA class names to C++ ones
    // - Parse logger data (QExtLogLevel, QExtLogAppender)
    // - Parse logger additivity

    QStringList keys = properties.propertyNames();

#if (__cplusplus >= 201703L)
    for (const auto &key : std::as_const(keys))
#else
    for (const auto &key : qAsConst(keys))
#endif
    {
        QString java_name;
        if (key.startsWith(logger_prefix))
            java_name = key.mid(logger_prefix.length());
        else if (key.startsWith(category_prefix))
            java_name = key.mid(category_prefix.length());
        QString cpp_name = QExtLogOptionConverter::classNameJavaToCpp(java_name);
        if (!java_name.isEmpty())
        {
            QExtLogger *p_logger = loggerRepository->logger(cpp_name);
            QString value = QExtLogOptionConverter::findAndSubst(properties, key);
            parseLogger(properties, p_logger, key, value);
            parseAdditivityForLogger(properties, p_logger, java_name);
        }
    }
}


void QExtLogPropertyConfigurator::configureRootLogger(const QExtLogProperties &properties,
        QExtLoggerRepository *loggerRepository)
{
    Q_ASSERT_X(loggerRepository, "QExtLogPropertyConfigurator::configureRootLogger()", "loggerRepository must not be null.");

    const QLatin1String key_root_logger("log4j.rootLogger");
    const QLatin1String key_root_category("log4j.rootCategory");

    // - Test for the logger/category prefix
    // - Parse logger data for root logger

    QString key = key_root_logger;
    QString value = QExtLogOptionConverter::findAndSubst(properties, key);
    if (value.isNull())
    {
        key = key_root_category;
        value = QExtLogOptionConverter::findAndSubst(properties, key);
        if (!value.isNull())
            staticLogger()->warn(QStringLiteral("[%1] is deprecated. Use [%2] instead."), key_root_category, key_root_logger);
    }

    if (value.isNull())
        staticLogger()->debug(QStringLiteral("Could not find root logger information. Is this correct?"));
    else
        parseLogger(properties, loggerRepository->rootLogger(), key, value);
}


void QExtLogPropertyConfigurator::parseAdditivityForLogger(const QExtLogProperties &properties,
        QExtLogger *logger,
        const QString &log4jName) const
{
    Q_ASSERT_X(logger, "parseAdditivityForLogger()", "pLogger must not be null.");

    const QLatin1String additivity_prefix("log4j.additivity.");

    // - Lookup additivity key for logger
    // - Set additivity, if specified

    QString key = additivity_prefix + log4jName;
    QString value = QExtLogOptionConverter::findAndSubst(properties, key);
    staticLogger()->debug(QStringLiteral("Parsing additivity for logger: key '%1', value '%2'"), key, value);
    if (!value.isEmpty())
    {
        bool additivity = QExtLogOptionConverter::toBoolean(value, true);
        staticLogger()->debug(QStringLiteral("Setting additivity for logger '%1' to '%2'"), logger->name(), QVariant(value).toString());
        logger->setAdditivity(additivity);
    }
}


QExtLogAppenderSharedPtr QExtLogPropertyConfigurator::parseAppender(const QExtLogProperties &properties,
        const QString &name)
{
    // - Test if appender has been parsed before
    // - Find appender key
    // - Create appender object
    // - Set layout, if required by appender
    // - Set properties
    // - Activate options
    // - Add appender to registry

    const QLatin1String appender_prefix("log4j.appender.");

    staticLogger()->debug(QStringLiteral("Parsing appender named '%1'"), name);

    if (mAppenderRegistry.contains(name))
    {
        staticLogger()->debug(QStringLiteral("QExtLogAppender '%1' was already parsed."), name);
        return mAppenderRegistry.value(name);
    }

    QString key = appender_prefix + name;
    QString value = QExtLogOptionConverter::findAndSubst(properties, key);
    if (value.isNull())
    {
        QExtLogError e = QEXT_LOG_ERROR(QT_TR_NOOP("Missing appender definition for appender named '%1'"),
                                  QExtLogError::Error_ConfiguratorMissingAppender,
                                  "QExtLogPropertyConfigurator");
        e << name;
        staticLogger()->error(e);
        return nullptr;
    }
    QExtLogAppenderSharedPtr p_appender(QExtLogFactory::createAppender(value));
    if (!p_appender)
    {
        QExtLogError e = QEXT_LOG_ERROR(QT_TR_NOOP("Unable to create appender of class '%1' named '%2'"),
                                  QExtLogError::Error_ConfiguratorUnknownAppenderClass,
                                  "QExtLogPropertyConfigurator");
        e << value << name;
        staticLogger()->error(e);
        return nullptr;
    }
    p_appender->setName(name);

    if (p_appender->requiresLayout())
    {
        QExtLogLayoutSharedPtr p_layout = parseLayout(properties, key);
        if (p_layout)
            p_appender->setLayout(p_layout);
        else
            return nullptr;
    }

    QStringList exclusions;
    exclusions << QStringLiteral("layout");
    setProperties(properties, key + QStringLiteral("."), exclusions, p_appender.data());
    auto *p_appenderskeleton = qobject_cast<QExtLogAppenderSkeleton *>(p_appender.data());
    if (p_appenderskeleton)
        p_appenderskeleton->activateOptions();

    mAppenderRegistry.insert(name, p_appender);
    return p_appender;
}


QExtLogLayoutSharedPtr QExtLogPropertyConfigurator::parseLayout(const QExtLogProperties &properties,
        const QString &appendename)
{
    Q_ASSERT_X(!appendename.isEmpty(), "QExtLogPropertyConfigurator::parseLayout()", "rAppenderKey must not be empty.");

    // - Find layout key
    // - Create layput object
    // - Set properties
    // - Activate options

    const QLatin1String layout_suffix(".layout");

    staticLogger()->debug(QStringLiteral("Parsing layout for appender named '%1'"), appendename);

    QString key = appendename + layout_suffix;
    QString value = QExtLogOptionConverter::findAndSubst(properties, key);
    QExtLogLayoutSharedPtr p_layout;
    if (value.isNull())
    {
        QExtLogError e = QEXT_LOG_ERROR(QT_TR_NOOP("Missing layout definition for appender '%1'"),
                                  QExtLogError::Error_ConfiguratorMissingLayout,
                                  "QExtLogPropertyConfigurator");
        e << appendename;
        staticLogger()->error(e);
        return p_layout;
    }
    p_layout.reset(QExtLogFactory::createLayout(value));
    if (!p_layout)
    {
        QExtLogError e = QEXT_LOG_ERROR(QT_TR_NOOP("Unable to create layoput of class '%1' requested by appender '%2'"),
                                  QExtLogError::Error_ConfiguratorUnknownLayoutClass,
                                  "QExtLogPropertyConfigurator");
        e << value << appendename;
        staticLogger()->error(e);
        return p_layout;
    }

    setProperties(properties, key + QStringLiteral("."), QStringList(), p_layout.data());
    p_layout->activateOptions();

    return p_layout;
}


void QExtLogPropertyConfigurator::parseLogger(const QExtLogProperties &properties,
                                       QExtLogger *logger,
                                       const QString &key,
                                       const QString &value)
{
    Q_ASSERT_X(logger, "QExtLogPropertyConfigurator::parseLogger()", "pLogger must not be null.");
    Q_ASSERT_X(!key.isEmpty(), "QExtLogPropertyConfigurator::parseLogger()", "rKey must not be empty.");

    const QLatin1String keyword_inherited("INHERITED");

    // - Split value on comma
    // - If level value, is specified
    //   - Test for NULL and INHERITED
    //   - Ensure root logger is not set to NULL
    //   - Set level
    // - For each entry
    //   - Create QExtLogAppender

    staticLogger()->debug(QStringLiteral("Parsing logger: key '%1', value '%2'"), key, value);
    QStringList appenders = value.split(QLatin1Char(','));
    QStringListIterator i (appenders);

    // First entry is the level. There will be always one entry, even if the rValue is
    // empty or does not contain a comma.
    QString sValue = i.next().trimmed();
    if (!sValue.isEmpty())
    {
        QExtLogLevel level;
        if (sValue.compare(keyword_inherited, Qt::CaseInsensitive) == 0)
            level = QExtLogLevel::Null;
        else
            level = QExtLogOptionConverter::toLevel(sValue, QExtLogLevel::Debug);
        if (level == QExtLogLevel::Null && logger->name() == QString())
            staticLogger()->warn(QStringLiteral("The root logger level cannot be set to NULL."));
        else
        {
            logger->setLevel(level);
            staticLogger()->debug(QStringLiteral("Set level for logger '%1' to '%2'"),
                            logger->name(), logger->level().toString());
        }
    }

    logger->removeAllAppenders();
    while (i.hasNext())
    {
        sValue = i.next().trimmed();
        if (sValue.isEmpty())
            continue;
        QExtLogAppenderSharedPtr appander = parseAppender(properties, sValue);
        if (appander)
            logger->addAppender(appander);
    }
}


void QExtLogPropertyConfigurator::setProperties(const QExtLogProperties &properties,
        const QString &prefix,
        const QStringList &exclusion,
        QObject *object)
{
    Q_ASSERT_X(!prefix.isEmpty(), "QExtLogPropertyConfigurator::setProperties()", "rPrefix must not be empty.");
    Q_ASSERT_X(object, "QExtLogPropertyConfigurator::setProperties()", "pObject must not be null.");

    // Iterate through all entries:
    // - Test for prefix to determine, if setting is for object
    // - Skip empty property name
    // - Skip property names in exclusion list
    // - Set property on object

    staticLogger()->debug(QStringLiteral("Setting properties for object of class '%1' from keys starting with '%2'"),
                    QLatin1String(object->metaObject()->className()),
                    prefix);

    QStringList keys = properties.propertyNames();

#if (__cplusplus >= 201703L)
    for (const auto &key : std::as_const(keys))
#else
    for (const auto &key : qAsConst(keys))
#endif
    {
        if (!key.startsWith(prefix))
            continue;
        QString property = key.mid(prefix.length());
        if (property.isEmpty())
            continue;
        QStringList split_property = property.split(QLatin1Char('.'));
        if (exclusion.contains(split_property.at(0), Qt::CaseInsensitive))
            continue;
        QString value = QExtLogOptionConverter::findAndSubst(properties, key);
        QExtLogFactory::setObjectProperty(object, property, value);
    }
}

void QExtLogPropertyConfigurator::startCaptureErrors()
{
    Q_ASSERT_X(!mpConfigureErrors, "QExtLogPropertyConfigurator::startCaptureErrors()", "mpConfigureErrors must be empty.");

    auto *listAppender = new QExtLogListAppender();
    mpConfigureErrors.reset(listAppender);
    listAppender->setName(QStringLiteral("QExtLogPropertyConfigurator"));
    listAppender->setConfiguratorList(true);
    listAppender->setThreshold(QExtLogLevel::Error);
    QExtLogManager::logLogger()->addAppender(mpConfigureErrors);
}

bool QExtLogPropertyConfigurator::stopCaptureErrors()
{
    Q_ASSERT_X(mpConfigureErrors, "QExtLogPropertyConfigurator::stopCaptureErrors()", "mpConfigureErrors must not be empty.");
    const auto *listAppender = static_cast<QExtLogListAppender *>(mpConfigureErrors.data());
    QExtLogManager::logLogger()->removeAppender(mpConfigureErrors);
    QExtLogConfiguratorHelper::setConfigureError(listAppender->list());
    bool result = (listAppender->list().count() == 0);
    return result;
}
