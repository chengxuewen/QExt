/*************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
** Copyright 2002, The libsigc++ Development Team
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
*************************************************************************************/

#ifndef _QEXTCONNECTION_H
#define _QEXTCONNECTION_H

#include <qextGlobal.h>
#include <qextSignal.h>
#include <qextFunction.h>



/** Convinience class for safe disconnection.
 * Iterators must not be used beyond the lifetime of the list
 * they work on. A connection object can be created from a
 * slot list iterator and may safely be used to disconnect
 * the referred slot at any time (disconnect()). If the slot
 * has already been destroyed, disconnect() does nothing. isEmpty() or
 * operator bool() can be used to test whether the connection is
 * still active. The connection can be blocked (block(), unblock()).
 *
 * This is possible because the connection object gets notified
 * when the referred slot dies (notify()).
 *
 * \ingroup signal
 */
class QEXT_CORE_API QExtConnection
{
public:
    typedef QExtPrivate::QExtFunctionBase SlotFunctionBase;

    /** Constructs an empty connection object. */
    QExtConnection();
    /** Constructs a connection object copying an existing one.
     * \param src The connection object to make a copy from.
     */
    QExtConnection(const QExtConnection &other);
    /** Constructs a connection object from a slot list iterator.
     * \param iter The slot list iterator to take the slot from.
     */
    template <typename T_slot>
    QExtConnection(const QExtPrivate::QExtFunctionIterator<T_slot> &iter) : m_slot(&(*iter))
    {
    }
    /** Constructs a connection object from a slot object.
     * This is only useful if you create your own slot list.
     * \param sl The slot to operate on.
     */
    explicit QExtConnection(SlotFunctionBase &slot);
    virtual ~QExtConnection();

    /** Overrides this connection object copying another one.
     * \param other The connection object to make a copy from.
     */
    QExtConnection &operator=(const QExtConnection &other);

    /** Overrides this connection object with another slot list iterator.
     * \param iter The new slot list iterator to take the slot from.
     */
    template <typename T_slot>
    QExtConnection &operator=(const QExtPrivate::QExtFunctionIterator<T_slot> &iter)
    {
        this->setSlot(&(*iter));
        return *this;
    }

    /** Returns whether the connection is still active.
     * \return @p false if the connection is still active.
     */
    bool isEmpty() const;
    /** Returns whether the connection is blocked.
     * \return @p true if the connection is blocked.
     */
    bool isBlocked() const;
    /** Sets or unsets the blocking state of this connection.
     * See QExtFunctionBase::setBlock() for details.
     * \param should_block Indicates whether the blocking state should be set or unset.
     * \return @p true if the connection has been in blocking state before.
     */
    bool setBlock(bool block = true);
    /** Unsets the blocking state of this connection.
     * \return @p true if the connection has been in blocking state before.
     */
    bool unblock();
    /** Returns whether the connection is still active.
     * \return @p true if the connection is still active.
     */
    bool isConnected() const;
    /** Disconnects the referred slot.
     */
    void disconnect();

    /** Returns whether the connection is still active.
     * \return @p true if the connection is still active.
     */
    operator bool();

    /** Callback that is executed when the referred slot is destroyed.
     * \param data The connection object notified (@p this).
     */
    static void *notify(void *data);

private:
    void setSlot(SlotFunctionBase *slot);

    /* Referred slot. Set to zero from notify().
     * A value of zero indicates an "empty" connection.
     */
    SlotFunctionBase *m_slot;
};



#endif // _QEXTCONNECTION_H
