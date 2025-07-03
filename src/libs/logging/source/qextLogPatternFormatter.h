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

#ifndef _QEXTLOGPATTERNFORMATTER_H
#define _QEXTLOGPATTERNFORMATTER_H

#include <qextLoggingGlobal.h>

#include <QList>
#include <QString>

class QExtLogFormattingInfo;
class QExtLogPatternConverter;
class QExtLoggingEvent;

/*!
 * \brief The class QExtLogPatternFormatter formats a logging event based on a
 *        pattern string.
 *
 * The class QExtLogPatternFormatter formats a QExtLoggingEvent base on a pattern
 * string. It is used by the patternLayout and QExtLogTTCCLayout class to
 * implement the formatting.
 *
 * On object construction the provided patterns tring is parsed. Based on
 * the information found a chain of QExtLogPatternConverter is created. Each
 * QExtLogPatternConverter handles a certain member of a QExtLoggingEvent.
 *
 * \sa QExtLogPatternLayout::format()
 * \sa QExtLogTTCCLayout::format()
 */
class QEXT_LOGGING_API QExtLogPatternFormatter
{
public:
    /*!
     * Creates a QExtLogPatternFormatter using a the specified \a pattern.
     */
    explicit QExtLogPatternFormatter(const QString &pattern);

    /*!
     * Destroys the QExtLogPatternFormatter and all QExtLogPatternConverter.
     */
    virtual ~QExtLogPatternFormatter();

private:
    QEXT_DISABLE_COPY_MOVE(QExtLogPatternFormatter)

public:
    /*!
     * Formats the given \a loggingEvent using the chain of
     * QExtLogPatternConverter created during construction from the specified
     * pattern.
     */
    QString format(const QExtLoggingEvent &loggingEvent) const;

private:
    /*!
     * If the character \a digit is a digit the digit is added to the
     * integer \a value and the function returns true. Otherwise the
     * function returns false.
     *
     * The function adds the digit by multiplying the existing value
     * with ten and adding the numerical value of the digit. If the
     * maximum integer value would be exceeded by the operation
     * \a value is set to INT_MAX.
     */
    bool addDigit(QChar digit,
                  int &value);

    /*!
     * Creates a QExtLogPatternConverter based on the specified conversion
     * character \a rChar, the formatting information
     * \a formattingInfo and the option \a option.
     *
     * The QExtLogPatternConverter converter is appended to the list of
     * PatternConverters.
     */
    void createConverter(QChar character,
                         QExtLogFormattingInfo formattingInfo,
                         const QString &option = QString());

    /*!
     * Creates a LiteralPatternConverter with the string literal
     * \a literal.
     *
     * The QExtLogPatternConverter converter is appended to the list of
     * PatternConverters.
     */
    void createLiteralConverter(const QString &literal);

    /*!
     * Parses the pattern string specified on construction and creates
     * QExtLogPatternConverter according to it.
     */
    void parse();

    /*!
     * Parses an integer option from an option string. If the string is
     * not a valid integer or the integer value is less then zero, zero
     * is returned. Returns the end of line seperator for the operating
     * system.
     */
    int parseIntegeoption(const QString &option);

private:
    const QString mIgnoreCharacters;
    const QString mConversionCharacters;
    const QString mOptionCharacters;
    QString mPattern;
    QList<QExtLogPatternConverter *> mPatternConverters;
};

Q_DECLARE_TYPEINFO(QExtLogPatternFormatter, Q_COMPLEX_TYPE);

#endif // _QEXTLOGPATTERNFORMATTER_H
