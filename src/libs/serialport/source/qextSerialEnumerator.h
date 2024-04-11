/****************************************************************************
** Copyright (c) 2000-2003 Wayne Roth
** Copyright (c) 2004-2007 Stefan Sander
** Copyright (c) 2007 Michal Policht
** Copyright (c) 2008 Brandon Fosdick
** Copyright (c) 2009-2010 Liam Staskawicz
** Copyright (c) 2011 Debao Zhang
** All right reserved.
** Web: http://code.google.com/p/qextserialport/
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#ifndef _QEXTSERIALENUMERATOR_H
#define _QEXTSERIALENUMERATOR_H

#include <qextSerialPortGlobal.h>
#include <qextSerialPortConfig.h>

#include <QtCore/QList>
#include <QtCore/QObject>


struct QEXTPortInfo
{
    QString portName;   ///< Port name.
    QString physName;   ///< Physical name.
    QString friendName; ///< Friendly name.
    QString enumName;   ///< Enumerator name.
    int vendorID;       ///< Vendor ID.
    int productID;      ///< Product ID
};

class QExtSerialEnumeratorPrivate;
class QEXT_SERIALPORT_API QExtSerialEnumerator : public QObject
{
Q_OBJECT

public:
    QExtSerialEnumerator(QObject *parent = 0);
    ~QExtSerialEnumerator();

    static QList<QEXTPortInfo> portInfoList();
    void setUpNotifications();

Q_SIGNALS:
    void deviceDiscovered(const QEXTPortInfo &info);
    void deviceRemoved(const QEXTPortInfo &info);

private:
    Q_DISABLE_COPY(QExtSerialEnumerator)
#if defined(Q_OS_LINUX) && !QEXT_FEATURE_SERIALPORT_LINUX_NO_UDEV
    Q_PRIVATE_SLOT(d_func(), void _q_deviceEvent())
#endif
    QExtSerialEnumeratorPrivate *dd_ptr;

    QEXT_DECL_PRIVATE_D(dd_ptr, QExtSerialEnumerator)
};


#endif /*_QEXTSERIALENUMERATOR_H*/
