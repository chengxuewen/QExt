#include "Player.h"
#include "ui_Player.h"

#include <qextVLCAudio.h>
#include <qextVLCCommon.h>
#include <qextVLCInstance.h>
#include <qextVLCMedia.h>
#include <qextVLCMediaPlayer.h>

Player::Player(QEXTVLCInstance *instance, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Player),
      m_instance(instance)
{
    ui->setupUi(this);

    if (!m_instance->status())
    {
        return;
    }

    m_player = new QEXTVLCMediaPlayer(m_instance);
    m_player->setVideoWidget(ui->video);

    ui->video->setMediaPlayer(m_player);
    ui->volume->setMediaPlayer(m_player);
    ui->volume->setVolume(50);
    ui->seek->setMediaPlayer(m_player);

    connect(ui->pause, SIGNAL(toggled(bool)), m_player, SLOT(togglePause()));
    connect(ui->stop, SIGNAL(clicked()), m_player, SLOT(stop()));

//    m_media = new QEXTVLCMedia("http://download.blender.org/peach/bigbuckbunny_movies/big_buck_bunny_480p_surround-fix.avi", _instance);
//    m_media = new QEXTVLCMedia("rtsp://192.168.91.225:8554/", m_instance);
//    m_media = new QEXTVLCMedia("rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov", m_instance);
    m_media = new QEXTVLCMedia("rtsp://admin:12345@192.168.5.51:8554/0", m_instance);
    m_media->setOption(":rtsp-tcp");
//    m_media->setOption(QString(":avcodec-hw=%1").arg("none"));
//    m_media->setOption(QString(":ffmpeg-hw"));
//    m_media->setOption(QString(":avcodec-fast"));
//    m_media->setOption(QString(":avcodec-dr"));
//    m_media->setOption(QString(":avcodec-fast"));
    m_media->setOption(QString(":gl=none"));
    m_media->setOption(QString(":glconv=none"));
//    m_media->setOption(QString(":network-caching=%1").arg(300));
//    m_media->setOption(QString(":auto-preparse"));
//    m_media->setOption(QString(":no-audio"));
//    m_media->setOption(QString(":preparse-timeout=%1").arg(300));
    m_player->open(m_media);
}

Player::~Player()
{
    if (m_instance->status())
    {
        m_player->stop();
        delete m_media;
        delete m_player;
    }
    delete m_instance;
    delete ui;
}
