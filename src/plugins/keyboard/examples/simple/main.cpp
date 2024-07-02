#include <QApplication>
#include <QDebug>

#include <qextCommonUtils.h>
#include <qextKeyboardInputContext.h>

#include "Widget.h"

int main(int argc, char *argv[])
{
    QString pluginPath = QString("%1/../plugins").arg(QExtCommonUtils::executableDir());
    qputenv("QT_PLUGIN_PATH", pluginPath.toLatin1());
    qputenv("QT_IM_MODULE",QByteArray("qextkeyboard"));
    qDebug() << "pluginPath=" << pluginPath;

    QApplication a(argc, argv);

    Widget w;
    w.show();

    QExtKeyboardInputContext *inputContext = QExtKeyboardInputContext::instance();
    inputContext->setInputPanelSize(600, 300);
    inputContext->setInputPanelPopupMode(QExtKeyboardInputContext::PopupMode_AutoFollow);
    return a.exec();
}
