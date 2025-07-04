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

#include <qextLogXMLLayout.h>
#include <qextLoggingEvent.h>

#include <QXmlStreamWriter>

QExtLogXMLLayout::QExtLogXMLLayout(QObject *parent)
    : QExtLogLayout(parent)

{
}

QString QExtLogXMLLayout::format(const QExtLoggingEvent &event)
{
    QString output;
    QXmlStreamWriter writer(&output);

    writer.writeStartElement(QStringLiteral("QExtLogging:Event"));
    writer.writeAttribute(QStringLiteral("logger"), event.loggename());
    writer.writeAttribute(QStringLiteral("timestamp"), QString::number(event.timeStamp()));
    writer.writeAttribute(QStringLiteral("level"), event.level().toString());
    writer.writeAttribute(QStringLiteral("thread"), event.threadName());

    writer.writeStartElement(QStringLiteral("QExtLogging:Message"));
    writer.writeCDATA(event.message());
    writer.writeEndElement();

    if (!event.ndc().isEmpty())
    {
        writer.writeStartElement(QStringLiteral("QExtLogging:NDC"));
        writer.writeCDATA(event.ndc());
        writer.writeEndElement();
    }

    auto props = event.properties();
    if (!props.isEmpty())
    {
        writer.writeStartElement(QStringLiteral("QExtLogging:Properties"));
        for (auto pos = props.constBegin(); pos != props.constEnd(); ++pos)
        {
            writer.writeStartElement(QStringLiteral("QExtLogging:Data"));
            writer.writeAttribute(QStringLiteral("name"), pos.key());
            writer.writeAttribute(QStringLiteral("value"), pos.value());
            writer.writeEndElement();
        }
        writer.writeEndElement();
    }
    writer.writeEndElement();

    return output;
}
