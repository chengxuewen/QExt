/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
 * Copyright 2010 Michael Filonenko
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

#include <qextLogDatabaseAppender.h>
#include <qextLogDatabaseLayout.h>
#include <qextLoggingEvent.h>
#include <qextLogDatetime.h>

#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QtSql/QSqlError>

QExtLogDatabaseAppender::QExtLogDatabaseAppender(QObject *parent) :
      QExtLogAppenderSkeleton(false, parent)
    , connectionName(QSqlDatabase::defaultConnection)
{
}


QExtLogDatabaseAppender::QExtLogDatabaseAppender(const QExtLogLayoutSharedPtr &layout,
                                   QObject *parent)
    : QExtLogAppenderSkeleton(false, layout, parent)
    , connectionName(QSqlDatabase::defaultConnection)
{
}


QExtLogDatabaseAppender::QExtLogDatabaseAppender(const QExtLogLayoutSharedPtr &layout,
                                   const QString &tableName,
                                   const QString &connection,
                                   QObject *parent)
    : QExtLogAppenderSkeleton(false, layout, parent)
    , connectionName(connection)
    , tableName(tableName)
{
}

void QExtLogDatabaseAppender::setConnection(const QString &connection)
{
    QMutexLocker locker(&mObjectGuard);

    if (connectionName == connection)
        return;

    connectionName = connection;
}

void QExtLogDatabaseAppender::setTable(const QString &table)
{
    QMutexLocker locker(&mObjectGuard);

    if (table == tableName)
        return;

    tableName = table;
}

void QExtLogDatabaseAppender::activateOptions()
{
    QMutexLocker locker(&mObjectGuard);

    if (!QSqlDatabase::contains(connectionName) || tableName.isEmpty())
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Activation of QExtLogAppender '%1' that requires sql connection and table and has no connection or table set")
                                         , QExtLogError::Error_AppenderMissingDatabaseOrTable);
        e << name();
        logger()->error(e);
        return;
    }

    QExtLogAppenderSkeleton::activateOptions();
}

bool QExtLogDatabaseAppender::requiresLayout() const
{
    return true;
}

void QExtLogDatabaseAppender::append(const QExtLoggingEvent &event)
{
    QExtLogDatabaseLayout *databaseLayout = qobject_cast<QExtLogDatabaseLayout *>(layout().data());

    if (databaseLayout != nullptr)
    {
        QSqlRecord record = databaseLayout->formatRecord(event);

        QSqlDatabase database = QSqlDatabase::database(connectionName);
        QSqlQuery query(database);
        if (!query.exec(database.driver()->sqlStatement(QSqlDriver::InsertStatement
                        , tableName, record, false)))
        {
            QExtLogError e = QEXT_LOG_ERROR(QT_TR_NOOP("Sql query exec error: '%1'"),
                                      QExtLogError::Error_AppenderExecSqlQueryFailed,
                                      Q_FUNC_INFO);
            e << query.lastQuery() + " " + query.lastError().text();
            logger()->error(e);
        }
    }
    else
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Use of appender '%1' with invalid layout"),
                                         QExtLogError::Error_AppenderInvalidDatabaseLayout);
        e << name();
        logger()->error(e);
    }
}

bool QExtLogDatabaseAppender::checkEntryConditions() const
{
    if (!QSqlDatabase::contains(connectionName) || tableName.isEmpty())
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Use of appender '%1' with invalid database or empty table name"),
                                         QExtLogError::Error_AppenderMissingDatabaseOrTable);
        e << name();
        logger()->error(e);
        return false;
    }

    return QExtLogAppenderSkeleton::checkEntryConditions();
}

// #include "moc_databaseappender.cpp"

