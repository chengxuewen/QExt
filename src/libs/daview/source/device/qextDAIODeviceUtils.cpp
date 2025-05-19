#include <qextDAIODeviceUtils.h>

QExtDAIODeviceUtils::QExtDAIODeviceUtils() {}

QString QExtDAIODeviceUtils::socketStateString(QAbstractSocket::SocketState state, bool isEng)
{
    switch (state)
    {
    case QAbstractSocket::UnconnectedState:
        return isEng ? "Unconnected"
                     : QExtDAIODeviceUtils::tr("Unconnected");
    case QAbstractSocket::HostLookupState:
        return isEng ? "HostLookup"
                     : QExtDAIODeviceUtils::tr("HostLookup");
    case QAbstractSocket::ConnectingState:
        return isEng ? "Connecting"
                     : QExtDAIODeviceUtils::tr("Connecting");
    case QAbstractSocket::ConnectedState:
        return isEng ? "Connected"
                     : QExtDAIODeviceUtils::tr("Connected");
    case QAbstractSocket::BoundState:
        return isEng ? "Bound"
                     : QExtDAIODeviceUtils::tr("Bound");
    case QAbstractSocket::ListeningState:
        return isEng ? "Listening"
                     : QExtDAIODeviceUtils::tr("Listening");
    case QAbstractSocket::ClosingState:
        return isEng ? "Closing"
                     : QExtDAIODeviceUtils::tr("Closing");
    default:
        break;
    }
    return isEng ? "Unknown error" : QExtDAIODeviceUtils::tr("Unknown error");
}

QString QExtDAIODeviceUtils::socketErrorString(QAbstractSocket::SocketError error, bool isEng)
{
    switch (error)
    {
    case QAbstractSocket::ConnectionRefusedError:
        return isEng ? "Connection refused"
                     : QExtDAIODeviceUtils::tr("Connection refused");
    case QAbstractSocket::RemoteHostClosedError:
        return isEng ? "Remote host closed"
                     : QExtDAIODeviceUtils::tr("Remote host closed");
    case QAbstractSocket::HostNotFoundError:
        return isEng ? "Host not found"
                     : QExtDAIODeviceUtils::tr("Host not found");
    case QAbstractSocket::SocketAccessError:
        return isEng ? "Socket access error"
                     : QExtDAIODeviceUtils::tr("Socket access error");
    case QAbstractSocket::SocketResourceError:
        return isEng ? "Socket resource error"
                     : QExtDAIODeviceUtils::tr("Socket resource error");
    case QAbstractSocket::SocketTimeoutError:
        return isEng ? "Socket operation timed out"
                     : QExtDAIODeviceUtils::tr("Socket operation timed out");
    case QAbstractSocket::DatagramTooLargeError:
        return isEng ? "Datagram too large"
                     : QExtDAIODeviceUtils::tr("Datagram too large");
    case QAbstractSocket::NetworkError:
        return isEng ? "Network error"
                     : QExtDAIODeviceUtils::tr("Network error");
    case QAbstractSocket::AddressInUseError:
        return isEng ? "Address in use"
                     : QExtDAIODeviceUtils::tr("Address in use");
    case QAbstractSocket::SocketAddressNotAvailableError:
        return isEng ? "Socket address not available"
                     : QExtDAIODeviceUtils::tr("Socket address not available");
    case QAbstractSocket::UnsupportedSocketOperationError:
        return isEng ? "Unsupported socket operation"
                     : QExtDAIODeviceUtils::tr("Unsupported socket operation");
    case QAbstractSocket::UnfinishedSocketOperationError:
        return isEng ? "Unfinished socket operation"
                     : QExtDAIODeviceUtils::tr("Unfinished socket operation");
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        return isEng ? "Proxy authentication required"
                     : QExtDAIODeviceUtils::tr("Proxy authentication required");
    case QAbstractSocket::SslHandshakeFailedError:
        return isEng ? "Ssl handshake failed"
                     : QExtDAIODeviceUtils::tr("Ssl handshake failed");
    case QAbstractSocket::ProxyConnectionRefusedError:
        return isEng ? "Proxy connection refused"
                     : QExtDAIODeviceUtils::tr("Proxy connection refused");
    case QAbstractSocket::ProxyConnectionClosedError:
        return isEng ? "Proxy connection closed"
                     : QExtDAIODeviceUtils::tr("Proxy connection closed");
    case QAbstractSocket::ProxyConnectionTimeoutError:
        return isEng ? "Proxy connection timeout"
                     : QExtDAIODeviceUtils::tr("Proxy connection timeout");
    case QAbstractSocket::ProxyNotFoundError:
        return isEng ? "Proxy not found"
                     : QExtDAIODeviceUtils::tr("Proxy not found");
    case QAbstractSocket::ProxyProtocolError:
        return isEng ? "Proxy protocol error"
                     : QExtDAIODeviceUtils::tr("Proxy protocol error");
    case QAbstractSocket::OperationError:
        return isEng ? "Operation error"
                     : QExtDAIODeviceUtils::tr("Operation error");
    case QAbstractSocket::SslInternalError:
        return isEng ? "Ssl internal error"
                     : QExtDAIODeviceUtils::tr("Ssl internal error");
    case QAbstractSocket::SslInvalidUserDataError:
        return isEng ? "Ssl invalid user data"
                     : QExtDAIODeviceUtils::tr("Ssl invalid user data");
    case QAbstractSocket::TemporaryError:
        return isEng ? "Temporary error"
                     : QExtDAIODeviceUtils::tr("Temporary error");
    default:
        break;
    }
    return isEng ? "Unknown error" : QExtDAIODeviceUtils::tr("Unknown error");
}

QString QExtDAIODeviceUtils::serialPortErrorString(QSerialPort::SerialPortError error, bool isEng)
{
    switch(error)
    {
    case QSerialPort::NoError:
        return "";
    case QSerialPort::ResourceError:
        return isEng ? "Resource unavaliable"
                     : QExtDAIODeviceUtils::tr("Resource unavaliable");
    case QSerialPort::DeviceNotFoundError:
        return isEng ? "Device doesn't exists"
                     : QExtDAIODeviceUtils::tr("Device doesn't exists");
    case QSerialPort::PermissionError:
        return isEng ? "Permission denied"
                     : QExtDAIODeviceUtils::tr("Permission denied");
    case QSerialPort::OpenError:
        return isEng ? "Device is already opened"
                     : QExtDAIODeviceUtils::tr("Device is already opened");
    case QSerialPort::NotOpenError:
        return isEng ? "Device is not open"
                     : QExtDAIODeviceUtils::tr("Device is not open");
    case QSerialPort::ParityError:
        return isEng ? "Parity error detected"
                     : QExtDAIODeviceUtils::tr("Parity error detected");
    case QSerialPort::FramingError:
        return isEng ? "Framing error detected"
                     : QExtDAIODeviceUtils::tr("Framing error detected");
    case QSerialPort::BreakConditionError:
        return isEng ? "Break condition is detected"
                     : QExtDAIODeviceUtils::tr("Break condition is detected");
    case QSerialPort::WriteError:
        return isEng ? "An error occurred while writing data"
                     : QExtDAIODeviceUtils::tr("An error occurred while writing data");
    case QSerialPort::ReadError:
        return isEng ? "An error occurred while reading data"
                     : QExtDAIODeviceUtils::tr("An error occurred while reading data");
    case QSerialPort::UnsupportedOperationError:
        return isEng ? "Operation is not supported"
                     : QExtDAIODeviceUtils::tr("Operation is not supported");
    case QSerialPort::TimeoutError:
        return isEng ? "A timeout error occurred"
                     : QExtDAIODeviceUtils::tr("A timeout error occurred");
    default:
        break;
    }
    return isEng ? "Unknown error" : QExtDAIODeviceUtils::tr("Unknown error");
}
