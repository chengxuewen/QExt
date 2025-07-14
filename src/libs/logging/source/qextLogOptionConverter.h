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

#ifndef _QEXTLOGOPTIONCONVERTER_H
#define _QEXTLOGOPTIONCONVERTER_H

#include <qextLoggingGlobal.h>
#include <qextLogLevel.h>

#include <QString>

#if QT_VERSION >= 0x060000
#include <QStringConverter>
#else
#include <QTextCodec>
Q_DECLARE_METATYPE(QTextCodec*)
#endif

class QExtLogProperties;
/*!
 * \brief The class QExtLogOptionConverter provides functions to convert strings
 *        to property values.
 */
class QEXT_LOGGING_API QExtLogOptionConverter
{
private:
    QExtLogOptionConverter();

public:
    static QString findAndSubst(const QExtLogProperties &properties,
                                const QString &key);

    /*!
     * Returns the JAVA class name \a className as C++ class name by
     * replacing all . characters with ::.
     */
    static QString classNameJavaToCpp(const QString &className);

    /*!
     * Converts the option \a option to a boolean value. Valid strings
     * for true are "true", "enabled" and "1". Valid strings
     * for false are "false", "disabled" and "0". If the conversion is
     * successful, the target is returned and \a ok is set to true.
     * Otherwise an error is written to the log, \a ok is set to false
     * and false is returned.
     */
    static bool toBoolean(const QString &option,
                          bool *ok = QEXT_NULLPTR);

    static bool toBoolean(const QString &option,
                          bool defaultValue);

    /*!
     * Converts the option string \a option to a file size. The string can
     * be a positive integer followed by an optional unit suffix "KB", "MB"
     * or "GB". If a unit suffix is specified the the integer is
     * interpreted as kilobytes, megabytes or gigabytes. If the conversion
     * is successful, the size is returned and \a ok is set to true.
     * Otherwise an error is written to the log, \a ok is set to false
     * and 0 is returned.
     */
    static qint64 toFileSize(const QString &option,
                             bool *ok = QEXT_NULLPTR);

    /*!
        * Converts the option \a option to a integer value using
        * QString::toInt(). If the conversion is successful, the integer is
        * returned and \a ok is set to true. Otherwise an error is written
        * to the log, \a ok is set to false and 0 is returned.
        */
    static int toInt(const QString &option,
                     bool *ok = QEXT_NULLPTR);

    /*!
     * Converts the option \a option to a level value using
     * QExtLogLevel::fromString(). If the conversion is successful, the level
     * is returned and \a ok is set to true. Otherwise an error is
     * written to the log, \a ok is set to false and a level with
     * the value QExtLogLevel::Null is returned.
     *
     * \sa QExtLogLevel::fromString()
     */
    static QExtLogLevel toLevel(const QString &option,
                         bool *ok = QEXT_NULLPTR);

    static QExtLogLevel toLevel(const QString &option,
                         QExtLogLevel defaultValue);

    /*!
     * Converts the option \a option to a QExtLogConsoleAppender::Target value.
     * Valid strings for \a option are "System.out", "Target_Stdout",
     * "System.err" and "Target_Stderr". If the conversion is successful,
     * the target is returned and \a ok is set to true. Otherwise an
     * error is written to the log, \a ok is set to false and
     * QExtLogConsoleAppender::Target_Stdout is returned.
     */
    static int toTarget(const QString &option,
                        bool *ok = QEXT_NULLPTR);

#if QT_VERSION < 0x060000
    /*!
     * Converts the option \a option to a QTextCodec* value using
     * QTextCodec::codecForName(). If the conversion is successful,
     * the codec is returned and \a ok is set to true. Otherwise an
     * error is written to the log, \a ok is set to false and
     * 0 is returned.
     */
    static QTextCodec* toEncoding(const QString &option,
                                  bool *ok = QEXT_NULLPTR);
#else
    /*!
     * Converts the option \a option to a QStringConverter::Encoding value using
     * QStringConverter::encodingForName(). If the conversion is successful,
     * the codec is returned and \a ok is set to true. Otherwise an
     * error is written to the log, \a ok is set to false and
     * QStringConverter::System is returned.
     */
    static QStringConverter::Encoding toEncoding(const QString &option,
                                  bool *ok = QEXT_NULLPTR);
#endif
};

Q_DECLARE_TYPEINFO(QExtLogOptionConverter, Q_COMPLEX_TYPE);

#endif // _QEXTLOGOPTIONCONVERTER_H
