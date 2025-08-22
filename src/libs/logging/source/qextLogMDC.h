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

#ifndef _QEXTLOGMDC_H
#define _QEXTLOGMDC_H

#include <qextLoggingGlobal.h>
#include <qextSingleton.h>

#include <QThreadStorage>
#include <QString>
#include <QHash>

/**
 * @brief The class QExtLogMDC implements a mapped diagnostic context.
 * @note All the functions declared in this class are thread-safe.
 */
class QEXT_LOGGING_API QExtLogMDC : public QExtSingleton<QExtLogMDC>
{
public:
    ~QExtLogMDC() QEXT_OVERRIDE {}

    static QHash<QString, QString> context();

    static QString get(const QString &key);
    static inline void remove(const QString &key)
    {
        localData()->remove(key);
    }
    static inline void put(const QString &key, const QString &value)
    {
        localData()->insert(key, value);
    }

protected:
    QExtLogMDC() {}
    QEXT_DECLARE_SINGLETON(QExtLogMDC)
    static QHash<QString, QString> *localData();

private:
    QThreadStorage<QHash<QString, QString> *> mHash;
    QEXT_DISABLE_COPY_MOVE(QExtLogMDC)
};

#endif // _QEXTLOGMDC_H
