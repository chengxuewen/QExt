/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
** Copyright 2010 Andreas Bacher
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#include <qextLogTelnetAppender.h>
#include <qextLoggingEvent.h>
#include <qextLogLayout.h>

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

#if (__cplusplus >= 201703L) // C++17 or later
#include <utility>
#endif

QExtLogTelnetAppender::QExtLogTelnetAppender(QObject *parent)
    : QExtLogAppenderSkeleton(false, parent)
    , mAddress(QHostAddress::Any)
    , mPort(23)
    , mTcpServer(nullptr)
    , mImmediateFlush(false)
{
}

QExtLogTelnetAppender::QExtLogTelnetAppender(const QExtLogLayoutSharedPtr &layout, QObject *parent)
    : QExtLogAppenderSkeleton(false, layout, parent)
    , mAddress(QHostAddress::Any)
    , mPort(23)
    , mTcpServer(nullptr)
    , mImmediateFlush(false)
{
}

QExtLogTelnetAppender::QExtLogTelnetAppender(const QExtLogLayoutSharedPtr &layout, int port, QObject *parent)
    : QExtLogAppenderSkeleton(false, layout, parent)
    , mAddress(QHostAddress::Any)
    , mPort(port)
    , mTcpServer(nullptr)
    , mImmediateFlush(false)
{
}

QExtLogTelnetAppender::QExtLogTelnetAppender(const QExtLogLayoutSharedPtr &layout, const QHostAddress &address,
                               int port, QObject *parent)
    : QExtLogAppenderSkeleton(false, layout, parent)
    , mAddress(address)
    , mPort(port)
    , mTcpServer(nullptr)
    , mImmediateFlush(false)
{
}

QExtLogTelnetAppender::~QExtLogTelnetAppender()
{
    close();
}

void QExtLogTelnetAppender::activateOptions()
{
    QMutexLocker locker(&mObjectGuard);

    closeServer();
    openServer();

    QExtLogAppenderSkeleton::activateOptions();
}

void QExtLogTelnetAppender::close()
{
    QMutexLocker locker(&mObjectGuard);

    if (isClosed())
        return;

    QExtLogAppenderSkeleton::close();
    closeServer();
}

void QExtLogTelnetAppender::setAddress(const QHostAddress &address)
{
    mAddress = address;
}

QHostAddress QExtLogTelnetAppender::address() const
{
    return mAddress;
}

void QExtLogTelnetAppender::setPort(int port)
{
    mPort = port;
}

int QExtLogTelnetAppender::port() const
{
    return mPort;
}

void QExtLogTelnetAppender::setWelcomeMessage(const QString &welcomeMessage)
{
    mWelcomeMessage = welcomeMessage;
}

bool QExtLogTelnetAppender::requiresLayout() const
{
    return true;
}

void QExtLogTelnetAppender::append(const QExtLoggingEvent &event)
{
    Q_ASSERT_X(layout(), "QExtLogTelnetAppender::append()", "QExtLogLayout must not be null");

    QString message(layout()->format(event));

#if (__cplusplus >= 201703L)
    for (auto &&clientConnection : std::as_const(mTcpSockets))
#else
    for (auto &&clientConnection : qAsConst(mTcpSockets))
#endif
    {
        clientConnection->write(message.toLocal8Bit().constData());
        if (immediateFlush())
            clientConnection->flush();
    }
}

bool QExtLogTelnetAppender::checkEntryConditions() const
{
    if ((mTcpServer == nullptr) || !mTcpServer->isListening())
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Use of appender '%1' without a listing telnet server"),
                                QExtLogError::Error_AppenderTelnetServerNotRunning);
        e << name();
        logger()->error(e);
        return false;
    }

    return QExtLogAppenderSkeleton::checkEntryConditions();
}

void QExtLogTelnetAppender::openServer()
{
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection, this, &QExtLogTelnetAppender::onNewConnection);
    mTcpServer->listen(mAddress, mPort);
}

void QExtLogTelnetAppender::closeServer()
{
    if (mTcpServer != nullptr)
        mTcpServer->close();

#if (__cplusplus >= 201703L)
    for (auto &&clientConnection : std::as_const(mTcpSockets))
#else
    for (auto &&clientConnection : qAsConst(mTcpSockets))
#endif
        delete clientConnection;

    mTcpSockets.clear();

    delete mTcpServer;
    mTcpServer = nullptr;
}

QList<QTcpSocket *> QExtLogTelnetAppender::clients() const
{
    return mTcpSockets;
}

void QExtLogTelnetAppender::onNewConnection()
{
    QMutexLocker locker(&mObjectGuard);

    if ((mTcpServer != nullptr) && mTcpServer->hasPendingConnections())
    {
        QTcpSocket *clientConnection = mTcpServer->nextPendingConnection();
        if (clientConnection != nullptr)
        {
            mTcpSockets.append(clientConnection);
            connect(clientConnection, &QTcpSocket::disconnected,
                    this, &QExtLogTelnetAppender::onClientDisconnected);
            sendWelcomeMessage(clientConnection);
        }
    }
}

void QExtLogTelnetAppender::sendWelcomeMessage(QTcpSocket *clientConnection)
{
    if (mWelcomeMessage.isEmpty())
        return;

    clientConnection->write(mWelcomeMessage.toLocal8Bit().constData());
}

void QExtLogTelnetAppender::onClientDisconnected()
{
    QMutexLocker locker(&mObjectGuard);

    QTcpSocket *clientConnection = qobject_cast<QTcpSocket *> (sender());
    if (clientConnection != nullptr)
    {
        mTcpSockets.removeOne(clientConnection);
        clientConnection->deleteLater();
    }
}

// #include "moc_telnetappender.cpp"
