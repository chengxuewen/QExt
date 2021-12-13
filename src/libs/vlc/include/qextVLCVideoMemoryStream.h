/*************************************************************************************
*
* Library: QEXT
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2014 Tadej Novak <tadej@tano.si>
*
* Based on Phonon multimedia library
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

#ifndef _QEXTVLCVIDEOMEMORYSTREAM_H
#define _QEXTVLCVIDEOMEMORYSTREAM_H

#include <qextVLCGlobal.h>

///* MSVC support fix */
#if defined(_MSC_VER)
    #include <BaseTsd.h>
    typedef SSIZE_T ssize_t;
#endif

///* MSVC + MinGW support fix */
#if defined (_WIN32)
    #define LIBVLC_USE_PTHREAD_CANCEL 1
#endif

#include <vlc_common.h>
#include <vlc_fourcc.h>

class QEXTVLCMediaPlayer;

/*!
    \class QEXTVLCVideoMemoryStream qextVLCVideoMemoryStream.h
    \ingroup QEXTVLC
    \brief Video memory stream (deprecated)

    QEXTVLCVideoMemoryStream is a template class for creating own video rendering engines.

    \see QEXTVLCAbstractVideoStream
    @deprecated Deprecated since QEXT 0.11.1, will be removed in 2.0
 */
class Q_DECL_DEPRECATED QEXT_VLC_API QEXTVLCVideoMemoryStream
{
public:
    explicit QEXTVLCVideoMemoryStream();
    virtual ~QEXTVLCVideoMemoryStream();

    /*!
        \brief Set required information for rendering video

        \returns overall buffersize needed
     */
    static unsigned setPitchAndLines(const vlc_chroma_description_t *chromaDescription,
                                     unsigned width,
                                     unsigned height,
                                     unsigned *pitches,
                                     unsigned *lines,
                                     unsigned *visiblePitches = 0,
                                     unsigned *visibleLines = 0);

    /*!
        \brief Set QEXTVLCMediaPlayer callbacks
        \param player media player (QEXTVLCMediaPlayer *)
     */
    void setCallbacks(QEXTVLCMediaPlayer *player);

    /*!
        \brief Unset QEXTVLCMediaPlayer callbacks
        \param player media player (QEXTVLCMediaPlayer *)
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
    virtual void unlockCallback(void *picture,
                                void *const *planes) = 0;

    /*!
        \brief Display callback
     */
    virtual void displayCallback(void *picture) = 0;

    /*!
        \brief Format callback
     */
    virtual unsigned formatCallback(char *chroma,
                                    unsigned *width,
                                    unsigned *height,
                                    unsigned *pitches,
                                    unsigned *lines) = 0;

    /*!
        \brief Format cleanup callback
     */
    virtual void formatCleanUpCallback() = 0;

private:
    static void *lockCallbackInternal(void *opaque,
                                      void **planes);
    static void unlockCallbackInternal(void *opaque,
                                       void *picture,
                                       void *const *planes);
    static void displayCallbackInternal(void *opaque,
                                        void *picture);

    static unsigned formatCallbackInternal(void **opaque,
                                           char *chroma,
                                           unsigned *width,
                                           unsigned *height,
                                           unsigned *pitches,
                                           unsigned *lines);
    static void formatCleanUpCallbackInternal(void *opaque);
};

#endif // _QEXTVLCVIDEOMEMORYSTREAM_H
