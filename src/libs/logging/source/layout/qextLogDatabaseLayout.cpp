/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
** Copyright 2010 Michael Filonenko
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

#include <qextLogDatabaseLayout.h>
#include <qextLoggingEvent.h>
#include <qextLogDatetime.h>

#include <QtSql/QSqlField>

QSqlRecord QExtLogDatabaseLayout::formatRecord(const QExtLoggingEvent &event)
{
    QSqlField field;
    QSqlRecord record;

    if (!mTimeStamp.isEmpty())
    {
        field.setName(mTimeStamp);
        // field.setMetaType(QMetaType(QMetaType::QDateTime));
        field.setGenerated(true);
        field.setValue(QExtLogDateTime::fromMSecsSinceEpoch(event.timeStamp()));
        record.append(field);
    }

    if (!mLoggename.isEmpty())
    {
        field.setName(mLoggename);
        // field.setMetaType(QMetaType(QMetaType::QString));
        field.setGenerated(true);
        field.setValue(event.loggename());
        record.append(field);
    }

    if (!mThreadName.isEmpty())
    {
        field.setName(mThreadName);
        // field.setMetaType(QMetaType(QMetaType::QString));
        field.setGenerated(true);
        field.setValue(event.threadName());
        record.append(field);
    }

    if (!mLevel.isEmpty())
    {
        field.setName(mLevel);
        // field.setMetaType(QMetaType(QMetaType::QString));
        field.setGenerated(true);
        field.setValue(event.level().toString());
        record.append(field);
    }

    if (!mMessage.isEmpty())
    {
        field.setName(mMessage);
        // field.setMetaType(QMetaType(QMetaType::QString));
        field.setGenerated(true);
        field.setValue(event.message());
        record.append(field);
    }
    return record;
}


QString QExtLogDatabaseLayout::format(const QExtLoggingEvent &event)
{
    QString result;

    if (!mTimeStamp.isEmpty())
    {
        result.append(mTimeStamp);
        result.append(":");
        result.append(QExtLogDateTime::fromMSecsSinceEpoch(event.timeStamp()).toString(QStringLiteral("dd.MM.yyyy hh:mm")));
    }

    if (!mThreadName.isEmpty())
    {
        result.append(mThreadName);
        result.append(":");
        result.append(mThreadName);
        result.append("; ");
    }

    if (!mLevel.isEmpty())
    {
        result.append(mLevel);
        result.append(":");
        result.append(mLevel);
        result.append("; ");
    }

    if (!mLoggename.isEmpty())
    {
        result.append(mLoggename);
        result.append(":");
        result.append(mLoggename);
        result.append("; ");
    }

    if (!mMessage.isEmpty())
    {
        result.append(mMessage);
        result.append(":");
        result.append(mMessage);
        result.append("; ");
    }
    return result;
}

QString QExtLogDatabaseLayout::timeStampColumn() const
{
    return mTimeStamp;
}
QString QExtLogDatabaseLayout::loggenameColumn() const
{
    return mLoggename;
}
QString QExtLogDatabaseLayout::threadNameColumn() const
{
    return mThreadName;
}

QString QExtLogDatabaseLayout::levelColumn() const
{
    return mLevel;
}

QString QExtLogDatabaseLayout::messageColumn() const
{
    return mMessage;
}


void QExtLogDatabaseLayout::setTimeStampColumn(const QString &columnName)
{
    mTimeStamp = columnName;
}

void QExtLogDatabaseLayout::setLoggenameColumn(const QString &columnName)
{
    mLoggename = columnName;
}

void QExtLogDatabaseLayout::setThreadNameColumn(const QString &columnName)
{
    mThreadName = columnName;
}

void QExtLogDatabaseLayout::setLevelColumn(const QString &columnName)
{
    mLevel = columnName;
}

void QExtLogDatabaseLayout::setMessageColumn(const QString &columnName)
{
    mMessage = columnName;
}

// #include "moc_databaselayout.cpp"
