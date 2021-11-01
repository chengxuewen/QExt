#include "qtksubscribereventhandler.h"

#include <QTKPluginFramework/QTKPluginContext>

#include <QDebug>
#include <QDateTime>
#include <QWidget>

void QTKSubscriberEventHandler::handleEvent(const QTKEvent &event)
{
    qDebug() << "QTKSubscriberEventHandler::handleEvent()----------------------------";
    qDebug() << "receive datetime=" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    qDebug() << "info thread:" << this->thread();

    QStringList listPropertyNames = event.getPropertyNames();
    foreach (QString strName, listPropertyNames) {
        qDebug() << strName << ": " << event.getProperty(strName);
    }

}
