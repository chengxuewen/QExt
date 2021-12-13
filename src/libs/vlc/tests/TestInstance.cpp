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

#include "qextVLCCommon.h"
#include "qextVLCInstance.h"

class TestInstance : public QObject
{
    Q_OBJECT
private slots:
    void init();

    void wrongArguments();
    void envArguments();
    void withExternalPluginsSet();
    void withPlugins();

    void versions();
    void userAgent();
    void appId();
    void filters();
};

void TestInstance::init()
{
    qunsetenv("VLC_PLUGIN_PATH");
}

void TestInstance::wrongArguments()
{
    QStringList wrong;
    wrong << "--something-wrong";
    QEXTVLCInstance *instance = new QEXTVLCInstance(wrong, this);

    QCOMPARE(instance->status(), false);

    delete instance;
}

void TestInstance::envArguments()
{
    qputenv("VLC_ARGS", QString("--something-wrong").toLocal8Bit());

    QEXTVLCInstance *instance = new QEXTVLCInstance(QEXTVLCCommon::args(), this);

    QCOMPARE(instance->status(), false);

    delete instance;

    qunsetenv("VLC_ARGS");
}

void TestInstance::withExternalPluginsSet()
{
    QEXTVLCCommon::setPluginPath("something/wrong");
    QEXTVLCCommon::setPluginPath(QString(QEXT_LIBVLC_PLUGIN_DIR));

    QEXTVLCInstance *instance = new QEXTVLCInstance(QEXTVLCCommon::args(), this);

    QCOMPARE(instance->status(), true);

    delete instance;
}

void TestInstance::withPlugins()
{
    QEXTVLCInstance *instance = new QEXTVLCInstance(QEXTVLCCommon::args(), this);
    instance->setLogLevel(QEXTVLC::LogLevel_Debug);

    QCOMPARE(instance->status(), true);

    delete instance;
}

void TestInstance::versions()
{
    QEXTVLCInstance *instance = new QEXTVLCInstance(QEXTVLCCommon::args(), this);

//    qDebug() << instance->libVersion() << instance->libVersionMajor() << instance->libVersionMinor();
    qCritical() << instance->version() << instance->changeset() << instance->compiler();

    delete instance;
}

void TestInstance::userAgent()
{
    QEXTVLCInstance *instance = new QEXTVLCInstance(QEXTVLCCommon::args(), this);

    instance->setUserAgent("TestCase", "1.0");

    delete instance;
}

void TestInstance::appId()
{
    QEXTVLCInstance *instance = new QEXTVLCInstance(QEXTVLCCommon::args(), this);

    instance->setAppId("si.tano.vlc-qt", "1.0", "image");

    delete instance;
}

void TestInstance::filters()
{
    QEXTVLCInstance *instance = new QEXTVLCInstance(QEXTVLCCommon::args(), this);

    instance->audioFilterList();
    instance->videoFilterList();

    delete instance;
}

QTEST_MAIN(TestInstance)
#include "TestInstance.moc"
