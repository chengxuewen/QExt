/*************************************************************************************
*
* Library: QEXT
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

#ifndef _QEXTQMLVLCVIDEOOBJECT_H
#define _QEXTQMLVLCVIDEOOBJECT_H

#include <QtCore/QMap>
#include <QtCore/QMutex>
#include <QtQuick/QQuickPaintedItem>

#include <qextVLC.h>
#include <qextVLCVideoFrame.h>
#include <qextVLCVideoMemoryStream.h>

#include <qextQmlVLCGlobal.h>

class QEXTVLCMediaPlayer;

class QEXTQmlVLCGLSLPainter;

/*!
    \class QEXTQmlVLCVideoObject qextQmlVLCVideoObject.h
    \ingroup QEXTQmlVLC
    \brief QML video object (deprecated)

    A basic QML video object for painting video. It acts as a replacement for video widget.

    @deprecated Deprecated since QEXT 0.11.1
 */
class Q_DECL_DEPRECATED QEXT_QMLVLC_API QEXTQmlVLCVideoObject : public QQuickPaintedItem, public QEXTVLCVideoMemoryStream
{
    Q_OBJECT
public:
    /*!
        \brief QEXTQmlVLCVideoObject constructor.
        \param parent parent item
     */
    explicit QEXTQmlVLCVideoObject(QQuickItem *parent = 0);

    /*!
        QEXTVLCMediaPlayer destructor
     */
    virtual ~QEXTQmlVLCVideoObject();


    /*!
        \brief Connect to media player
        \param player media player
     */
    void connectToMediaPlayer(QEXTVLCMediaPlayer *player);

    /*!
        \brief Disconnect from media player
        \param player media player
     */
    void disconnectFromMediaPlayer(QEXTVLCMediaPlayer *player);


    /*!
        \brief Get current aspect ratio
        \return aspect ratio
     */
    QEXTVLC::RatioType aspectRatio() const;

    /*!
        \brief Set aspect ratio
        \param aspectRatio new aspect ratio
     */
    void setAspectRatio(const QEXTVLC::RatioType &aspectRatio);

    /*!
        \brief Get current crop ratio
        \return crop ratio
     */
    QEXTVLC::RatioType cropRatio() const;

    /*!
        \brief Set crop ratio
        \param cropRatio new crop ratio
     */
    void setCropRatio(const QEXTVLC::RatioType &cropRatio);

protected:
    /*!
        \brief Core media player
     */
    QEXTVLCMediaPlayer *m_player;

private slots:
    void frameReady();
    void reset();

private:
    virtual void *lockCallback(void **planes);
    virtual void unlockCallback(void *picture, void *const *planes);
    virtual void displayCallback(void *picture);

    virtual unsigned formatCallback(char *chroma, unsigned *width, unsigned *height,
                                    unsigned *pitches, unsigned *lines);
    virtual void formatCleanUpCallback();

    virtual QRectF boundingRect() const;
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

    void paint(QPainter *painter);

    void lock();
    bool tryLock();
    void unlock();

    void updateBoundingRect();
    void updateAspectRatio();
    void updateCropRatio();

    QMutex m_mutex;
    QEXTVLCVideoFrame m_frame;

    QRectF m_geometry;
    QRectF m_boundingRect;
    QSize m_frameSize;

    QEXTQmlVLCGLSLPainter *m_graphicsPainter;

    bool m_paintedOnce;
    bool m_gotSize;

    QEXTVLC::RatioType m_aspectRatio;
    QEXTVLC::RatioType m_cropRatio;
};

#endif // _QEXTQMLVLCVIDEOOBJECT_H
