/*************************************************************************************
*
* Library: QExt
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
* Copyright (C) 2014-2015, Sergey Radionov <rsatom_gmail.com>
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

#ifndef _QEXTVLCABSTRACTVIDEOFRAME_H
#define _QEXTVLCABSTRACTVIDEOFRAME_H

#include <qextVLC.h>
#include <qextVLCGlobal.h>

#include <QByteArray>
#include <QVector>

#include <QSharedPointer>

/*!
    \struct QEXTVLCAbstractVideoFrame qextVLCAbstractVideoFrame.h
    \ingroup QEXTVLC
    \brief Abstract video frame data container
    \since QExt 0.11.1
*/
struct QEXT_VLC_API QEXTVLCAbstractVideoFrame
{
    /*!
        \brief QEXTVLCVideoFrame constructor.
        \param planeCount
    */
    QEXTVLCAbstractVideoFrame(int planeCount);
    virtual ~QEXTVLCAbstractVideoFrame() = 0;

    /*!
        \brief Reset frame to default values
     */
    void clear();

    /*!
        \brief Validate frame
        \return true if frame has size greater than 0 in both dimensions
     */
    bool isValid();

    /*!
        \brief Set pitches and lines helper
        \param pitches
        \param lines
     */
    void setPitchesAndLines(unsigned *pitches, unsigned *lines);

    /*!
        \brief Set pitches and lines helper
        \param frame frame to copy from
     */
    void setPitchesAndLines(const QSharedPointer<QEXTVLCAbstractVideoFrame> &frame);

    QByteArray frameBuffer; /*!< frame buffer */

    quint16 width;  /*!< frame width */
    quint16 height; /*!< frame height */

    QVector<char *> planes;      /*!< planes */
    QVector<quint32> planeSizes; /*!< plane sizes */
};

#endif // _QEXTVLCABSTRACTVIDEOFRAME_H
