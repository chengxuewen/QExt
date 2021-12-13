#include <qextVLCControlVideo.h>
#include <qextVLCError.h>
#include <qextVLCMediaPlayer.h>
#include <qextVLCVideo.h>

#include <QtCore/QTimer>

#if QT_VERSION >= 0x050000
    #include <QtWidgets/QAction>
#else
    #include <QtGui/QAction>
#endif

QEXTVLCControlVideo::QEXTVLCControlVideo(QEXTVLCMediaPlayer *player, const QString &language,  QObject *parent)
    : QObject(parent)
    , m_vlcMediaPlayer(player)
    , m_vlcVideo(player->video())
    , m_actionSubList(QList<QAction *>())
    , m_descSub(QMap<QString, int>())
    , m_idSub(QMap<int, int>())
    , m_actionVideoList(QList<QAction *>())
    , m_descVideo(QMap<QString, int>())
    , m_idVideo(QMap<int, int>())
    , m_manualLanguage(false)
{
    if (!language.isNull() && !language.isEmpty())
    {
        m_preferedLanguage = language.split(" / ");
    }

    m_timerSubtitles = new QTimer(this);
    connect(m_timerSubtitles, SIGNAL(timeout()), this, SLOT(updateSubtitleActions()));
    m_timerVideo = new QTimer(this);
    connect(m_timerVideo, SIGNAL(timeout()), this, SLOT(updateVideoActions()));

    m_timerSubtitles->start(1000);
    m_timerVideo->start(1000);
}

QEXTVLCControlVideo::~QEXTVLCControlVideo()
{
    delete m_timerSubtitles;
    delete m_timerVideo;
}

void QEXTVLCControlVideo::updateSubtitleActions()
{
    qDeleteAll(m_actionSubList);
    m_actionSubList.clear();
    m_descSub.clear();
    m_idSub.clear();

    if (!(m_vlcMediaPlayer->state() == QEXTVLC::State_Playing || m_vlcMediaPlayer->state() == QEXTVLC::State_Paused))
    {
        emit actions(m_actionSubList, QEXTVLC::Actions_Subtitles);
        emit subtitleTracks(m_actionSubList);
        return;
    }

    if (m_vlcVideo->subtitleCount() > 0)
    {
        QStringList desc = m_vlcVideo->subtitleDescription();
        //QList<int> ids = _vlcVideo->subtitleIds();
        for (int i = 0; i < desc.size(); i++)
        {
            m_descSub.insert(desc[i], i); //_descSub.insert(desc[i], ids[i]);
            m_idSub.insert(i, i);         //_idSub.insert(ids[i], i);
            m_actionSubList << new QAction(desc[i], this);
        }
    }
    else
    {
        emit actions(m_actionSubList, QEXTVLC::Actions_Subtitles);
        emit subtitleTracks(m_actionSubList);
        m_timerSubtitles->start(1000);
        return;
    }

    foreach (QAction *action, m_actionSubList)
    {
        action->setCheckable(true);
        connect(action, SIGNAL(triggered()), this, SLOT(updateSubtitles()));

        if (!m_manualLanguage)
        {
            foreach (const QString &language, m_preferedLanguage)
            {
                if (action->text().contains(language, Qt::CaseInsensitive))
                {
                    action->trigger();
                    m_manualLanguage = true;
                }
            }
        }
    }

    m_actionSubList[m_idSub[m_vlcVideo->subtitle()]]->setChecked(true);

    emit actions(m_actionSubList, QEXTVLC::Actions_Subtitles);
    emit subtitleTracks(m_actionSubList);

    m_timerSubtitles->start(60000);
}

void QEXTVLCControlVideo::updateSubtitles()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
    {
        return;
    }

    int id = m_descSub.value(action->text());

    m_vlcVideo->setSubtitle(id);
}

void QEXTVLCControlVideo::loadSubtitle(const QString &subtitle)
{
    if (subtitle.isEmpty())
    {
        return;
    }

    m_vlcVideo->setSubtitleFile(subtitle);

    m_timerSubtitles->start(1000);
}

void QEXTVLCControlVideo::updateVideoActions()
{
    qDeleteAll(m_actionVideoList);
    m_actionVideoList.clear();
    m_descVideo.clear();
    m_idVideo.clear();

    if (!(m_vlcMediaPlayer->state() == QEXTVLC::State_Playing || m_vlcMediaPlayer->state() == QEXTVLC::State_Paused))
    {
        emit actions(m_actionVideoList, QEXTVLC::Actions_VideoTrack);
        emit videoTracks(m_actionVideoList);
        return;
    }

    if (m_vlcVideo->trackCount() > 0)
    {
        QStringList desc = m_vlcVideo->trackDescription();
        QList<int> ids = m_vlcVideo->trackIds();
        for (int i = 0; i < desc.size(); i++)
        {
            m_descVideo.insert(desc[i], ids[i]);
            m_idVideo.insert(ids[i], i);
            m_actionVideoList << new QAction(desc[i], this);
        }
    }
    else
    {
        emit actions(m_actionVideoList, QEXTVLC::Actions_VideoTrack);
        emit videoTracks(m_actionVideoList);
        m_timerVideo->start(1000);
        return;
    }

    foreach (QAction *action, m_actionVideoList)
    {
        action->setCheckable(true);
        connect(action, SIGNAL(triggered()), this, SLOT(updateVideo()));
    }

    m_actionVideoList[m_idVideo[m_vlcVideo->track()]]->setChecked(true);

    emit actions(m_actionVideoList, QEXTVLC::Actions_VideoTrack);
    emit videoTracks(m_actionVideoList);

    m_timerVideo->start(60000);
}

void QEXTVLCControlVideo::updateVideo()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
    {
        return;
    }

    int id = m_descVideo.value(action->text());

    m_vlcVideo->setTrack(id);
}

void QEXTVLCControlVideo::reset()
{
    m_timerSubtitles->start(1000);
    m_timerVideo->start(1000);
    m_manualLanguage = false;
}

void QEXTVLCControlVideo::setDefaultSubtitleLanguage(const QString &language)
{
    m_preferedLanguage = language.split(" / ");
}
