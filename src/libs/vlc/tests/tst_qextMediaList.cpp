/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
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

#include <QtTest/QtTest>

#include "TestsConfig.h"
#include "TestsCommon.h"

#include "qextVLCAudio.h"
#include "qextVLCMedia.h"
#include "qextVLCMediaList.h"
#include "qextVLCMediaListPlayer.h"
#include <qextVLCMediaPlayer.h>

class TestMediaList : public TestsCommon
{
    Q_OBJECT
private slots:
    void list();
    void player();
};

void TestMediaList::list()
{
    QEXTVLCMedia *referenceMedia = new QEXTVLCMedia("http://download.blender.org/peach/bigbuckbunny_movies/big_buck_bunny_480p_surround-fix.avi", m_instance);

    QEXTVLCMediaList *mediaList = new QEXTVLCMediaList(m_instance);
    mediaList->addMedia(new QEXTVLCMedia("http://videos.hd-trailers.net/Hobbit_The_Battle_Of_The_Five_Armies_2014_Trailer2_5.1-480p-HDTN.mp4", m_instance));
    mediaList->addMedia(referenceMedia);
    mediaList->insertMedia(new QEXTVLCMedia(QString(QEXT_TEST_SAMPLES_DIR) + "/sample.mp3", true, m_instance), 0);

    QCOMPARE(mediaList->count(), 3);
    QCOMPARE(mediaList->indexOf(referenceMedia), 2);
    QCOMPARE(mediaList->indexOf(referenceMedia->core()), 2);
    QCOMPARE(mediaList->at(2), referenceMedia);

    mediaList->removeMedia(0);

    QCOMPARE(mediaList->count(), 2);
    QCOMPARE(mediaList->indexOf(referenceMedia), 1);

    delete mediaList;
}

void TestMediaList::player()
{
    QEXTVLCMediaPlayer *player = new QEXTVLCMediaPlayer(m_instance);
    player->audio()->setVolume(0);
    QEXTVLCMediaListPlayer *listPlayer = new QEXTVLCMediaListPlayer(player, m_instance);

    QEXTVLCMediaList *mediaList = new QEXTVLCMediaList(m_instance);
    mediaList->addMedia(new QEXTVLCMedia("http://download.blender.org/peach/bigbuckbunny_movies/big_buck_bunny_480p_surround-fix.avi", m_instance));
    mediaList->addMedia(new QEXTVLCMedia(QString(QEXT_TEST_SAMPLES_DIR) + "/sample.mp3", true, m_instance));

    listPlayer->setMediaList(mediaList);
    listPlayer->setPlaybackMode(QEXTVLC::Playback_Loop);

    QCOMPARE(listPlayer->playbackMode(), QEXTVLC::Playback_Loop);

    listPlayer->play();

    QCOMPARE(listPlayer->currentMediaList(), mediaList);
    QCOMPARE(listPlayer->mediaPlayer(), player);

    QTest::qWait(2000);

    listPlayer->next();

    QTest::qWait(100);

    listPlayer->previous();

    QTest::qWait(1000);

    listPlayer->itemAt(1);

    QTest::qWait(100);

    listPlayer->stop();

    QTest::qWait(500);

    QEXTVLCMediaListPlayer *listPlayerStandalone = new QEXTVLCMediaListPlayer(m_instance);
    listPlayerStandalone->core();
}

QTEST_MAIN(TestMediaList)

#include "tst_qextMediaList.moc"
