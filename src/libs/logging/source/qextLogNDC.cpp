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

#include <qextLogNDC.h>
#include <qextLogger.h>

#include <QThread>
#include <QMutex>

QEXT_DECLARE_STATIC_LOGGER(qextLogNDC, QExtLogNDC)

void QExtLogNDC::clear()
{
    if (!instance()->mStack.hasLocalData())
    {
        return;
    }
    instance()->mStack.localData()->clear();
}


int QExtLogNDC::depth()
{
    if (!instance()->mStack.hasLocalData())
    {
        return 0;
    }
    return instance()->mStack.localData()->count();
}

QString QExtLogNDC::pop()
{
    if (!instance()->mStack.hasLocalData() || instance()->mStack.localData()->isEmpty())
    {
        qextLogNDC()->warn(QStringLiteral("Requesting pop from empty QExtLogNDC stack"));
        return QString();
    }

    return instance()->mStack.localData()->pop();
}


void QExtLogNDC::push(const QString &message)
{
    if (!instance()->mStack.hasLocalData())
    {
        instance()->mStack.setLocalData(new QStack<QString>);
    }

    instance()->mStack.localData()->push(message);
}


void QExtLogNDC::setMaxDepth(int maxDepth)
{
    if (!instance()->mStack.hasLocalData() || instance()->mStack.localData()->size() <= maxDepth)
    {
        return;
    }

    instance()->mStack.localData()->resize(maxDepth);
}


QString QExtLogNDC::peek()
{
    if (!instance()->mStack.hasLocalData() || instance()->mStack.localData()->isEmpty())
    {
        return QString();
    }

    return instance()->mStack.localData()->top();
}
