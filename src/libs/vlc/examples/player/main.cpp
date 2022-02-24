#include <QApplication>
#include <QThread>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QLoggingCategory>
#endif

#include <qextVLCCommon.h>
#include <qextVLCInstance.h>
#include <qextVLCMedia.h>
#include <qextVLCMetaManager.h>

#include "Player.h"
#include <stdio.h>

#define LIBVLC_PLUGINS_DIR "/usr/plugins"


#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
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
#else
void logMessageHandler(QtMsgType type, const char *msg)
{
    QString typeString;
    switch(type)
    {
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

    fprintf(stdout, "%s\n", formatMessage.toLatin1().data());
    fflush(stdout);
}
#endif

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, false);
    QLoggingCategory::defaultCategory()->setEnabled(QtWarningMsg, false);
    //    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, false);
#endif


#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    qInstallMessageHandler(&logMessageHandler);
#else
    qInstallMsgHandler(&logMessageHandler);
#endif

    QApplication app(argc, argv);

    QEXT_DECL_UNSETENV("VLC_PLUGIN_PATH");

#ifndef Q_OS_DARWIN
    QEXTVLCCommon::setPluginPath(QString(LIBVLC_PLUGINS_DIR));
#endif

    //    QThread thread;
    QEXTVLCInstance instance(QEXTVLCCommon::args());
    //    instance.moveToThread(&thread);
    //    thread.start();
    instance.setLogLevel(QEXTVLC::LogLevel_Debug);
    Player *testPlayer = new Player(&instance);
    testPlayer->show();

    return app.exec();
}


//#include "TestPlayer.moc"
