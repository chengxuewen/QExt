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

#include <qextLogPatternFormatter.h>

#include <qextLogDatetime.h>
#include <qextLogError.h>
#include <qextLogLayout.h>
#include <qextLogger.h>
#include <qextLoggingEvent.h>
#include <qextLogManager.h>

#include <QString>

#include <limits>
#if (__cplusplus >= 201703L) // C++17 or later
#   include <utility>
#endif

/*!
 * \brief The class QExtLogFormattingInfo stores the formatting modifier for a
 * pattern converter.
 *
 * \sa QExtLogPatternConverter
 */
class QExtLogFormattingInfo
{
public:
    QExtLogFormattingInfo()
    {
        clear();
    }

    void clear();
    static QString intToString(int i);

public:
    int mMinLength;
    int mMaxLength;
    bool mLeftAligned;
};

/*!
 * \brief The class QExtLogPatternConverter is the abstract base class for all
 * pattern converters.
 *
 * QExtLogPatternConverter handles the minimum and maximum modifier for a
 * conversion character. The actual conversion is by calling the
 * convert() member function of the derived class.
 *
 * \sa QExtLogPatternLayout::format()
 */
class QExtLogPatternConverter
{
public:
    QExtLogPatternConverter(QExtLogFormattingInfo formattingInfo = QExtLogFormattingInfo()) :
        mFormattingInfo(formattingInfo)
    {}
    virtual ~QExtLogPatternConverter() = default;

private:
    QEXT_DISABLE_COPY_MOVE(QExtLogPatternConverter)

public:
    void format(QString &format, const QExtLoggingEvent &loggingEvent) const;

protected:
    virtual QString convert(const QExtLoggingEvent &loggingEvent) const = 0;

protected:
    QExtLogFormattingInfo mFormattingInfo;
};


/*!
 * \brief The class BasicPatternConverter converts several members of a
 *        QExtLoggingEvent to a string.
 *
 * BasicPatternConverter is used by QExtLogPatternLayout to convert members that
 * do not reuquire additional formatting to a string as part of formatting
 * the QExtLoggingEvent. It handles the following conversion characters:
 * 'm', 'p', 't', 'x'
 *
 * \sa QExtLogPatternLayout::format()
 * \sa QExtLogPatternConverter::format()
 */
class BasicPatternConverter : public QExtLogPatternConverter
{
public:
    enum Type
    {
        MESSAGE_CONVERTER,
        NDC_CONVERTER,
        LEVEL_CONVERTER,
        THREAD_CONVERTER,
        FILENAME_CONVERTER,
        FUNCTIONNAME_CONVERTER,
        LINENUMBER_CONVERTER,
        LOCATION_CONVERTER,
        CATEGORYNAME_CONVERTER
    };

public:
    BasicPatternConverter(QExtLogFormattingInfo formattingInfo,
                          Type type) :
        QExtLogPatternConverter(formattingInfo),
        mType(type)
    {}

private:
    QEXT_DISABLE_COPY_MOVE(BasicPatternConverter)

protected:
    QString convert(const QExtLoggingEvent &loggingEvent) const override;

private:
    Type mType;
};


/*!
 * \brief The class DatePatternConverter converts the time stamp of a
 *        QExtLoggingEvent to a string.
 *
 * DatePatternConverter is used by QExtLogPatternLayout to convert the time stamp
 * of a QExtLoggingEvent to a string as part of formatting the QExtLoggingEvent.
 * It handles the 'd' and 'r' conversion character.
 *
 * \sa QExtLogPatternLayout::format()
 * \sa QExtLogPatternConverter::format()
 */
class DatePatternConverter : public QExtLogPatternConverter
{
public:
    DatePatternConverter(QExtLogFormattingInfo formattingInfo,
                         const QString &format) :
        QExtLogPatternConverter(formattingInfo),
        mFormat(format)
    {}

private:
    QEXT_DISABLE_COPY_MOVE(DatePatternConverter)

protected:
    QString convert(const QExtLoggingEvent &loggingEvent) const override;

private:
    QString mFormat;
};


/*!
 * \brief The class LiteralPatternConverter provides string literals.
 *
 * LiteralPatternConverter is used by QExtLogPatternLayout to embed string
 * literals as part of formatting the QExtLoggingEvent. It handles string
 * literals and the 'n' conversion character.
 *
 * \sa QExtLogPatternLayout::format()
 * \sa QExtLogPatternConverter::format()
 */
class LiteralPatternConverter : public QExtLogPatternConverter
{
public:
    LiteralPatternConverter(const QString &literal) :
        mLiteral(literal)
    {}

private:
    QEXT_DISABLE_COPY_MOVE(LiteralPatternConverter)

protected:
    QString convert(const QExtLoggingEvent &loggingEvent) const override;

private:
    QString mLiteral;
};


/*!
 * \brief The class LoggepatternConverter converts the QExtLogger name of a
 *        QExtLoggingEvent to a string.
 *
 * LoggepatternConverter is used by QExtLogPatternLayout to convert the QExtLogger
 * name of a QExtLoggingEvent to a string as part of formatting the
 * QExtLoggingEvent. It handles the 'c' conversion character.
 *
 * \sa QExtLogPatternLayout::format()
 * \sa QExtLogPatternConverter::format()
 */
class LoggepatternConverter : public QExtLogPatternConverter
{
public:
    LoggepatternConverter(QExtLogFormattingInfo formattingInfo,
                          int precision) :
        QExtLogPatternConverter(formattingInfo),
        mPrecision(precision)
    {}

private:
    QEXT_DISABLE_COPY_MOVE(LoggepatternConverter)

protected:
    QString convert(const QExtLoggingEvent &loggingEvent) const override;

private:
    int mPrecision;
};



/*!
 * \brief The class MDCPatternConverter converts the QExtLogMDC data of a
 *        QExtLoggingEvent to a string.
 *
 * MDCPatternConverter is used by QExtLogPatternLayout to convert the QExtLogMDC data of
 * a QExtLoggingEvent to a string as part of formatting the QExtLoggingEvent. It
 * handles the 'X' conversion character.
 *
 * \sa QExtLogPatternLayout::format()
 * \sa QExtLogPatternConverter::format()
 */
class MDCPatternConverter : public QExtLogPatternConverter
{
public:
    MDCPatternConverter(QExtLogFormattingInfo formattingInfo,
                        const QString &key) :
        QExtLogPatternConverter(formattingInfo),
        mKey(key)
    {}

private:
    QEXT_DISABLE_COPY_MOVE(MDCPatternConverter)

protected:
    QString convert(const QExtLoggingEvent &loggingEvent) const override;

private:
    QString mKey;
};

QEXT_DECLARE_STATIC_LOGGER(logger, QExtLogPatternFormatter)

QExtLogPatternFormatter::QExtLogPatternFormatter(const QString &pattern) :
    mIgnoreCharacters(QStringLiteral("C")),
    mConversionCharacters(QStringLiteral("cdmprtxXFMLl")),
    mOptionCharacters(QStringLiteral("cd")),
    mPattern(pattern)
{
    parse();
}


QExtLogPatternFormatter::~QExtLogPatternFormatter()
{
    qDeleteAll(mPatternConverters);
}


QString QExtLogPatternFormatter::format(const QExtLoggingEvent &loggingEvent) const
{
    QString result;
#if (__cplusplus >= 201703L)
    for (auto &&converter : std::as_const(mPatternConverters))
#else
    for (auto &&converter : qAsConst(mPatternConverters))
#endif
    {
        converter->format(result, loggingEvent);
    }
    return result;
}


bool QExtLogPatternFormatter::addDigit(QChar digit,
                                       int &value)
{
    if (!digit.isDigit())
    {
        return false;
    }

    int digit_value = digit.digitValue();
    if (value > (INT_MAX - digit_value) / 10)
    {
        value = INT_MAX;
    }
    else
    {
        value = value * 10 + digit_value;
    }
    return true;
}


void QExtLogPatternFormatter::createConverter(QChar character,
                                              QExtLogFormattingInfo formattingInfo,
                                              const QString &option)
{
    Q_ASSERT_X(mConversionCharacters.indexOf(character) >= 0, "QExtLogPatternFormatter::createConverter", "Unknown conversion character" );

    QExtLogError e("Creating Converter for character '%1' min %2, max %3, left %4 and option '%5'");
    e << QString(character)
      << QExtLogFormattingInfo::intToString(formattingInfo.mMinLength)
      << QExtLogFormattingInfo::intToString(formattingInfo.mMaxLength)
      << formattingInfo.mLeftAligned
      << option;
    logger()->trace(e);

    switch (character.toLatin1())
    {
    case 'c':
        mPatternConverters << new LoggepatternConverter(formattingInfo,
                                                        parseIntegeoption(option));
        break;
    case 'd':
    {
        QString format = option;
        if (option.isEmpty())
            format = QStringLiteral("ISO8601");
        else if (option == QLatin1String("locale:long"))
            format = QLocale().dateTimeFormat(QLocale::LongFormat);
        else if (option == QLatin1String("locale:short"))
            format = QLocale().dateTimeFormat(QLocale::ShortFormat);
        else if (option == QLatin1String("locale:narrow"))
            format = QLocale().dateTimeFormat(QLocale::NarrowFormat);
        else if (option == QLatin1String("locale"))
            format = QLocale().dateTimeFormat(QLocale::ShortFormat);
        mPatternConverters << new DatePatternConverter(formattingInfo,
                                                       format);
        break;
    }
    case 'm':
        mPatternConverters << new BasicPatternConverter(formattingInfo,
                                                        BasicPatternConverter::MESSAGE_CONVERTER);
        break;
    case 'p':
        mPatternConverters << new BasicPatternConverter(formattingInfo,
                                                        BasicPatternConverter::LEVEL_CONVERTER);
        break;
    case 'r':
        mPatternConverters << new DatePatternConverter(formattingInfo,
                                                       QStringLiteral("RELATIVE"));
        break;
    case 't':
        mPatternConverters << new BasicPatternConverter(formattingInfo,
                                                        BasicPatternConverter::THREAD_CONVERTER);
        break;
    case 'x':
        mPatternConverters << new BasicPatternConverter(formattingInfo,
                                                        BasicPatternConverter::NDC_CONVERTER);
        break;
    case 'X':
        mPatternConverters << new MDCPatternConverter(formattingInfo,
                                                      option);
        break;
    case 'F':
        mPatternConverters << new BasicPatternConverter(formattingInfo,
                                                        BasicPatternConverter::FILENAME_CONVERTER);
        break;
    case 'M':
        mPatternConverters << new BasicPatternConverter(formattingInfo,
                                                        BasicPatternConverter::FUNCTIONNAME_CONVERTER);
        break;
    case 'L':
        mPatternConverters << new BasicPatternConverter(formattingInfo,
                                                        BasicPatternConverter::LINENUMBER_CONVERTER);
        break;
    case 'l':
        mPatternConverters << new BasicPatternConverter(formattingInfo,
                                                        BasicPatternConverter::LOCATION_CONVERTER);
        break;
    default:
        Q_ASSERT_X(false, "QExtLogPatternFormatter::createConverter", "Unknown pattern character");
    }
}


void QExtLogPatternFormatter::createLiteralConverter(const QString &literal)
{
    logger()->trace(QStringLiteral("Creating literal LiteralConverter with Literal '%1'"),
                    literal);
    mPatternConverters << new LiteralPatternConverter(literal);
}


void QExtLogPatternFormatter::parse()
{
    enum State
    {
        LITERAL_STATE,
        ESCAPE_STATE,
        MIN_STATE,
        DOT_STATE,
        MAX_STATE,
        CHARACTER_STATE,
        POSSIBLEOPTION_STATE,
        OPTION_STATE
    };

    int i = 0;
    QChar c;
    char ch;
    State state = LITERAL_STATE;
    QExtLogFormattingInfo formatting_info;
    QString literal;
    int converter_start = 0;
    int option_start = 0;
    while (i < mPattern.length())
    {
        // i points to the current character
        // c contains the current character
        // ch contains the Latin1 equivalent of the current character
        // i is incremented at the end of the loop to consume the character
        // continue is used to change state without consuming the character

        c = mPattern.at(i);
        ch = c.toLatin1();
        switch (state)
        {
        case LITERAL_STATE:
            if (ch == '%')
            {
                formatting_info.clear();
                converter_start = i;
                state = ESCAPE_STATE;
            }
            else
            {
                literal += c;
            }
            break;
        case ESCAPE_STATE:
            if (ch == '%')
            {
                literal += c;
                state = LITERAL_STATE;
            }
            else if (ch == 'n')
            {
                literal += QExtLogLayout::endOfLine();
                state = LITERAL_STATE;
            }
            else
            {
                if (!literal.isEmpty())
                {
                    createLiteralConverter(literal);
                    literal.clear();
                }
                if (ch == '-')
                {
                    formatting_info.mLeftAligned = true;
                }
                else if (c.isDigit())
                {
                    formatting_info.mMinLength = c.digitValue();
                    state = MIN_STATE;
                }
                else if (ch == '.')
                {
                    state = DOT_STATE;
                }
                else
                {
                    state = CHARACTER_STATE;
                    continue;
                }
            }
            break;
        case MIN_STATE:
            if (!addDigit(c, formatting_info.mMinLength))
            {
                if (ch == '.')
                {
                    state = DOT_STATE;
                }
                else
                {
                    state = CHARACTER_STATE;
                    continue;
                }
            }
            break;
        case DOT_STATE:
            if (c.isDigit())
            {
                formatting_info.mMaxLength = c.digitValue();
                state = MAX_STATE;
            }
            else
            {
                QExtLogError e = QEXT_LOG_ERROR(QT_TR_NOOP("Found character '%1' where digit was expected."),
                                                QExtLogError::Error_LayoutExpectedDigitFailed,
                                                "QExtLogPatternFormatter");
                e << QString(c);
                logger()->error(e);
            }
            break;
        case MAX_STATE:
            if (!addDigit(c, formatting_info.mMaxLength))
            {
                state = CHARACTER_STATE;
                continue;
            }
            break;
        case CHARACTER_STATE:
            if (mIgnoreCharacters.indexOf(c) >= 0)
            {
                state = LITERAL_STATE;
            }
            else if (mOptionCharacters.indexOf(c) >= 0)
            {
                state = POSSIBLEOPTION_STATE;
            }
            else if (mConversionCharacters.indexOf(c) >= 0)
            {
                createConverter(c, formatting_info);
                state = LITERAL_STATE;
            }
            else
            {
                logger()->warn(QStringLiteral("Invalid conversion character '%1' at %2 in pattern '%3'"),
                               c, i, mPattern);
                createLiteralConverter(mPattern.mid(converter_start, i - converter_start + 1));
                state = LITERAL_STATE;
            }
            break;
        case POSSIBLEOPTION_STATE:
            if (ch == '{')
            {
                option_start = i;
                state = OPTION_STATE;
            }
            else
            {
                createConverter(mPattern.at(i - 1),
                                formatting_info);
                state = LITERAL_STATE;
                continue;
            }
            break;
        case OPTION_STATE:
            if (ch == '}')
            {
                createConverter(mPattern.at(option_start - 1),
                                formatting_info,
                                mPattern.mid(option_start + 1, i - option_start - 1));
                state = LITERAL_STATE;
            }
            break;
        default:
            Q_ASSERT_X(false, "QExtLogPatternFormatter::parse()", "Unknown parsing state constant");
            state = LITERAL_STATE;
        }
        i++;
    }

    if (state != LITERAL_STATE)
    {
        logger()->warn(QStringLiteral("Unexptected end of pattern '%1'"), mPattern);
        if (state == ESCAPE_STATE)
        {
            literal += c;
        }
        else
        {
            literal += mPattern.mid(converter_start);
        }
    }

    if (!literal.isEmpty())
    {
        createLiteralConverter(literal);
    }
}


int QExtLogPatternFormatter::parseIntegeoption(const QString &option)
{
    if (option.isEmpty())
    {
        return 0;
    }

    bool ok;
    int result = option.toInt(&ok);
    if (!ok)
    {
        QExtLogError e = QEXT_LOG_ERROR(QT_TR_NOOP("Option '%1' cannot be converted into an integer"),
                                        QExtLogError::Error_LayoutOptionIsNotPositive,
                                        "Patteformatter");
        e << option;
        logger()->error(e);
    }
    if (result < 0)
    {
        QExtLogError e = QEXT_LOG_ERROR(QT_TR_NOOP("Option %1 isn't a positive integer"),
                                        QExtLogError::Error_LayoutIntegerIsNotPositive,
                                        "Patteformatter");
        e << result;
        logger()->error(e);
        result = 0;
    }
    return result;
}

void QExtLogFormattingInfo::clear()
{
    mMinLength = 0;
    mMaxLength = INT_MAX;
    mLeftAligned = false;
}


QString QExtLogFormattingInfo::intToString(int i)
{
    if (i == INT_MAX)
    {
        return QStringLiteral("INT_MAX");
    }
    return QString::number(i);
}

void QExtLogPatternConverter::format(QString &format, const QExtLoggingEvent &loggingEvent) const
{
    Q_DECL_CONSTEXPR const QLatin1Char space(' ');
    const QString s = convert(loggingEvent);

    // If the data item is longer than the maximum field, then the extra characters
    // are removed from the beginning of the data item and not from the end.
    if (s.length() > mFormattingInfo.mMaxLength)
    {
        format += s.right(mFormattingInfo.mMaxLength);
    }
    else if (mFormattingInfo.mLeftAligned)
    {
        format += s.leftJustified(mFormattingInfo.mMinLength, space, false);
    }
    else
    {
        format += s.rightJustified(mFormattingInfo.mMinLength, space, false);
    }
}

QString BasicPatternConverter::convert(const QExtLoggingEvent &loggingEvent) const
{
    switch (mType)
    {
    case MESSAGE_CONVERTER:
        return loggingEvent.message();
    case NDC_CONVERTER:
        return loggingEvent.ndc();
    case LEVEL_CONVERTER:
        return loggingEvent.level().toString();
    case THREAD_CONVERTER:
        return loggingEvent.threadName();
    case FILENAME_CONVERTER:
        return loggingEvent.context().file;
    case LINENUMBER_CONVERTER:
        return QString::number(loggingEvent.context().line);
    case FUNCTIONNAME_CONVERTER:
        return loggingEvent.context().function;
    case LOCATION_CONVERTER:
        return QStringLiteral("%1:%2 - %3").arg(loggingEvent.context().file, QString::number(loggingEvent.context().line), loggingEvent.context().function);
    case CATEGORYNAME_CONVERTER:
        return loggingEvent.categoryName();
    default:
        Q_ASSERT_X(false, "BasicPatternConverter::convert()", "Unknown type constant");
        return QString();
    }
}

QString DatePatternConverter::convert(const QExtLoggingEvent &loggingEvent) const
{
    return QExtLogDateTime::fromMSecsSinceEpoch(loggingEvent.timeStamp()).toString(mFormat);
}

QString LiteralPatternConverter::convert(const QExtLoggingEvent &loggingEvent) const
{
    Q_UNUSED(loggingEvent);
    return mLiteral;
}

QString LoggepatternConverter::convert(const QExtLoggingEvent &loggingEvent) const
{
    if (!loggingEvent.logger())
    {
        return QString();
    }
    QString name;

    if (loggingEvent.logger() == QExtLogManager::instance()->qtLogger())   // is qt logger
    {
        if (loggingEvent.categoryName().isEmpty())
        {
            name = QExtLogManager::instance()->qtLogger()->name();
        }
        else
        {
            name = loggingEvent.categoryName();
        }
    }
    else
    {
        name = loggingEvent.logger()->name();
    }

    if (mPrecision <= 0 || (name.isEmpty()))
    {
        return name;
    }

    const QString separator(QStringLiteral("::"));

    int i = mPrecision;
    int begin = name.length();
    while ((i > 0) && (begin >= 0))
    {
        begin = name.lastIndexOf(separator, begin - name.length() - 1);
        i--;
    }
    if (begin < 0)
    {
        begin = 0;
    }
    else
    {
        begin += 2;
    }
    return name.mid(begin);
}

QString MDCPatternConverter::convert(const QExtLoggingEvent &loggingEvent) const
{
    return loggingEvent.mdc().value(mKey);
}
