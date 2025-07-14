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

#ifndef _QEXTLOGDATABASEAPPENDER_H
#define _QEXTLOGDATABASEAPPENDER_H

#include <qextLogAppenderSkeleton.h>

#include <QtSql/QSqlDatabase>

/*!
 * \brief The class QExtLogDatabaseAppender appends log events to a sql database.
 *
 * \note All the functions declared in this class are thread-safe.
 * &nbsp;
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogDatabaseAppender : public QExtLogAppenderSkeleton
{
    Q_OBJECT

    /*!
     * The property holds sql database connection the appender uses.
     *
     * The default is null to use the codec the writer has set.
     *
     * \sa connection(), setConnection()
     */
    Q_PROPERTY(QString connection READ connection WRITE setConnection)

    /*!
     * The property holds sql database table name
     *
    \sa table(), setTable()
     */
    Q_PROPERTY(QString table READ table WRITE setTable)
public:
    QExtLogDatabaseAppender(QObject *parent = QEXT_NULLPTR);
    QExtLogDatabaseAppender(const QExtLogLayoutSharedPtr &layout,
                     QObject *parent = QEXT_NULLPTR);
    QExtLogDatabaseAppender(const QExtLogLayoutSharedPtr &layout
                     , const QString &tableName
                     , const QString &connection = QSqlDatabase::defaultConnection
                     , QObject *parent = QEXT_NULLPTR);

private:
    Q_DISABLE_COPY(QExtLogDatabaseAppender)

public:
    bool requiresLayout() const QEXT_OVERRIDE;

    QString connection() const;
    QString table() const;

    void setConnection(const QString &connection);
    void setTable(const QString &table);

    void activateOptions() QEXT_OVERRIDE;

protected:
    void append(const QExtLoggingEvent &event) QEXT_OVERRIDE;

    /*!
     * Tests if all entry conditions for using append() in this class are
     * met.
     *
     * If a conditions is not met, an error is logged and the function
     * returns false. Otherwise the result of
     * QExtLogAppenderSkeleton::checkEntryConditions() is returned.
     *
     * The checked conditions are:
     * - A writer has been set (QExtLogError::Error_AppenderUseMissingWriter)
     *
     * The function is called as part of the checkEntryConditions() chain
     * started by QExtLogAppenderSkeleton::doAppend().
     *
     * \sa QExtLogAppenderSkeleton::doAppend(),
     *     QExtLogAppenderSkeleton::checkEntryConditions()
     */
    bool checkEntryConditions() const QEXT_OVERRIDE;

    void closeWriter();

private:
    QString connectionName;
    QString tableName;
};

inline QString QExtLogDatabaseAppender::connection() const
{
    QMutexLocker locker(&mObjectGuard);
    return connectionName;
}

inline QString QExtLogDatabaseAppender::table() const
{
    QMutexLocker locker(&mObjectGuard);
    return tableName;
}

#endif // _QEXTLOGDATABASEAPPENDER_H
