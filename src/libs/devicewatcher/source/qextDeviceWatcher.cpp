/******************************************************************************
    QExtDeviceWatcher: Device watcher class
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

#include "qextDeviceWatcher.h"
#include "qextDeviceWatcher_p.h"

QExtDeviceWatcher::QExtDeviceWatcher(QObject *parent)
    : QObject(parent),running(false),dd_ptr(new QExtDeviceWatcherPrivate)
{
    Q_D(QExtDeviceWatcher);
    d->setWatcher(this);
}

QExtDeviceWatcher::~QExtDeviceWatcher()
{
    if (dd_ptr) {
        delete dd_ptr;
        dd_ptr = NULL;
    }
}

bool QExtDeviceWatcher::start()
{
    Q_D(QExtDeviceWatcher);
    if (!d->start()) {
        stop();
        running = false;
    }
    running = true;
    return running;
}

bool QExtDeviceWatcher::stop()
{
    Q_D(QExtDeviceWatcher);
    running = !d->stop();
    return !running;
}

bool QExtDeviceWatcher::isRunning() const
{
    return running;
}

void QExtDeviceWatcher::appendEventReceiver(QObject *receiver)
{
    Q_D(QExtDeviceWatcher);
    d->event_receivers.append(receiver);
}

void QExtDeviceWatcherPrivate::emitDeviceAdded(const QString &dev)
{
    if (!QMetaObject::invokeMethod(watcher, "deviceAdded", Q_ARG(QString, dev)))
        qWarning("invoke deviceAdded failed");
}

void QExtDeviceWatcherPrivate::emitDeviceChanged(const QString &dev)
{
    if (!QMetaObject::invokeMethod(watcher, "deviceChanged", Q_ARG(QString, dev)))
        qWarning("invoke deviceChanged failed");
}

void QExtDeviceWatcherPrivate::emitDeviceRemoved(const QString &dev)
{
    if (!QMetaObject::invokeMethod(watcher, "deviceRemoved", Q_ARG(QString, dev)))
        qWarning("invoke deviceRemoved failed");
}

void QExtDeviceWatcherPrivate::emitDeviceAction(const QString &dev, const QString &action)
{
    QString a(action.toLower());
    if (a == QLatin1String("add"))
        emitDeviceAdded(dev);
    else if (a == QLatin1String("remove"))
        emitDeviceRemoved(dev);
    else if (a == QLatin1String("change"))
        emitDeviceChanged(dev);
}


//const QEvent::Type  QExtDeviceChangeEvent::EventType = static_cast<QEvent::Type>(QEvent::registerEventType());
QExtDeviceChangeEvent::QExtDeviceChangeEvent(Action action, const QString &device) :
    QEvent(registeredType())
{
    m_action = action;
    m_device = device;
}
