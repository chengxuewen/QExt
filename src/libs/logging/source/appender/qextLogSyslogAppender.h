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

#ifndef _QEXTLOGSYSTEMLOGAPPENDER_H
#define _QEXTLOGSYSTEMLOGAPPENDER_H

#include <qextLogAppenderSkeleton.h>

/*!
 * \brief The class QExtLogSystemLogAppender appends log events to a Event Log under win*
 * and to syslog under *nix.
 *
 * \note All the functions declared in this class are thread-safe.
 *
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogSystemLogAppender: public QExtLogAppenderSkeleton
{
    Q_OBJECT

    /**
     * The property holds the port used by the telenet appender.
     *
     * The default is QCoreApplication::applicationName()
     *
     * \sa serviceName(), setServiceName()
     */
    Q_PROPERTY(QString serviceName READ serviceName WRITE setServiceName)

public:
    explicit QExtLogSystemLogAppender(QObject *parent = nullptr);
    ~QExtLogSystemLogAppender() override;

    bool requiresLayout() const override;
    QString serviceName() const;
    void setServiceName(const QString &serviceName);

protected:
    void append(const QExtLoggingEvent &event) override;

    QString mServiceName;
    char *ident;
};

inline bool QExtLogSystemLogAppender::requiresLayout() const
{
    return true;
}

#endif // _QEXTLOGSYSTEMLOGAPPENDER_H
