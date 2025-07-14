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

#include <qextLogger.h>
#include <qextLogPropertyConfigurator.h>
#include <qextLoggerRepository.h>
#include <qextLogConsoleAppender.h>
#include <qextLogTTCCLayout.h>
#include <qextLogManager.h>
#include <qextLogFileAppender.h>

#include "loggerobject.h"
#include "loggerobjectprio.h"
#include "loggerstatic.h"

#include <QCoreApplication>
#include <QScopedPointer>
#include <QStringBuilder>
#include <QString>
#include <QFile>
#include <QLoggingCategory>

static void initializeRootLogger();
static void shutdownRootLogger();
static void logStartup();
static void logShutdown();
static void setupRootLogger(const QString &introMessage);
static void shutDownRootLogger(const QString &extroMessage);

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);

    const auto *object = new LoggerObject(&application);
    const auto *object1 = new LoggerObjectPrio(&application);
    Q_UNUSED(object1)
    QLoggingCategory::setFilterRules("*.debug=false\n"
                                     "test.category1.debug=true");

    QObject::connect(object, &LoggerObject::exit, &application, &QCoreApplication::exit);

    initializeRootLogger();
    logStartup();

    int ret;
    {
        QScopedPointer<LoggerStatic> object2(new LoggerStatic());

        ret = QCoreApplication::exec();
    }

    logShutdown();
    shutdownRootLogger();

    return ret;
}

void initializeRootLogger()
{
    setupRootLogger(QStringLiteral("Root logger is setup."));
}

void shutdownRootLogger()
{
    shutDownRootLogger(QStringLiteral("Root logger was shutdown."));
}

void logStartup()
{
    auto logger = QExtLogger::rootLogger();

    logger->info(QStringLiteral("################################################################"));
    logger->info(QStringLiteral("#                          START                               #"));
    logger->info(QStringLiteral("################################################################"));
}

void logShutdown()
{
    auto logger = QExtLogger::rootLogger();

    logger->info(QStringLiteral("################################################################"));
    logger->info(QStringLiteral("#                          STOP                                #"));
    logger->info(QStringLiteral("################################################################"));
}

void setupRootLogger(const QString &introMessage)
{
    // Create a layout
    auto logger = QExtLogger::rootLogger();
    auto *layout = new QExtLogTTCCLayout();
    layout->setName(QStringLiteral("My QExtLogLayout"));
    layout->activateOptions();
    // Create a console appender
    QExtLogConsoleAppender *consoleAppender = new QExtLogConsoleAppender(layout, QExtLogConsoleAppender::Target_Stdout);
    consoleAppender->setName(QStringLiteral("My QExtLogAppender"));
    consoleAppender->activateOptions();
    // Add appender on root logger
    logger->addAppender(consoleAppender);
    // Create a file appender
    QExtLogFileAppender *fileAppender = new QExtLogFileAppender(layout, QCoreApplication::applicationDirPath() + "/basic.log", true);
    fileAppender->setName(QStringLiteral("My file appender"));
    fileAppender->activateOptions();
    // Add appender on root logger
    logger->addAppender(fileAppender);

    // Set level to info
    logger->setLevel(QExtLogLevel::Info);
    // Enable handling of Qt messages
    QExtLogManager::setHandleQtMessages(true);

    if (!introMessage.isEmpty())
        logger->info(introMessage);

    qWarning("Handling Qt messages is enabled");
}

void shutDownRootLogger(const QString &extroMessage)
{
    auto logger = QExtLogger::rootLogger();

    if (!extroMessage.isEmpty())
        logger->info(extroMessage);
    logger->removeAllAppenders();
    logger->loggerRepository()->shutdown();
}
