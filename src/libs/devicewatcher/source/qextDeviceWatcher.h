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

#ifndef _QEXTDEVICEWATCHER_H
#define _QEXTDEVICEWATCHER_H

#include <qextDeviceWatcherGlobal.h>

#include <QtCore/QObject>
#include <QtCore/QEvent>

class QExtDeviceWatcherPrivate;
class QEXT_DEVICEWATCHER_API QExtDeviceWatcher : public QObject
{
    Q_OBJECT
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtDeviceWatcher)

public:
    explicit QExtDeviceWatcher(QObject *parent = 0);
    ~QExtDeviceWatcher();

    bool start();
    bool stop();
    bool isRunning() const;

    void appendEventReceiver(QObject* receiver);

signals:
    void deviceAdded(const QString& dev);
    void deviceChanged(const QString& dev); //when umounting the device
    void deviceRemoved(const QString& dev);

protected:
    bool running;
    QExtDeviceWatcherPrivate *dd_ptr;
};


class QEXT_DEVICEWATCHER_API QExtDeviceChangeEvent : public QEvent
{
public:
    enum Action { Add, Remove, Change};
    //static const Type EventType; //VC link error

    explicit QExtDeviceChangeEvent(Action action, const QString& device);

    Action action() const {return m_action;}
    QString device() const {return m_device;}
    static Type registeredType()
    {
        static Type EventType = static_cast<Type>(registerEventType());
        return EventType;
    }

private:
    Action m_action;
    QString m_device;
};

#endif // _QEXTDEVICEWATCHER_H
