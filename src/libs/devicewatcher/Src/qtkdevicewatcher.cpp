/******************************************************************************
    QTKDeviceWatcher: Device watcher class
    Copyright (C) 2011-2015 Wang Bin <wbsecg1@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
******************************************************************************/

#include "qtkdevicewatcher.h"
#include "qtkdevicewatcher_p.h"

QTKDeviceWatcher::QTKDeviceWatcher(QObject* parent)
    :QObject(parent),running(false),d_ptr(new QTKDeviceWatcherPrivate)
{
    Q_D(QTKDeviceWatcher);
    d->setWatcher(this);
}

QTKDeviceWatcher::~QTKDeviceWatcher()
{
    if (d_ptr) {
        delete d_ptr;
        d_ptr = NULL;
    }
}

bool QTKDeviceWatcher::start()
{
    Q_D(QTKDeviceWatcher);
    if (!d->start()) {
        stop();
        running = false;
    }
    running = true;
    return running;
}

bool QTKDeviceWatcher::stop()
{
    Q_D(QTKDeviceWatcher);
    running = !d->stop();
    return !running;
}

bool QTKDeviceWatcher::isRunning() const
{
    return running;
}

void QTKDeviceWatcher::appendEventReceiver(QObject *receiver)
{
    Q_D(QTKDeviceWatcher);
    d->event_receivers.append(receiver);
}

void QTKDeviceWatcherPrivate::emitDeviceAdded(const QString &dev)
{
    if (!QMetaObject::invokeMethod(watcher, "deviceAdded", Q_ARG(QString, dev)))
        qWarning("invoke deviceAdded failed");
}

void QTKDeviceWatcherPrivate::emitDeviceChanged(const QString &dev)
{
    if (!QMetaObject::invokeMethod(watcher, "deviceChanged", Q_ARG(QString, dev)))
        qWarning("invoke deviceChanged failed");
}

void QTKDeviceWatcherPrivate::emitDeviceRemoved(const QString &dev)
{
    if (!QMetaObject::invokeMethod(watcher, "deviceRemoved", Q_ARG(QString, dev)))
        qWarning("invoke deviceRemoved failed");
}

void QTKDeviceWatcherPrivate::emitDeviceAction(const QString &dev, const QString &action)
{
    QString a(action.toLower());
    if (a == QLatin1String("add"))
        emitDeviceAdded(dev);
    else if (a == QLatin1String("remove"))
        emitDeviceRemoved(dev);
    else if (a == QLatin1String("change"))
        emitDeviceChanged(dev);
}


//const QEvent::Type  QTKDeviceChangeEvent::EventType = static_cast<QEvent::Type>(QEvent::registerEventType());
QTKDeviceChangeEvent::QTKDeviceChangeEvent(Action action, const QString &device) :
    QEvent(registeredType())
{
    m_action = action;
    m_device = device;
}
