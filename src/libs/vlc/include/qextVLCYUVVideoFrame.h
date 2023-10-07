/*************************************************************************************
*
* Library: QExt
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

#ifndef _QEXTVLCYUVVIDEOFRAME_H
#define _QEXTVLCYUVVIDEOFRAME_H

#include <qextVLCAbstractVideoFrame.h>
#include <qextVLCGlobal.h>

#include <QSharedPointer>

/*!
    \struct QEXTVLCYUVVideoFrame qextVLCYUVVideoFrame.h
    \ingroup QEXTVLC
    \brief Video YUV frame data container
    \since QExt 0.11.1
*/
struct QEXT_VLC_API QEXTVLCYUVVideoFrame : QEXTVLCAbstractVideoFrame
{
    /*!
        \brief QEXTVLCVideoFrame constructor.
        This construction ensures data is set and containers prepared.
        \param width
        \param height
        \param pitches
        \param lines
    */
    QEXTVLCYUVVideoFrame(unsigned *width, unsigned *height,
                         unsigned *pitches, unsigned *lines);

    /*!
        \brief QEXTVLCVideoFrame constructor.
        This construction copies an existing frame into a new one.
        \param frame existing shared pointer to a frame
    */
    QEXTVLCYUVVideoFrame(const QSharedPointer<QEXTVLCYUVVideoFrame> &frame);

    ~QEXTVLCYUVVideoFrame();
};

#endif // _QEXTVLCYUVVIDEOFRAME_H
