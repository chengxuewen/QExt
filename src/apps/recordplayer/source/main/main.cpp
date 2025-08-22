#undef NDEBUG
#include <rpApp.h>
#include <rpConfig.h>
#include <rpLogger.h>
#include <rpMainWindow.h>
#include <rpSplashScreen.h>

#include <qextCommonUtils.h>
#include <qextBreakpadHandler.h>
#include <qextInputMethodTrigger.h>
#include <qextKeyboardInputContext.h>

#ifdef RP_BUILD_USE_SINGLEAPP
#   include <singleapplication.h>
#endif

#include <QApplication>
#include <QLoggingCategory>
#include <QtMessageHandler>
#include <QCoreApplication>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QDateTime>
#include <QtGlobal>
#include <QIcon>
#include <QDebug>
#include <QFont>
#include <QtEndian>
#include <QLocale>
#include <QInputMethod>

#undef NDEBUG
#include<cassert>

int main(int argc, char *argv[])
{
#if 0
    QString pluginPath = QString("%1/../plugins").arg(QExtCommonUtils::executableDir());
    qputenv("QT_PLUGIN_PATH", pluginPath.toLatin1());
    qputenv("QT_IM_MODULE", QByteArray("qextkeyboard"));
    // qDebug() << "pluginPath=" << pluginPath;

    auto inputContext = QExtKeyboardInputContext::instance();
    inputContext->setInputPanelSize(800, 400);
    inputContext->setInputPanelPopupMode(QExtKeyboardInputContext::PopupMode_AutoFollow);
#endif

    QElapsedTimer timer;
    timer.start();

    QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#   if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#   endif
#endif

    QApplication::setOrganizationDomain(RP_ORGANIZATION_DOMAIN_NAME);
    QApplication::setApplicationName(RP_PROGRAM_NAME);
    QApplication application(argc, argv);
#ifdef RP_BUILD_USE_SINGLEAPP
    SingleApplication singleApp(argc, argv);
    if (singleApp.sendMessage("Wake up!"))
    {
        return 0;
    }
#endif

    qInstallMessageHandler(&RPLogger::messageHandler);
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);

    qextBreakpadHandler->setDumpPath(QExtCommonUtils::appUniqueDataLocation() + "crashes");
    qextBreakpadHandler->setReporterEnable(true);

    /* set logger */
    RPLogger::instance(RP_DEV().categoryName())->setAllFormatsEnable(true);
    RPLogger::instance(RP_DEV().categoryName())->setOutputEnable(RPLogger::Output_Console, true);

    /* set splashScreen */
    RPSplashScreen splashScreen;
    splashScreen.showMessage(QObject::tr("Initializing the application..."),
                             Qt::AlignHCenter | Qt::AlignBottom);
    splashScreen.show();
    application.processEvents();

    /* set input method trigger */
    QExtInputMethodTrigger::instance()->setAutoTriggerInputMethodEnable(true);

    /* start app */
    if (!RPApp::instance()->startApp())
    {
        qCCritical(RP_DEV()) << QString("%1 already started!").arg(RP_PROGRAM_NAME);
        return 0;
    }
    // splashScreen finish
    application.processEvents();
    splashScreen.finish(RPApp::instance()->mainwindow());

#ifdef RP_BUILD_USE_SINGLEAPP
    QObject::connect(&singleApp, &SingleApplication::instanceStarted, RPApp::instance(), &RPApp::raiseMainWindow);
#endif
    qCInfo(RP_DEV()) << QString("%1_%2 Startup time: %3ms").arg(RP_PROGRAM_NAME, RP_VERSION_STAGE).arg(timer.elapsed());
    return application.exec();
}
