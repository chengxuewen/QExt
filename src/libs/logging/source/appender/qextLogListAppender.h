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

#ifndef _QEXTLOGLISTAPPENDER_H
#define _QEXTLOGLISTAPPENDER_H

#include <qextLogAppenderSkeleton.h>
#include <qextLoggingEvent.h>

#include <QList>

/*!
 * \brief The class QExtLogListAppender appends logging events to a list for later
 *        processing.
 *
 * \note All the functions declared in this class are thread-safe.
 *
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogListAppender : public QExtLogAppenderSkeleton
{
    Q_OBJECT

    /*!
     * The property holds, if the QExtLogAppender is used by a configurator.
     *
     * The default value is false for not being a configurator list.
     *
     * \sa configuratorList(), setConfiguratorList()
     */
    Q_PROPERTY(bool configuratorList READ configuratorList WRITE setConfiguratorList)

    /*!
     * The property holds the maximum count used by the appender.
     *
     * The default maximum count is -1 for unlimited.
     *
     * \sa maxCount(), setMaxCount()
     */
    Q_PROPERTY(int maxCount READ maxCount WRITE setMaxCount)

public:
    QExtLogListAppender(QObject *parent = nullptr);

public:
    /*!
     * Returns true, if the appender is used by a configurator. Otherweise it returns
     * false.
     *
     * \sa setConfiguratorList()
     */
    bool configuratorList() const;

    QList<QExtLoggingEvent> list() const;
    int maxCount() const;

    /*!
     * Sets that the appender is used by a configurator. If set to true, the appender
     * will not be removed from a QExtLogger when QExtLogger::removeAllAppenders()is called.
     * This way the appender can collect events raised during the configuration process.
     *
     * \sa configuratorList(), QExtLogBasicConfigurator, QExtLogPropertyConfigurator,
     *     QExtLogConfiguratorHelper::configureError()
     */
    void setConfiguratorList(bool isConfiguratorList);

    void setMaxCount(int n);

    QList<QExtLoggingEvent> clearList();
    bool requiresLayout() const override;

protected:
    void append(const QExtLoggingEvent &event) override;

    /*!
     * Ensures that the count of events is less or equal then the maxium
     * count. If the list contains too many items, items are deleted from
     * the begin of the list.
     */
    void ensureMaxCount();

private:
    QEXT_DISABLE_COPY_MOVE(QExtLogListAppender)
    volatile bool mConfiguratorList;
    QList<QExtLoggingEvent> mList;
    volatile int mMaxCount;
};

inline bool QExtLogListAppender::configuratorList() const
{
    return mConfiguratorList;
}

inline int QExtLogListAppender::maxCount() const
{
    return mMaxCount;
}

inline void QExtLogListAppender::setConfiguratorList(bool isConfiguratorList)
{
    mConfiguratorList = isConfiguratorList;
}

inline bool QExtLogListAppender::requiresLayout() const
{
    return false;
}

#endif // _QEXTLOGLISTAPPENDER_H
