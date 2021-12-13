/*************************************************************************************
*
* Library: QEXT
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
* Copyright (C) 2012 Harald Sitter <sitter@kde.org>
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

#ifndef _QEXTVLCABSTRACTVIDEOSTREAM_H
#define _QEXTVLCABSTRACTVIDEOSTREAM_H

#include <qextVLCGlobal.h>

class QEXTVLCMediaPlayer;

/*!
    \class QEXTVLCAbstractVideoStream qextVLCAbstractVideoStream.h
    \ingroup QEXTVLC
    \brief Abstract video memory stream

    QEXTVLCAbstractVideoStream is a template class for creating own video rendering engines.
    Subclass it and implement necessary calbacks.

    \since QEXT 0.11.1
 */
class QEXT_VLC_API QEXTVLCAbstractVideoStream
{
public:
    explicit QEXTVLCAbstractVideoStream();
    virtual ~QEXTVLCAbstractVideoStream();

    /*!
        \brief Set QEXTVLCMediaPlayer callbacks
        \param player media player
     */
    void setCallbacks(QEXTVLCMediaPlayer *player);

    /*!
        \brief Unset QEXTVLCMediaPlayer callbacks
        \param player media player
     */
    void unsetCallbacks(QEXTVLCMediaPlayer *player);

protected:
    /*!
        \brief Lock callback
     */
    virtual void *lockCallback(void **planes) = 0;

    /*!
        \brief Unlock callback
     */
    virtual void unlockCallback(void *picture, void *const *planes) = 0;

    /*!
        \brief Display callback
     */
    virtual void displayCallback(void *picture) = 0;

    /*!
        \brief Format callback
     */
    virtual unsigned formatCallback(char *chroma, unsigned *width, unsigned *height,
                                    unsigned *pitches, unsigned *lines) = 0;

    /*!
        \brief Format cleanup callback
     */
    virtual void formatCleanUpCallback() = 0;

private:
    static void *lockCallbackInternal(void *opaque, void **planes);
    static void unlockCallbackInternal(void *opaque, void *picture, void *const *planes);
    static void displayCallbackInternal(void *opaque, void *picture);

    static unsigned formatCallbackInternal(void **opaque, char *chroma,
                                           unsigned *width, unsigned *height,
                                           unsigned *pitches, unsigned *lines);
    static void formatCleanUpCallbackInternal(void *opaque);
};

#endif // _QEXTVLCABSTRACTVIDEOSTREAM_H
