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

#include <qextLogRollingFileAppender.h>
#include <qextLogOptionConverter.h>
#include <qextLoggingEvent.h>
#include <qextLogLayout.h>

#include <QFile>

QExtLogRollingFileAppender::QExtLogRollingFileAppender(QObject *parent) :
    QExtLogFileAppender(parent),
    mMaxBackupIndex(1),
    mMaximumFileSize(10 * 1024 * 1024)
{
}

QExtLogRollingFileAppender::QExtLogRollingFileAppender(const QExtLogLayoutSharedPtr &layout,
        const QString &fileName,
        QObject *parent) :
    QExtLogFileAppender(layout, fileName, parent),
    mMaxBackupIndex(1),
    mMaximumFileSize(10 * 1024 * 1024)
{
}

QExtLogRollingFileAppender::QExtLogRollingFileAppender(const QExtLogLayoutSharedPtr &layout,
        const QString &fileName,
        bool append,
        QObject *parent) :
    QExtLogFileAppender(layout, fileName, append, parent),
    mMaxBackupIndex(1),
    mMaximumFileSize(10 * 1024 * 1024)
{
}

void QExtLogRollingFileAppender::setMaxFileSize(const QString &maxFileSize)
{
    bool ok;
    qint64 max_file_size = QExtLogOptionConverter::toFileSize(maxFileSize, &ok);
    if (ok)
        setMaximumFileSize(max_file_size);
}

void QExtLogRollingFileAppender::append(const QExtLoggingEvent &event)
{
    QExtLogFileAppender::append(event);
    if (writer()->device()->size() > this->mMaximumFileSize)
        rollOver();
}

void QExtLogRollingFileAppender::openFile()
{
    // if we do not append, we roll the file to avoid data loss
    if (appendFile())
        QExtLogFileAppender::openFile();
    else
        rollOver();
}

void QExtLogRollingFileAppender::rollOver()
{
    logger()->debug(QStringLiteral("Rolling over with maxBackupIndex = %1"), mMaxBackupIndex);

    closeFile();

    QFile f;
    f.setFileName(file() + QLatin1Char('.') + QString::number(mMaxBackupIndex));
    if (f.exists() && !removeFile(f))
        return;

    for (int i = mMaxBackupIndex - 1; i >= 1; i--)
    {
        f.setFileName(file() + QLatin1Char('.') + QString::number(i));
        if (f.exists())
        {
            const QString target_file_name = file() + QLatin1Char('.') + QString::number(i + 1);
            if (!renameFile(f, target_file_name))
                return;
        }
    }

    f.setFileName(file());
    // it may not exist on first startup, don't output a warning in this case
    if (f.exists())
    {
        const QString target_file_name = file() + QStringLiteral(".1");
        if (!renameFile(f, target_file_name))
            return;
    }

    QExtLogFileAppender::openFile();
}

// #include "moc_rollingfileappender.cpp"
