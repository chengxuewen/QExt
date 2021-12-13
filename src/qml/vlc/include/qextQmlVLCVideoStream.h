/*************************************************************************************
*
* Library: QEXT
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
* Copyright (C) 2014-2015, Sergey Radionov <rsatom_gmail.com>
*
* This file is based on QmlVlc library
*
* License: MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*************************************************************************************/

#ifndef _QEXTQMLVLCVIDEOSTREAM_H
#define _QEXTQMLVLCVIDEOSTREAM_H

#include <qextVLCVideoStream.h>

class QEXTQmlVLCVideoOutput;

class QEXTQmlVLCVideoStream : public QEXTVLCVideoStream
{
    Q_OBJECT
public:
    explicit QEXTQmlVLCVideoStream(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTQmlVLCVideoStream();

    void registerVideoOutput(QEXTQmlVLCVideoOutput *output);
    void deregisterVideoOutput(QEXTQmlVLCVideoOutput *output);

    QList<QEXTQmlVLCVideoOutput *> attachedOutputs() const { return m_attachedOutputs; }

private:
    Q_INVOKABLE virtual void frameUpdated();

    QList<QEXTQmlVLCVideoOutput *> m_attachedOutputs;
};

#endif // _QEXTQMLVLCVIDEOSTREAM_H
