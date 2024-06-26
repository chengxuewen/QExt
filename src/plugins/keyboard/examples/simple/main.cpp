#include <QApplication>
#include <QDebug>

#include <qextCommonUtils.h>

#include "Widget.h"

int main(int argc, char *argv[])
{
    QString pluginPath = QString("%1/../plugins").arg(QExtCommonUtils::executableDir());
    qputenv("QT_PLUGIN_PATH", pluginPath.toLatin1());
    qputenv("QT_IM_MODULE",QByteArray("qextkeyboard"));

    QApplication a(argc, argv);

    Widget w;
    w.show();

    return a.exec();
}
