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

#ifndef _QEXTLOGPATTERNLAYOUT_H
#define _QEXTLOGPATTERNLAYOUT_H

#include <qextLogLayout.h>
#include <qextLogPatternFormatter.h>

#include <QScopedPointer>

/*!
 * \brief The class QExtLogPatternLayout outputs a logging event based on a
 *        pattern string.
        \li c{section_count} : logger name with optional parameter section_count. Section count from end of logger name, sections delimiter is "::";
        \li d{format_string} : date with optional parameters in "{}"-brackets which used by QDateTime::toString();
        \li m : message
        \li p : level name
        \li r : relative date/time to start application
        \li t : thread name
        \li x : ndc name
        \li X : mdc name
        \li F : file name
        \li M : method name
        \li L : line number
 *
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogPatternLayout : public QExtLogLayout
{
    Q_OBJECT

    /*!
     * The property holds the conversion pattern used by the appender.
     *
     * The default is "%m%n".
     *
     * \sa conversionPattern(), setConversionPattern()
     */
    Q_PROPERTY(QString conversionPattern READ conversionPattern WRITE setConversionPattern)

public:
    /*!
     * The enum ConversionPattern defines constants for pattern strings.
     *
     * \sa setConversionPattern(ConversionPattern);
     */
    enum ConversionPattern
    {
        /*! The default conversion pattern string is "%m,%n". */
        DEFAULT_CONVERSION_PATTERN,
        /*!
         * The ttcc conversion pattern string is
         * "%r [%t] %p %c %x - %m%n".
         */
        TTCC_CONVERSION_PATTERN
    };
    Q_ENUM(ConversionPattern)

    QExtLogPatternLayout(QObject *parent = QEXT_NULLPTR);
    QExtLogPatternLayout(const QString &pattern,
                  QObject *parent = QEXT_NULLPTR);

    /*!
     * Creates a QExtLogPatternLayout with the conversion pattern value specified
     * by the \a conversionPattern constant.
     */
    QExtLogPatternLayout(ConversionPattern conversionPattern,
                  QObject *parent = QEXT_NULLPTR);

private:
    QEXT_DISABLE_COPY_MOVE(QExtLogPatternLayout)

public:
    QString conversionPattern() const;
    void setConversionPattern(const QString &pattern);

    /*!
     * Sets the conversion pattern to the value specified by the
     * \a conversionPattern constant.
     */
    void setConversionPattern(ConversionPattern conversionPattern);

    QString format(const QExtLoggingEvent &event) override;

private:
    void updatePatternFormatter();

private:
    QString mPattern;
    QScopedPointer<QExtLogPatternFormatter> mPatternFormatter;
};

inline QString QExtLogPatternLayout::conversionPattern() const
{
    return QExtLogPatternLayout::mPattern;
}

inline void QExtLogPatternLayout::setConversionPattern(const QString &pattern)
{
    mPattern = pattern;
    updatePatternFormatter();
}

#endif // _QEXTLOGPATTERNLAYOUT_H
