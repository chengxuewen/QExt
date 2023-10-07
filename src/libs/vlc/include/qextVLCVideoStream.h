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

#ifndef _QEXTVLCVIDEOSTREAM_H
#define _QEXTVLCVIDEOSTREAM_H

#include <qextVLCAbstractVideoFrame.h>
#include <qextVLCAbstractVideoStream.h>
#include <qextVLC.h>
#include <qextVLCGlobal.h>

#include <QObject>
#include <QSharedPointer>
#include <QQueue>
#include <QList>

#include <deque>
#include <list>
#include <memory>

class QEXTVLCMediaPlayer;

/*!
    \class QEXTVLCVideoStream qextVLCVideoStream.h
    \ingroup QEXTVLC
    \brief Video memory stream

    QEXTVLCVideoStream sets proper callbacks to get YUV frames from libVLC.
    This class should be subclassed and implement frameUpdated to specify what to do with the frame.

    \see QEXTQmlVLCVideoStream
    \see QEXTVLCAbstractVideoFrame
    \since QExt 0.11.1
 */
class QEXT_VLC_API QEXTVLCVideoStream : public QObject, public QEXTVLCAbstractVideoStream
{
    Q_OBJECT
public:
    /*!
        \brief QEXTVLCVideoStream constructor
        \param format rendering format
        \param parent parent object
     */
    explicit QEXTVLCVideoStream(QEXTVLC::RenderFormatType format, QObject *parent = 0);
    ~QEXTVLCVideoStream();

    /*!
        \brief Rendering format
        \return current rendering format
     */
    QEXTVLC::RenderFormatType format() const
    {
        return m_format;
    }

    /*!
        \brief Initialise video memory stream with player
        \param player media player
     */
    void init(QEXTVLCMediaPlayer *player);

    /*!
        \brief Prepare video memory stream for deletion
     */
    void deinit();

    /*!
        \brief Get current frame
        \return current frame
     */
    QSharedPointer<const QEXTVLCAbstractVideoFrame> renderFrame() const
    {
        return m_renderFrame;
    }

private:
    Q_INVOKABLE virtual void frameUpdated() = 0;

    unsigned formatCallback(char *chroma, unsigned *width, unsigned *height,
                            unsigned *pitches, unsigned *lines);
    void formatCleanUpCallback();

    void *lockCallback(void **planes);
    void unlockCallback(void *picture, void *const *planes);
    void displayCallback(void *picture);

    QSharedPointer<QEXTVLCAbstractVideoFrame> cloneFrame(const QSharedPointer<QEXTVLCAbstractVideoFrame> &frame);

    QEXTVLC::RenderFormatType m_format;
    QEXTVLCMediaPlayer *m_player;

    QQueue<QSharedPointer<QEXTVLCAbstractVideoFrame> > m_framesQueue;
    QList<QSharedPointer<QEXTVLCAbstractVideoFrame> > m_lockedFramesList;
    QSharedPointer<QEXTVLCAbstractVideoFrame> m_renderFrame;
};

#endif // _QEXTVLCVIDEOSTREAM_H
