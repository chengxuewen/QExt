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

#include <qextLogProperties.h>
#include <qextLogger.h>

#include <QIODevice>
#include <QSettings>
#include <QTextStream>

#if (__cplusplus >= 201703L) // C++17 or later
#   include <utility>
#endif

QEXT_DECLARE_STATIC_LOGGER(qextLogPropertiesLogger, QExtLogProperties)

void QExtLogProperties::load(QIODevice *device)
{
    const QLatin1Char append_char(msEscapeChar);

    if (QEXT_NULLPTR == device)
    {
        qextLogPropertiesLogger()->warn(QStringLiteral("No device specified for load."));
        return;
    }

    QTextStream stream(device);
    QString line;
    int line_number = 0;
    QString property;
    int property_start_line = 1;

    do
    {
        line = trimLeft(stream.readLine());
        line_number++;

        if (!line.isEmpty() && line.at(line.length() - 1) == append_char)
        {
            property += line.left(line.length() - 1);
        }
        else
        {
            property += line;
            parseProperty(property, property_start_line);
            property.clear();
            property_start_line = line_number + 1;
        }
    }
    while (!line.isNull());
}

void QExtLogProperties::load(const QSettings &settings)
{
    QStringList keys = settings.childKeys();
#if (__cplusplus >= 201703L)
    for (const auto &key : std::as_const(keys))
#else
    for (const auto &key : qAsConst(keys))
#endif
    {
        insert(key, settings.value(key).toString());
    }
}


QString QExtLogProperties::property(const QString &key) const
{
    // Null string indicates the property does not contain the key.
    if (this->contains(key))
    {
        QString value = this->value(key);
        if (value.isNull())
        {
            return QString(QLatin1String(""));
        }
        return value;
    }

    if (mpDefaultProperties)
    {
        return mpDefaultProperties->property(key);
    }
    return QString();
}


QString QExtLogProperties::property(const QString &key, const QString &defaultValue) const
{
    QString value = property(key);
    if (value.isNull())
    {
        return defaultValue;
    }
    return value;
}

QStringList QExtLogProperties::propertyNames() const
{
    QStringList defaultKeys;
    if (mpDefaultProperties)
    {
        defaultKeys = mpDefaultProperties->propertyNames();
    }

    QStringList keys = this->keys();
#if (__cplusplus >= 201703L)
    for (const auto &key : std::as_const(default_keys))
#else
    for (const auto &key : qAsConst(defaultKeys))
#endif
    {
        if (!keys.contains(key))
        {
            keys << key;
        }
    }

    return keys;
}


void QExtLogProperties::parseProperty(const QString &property, int line)
{
    Q_ASSERT_X(property == trimLeft(property), "parseProperty()", "property has leading spaces");

    enum State
    {
        KEY_STATE,
        KEYSPACE_STATE,
        SPACEVALUE_STATE,
        VALUE_STATE,
        KEYESCAPE_STATE,
        VALUEESCAPE_STATE,
        UNICODEESCAPE_STATE
    };
    const QString valueEscapeCodes = QLatin1String(msValueEscapeCodes);
    const QString valueEscapeChars = QLatin1String(msValueEscapeChars);
    Q_ASSERT_X(valueEscapeCodes.length() == valueEscapeChars.length(),
               "parseProperty()", "Value escape sequence character definition does not map");
    const QString keyEscapeCodes = QLatin1String(msKeyEscapeCodes);
    const QString keyEscapeChars = QLatin1String(msKeyEscapeChars);
    Q_ASSERT_X(keyEscapeCodes.length() == keyEscapeChars.length(),
               "parseProperty()", "Key escape sequence character definition does not map");

    if (property.isEmpty())
        return;

    int i = 0;
    QChar c;
    State state = KEY_STATE;
    QString key;
    QString value;
    QString *p_string = &key;
    uint ucs = 0;
    int ucs_digits = 0;
    while (i < property.length())
    {
        // i points to the current character.
        // c contains the current character
        // ch contains the Latin1 equivalent of the current character
        // i is incremented at the end of the loop to consume the character.
        // continue is used to change state without consuming the character
        char ch;
        c = property.at(i);
        ch = c.toLatin1();

        switch (state)
        {
        case KEY_STATE:
        {
            if (ch == '!' || ch == '#' )
            {
                return;
            }
            else if (c.isSpace())
            {
                p_string = &value;
                state = KEYSPACE_STATE;
            }
            else if (ch == '=' || ch == ':')
            {
                p_string = &value;
                state = SPACEVALUE_STATE;
            }
            else if (ch == msEscapeChar)
            {
                state = KEYESCAPE_STATE;
            }
            else
            {
                *p_string += c;
            }
            break;
        }
        case KEYSPACE_STATE:
        {
            if (ch == '=' || ch == ':')
            {
                state = SPACEVALUE_STATE;
            }
            else if (!c.isSpace())
            {
                *p_string += c;
                state = VALUE_STATE;
            }
            break;
        }
        case SPACEVALUE_STATE:
        {
            if (!c.isSpace())
            {
                *p_string += c;
                state = VALUE_STATE;
            }
            break;
        }
        case VALUE_STATE:
        {
            if (ch == msEscapeChar)
            {
                state = VALUEESCAPE_STATE;
            }
            else
            {
                *p_string += c;
            }
            break;
        }
        case KEYESCAPE_STATE:
        {
            int convert = keyEscapeCodes.indexOf(c);
            if (convert >= 0)
            {
                *p_string += keyEscapeChars.at(convert);
            }
            else
            {
                qextLogPropertiesLogger()->warn(QStringLiteral("Unknown escape sequence '\\%1' in key of property "
                                                               "starting at line %2"),
                                                QString(c), line);
                *p_string += c;
            }
            state = KEY_STATE;
            break;
        }
        case VALUEESCAPE_STATE:
        {
            int convert = valueEscapeCodes.indexOf(c);
            if (convert >= 0)
            {
                *p_string += valueEscapeChars.at(convert);
                state = VALUE_STATE;
            }
            else if (ch == 'u')
            {
                ucs = 0;
                ucs_digits = 0;
                state = UNICODEESCAPE_STATE;
            }
            else
            {
                qextLogPropertiesLogger()->warn(QStringLiteral("Unknown escape sequence '\\%1' in value of property "
                                                               "starting at line %2"),
                                                QString(c), line);
                *p_string += c;
                state = VALUE_STATE;
            }
            break;
        }
        case UNICODEESCAPE_STATE:
        {
            int hex = hexDigitValue(c);
            if (hex >= 0)
            {
                ucs = ucs * 16 + hex;
                ucs_digits++;
                if (ucs_digits == 4 || i == property.length() - 1)
                {
                    *p_string += QChar(ucs);
                    state = VALUE_STATE;
                }
            }
            else
            {
                if (ucs_digits > 0)
                {
                    *p_string += QChar(ucs);
                }
                state = VALUE_STATE;
                continue;
            }
            break;
        }
        default:
            Q_ASSERT_X(false, "QExtLogProperties::parseProperty()", "Unknown state constant");
            return;
        }
        i++;
    }

    if (key.isEmpty() && !value.isEmpty())
    {
        qextLogPropertiesLogger()->warn(QStringLiteral("Found value with no key in property starting at line %1"),
                                        line);
    }

    qextLogPropertiesLogger()->trace(QStringLiteral("Loaded property '%1' : '%2'"), key, value);
    insert(key, value);
}

int QExtLogProperties::hexDigitValue(QChar digit)
{
    bool ok;
    int result = QString(digit).toInt(&ok, 16);
    if (!ok)
    {
        return -1;
    }

    return result;
}

QString QExtLogProperties::trimLeft(const QString &line)
{
    int i = 0;
    while (i < line.length() && line.at(i).isSpace())
    {
        i++;
    }
    return line.right(line.length() - i);
}

const char QExtLogProperties::msEscapeChar = '\\';
const char *QExtLogProperties::msValueEscapeCodes = R"(tnr\"' )";
const char *QExtLogProperties::msValueEscapeChars = "\t\n\r\\\"\' ";
const char *QExtLogProperties::msKeyEscapeCodes = " :=";
const char *QExtLogProperties::msKeyEscapeChars = " :=";
