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

#ifndef _QEXTVLCCONTROLVIDEO_H
#define _QEXTVLCCONTROLVIDEO_H

#include <QtCore/QList>
#include <QtCore/QMap>

#include <qextVLC.h>
#include <qextVLCGlobal.h>

class QAction;
class QTimer;

class QEXTVLCMediaPlayer;
class QEXTVLCVideo;

/*!
    \class QEXTVLCControlVideo qextVLCControlVideo.h
    \ingroup QEXTVLC
    \brief Video control class

    This is one of VLC-Qt control classes.
    It provides video and subtitle tracks management.
*/
class QEXT_VLC_API QEXTVLCControlVideo : public QObject
{
    Q_OBJECT
public:
    /*!
        \brief VideoControl constructor
        \param player media player
        \param language default subtitle language
        \param parent video controller's parent object
    */
    explicit QEXTVLCControlVideo(QEXTVLCMediaPlayer *player, const QString &language = 0, QObject *parent = 0);

    /*!
        \brief VideoControl destructor
    */
    ~QEXTVLCControlVideo();

    /*!
        \brief Reset all settings and selected video and subtitle tracks

        Usually called on media change.
    */
    void reset();

    /*!
        \brief Set default subtitle language
        \param language comma separated languages
    */
    void setDefaultSubtitleLanguage(const QString &language);

public slots:
    /*!
        \brief Open and load subtitles from file
        \param subtitle full path to subtitles file
    */
    void loadSubtitle(const QString &subtitle);

signals:
    /*!
        \brief Signal sending actions for changing video and subititle tracks
        \param actions list of actions
        \param type type of actions
    */
    void actions(QList<QAction *> actions, const QEXTVLC::ActionsType type);

    /*!
        \brief Signal sending actions for changing subititle tracks
        \param actions list of actions
    */
    void subtitleTracks(QList<QAction *> actions);

    /*!
        \brief Signal sending actions for changing video tracks
        \param actions list of actions
    */
    void videoTracks(QList<QAction *> actions);

private slots:
    void updateSubtitleActions();
    void updateSubtitles();
    void updateVideoActions();
    void updateVideo();

private:
    QEXTVLCMediaPlayer *m_vlcMediaPlayer;
    QEXTVLCVideo *m_vlcVideo;

    QTimer *m_timerSubtitles;
    QTimer *m_timerVideo;

    QList<QAction *> m_actionSubList;
    QMap<QString, int> m_descSub;
    QMap<int, int> m_idSub;

    QList<QAction *> m_actionVideoList;
    QMap<QString, int> m_descVideo;
    QMap<int, int> m_idVideo;

    bool m_manualLanguage;
    QStringList m_preferedLanguage;
};

#endif // _QEXTVLCCONTROLVIDEO_H
