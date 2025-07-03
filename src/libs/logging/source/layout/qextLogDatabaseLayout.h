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

#ifndef _QEXTLOGDATABASELAYOUT_H
#define _QEXTLOGDATABASELAYOUT_H

#include <qextLogLayout.h>

#include <QtSql/QSqlRecord>

/*!
 * \brief The class QExtLogDatabaseLayout outputs loggin event into sql table.
 *
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogDatabaseLayout : public QExtLogLayout
{
    Q_OBJECT

    /*!
        The property holds column name to save timestamp of log event
    */
    Q_PROPERTY(QString timeStampColumn READ timeStampColumn WRITE setTimeStampColumn)
    /*!
        The property holds column name to save logger name of log event
    */
    Q_PROPERTY(QString loggenameColumn READ loggenameColumn WRITE setLoggenameColumn)
    /*!
        The property holds column name to save thread name of log event
    */
    Q_PROPERTY(QString threadNameColumn READ threadNameColumn WRITE setThreadNameColumn)
    /*!
        The property holds column name to save level of log event
    */
    Q_PROPERTY(QString levelColumn READ levelColumn WRITE setLevelColumn)
    /*!
        The property holds column name to save message of log event
    */
    Q_PROPERTY(QString messageColumn READ messageColumn WRITE setMessageColumn)


public:
    QExtLogDatabaseLayout(QObject *parent = nullptr);
    // virtual ~QExtLogDatabaseLayout(); // Use compiler default
private:
    Q_DISABLE_COPY(QExtLogDatabaseLayout)

public:
    virtual QSqlRecord formatRecord(const QExtLoggingEvent &event);
    QString format(const QExtLoggingEvent &event) override;

    QString timeStampColumn() const;
    QString loggenameColumn() const;
    QString threadNameColumn() const;
    QString levelColumn() const;
    QString messageColumn() const;

    void setTimeStampColumn(const QString &columnName);
    void setLoggenameColumn(const QString &columnName);
    void setThreadNameColumn(const QString &columnName);
    void setLevelColumn(const QString &columnName);
    void setMessageColumn(const QString &columnName);

private:
    QString mTimeStamp;
    QString mLoggename;
    QString mThreadName;
    QString mLevel;
    QString mMessage;
};


inline QExtLogDatabaseLayout::QExtLogDatabaseLayout(QObject *parent) :
    QExtLogLayout(parent)
{}

#endif // _QEXTLOGDATABASELAYOUT_H
