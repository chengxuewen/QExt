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

#ifndef _QEXTLOGPROPERTIES_H
#define _QEXTLOGPROPERTIES_H

#include <qextLoggingGlobal.h>

#include <QStringList>
#include <QHash>

class QIODevice;
class QSettings;

/*!
 * \brief The class QExtLogProperties implements a JAVA property hash.
 */
class QEXT_LOGGING_API QExtLogProperties : public QHash<QString, QString>
{
public:
    explicit QExtLogProperties(QExtLogProperties *pDefaultProperties = QEXT_NULLPTR);

public:
    QExtLogProperties *defaultProperties() const;
    QString property(const QString &key) const;
    QString property(const QString &key, const QString &defaultValue) const;
    void setDefaultProperties(QExtLogProperties *defaultProperties);
    void setProperty(const QString &key, const QString &value);

    void load(QIODevice *device);

    /*!
     * Reads all child keys from the QSettings object \a settings and
     * inserts them into this object. The value is created using
     * QVariant::toString(). Types that do not support toString() are
     * resulting in an empty string.
     *
     * \code
     * QSettings settings;
     * settings.setValue("Package", "Full");
     * settings.setValue("Background", Qt::white);
     * settings.setValue("Support", true);
     * settings.setValue("Help/Language", "en_UK");
     *
     * QExtLogProperties properties
     * properties.load(&settings)
     *
     * // properties (("Package", "Full"), ("Background", ""), ("Support", "true"))
     * \endcode
     */
    void load(const QSettings &settings);

    QStringList propertyNames() const;

private:
    void parseProperty(const QString &property, int line);
    static int hexDigitValue(QChar digit);
    static QString trimLeft(const QString &line);

private:
    QExtLogProperties *mpDefaultProperties;
    static const char msEscapeChar;
    static const char *msValueEscapeCodes;
    static const char *msValueEscapeChars;
    static const char *msKeyEscapeCodes;
    static const char *msKeyEscapeChars;
};

inline QExtLogProperties::QExtLogProperties(QExtLogProperties *pDefaultProperties) :
    mpDefaultProperties(pDefaultProperties)
{}

inline QExtLogProperties *QExtLogProperties::defaultProperties() const
{
    return mpDefaultProperties;
}

inline void QExtLogProperties::setDefaultProperties(QExtLogProperties *defaultProperties)
{
    mpDefaultProperties = defaultProperties;
}

inline void QExtLogProperties::setProperty(const QString &key,
                                           const QString &value)
{
    insert(key, value);
}

Q_DECLARE_TYPEINFO(QExtLogProperties, Q_MOVABLE_TYPE);


#endif // _QEXTLOGPROPERTIES_H
