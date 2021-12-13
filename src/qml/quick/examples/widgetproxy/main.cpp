#include <QApplication>
#include <QQuickView>
#include <QDir>
#include <QQmlEngine>
#include <QQmlApplicationEngine>

#include "calendarwidgetproxyitem.h"

int main(int argc, char *argv[])
{
    // Qt Charts uses Qt Graphics View Framework for drawing, therefore QApplication must be used.
    QApplication app(argc, argv);

    qmlRegisterType<CalendarWidgetProxyItem>("QEXTQuick", 1, 0, "QEXTCalendar");

    QQmlApplicationEngine engine("qrc:/qmlwindow.qml");
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}
