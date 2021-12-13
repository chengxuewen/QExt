/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include <QtCore/QTimer>

#if QT_VERSION >= 0x050000
#include <QtWidgets/QAction>
#else
#include <QtGui/QAction>
#endif

#include "qextVLCAudio.h"
#include <qextVLCMediaPlayer.h>

#include "qextVLCControlAudio.h"

QEXTVLCControlAudio::QEXTVLCControlAudio(QEXTVLCMediaPlayer *player,
                                 const QString &language,
                                 QObject *parent)
    : QObject(parent),
      m_vlcAudio(player->audio()),
      m_vlcMediaPlayer(player),
      m_actionList(QList<QAction *>()),
      m_desc(QMap<QString, int>()),
      m_idMap(QMap<int, int>()),
      m_manualLanguage(false)
{
    if (!language.isNull() && !language.isEmpty())
        m_preferedLanguage = language.split(" / ");

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateActions()));

    m_timer->start(1000);
}

QEXTVLCControlAudio::~QEXTVLCControlAudio()
{
    delete m_timer;
}

void QEXTVLCControlAudio::clean()
{
    qDeleteAll(m_actionList);
    m_actionList.clear();
    m_desc.clear();
    m_idMap.clear();
}

void QEXTVLCControlAudio::reset()
{
    m_timer->start(1000);
}

void QEXTVLCControlAudio::update()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
        return;

    int id = m_desc.value(action->text());

    m_vlcAudio->setTrack(id);
}

void QEXTVLCControlAudio::updateActions()
{
    clean();

    if (!(m_vlcMediaPlayer->state() == QEXTVLC::State_Playing || m_vlcMediaPlayer->state() == QEXTVLC::State_Paused)) {
        emit actions(m_actionList, QEXTVLC::Actions_AudioTrack);
        emit audioTracks(m_actionList);
        return;
    }

    if (m_vlcAudio->trackCount() > 0) {
        QStringList desc = m_vlcAudio->trackDescription();
        QList<int> ids = m_vlcAudio->trackIds();
        for (int i = 0; i < desc.size(); i++) {
            m_desc.insert(desc[i], ids[i]);
            m_idMap.insert(ids[i], i);
            m_actionList << new QAction(desc[i], this);
        }
    } else {
        emit actions(m_actionList, QEXTVLC::Actions_AudioTrack);
        emit audioTracks(m_actionList);
        m_timer->start(1000);
        return;
    }

    foreach (QAction *action, m_actionList) {
        action->setCheckable(true);
        connect(action, SIGNAL(triggered()), this, SLOT(update()));

        if (!m_manualLanguage) {
            foreach (const QString &language, m_preferedLanguage) {
                if (action->text().contains(language, Qt::CaseInsensitive)) {
                    action->trigger();
                    m_manualLanguage = true;
                }
            }
        }
    }

    m_actionList[m_idMap[m_vlcAudio->track()]]->setChecked(true);

    emit actions(m_actionList, QEXTVLC::Actions_AudioTrack);
    emit audioTracks(m_actionList);

    m_timer->start(60000);
}

void QEXTVLCControlAudio::setDefaultAudioLanguage(const QString &language)
{
    m_preferedLanguage = language.split(" / ");
}
