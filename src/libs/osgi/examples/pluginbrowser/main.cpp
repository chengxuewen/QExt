#include "qtkpluginbrowser.h"

#include <QTKPluginFramework/QTKPluginFrameworkFactory>
#include <QTKPluginFramework/QTKPluginFramework>
#include <QTKPluginFramework/QTKPluginException>

#include <QTKLog4/logger>
#include <QTKLog4/logmanager>
#include <QTKLog4/databaseappender>
#include <QTKLog4/databaselayout>
#include <QTKLog4/loggerrepository>
#include <QTKLog4/QTKLog4Configurator>
#include <QTKLog4/QTKLog4SqliteDatabaseAppender>

#include <QApplication>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QThread>

int main(int argv, char** argc)
{
    QApplication app(argv, argc);

//    QTKLog4Configurator::init();

//    app.setOrganizationName("QTK");
//    app.setOrganizationDomain("QTK.org");
//    app.setApplicationName("QTKPluginBrowser");

//    const QString connectionName = "MyConnection";
//    const QString databaseName = "MyDB.db";
//    const QString tableName = "MyTable";
//    const QString timeStampField = "TimeStamp";
//    const QString loggeNameField = "LoggeName";
//    const QString threadNameField = "ThreadName";
//    const QString levelField = "Level";
//    const QString messageField = "Message";


//    Log4Qt::Logger *logger = Log4Qt::Logger::rootLogger();
//    Log4Qt::DatabaseLayout *layout = new Log4Qt::DatabaseLayout();
//    layout->setName("SQliteLayout");
//    layout->setTimeStampColumn(timeStampField);
//    layout->setLoggenameColumn(loggeNameField);
//    layout->setThreadNameColumn(threadNameField);
//    layout->setLevelColumn(levelField);
//    layout->setMessageColumn(messageField);
//    layout->activateOptions();

//    Log4Qt::QTKLog4SqliteDatabaseAppender *appender = new Log4Qt::QTKLog4SqliteDatabaseAppender(layout);
//    appender->setLayout(layout);
//    appender->setName("SQliteAppender");
//    appender->initDatabase(databaseName, tableName);
//    appender->activateOptions();

//    logger->addAppender(appender);
//    logger->setLevel(Log4Qt::Level::DEBUG_INT);
//    logger->debug("Hello, Log4Qt!");
//    logger->removeAllAppenders();
//    logger->loggerRepository()->shutdown();
    qDebug() << "********** End **********";



    QTKPluginFrameworkFactory pfwFactory;
    QSharedPointer<QTKPluginFramework> framework = pfwFactory.getFramework();

    try {
        framework->init();
    } catch (const QTKPluginException &e) {
        qCritical() << "Failed to initialize the plug-in framework:" << e.printStackTrace();
        exit(1);
    }

    QTKPluginBrowser browser(framework.data());
    browser.show();

    qDebug() << "main test";

    return app.exec();
}
