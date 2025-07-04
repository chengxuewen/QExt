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

#include <qextLogBasicConfigurator.h>

#include <qextLogConsoleAppender.h>
#include <qextLogConfiguratorHelper.h>
#include <qextLogManager.h>
#include <qextLogPatternLayout.h>
#include <qextLogListAppender.h>

#include <QCoreApplication>
#include <QThread>

bool QExtLogBasicConfigurator::configure()
{
    auto *list = new QExtLogListAppender;
    list->setName(QStringLiteral("QExtLogBasicConfigurator"));
    list->setConfiguratorList(true);
    list->setThreshold(QExtLogLevel::Error);
    QExtLogManager::logLogger()->addAppender(QExtLogAppenderSharedPtr(list));

    QExtLogLayoutSharedPtr layout(new QExtLogPatternLayout(QExtLogPatternLayout::TTCC_CONVERSION_PATTERN));
    layout->setName(QStringLiteral("QExtLogBasicConfigurator TTCC"));
    layout->activateOptions();
    QExtLogConsoleAppender *appender = new QExtLogConsoleAppender(layout, QExtLogConsoleAppender::STDOUT_TARGET);
    appender->setName(QStringLiteral("QExtLogBasicConfigurator stdout"));
    appender->activateOptions();
    QExtLogManager::rootLogger()->addAppender(appender);

    QExtLogManager::logLogger()->removeAppender(list);
    QExtLogConfiguratorHelper::setConfigureError(list->list());
    return (list->list().count() == 0);
}

void QExtLogBasicConfigurator::configure(QExtLogAppender *pAppender)
{
    QExtLogManager::rootLogger()->addAppender(pAppender);
}

void QExtLogBasicConfigurator::resetConfiguration()
{
    QExtLogManager::resetConfiguration();
}
