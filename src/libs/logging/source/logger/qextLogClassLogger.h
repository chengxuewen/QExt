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

#ifndef _QEXTLOGCLASSLOGGER_H
#define _QEXTLOGCLASSLOGGER_H

#include <qextLoggingGlobal.h>

#include <QAtomicPointer>

class QObject;

class QExtLogger;

/*!
 * \brief The class QExtClassLogger provides logging for a QObject derived
 *        class.
 *
 * The class QExtClassLogger provides a logger for a specified QObject derived
 * object. It is used by \ref QEXT_DECLARE_QCLASS_LOGGER to implement the
 * member functions provided by the macro.
 *
 * \note All the functions declared in this class are thread-safe.
 *
 * \sa QEXT_DECLARE_QCLASS_LOGGER
 */
class QEXT_LOGGING_API QExtClassLogger
{
public:
    /*!
     * Creates a QExtClassLogger object.
     */
    QExtClassLogger();
    virtual ~QExtClassLogger();

    /*!
     * Returns a pointer to a QExtLogger named after the class of the object
     * \a pObject.
     *
     * On the first invocation the QExtLogger is requested by a call to
     * QExtLogManager::logger(const char *pName). The pointer is stored to be
     * returned on subsequent invocations.
     *
     * \sa QExtLogManager::logger(const char *pName)
     */
    QExtLogger *logger(const QObject *object);

private:
    mutable QAtomicPointer<QExtLogger> mLogger;
};

#endif // _QEXTLOGCLASSLOGGER_H
