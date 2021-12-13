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

#ifndef _QEXTQMLVLCSOURCE_H
#define _QEXTQMLVLCSOURCE_H

#include <QtCore/QObject>
#include <QtQml/QQmlParserStatus>

#include <qextQmlVLCGlobal.h>

class QEXTVLCMediaPlayer;

class QEXTQmlVLCVideoOutput;
class QEXTQmlVLCVideoStream;

/*!
    \class QEXTQmlVLCSource qextQmlVLCSource.h
    \ingroup QEXTQmlVLC
    \brief QML video source

    A special class which represents video source.
    QEXTQmlVLCVideoOutput can connect to any class that subclasses this one.

    \see QEXTQmlVLCPlayer
    \see QEXTQmlVLCVideoOutput

    \since QEXT 0.11.1
 */
class QEXT_QMLVLC_API QEXTQmlVLCSource : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
public:
    /*!
        \brief QEXTQmlVLCSource constructor
        \param parent parent object
     */
    QEXTQmlVLCSource(QObject *parent);
    ~QEXTQmlVLCSource();

    /*!
        \brief Set media player to use
        \param player media player
     */
    void setPlayer(QEXTVLCMediaPlayer *player);

    /*!
        \brief Remove player from source
    */
    void removePlayer();

    /*!
        \brief Register video output
        \param output QML video output
     */
    virtual void registerVideoOutput(QEXTQmlVLCVideoOutput *output);

    /*!
        \brief Deregister video output
        \param output QML video output
     */
    virtual void deregisterVideoOutput(QEXTQmlVLCVideoOutput *output);

private:
    void classBegin() override {}
    void componentComplete() override {}

    QEXTQmlVLCVideoStream *m_videoStream;
};

#endif // _QEXTQMLVLCSOURCE_H
