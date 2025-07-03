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

#ifndef _QEXTLOGDATETIME_H
#define _QEXTLOGDATETIME_H

#include <qextLoggingGlobal.h>

#include <QDateTime>
#include <QTimeZone>

/*!
 * \brief The class QExtLogDateTime provides extended functionality for QDateTime.
 *
 * The class QExtLogDateTime implements additional formatting options for
 * toString() and provides conversion functions from and to milliseconds.
 */
class QEXT_LOGGING_API QExtLogDateTime : public QDateTime
{
public:
    /*!
     * Constructs a null date time.
     *
     * \sa QDateTime::QDateTime()
     */
    QExtLogDateTime();

    ~QExtLogDateTime();

    /*!
     * Constructs a copy of another QDateTime.
     *
     * \sa QDateTime::QDateTime(const QDateTime &other)
     */
    QExtLogDateTime(const QDateTime &other);

    QExtLogDateTime(const QExtLogDateTime &other);

#if QT_VERSION < 0x060500
    /*!
     * Constructs a datetime with the given \a date and \a time, using
     * the time specification defined by \a timeSpec.
     *
     * \sa QDateTime::QDateTime(const QDate &date, const QTime &time,
     *     Qt::TimeSpec timeSpec = Qt::LocalTime)
     */
    QExtLogDateTime(QDate date, QTime time, Qt::TimeSpec timeSpec = Qt::LocalTime);
#else
    /*!
     * Constructs a datetime with the given \a date and \a time, using
     * the time zone defined by \a QTimeZone.
     *
     * \sa QDateTime::QDateTime(const QDate &date, const QTime &time,
     *     QTimeZone = QTimeZone(QTimeZone::LocalTime))
     */
    QExtLogDateTime(QDate date, QTime time, QTimeZone = QTimeZone(QTimeZone::LocalTime));
#endif

    /*!
     * Assigns \a other to this QExtLogDateTime and returns a reference to it.
     */
    QExtLogDateTime &operator=(const QExtLogDateTime &other);

    /*!
     * Returns the datetime as a string. The \a format parameter
     * determines the format of the result string.
     *
     *
     * Alternatively the \a format parameter can specify one of the
     * following strings.
     *
     * <table align="center" border="1" cellpadding="2" cellspacing="0" bordercolor="#84b0c7">
     * <tr bgcolor="#d5e1e8">
     * <th width="20%"> String </th>
     * <th> Format </th>
     * </tr><tr>
     * <td> ABSOLUTE </td>
     * <td> uses the format HH:mm:ss.zzz </td>
     * </tr><tr bgcolor="#ffffff">
     * <td> DATE </td>
     * <td> uses the format dd MMM YYYY HH:mm:ss.zzz </td>
     * </tr><tr>
     * <td> ISO8601 </td>
     * <td> uses the format yyyy-MM-dd hh:mm:ss.zzz </td>
     * </tr><tr bgcolor="#ffffff">
     * <td> NONE </td>
     * <td> uses an empty string as format </td>
     * </tr><tr bgcolor="#ffffff">
     * <td> RELATIVE </td>
     * <td> returns the milliseconds since start of the program</td>
     * </tr>
     * </table>
     *
     * \sa QDateTime::toString(const QString &format)
     */
    QString toString(const QString &format) const;

    /*!
     * Returns the current datetime, as reported by the system clock, in
     * the local time zone.
     *
     * \sa QDateTime::currentDateTime()
     */
    static QExtLogDateTime currentDateTime();
#if QT_VERSION < 0x060500
    static QExtLogDateTime fromMSecsSinceEpoch(qint64 msecs, Qt::TimeSpec spec, int offsetSeconds = 0);
#else
    static QExtLogDateTime fromMSecsSinceEpoch(qint64 msecs, QTimeZone timeZone);
#endif

    static QExtLogDateTime fromMSecsSinceEpoch(qint64 msecs);

private:
    QString formatDateTime(const QString &format) const;
};

inline QExtLogDateTime::QExtLogDateTime(const QDateTime &other) : QDateTime(other)
{}

#if QT_VERSION < 0x060500
inline QExtLogDateTime::QExtLogDateTime(QDate date, QTime time, Qt::TimeSpec timeSpec) :
    QDateTime(date, time, timeSpec)
{}
#else
inline QExtLogDateTime::QExtLogDateTime(QDate date, QTime time, QTimeZone timeZone) :
    QDateTime(date, time, timeZone)
{}
#endif

inline QExtLogDateTime &QExtLogDateTime::operator=(const QExtLogDateTime &other)
{
    QDateTime::operator=(other);
    return *this;
}

inline QExtLogDateTime QExtLogDateTime::currentDateTime()
{
    return QExtLogDateTime(QDateTime::currentDateTime());
}

inline QExtLogDateTime QExtLogDateTime::fromMSecsSinceEpoch(qint64 msecs)
{
    return QExtLogDateTime(QDateTime::fromMSecsSinceEpoch(msecs));
}

#if QT_VERSION < 0x060500
inline QExtLogDateTime QExtLogDateTime::fromMSecsSinceEpoch(qint64 msecs, Qt::TimeSpec spec, int offsetSeconds)
{
    return QExtLogDateTime(QDateTime::fromMSecsSinceEpoch(msecs, spec, offsetSeconds));
}
#else
inline QExtLogDateTime QExtLogDateTime::fromMSecsSinceEpoch(qint64 msecs, QTimeZone timeZone)
{
    return QExtLogDateTime(QDateTime::fromMSecsSinceEpoch(msecs, timeZone));
}
#endif

Q_DECLARE_TYPEINFO(QExtLogDateTime, Q_MOVABLE_TYPE);

#endif // _QEXTLOGDATETIME_H
