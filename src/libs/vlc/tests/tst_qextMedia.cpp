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

class TestMedia : public TestsCommon
{
    Q_OBJECT
private slots:
    void localInit();
    void remoteInit();
    void copyInit();

    void basic();
    void recording();
    void options();
};

void TestMedia::localInit()
{
    QEXTVLCMedia *media = new QEXTVLCMedia(QString(QEXT_TEST_SAMPLES_DIR) + "/sample.mp3", true, m_instance);

    delete media;
}

void TestMedia::remoteInit()
{
    QEXTVLCMedia *media = new QEXTVLCMedia("http://localhost/sample.mp3", m_instance);

    delete media;
}

void TestMedia::copyInit()
{
    QEXTVLCMedia *media1 = new QEXTVLCMedia(QString(QEXT_TEST_SAMPLES_DIR) + "/sample.mp3", true, m_instance);
    QEXTVLCMedia *media2 = new QEXTVLCMedia(media1->core());

    Q_UNUSED(media2)
}

void TestMedia::basic()
{
    QEXTVLCMedia *media = new QEXTVLCMedia(QString(QEXT_TEST_SAMPLES_DIR) + "/sample.mp3", true, m_instance);

    QCOMPARE(media->parsed(), false);
    QCOMPARE(media->currentLocation(), QString(QEXT_TEST_SAMPLES_DIR) + "/sample.mp3");
    QCOMPARE(media->state(), QEXTVLC::State_Idle);

#ifdef Q_OS_MAC
    QEventLoop *loop = new QEventLoop(this);

    connect(media, static_cast<void (QEXTVLCMedia::*)(bool)>(&QEXTVLCMedia::parsedChanged), [=]() {
        QCOMPARE(media->duration(), 30097);

        media->getStats();

        loop->exit();

        delete media;
    });

    media->parse();

    loop->exec();
#endif
}

void TestMedia::recording()
{
    QEXTVLCMedia *media = new QEXTVLCMedia(QString(QEXT_TEST_SAMPLES_DIR) + "/sample.mp3", true, m_instance);
    QCOMPARE(media->duplicate("test", "path", QEXTVLC::Mux_AVI), QDir::toNativeSeparators("path/test.avi"));
    QCOMPARE(media->duplicate("test", "path", QEXTVLC::Mux_AVI, QEXTVLC::AudioCodec_MPEG2, QEXTVLC::VideoCodec_MPEG4), QDir::toNativeSeparators("path/test.avi"));
    QCOMPARE(media->duplicate("test", "path", QEXTVLC::Mux_AVI, QEXTVLC::AudioCodec_MPEG2, QEXTVLC::VideoCodec_MPEG4, 1000, 25, 1), QDir::toNativeSeparators("path/test.avi"));
    QCOMPARE(media->merge("test", "path", QEXTVLC::Mux_AVI), QDir::toNativeSeparators("path/test.avi"));
    QCOMPARE(media->record("test", "path", QEXTVLC::Mux_AVI, false), QDir::toNativeSeparators("path/test.avi"));
    QCOMPARE(media->record("test", "path", QEXTVLC::Mux_AVI, QEXTVLC::AudioCodec_MPEG2, QEXTVLC::VideoCodec_MPEG4, false), QDir::toNativeSeparators("path/test.avi"));
    QCOMPARE(media->record("test", "path", QEXTVLC::Mux_AVI, QEXTVLC::AudioCodec_MPEG2, QEXTVLC::VideoCodec_MPEG4, 1000, 25, 1, false), QDir::toNativeSeparators("path/test.avi"));

    delete media;
}

void TestMedia::options()
{
    QEXTVLCMedia *media = new QEXTVLCMedia(QString(QEXT_TEST_SAMPLES_DIR) + "/sample.mp3", true, m_instance);
    media->setProgram(1);
    media->setOptions(QStringList() << "option1"
                                    << "option2");
    delete media;
}

QTEST_MAIN(TestMedia)
#include "tst_qextMedia.moc"
