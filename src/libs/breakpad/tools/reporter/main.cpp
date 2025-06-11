#include <QCommandLineParser>
#include <QElapsedTimer>
#include <QApplication>
#include <QDateTime>
#include <QDebug>

#include <qextStyleThemes.h>

#include "mainwindow.h"

#define OPTION_STYLE "style"
#define OPTION_TITLE "title"
#define OPTION_TIME "time"
#define OPTION_PATH "path"
#define OPTION_APP "app"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#   if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#   endif
#endif

    QApplication::setOrganizationName("QExt");
    QApplication::setOrganizationDomain("BreakpadReporter");
    QApplication::setApplicationName("QExt Breakpad Crash Reporter");
    QApplication::setApplicationVersion("1.0");

    QApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();

    QStringList styleThemes = qextStyleThemes->styleThemes();
    QString styleThemesOptions = styleThemes.join(", ");
    QCommandLineOption styleValueLongOption(OPTION_STYLE, QString("QExt breakpad crash reporter styletheme name.\noptions[%1]").
                                                          arg(styleThemesOptions),
                                            "NAME", "fusion White");
    QCommandLineOption titleValueLongOption(OPTION_TITLE, "QExt breakpad crash reporter title name.",
                                            "NAME", "QExt Breakpad Crash Reporter");
    QCommandLineOption timeValueLongOption(OPTION_TIME, "QExt breakpad crash reporter auto close time.",
                                           "NUMBER", "0");
    QCommandLineOption pathValueLongOption(OPTION_PATH, "QExt breakpad crash dump file path.",
                                           "PATH", "");
    QCommandLineOption appValueLongOption(OPTION_APP, "QExt crashed app path.",
                                          "PATH", "");
    parser.addOption(styleValueLongOption);
    parser.addOption(titleValueLongOption);
    parser.addOption(timeValueLongOption);
    parser.addOption(pathValueLongOption);
    parser.addOption(appValueLongOption);

    parser.process(app);

    MainWindow mainWindow;
    QString styleTheme = parser.value(OPTION_STYLE);
    qDebug() << "styleTheme=" << styleTheme;
    if (!styleTheme.isEmpty())
    {
        qextStyleThemes->setCurrentStyleTheme(styleTheme);
        qextStyleThemes->updateStylesheet();
        mainWindow.setStyleSheet(qextStyleThemes->styleSheet());
    }
    mainWindow.setWindowTitle(parser.value(OPTION_TITLE));
    mainWindow.setCrashedAppName(parser.value(OPTION_APP));
    mainWindow.setCrashedFilePath(parser.value(OPTION_PATH));
    mainWindow.setAutoCloseTime(parser.value(OPTION_TIME).toInt());

    mainWindow.start();
    return app.exec();
}
