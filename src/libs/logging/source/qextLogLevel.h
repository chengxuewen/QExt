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

#ifndef _QEXTLOGLEVEL_H
#define _QEXTLOGLEVEL_H

#include <qextLoggingGlobal.h>

#include <QString>
#include <QMetaType>

/*!
 * \brief The class QExtLogLevel defines the level of a logging event.
 *
 * \note All the functions declared in this class are thread-safe.
 */
class QEXT_LOGGING_API QExtLogLevel
{
public:
    // Comparisson operators rely on the order:
    // Null < All < Trace < ...
    // Serialisation uses unsigned 8 bit int

    /*!
     * The enumeration Value contains all possible QExtLogLevel values.
     */
    enum LevelEnum
    {
        /*! Null is used for no level has been specified */
        Null = 0,
        All = 32,
        Trace = 64,
        Debug = 96,
        Info = 128,
        Warn = 150,
        Error = 182,
        Fatal = 214,
        Off = 255
    };

public:
    QExtLogLevel(LevelEnum value = Null)
        : mValue(value)
    {
    }

    int syslogEquivalent() const;

    int toInt() const
    {
        return mValue;
    }

    bool operator==(const QExtLogLevel other) const
    {
        return mValue == other.mValue;
    }

    bool operator!=(const QExtLogLevel other) const
    {
        return mValue != other.mValue;
    }

    bool operator<(const QExtLogLevel other) const
    {
        return mValue < other.mValue;
    }

    bool operator<=(const QExtLogLevel other) const
    {
        return mValue <= other.mValue;
    }

    bool operator>(const QExtLogLevel other) const
    {
        return mValue > other.mValue;
    }

    bool operator>=(const QExtLogLevel other) const
    {
        return mValue >= other.mValue;
    }

    QString toString() const;

    static const QList<int> &levelEnumList();
    static const char *levelEnumString(int level);
    static QExtLogLevel fromString(const QString &level, bool *ok = QEXT_NULLPTR);

private:
    volatile LevelEnum mValue;

#ifndef QT_NO_DATASTREAM
    // Needs to be friend to stream objects
    friend QEXT_LOGGING_API QDataStream &operator<<(QDataStream &out, QExtLogLevel level);
    friend QEXT_LOGGING_API QDataStream &operator>>(QDataStream &in, QExtLogLevel &level);
#endif // QT_NO_DATASTREAM
};

#ifndef QT_NO_DATASTREAM
/*!
 * \relates QExtLogLevel
 *
 * Writes the given error \a rLevel to the given stream \a rStream,
 * and returns a reference to the stream.
 */
QEXT_LOGGING_API QDataStream &operator<<(QDataStream &out, QExtLogLevel level);

/*!
 * \relates QExtLogLevel
 *
 * Reads an error from the given stream \a rStream into the given
 * error \a rLevel, and returns a reference to the stream.
 */
QEXT_LOGGING_API QDataStream &operator>>(QDataStream &in, QExtLogLevel &level);
#endif // QT_NO_DATASTREAM

Q_DECLARE_METATYPE(QExtLogLevel)
Q_DECLARE_TYPEINFO(QExtLogLevel, Q_MOVABLE_TYPE);


#endif // _QEXTLOGLEVEL_H
