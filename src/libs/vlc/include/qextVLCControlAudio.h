/*************************************************************************************
*
* Library: QExt
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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

#ifndef _QEXTVLCCONTROLAUDIO_H
#define _QEXTVLCCONTROLAUDIO_H

#include <qextVLC.h>
#include <qextVLCGlobal.h>

#include <QtCore/QList>
#include <QtCore/QMap>

class QAction;
class QTimer;

class QEXTVLCAudio;
class QEXTVLCMediaPlayer;

/*!
    \class QEXTVLCControlAudio qextVLCControlAudio.h
    \ingroup QEXTVLC
    \brief Audio control class

    This is one of VLC-Qt control classes.
    It provides audio tracks management.
*/
class QEXT_VLC_API QEXTVLCControlAudio : public QObject
{
    Q_OBJECT
public:
    /*!
        \brief QEXTVLCControlAudio constructor
        \param player media player
        \param language default audio language
        \param parent audio controller's parent object
    */
    explicit QEXTVLCControlAudio(QEXTVLCMediaPlayer *player, const QString &language = 0, QObject *parent = 0);

    /*!
        \brief AudioControl destructor
    */
    ~QEXTVLCControlAudio();

    /*!
        \brief Reset all settings and selected audio tracks.

        Usually called on media change.
    */
    void reset();

    /*!
        \brief Set default audio language
        \param language comma separated languages
    */
    void setDefaultAudioLanguage(const QString &language);

signals:
    /*!
        \brief Signal sending actions for changing audio tracks
        \param actions list of actions
        \param type type of actions
    */
    void actions(QList<QAction *> actions, const QEXTVLC::ActionsType type);

    /*!
        \brief Signal sending actions for changing audio tracks
        \param actions list of actions
    */
    void audioTracks(QList<QAction *> actions);

private slots:
    void clean();
    void update();
    void updateActions();

private:
    QEXTVLCAudio *m_vlcAudio;
    QEXTVLCMediaPlayer *m_vlcMediaPlayer;

    QTimer *m_timer;

    QList<QAction *> m_actionList;
    QMap<QString, int> m_desc;
    QMap<int, int> m_idMap;

    bool m_manualLanguage;
    QStringList m_preferedLanguage;
};

#endif // _QEXTVLCCONTROLAUDIO_H
