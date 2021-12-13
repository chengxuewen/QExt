/*************************************************************************************
*
* Library: QEXT
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
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

#ifndef _QEXTQMLVLCVIDEOOUTPUT_H
#define _QEXTQMLVLCVIDEOOUTPUT_H

#include <qextVLC.h>
#include <qextQmlVLCGlobal.h>

#include <QQuickItem>
#include <QPointer>

struct QEXTVLCYUVVideoFrame;
class QEXTQmlVLCSource;

/*!
    \class QEXTQmlVLCVideoOutput qextQmlVLCVideoOutput.h
    \ingroup QEXTQmlVLC
    \brief QML video output

    A QML video output that can be used to display video inside QML.

    \since QEXT 0.11.1
 */
class QEXT_QMLVLC_API QEXTQmlVLCVideoOutput : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QEXTQmlVLCSource *source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int fillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged)
    Q_PROPERTY(int aspectRatio READ aspectRatio WRITE setAspectRatio NOTIFY aspectRatioChanged)
    Q_PROPERTY(int cropRatio READ cropRatio WRITE setCropRatio NOTIFY cropRatioChanged)

public:
    QEXTQmlVLCVideoOutput();
    ~QEXTQmlVLCVideoOutput();

    /*!
        \brief Current video source
        \return source

        Used as property in QML.
     */
    QEXTQmlVLCSource *source() const;

    /*!
        \brief Set video source
        \param source video source

        Used as property in QML.
     */
    void setSource(QEXTQmlVLCSource *source);

    /*!
        \brief Current fill mode
        \return fill mode

        Used as property in QML.
     */
    int fillMode() const;

    /*!
        \brief Set fill mode
        \param mode fill mode

        Used as property in QML.
     */
    void setFillMode(int mode);

    /*!
        \brief Current aspect ratio
        \return aspect ratio

        Used as property in QML.
     */
    int aspectRatio() const;

    /*!
        \brief Set aspect ratio
        \param aspectRatio new aspect ratio

        No effect when fillMode equals QEXTVLC::Stretch.
        Used as property in QML.
     */
    void setAspectRatio(int aspectRatio);

    /*!
        \brief Current crop ratio
        \return crop ratio

        Used as property in QML.
     */
    int cropRatio() const;

    /*!
        \brief Set crop ratio
        \param cropRatio new crop ratio

        No effect when fillMode equals QEXTVLC::Stretch.
        Used as property in QML.
     */
    void setCropRatio(int cropRatio);

public slots:
    /*!
        \brief Set frame which will be rendered in the output.
        \param frame
     */
    void presentFrame(const QSharedPointer<const QEXTVLCYUVVideoFrame> &frame);

signals:
    /*!
        \brief Source changed signal
     */
    void sourceChanged();

    /*!
        \brief Fill mode changed signal
     */
    void fillModeChanged();

    /*!
        \brief Fill mode changed signal
     */
    void aspectRatioChanged();

    /*!
        \brief Fill mode changed signal
     */
    void cropRatioChanged();

private:
    virtual QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data);

    QEXTVLC::FillMode m_fillMode;
    QEXTVLC::RatioType m_aspectRatio;
    QEXTVLC::RatioType m_cropRatio;

    bool m_frameUpdated;
    QPointer<QEXTQmlVLCSource> m_source;
    QSharedPointer<const QEXTVLCYUVVideoFrame> m_frame;
};

#endif // _QEXTQMLVLCVIDEOOUTPUT_H
