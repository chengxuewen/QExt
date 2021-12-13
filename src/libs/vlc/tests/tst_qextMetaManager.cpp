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

#include "qextVLCMedia.h"
#include "qextVLCMetaManager.h"

class TestMetaManager : public TestsCommon
{
    Q_OBJECT
private slots:
    void reading();
    void writing();
    void reset();
};

void TestMetaManager::reading()
{
    QEXTVLCMedia *media = new QEXTVLCMedia(QString(QEXT_TEST_SAMPLES_DIR) + "/sample.mp3", true, m_instance);
    QEXTVLCMetaManager *meta = new QEXTVLCMetaManager(media);

    QCOMPARE(meta->title(), QString("Noise"));
    QCOMPARE(meta->artist(), QString("Toine Heuvelmans"));
    QCOMPARE(meta->genre(), QString("Sample"));
    QCOMPARE(meta->copyright(), QString("Sample Copyright"));
    QCOMPARE(meta->album(), QString("Noise"));
    QCOMPARE(meta->number(), 1);
    QCOMPARE(meta->description(), QString("Noise sample description"));
    QCOMPARE(meta->year(), 2016);
    QCOMPARE(meta->language(), QString("Machine"));
    QCOMPARE(meta->publisher(), QString("Publisher"));
    QCOMPARE(meta->encoder(), QString("Encoder"));

    // TODO: meta->rating(), meta->setting(), meta->url(), meta->id()

    delete meta;
    delete media;
}

void TestMetaManager::writing()
{
    QEXTVLCMedia *media = new QEXTVLCMedia(QString(QEXT_TEST_SAMPLES_DIR) + "/sample.mp3", true, m_instance);
    QEXTVLCMetaManager *meta = new QEXTVLCMetaManager(media);

    QString title("TitleTest");
    QString artist("ArtistTest");
    QString genre("GenreTest");
    QString copyright("CopyrightTest");
    QString album("AlbumTest");
    int number = 100;
    QString description("DescriptionTest");
    int year = 1997;
    QString language("LanguageTest");
    QString publisher("PublisherTest");
    QString encoder("EncoderTest");

    meta->setTitle(title);
    meta->setArtist(artist);
    meta->setGenre(genre);
    meta->setCopyright(copyright);
    meta->setAlbum(album);
    meta->setNumber(number);
    meta->setDescription(description);
    meta->setYear(year);
    meta->setLanguage(language);
    meta->setPublisher(publisher);
    meta->setEncoder(encoder);

    QVERIFY(meta->saveMeta());

    delete meta;
    delete media;

    media = new QEXTVLCMedia(QString(QEXT_TEST_SAMPLES_DIR) + "/sample.mp3", true, m_instance);
    meta = new QEXTVLCMetaManager(media);

    QCOMPARE(meta->title(), title);
    QCOMPARE(meta->artist(), artist);
    QCOMPARE(meta->genre(), genre);
    QCOMPARE(meta->copyright(), copyright);
    QCOMPARE(meta->album(), album);
    QCOMPARE(meta->number(), number);
    QCOMPARE(meta->description(), description);
    QCOMPARE(meta->year(), year);
    QCOMPARE(meta->language(), language);
    QCOMPARE(meta->publisher(), publisher);
    QCOMPARE(meta->encoder(), encoder);

    delete meta;
    delete media;
}

void TestMetaManager::reset()
{
    QEXTVLCMedia *media = new QEXTVLCMedia(QString(QEXT_TEST_SAMPLES_DIR) + "/sample.mp3", true, m_instance);
    QEXTVLCMetaManager *meta = new QEXTVLCMetaManager(media);

    meta->setTitle("Noise");
    meta->setArtist("Toine Heuvelmans");
    meta->setGenre("Sample");
    meta->setCopyright("Sample Copyright");
    meta->setAlbum("Noise");
    meta->setNumber(1);
    meta->setDescription("Noise sample description");
    meta->setYear(2016);
    meta->setLanguage("Machine");
    meta->setPublisher("Publisher");
    meta->setEncoder("Encoder");

    meta->saveMeta();

    delete meta;
    delete media;
}

QTEST_MAIN(TestMetaManager)
#include "tst_qextMetaManager.moc"
