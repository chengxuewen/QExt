
/******************************************************************************
  QTKDeviceWatcherPrivate: watching depends on platform
  Copyright (C) 2014-2015 Wang Bin <wbsecg1@gmail.com>

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

#include "qtkdevicewatcher_p.h"
#include <QtCore/QStringList>

#include <CoreServices/CoreServices.h>
#include <IOKit/storage/IOCDMedia.h>
#include <IOKit/storage/IODVDMedia.h>

static QStringList sDevices; //disk list, or mount point list?

static void onDiskAppear(DADiskRef disk, void *context)
{
    QString disk_name = DADiskGetBSDName(disk);
    if (sDevices.contains(disk_name))
        return;
    sDevices.append(disk_name);
    QTKDeviceWatcherPrivate *p = static_cast<QTKDeviceWatcherPrivate*>(context);
    p->emitDeviceAdded(disk_name);
}

static void onDiskDisappear(DADiskRef disk, void *context)
{
    QString disk_name = DADiskGetBSDName(disk);
    sDevices.removeAll(disk_name); //erase?
    QTKDeviceWatcherPrivate *p = static_cast<QTKDeviceWatcherPrivate*>(context);
    p->emitDeviceRemoved(disk_name);
}

QTKDeviceWatcherPrivate::~QTKDeviceWatcherPrivate()
{
    stop();
}

bool QTKDeviceWatcherPrivate::start()
{
    init();
    QThread::start();
}

bool QTKDeviceWatcherPrivate::stop()
{
    mStop = true;
    wait();
    //DAUnregisterApprovalCallback
    DAUnregisterCallback(mSession, (void*)onDiskAppear, this);
    DAUnregisterCallback(mSession, (void*)onDiskDisappear, this);
}


void QTKDeviceWatcherPrivate::parseDeviceInfo()
{
}


bool QTKDeviceWatcherPrivate::init()
{
    //get sDevices
    //FSGetVolumeInfo()
    mSession = DASessionCreate(kCFAllocatorDefault);

    DARegisterDiskAppearedCallback(mSession, NULL, onDiskAppear, this);
    DARegisterDiskDisappearedCallback(mSession, NULL, onDiskDisappear, this);

}

void QTKDeviceWatcherPrivate::run()
{
    mStop = false;

    DASessionScheduleWithRunLoop(mSession, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
    SInt32 result;
    do {
        result = CFRunLoopRunInMode(kCFRunLoopDefaultMode, 1, true);
    } while (!mStop && result);

    DASessionUnscheduleFromRunLoop(mSession, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
}
