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

#include <qextLogBinaryToTextLayout.h>
#include <qextBinaryLoggingEvent.h>
#include <qextLogSimpleLayout.h>

#include <QStringBuilder>

QExtLogBinaryToTextLayout::QExtLogBinaryToTextLayout(const QExtLogLayoutSharedPtr &subLayout, QObject *parent)
    : QExtLogLayout(parent)
    , mSubLayout(subLayout)
{
}

QString QExtLogBinaryToTextLayout::format(const QExtLoggingEvent &event)
{
    if (!mSubLayout.isNull())
    {
        if (const auto *binaryEvent = dynamic_cast<const QExtBinaryLoggingEvent *>(&event))
        {
            QString hexData = binaryEvent->binaryMessage().toHex();
            QString spacedHexData;

            for (int i = 0; i < hexData.length(); i += 2)
            {
                spacedHexData.append(hexData.mid(i, 2) % " ");
            }

            // replace binary marker in output with hexdump
            return mSubLayout->format(event).replace(QExtBinaryLoggingEvent::binaryMarker(),
                                                     QStringLiteral("%1 bytes: %2").
                                                     arg(binaryEvent->binaryMessage().size()).arg(spacedHexData));
        }
    }
    return QString();
}

