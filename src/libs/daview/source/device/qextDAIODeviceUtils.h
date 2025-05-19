#ifndef _QEXTDAIODEVICEUTILS_H
#define _QEXTDAIODEVICEUTILS_H

#include <QSerialPort>
#include <QAbstractSocket>

#include <qextDAViewGlobal.h>

class QEXT_DAVIEW_API QExtDAIODeviceUtils : public QObject
{
    Q_OBJECT
public:
    QExtDAIODeviceUtils();


    static QString socketStateString(QAbstractSocket::SocketState state, bool isEng = false);

    static QString socketErrorString(QAbstractSocket::SocketError error, bool isEng = false);
    static QString serialPortErrorString(QSerialPort::SerialPortError error, bool isEng = false);

};

#endif // _QEXTDAIODEVICEUTILS_H
