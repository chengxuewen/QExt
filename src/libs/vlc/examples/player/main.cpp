#include <QApplication>
#include <QThread>
#include <QLoggingCategory>

#include <qextVLCCommon.h>
#include <qextVLCInstance.h>
#include <qextVLCMedia.h>
#include <qextVLCMetaManager.h>

#include "Player.h"

#define LIBVLC_PLUGINS_DIR "/usr/plugins"

void logMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString typeString;
    switch(type)
    {
    case QtInfoMsg:
        typeString = QString("Info:");
        break;
    case QtDebugMsg:
        typeString = QString("Debug:");
        break;
    case QtWarningMsg:
        typeString = QString("Warning:");
        break;
    case QtCriticalMsg:
        typeString = QString("Critical:");
        break;
    case QtFatalMsg:
        typeString = QString("Fatal:");
    }

    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString formatMessage = QString("%1 [%2] MSG:%3").arg(dateTime, typeString, msg);
    if (QtWarningMsg == type || QtCriticalMsg == type || QtFatalMsg == type)
    {
        formatMessage += QString("\n        [file]:%1 [line]:%2").arg(context.file).arg(context.line);
    }

    fprintf(stdout, "%s\n", formatMessage.toLatin1().data());
    fflush(stdout);
}

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, false);
#endif
    qInstallMessageHandler(&logMessageHandler);

    QApplication app(argc, argv);

    qunsetenv("VLC_PLUGIN_PATH");

#ifndef Q_OS_DARWIN
    QEXTVLCCommon::setPluginPath(QString(LIBVLC_PLUGINS_DIR));
#endif

    QThread thread;
    QEXTVLCInstance instance(QEXTVLCCommon::args());
    instance.moveToThread(&thread);
    thread.start();
    instance.setLogLevel(QEXTVLC::LogLevel_Debug);
    Player *testPlayer = new Player(&instance);
    testPlayer->show();

    return app.exec();
}


//#include "TestPlayer.moc"
