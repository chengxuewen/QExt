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

#ifndef _QEXTLOGTELNETAPPENDER_H
#define _QEXTLOGTELNETAPPENDER_H

#include <qextLogAppenderSkeleton.h>

#include <QString>
#include <QHostAddress>

class QTcpServer;
class QTcpSocket;

/*!
 * \brief The class QExtLogTelnetAppender appends log events to a read-only socket (telnet)
 *T
 * \note All the functions declared in this class are thread-safe.
 * &nbsp;
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogTelnetAppender : public QExtLogAppenderSkeleton
{
    Q_OBJECT

    /*!
     * The property holds the port used by the telenet appender.
     *
     * The default is 23 for the port.
     *
     * \sa port, port(), setPort()
     */
    Q_PROPERTY(int port READ port WRITE setPort)

    /*!
     * The property holds, if the writer flushes after all write operations.
     *
     * The default is false for flushing.
     *
     * \sa immediateFlush(), setImmediateFlush()
     */
    Q_PROPERTY(bool immediateFlush READ immediateFlush WRITE setImmediateFlush)

    Q_PROPERTY(QHostAddress address READ address WRITE setAddress)

public:
    QExtLogTelnetAppender(QObject *parent = QEXT_NULLPTR);
    QExtLogTelnetAppender(const QExtLogLayoutSharedPtr &layout,
                   QObject *parent = QEXT_NULLPTR);
    QExtLogTelnetAppender(const QExtLogLayoutSharedPtr &layout,
                   const QHostAddress &address,
                   int port,
                   QObject *parent = QEXT_NULLPTR);
    QExtLogTelnetAppender(const QExtLogLayoutSharedPtr &layout,
                   int port,
                   QObject *parent = QEXT_NULLPTR);
    ~QExtLogTelnetAppender() QEXT_OVERRIDE;

private:
    Q_DISABLE_COPY(QExtLogTelnetAppender)

public:
    bool requiresLayout() const QEXT_OVERRIDE;
    void activateOptions() QEXT_OVERRIDE;
    void close() QEXT_OVERRIDE;

    /*!
     * Sets the listening port of the telnet server (default = 23)
     */
    void setPort(int port);
    /*!
     * Returns the listening port of the telnet server
     */
    int  port() const;
    /*!
     * Set the property immediate flush (default: false)
     */
    void setImmediateFlush(bool immediateFlush);
    /*!
     *  Returns <true> immediate flush is enabled
     */
    bool immediateFlush() const;

    /*!
     * Sets the listenning address of the telnet server (default QHostAddress::Any)
     */
    void setAddress(const QHostAddress &address);
    /*!
     * Returns the listenning address of the telnet server
     */
    QHostAddress address() const;
    /*!
     *  Set the welcome message which is send on
     */
    void setWelcomeMessage(const QString &welcomeMessage);

protected:
    void append(const QExtLoggingEvent &event) QEXT_OVERRIDE;

    /*!
     * Tests if all entry conditions for using append() in this class are
     * met.
     *
     * If a conditions is not met, an error is logged and the function
     * returns false. Otherwise the result of
     * QExtLogAppenderSkeleton::checkEntryConditions() is returned.
     *
     * The checked conditions are:
     * - A writer has been set (QExtLogError::Error_AppenderUseMissingWriter)
     *
     * The function is called as part of the checkEntryConditions() chain
     * started by QExtLogAppenderSkeleton::doAppend().
     *
     * \sa QExtLogAppenderSkeleton::doAppend(),
     *     QExtLogAppenderSkeleton::checkEntryConditions()
     */
    bool checkEntryConditions() const QEXT_OVERRIDE;

    /*!
     *  Creates and starts (listening) the TCP server
     */
    void openServer();
    /*!
     *  Stops and destroys the TCP server
     */
    void closeServer();

    QList<QTcpSocket *> clients() const;

private Q_SLOTS:
    /*!
     *  Handles a new incomming connection
     */
    void onNewConnection();
    /*!
     *  Handles a client disconnect
     */
    void onClientDisconnected();

private:
    QHostAddress mAddress;
    int             mPort;
    QTcpServer     *mTcpServer;
    QList<QTcpSocket *> mTcpSockets;
    QString         mWelcomeMessage;
    volatile bool   mImmediateFlush;

    void sendWelcomeMessage(QTcpSocket *clientConnection);
};

inline bool QExtLogTelnetAppender::immediateFlush() const
{
    return mImmediateFlush;
}

inline void QExtLogTelnetAppender::setImmediateFlush(bool immediateFlush)
{
    mImmediateFlush = immediateFlush;
}

#endif // _QEXTLOGTELNETAPPENDER_H
