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

#ifndef _QEXTLOGLAYOUT_H
#define _QEXTLOGLAYOUT_H

#include <qextLoggingGlobal.h>
#include <qextObjectSharedPointer.h>

#include <QObject>

class QExtLoggingEvent;

/*!
 * \brief The class QExtLogLayout is the base class for all layouts.
 *
 * \note The ownership and lifetime of objects of this class are managed. See
 *       \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogLayout : public QObject
{
    Q_OBJECT

    /*!
     * The property holds the content type of the layout.
     *
     * \sa contentType()
     */
    Q_PROPERTY(QString footercontentType READ contentType)
    /*!
     * The property holds the footer used by the layout.
     *
     * \sa footer(), setFooter()
     */
    Q_PROPERTY(QString footer READ footer WRITE setFooter)
    /*!
     * The property holds the header used by the layout.
     *
     * \sa header(), setHeader()
     */
    Q_PROPERTY(QString header READ header WRITE setHeader)

public:
    QExtLogLayout(QObject *parent = QEXT_NULLPTR);
    virtual ~QExtLogLayout();

public:
    virtual QString contentType() const;
    QString footer() const;
    QString header() const;
    QString name() const;
    void setFooter(const QString &footer);
    void setHeader(const QString &header);
    void setName(const QString &name);

    virtual void activateOptions();
    virtual QString format(const QExtLoggingEvent &event) = 0;

    /*!
     * Returns the end of line seperator for the operating system.
     *
     * Windows: \\r\\n
     * Mac: \\r
     * UNIX: \\n
     */
    static QString endOfLine();

    // Member variables
private:
    QEXT_DISABLE_COPY_MOVE(QExtLogLayout)
    QString mFooter;
    QString mHeader;
};

inline QString QExtLogLayout::footer() const
{
    return mFooter;
}

inline QString QExtLogLayout::header() const
{
    return mHeader;
}

inline QString QExtLogLayout::name() const
{
    return objectName();
}

inline void QExtLogLayout::setFooter(const QString &footer)
{
    mFooter = footer;
}

inline void QExtLogLayout::setHeader(const QString &header)
{
    mHeader = header;
}

inline void QExtLogLayout::setName(const QString &name)
{
    setObjectName(name);
}

using QExtLogLayoutSharedPtr = QExtObjectSharedPointer<QExtLogLayout>;

#endif // _QEXTLOGLAYOUT_H
