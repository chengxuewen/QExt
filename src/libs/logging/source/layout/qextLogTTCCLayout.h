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

#ifndef _QEXTLOGTTCCLAYOUT_H
#define _QEXTLOGTTCCLAYOUT_H

#include <qextLogLayout.h>
#include <qextLogPatternFormatter.h>

#include <QScopedPointer>

class QExtLoggingEvent;

/*!
 * \brief The class QExtLogTTCCLayout outputs the time, thread, logger and nested
 *        diagnostic context information of a logging event.
 *
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogTTCCLayout : public QExtLogLayout
{
    Q_OBJECT

    /*!
     * The property holds if the logger name is part of the formatted output.
     *
     * The default value is true for including the logger name.
     *
     * \sa categoryPrefixing(), setCategoryPrefixing()
     */
    Q_PROPERTY(bool categoryPrefixing READ categoryPrefixing WRITE setCategoryPrefixing)

    /*!
     * The property holds if the nested context information is part of the
     * formatted output.
     *
     * The default value it true for including the nested context information.
     *
     * \sa contextPrinting(), setContextPrinting()
     */
    Q_PROPERTY(bool contextPrinting READ contextPrinting WRITE setContextPrinting)

    /*!
     * The property holds the date format used by the layout.
     *
     * The default date format is "RELATIVE".
     *
     * \sa dateFormat(), setDateFormat()
     */
    Q_PROPERTY(QString dateFormat READ dateFormat WRITE setDateFormat)

    /*!
     * The property holds if the thread name is part of the formatted output.
     *
     * The default value it true for including the thread name.
     *
     * \sa threadPrinting(), setThreadPrinting()
     */
    Q_PROPERTY(bool threadPrinting READ threadPrinting WRITE setThreadPrinting)

public:
    /*!
     * The enum DateFormat defines constants for date formats.
     *
     * \sa setDateFormat(DateFormat), QExtLogDateTime::toString()
     */
    enum DateFormat
    {
        /*! The none date format string is "NONE".  */
        NONE,
        /*!
         * The iso8601 date format string is "ISO8601". The date will be
         * formatted as yyyy-MM-dd hh:mm:ss.zzz.
         */
        ISO8601,
        /*!
         * The absolute date format string is "ABSOLUTE". The date will be
         * formatted as HH:mm:ss.zzz.
         */
        ABSOLUTE,
        /*!
         * The date date format string is "DATE". The date will be formatted
         * as MMM YYYY HH:mm:ss.zzz.
         */
        DATE,
        /*!
         * The relative date format string is "RELATIVE". The date will be
         * formatted as milliseconds since start of the program.
         */
        RELATIVE
    };
    Q_ENUM(DateFormat)

    QExtLogTTCCLayout(QObject *parent = QEXT_NULLPTR);
    QExtLogTTCCLayout(const QString &dateFormat,
               QObject *parent = QEXT_NULLPTR);

    /*!
     * Creates a QExtLogTTCCLayout with the date formar value specified by
     * the \a dateFormat constant and the parent \a parent.
     */
    QExtLogTTCCLayout(DateFormat dateFormat,
               QObject *parent = QEXT_NULLPTR);

private:
    QEXT_DISABLE_COPY_MOVE(QExtLogTTCCLayout)

public:
    bool categoryPrefixing() const;
    bool contextPrinting() const;
    QString dateFormat() const;
    bool threadPrinting() const;
    void setCategoryPrefixing(bool categoryPrefixing);
    void setContextPrinting(bool contextPrinting);
    void setDateFormat(const QString &dateFormat);

    /*!
    * Sets the date format to the value specified by the \a dateFormat
    * constant.
    */
    void setDateFormat(DateFormat dateFormat);

    void setThreadPrinting(bool threadPrinting);
    virtual QString format(const QExtLoggingEvent &event) override;

private:
    void updatePatternFormatter();

private:
    bool mCategoryPrefixing;
    bool mContextPrinting;
    QString mDateFormat;
    bool mThreadPrinting;
    QScopedPointer<QExtLogPatternFormatter> mPatternFormatter;
};

inline bool QExtLogTTCCLayout::categoryPrefixing() const
{
    return mCategoryPrefixing;
}

inline bool QExtLogTTCCLayout::contextPrinting() const
{
    return mContextPrinting;
}

inline QString QExtLogTTCCLayout::dateFormat() const
{
    return mDateFormat;
}

inline bool QExtLogTTCCLayout::threadPrinting() const
{
    return mThreadPrinting;
}

inline void QExtLogTTCCLayout::setCategoryPrefixing(bool categoryPrefixing)
{
    mCategoryPrefixing = categoryPrefixing;
    updatePatternFormatter();
}

inline void QExtLogTTCCLayout::setContextPrinting(bool contextPrinting)
{
    mContextPrinting = contextPrinting;
    updatePatternFormatter();
}

inline void QExtLogTTCCLayout::setDateFormat(const QString &dateFormat)
{
    mDateFormat = dateFormat;
    updatePatternFormatter();
}

inline void QExtLogTTCCLayout::setThreadPrinting(bool threadPrinting)
{
    mThreadPrinting = threadPrinting;
    updatePatternFormatter();
}

#endif // _QEXTLOGTTCCLAYOUT_H
