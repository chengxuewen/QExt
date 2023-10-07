/*************************************************************************************
*
* Library: QExt
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
*
* Based on Phonon multimedia library
* Copyright (C) 2011 Harald Sitter <sitter@kde.org>
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

#ifndef _QEXTQMLVLCGLSLPAINTER_H
#define _QEXTQMLVLCGLSLPAINTER_H

#include <qextQmlVLCGLPainter.h>

#include <QtCore/QRectF>
#include <QtCore/QTime>
#include <QtQuick/QQuickItem>

class QOpenGLShaderProgram;
class QPainter;
class QQuickItem;

struct VideoFrame;

class QEXTQmlVLCGLSLPainter : public QEXTQmlVLCGlPainter
{
public:
    QEXTQmlVLCGLSLPainter();
    virtual ~QEXTQmlVLCGLSLPainter();

    void init();
    void paint(QPainter *painter, QRectF target, QQuickItem *quickItem);

private:
    void calculateFPS();

    struct FPS
    {
        FPS() : value(0),
            frames(0) { }

        qreal value;
        quint64 frames;
        QTime lastTime;
    };
    struct FPS m_fps;

    QOpenGLShaderProgram *m_program;
};

#endif // _QEXTQMLVLCGLSLPAINTER_H
