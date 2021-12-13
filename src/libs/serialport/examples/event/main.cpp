/**
 * @file main.cpp
 * \brief Main file.
 * @author Michal Policht
 */

#include <QCoreApplication>
#include "PortListener.h"

#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
#include <QLoggingCategory>
#endif

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
#endif

    QCoreApplication app(argc, argv);

    QString portName = QLatin1String("COM1");              // update this to use your port of choice
    PortListener listener(portName);        // signals get hooked up internally

    // start the event loop and wait for signals
    return app.exec();
}
