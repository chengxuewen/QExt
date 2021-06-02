#ifndef QEXTCONNECTION_H
#define QEXTCONNECTION_H

#include <qextglobal.h>
#include <qextconnection.h>
#include <qextsignal.h>

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
 * @ingroup signal
 */
class QEXT_CORE_API QEXTConnection
{
public:
    /** Constructs an empty connection object. */
    QEXTConnection();
    /** Constructs a connection object copying an existing one.
     * @param src The connection object to make a copy from.
     */
    QEXTConnection(const QEXTConnection &src);
    /** Constructs a connection object from a slot list iterator.
     * @param iter The slot list iterator to take the slot from.
     */
    template <typename T_slot>
    QEXTConnection(const QEXTSlotIterator<T_slot> &iter) : m_slot(&(*iter)) {
        if (m_slot) {
            m_slot->addDestroyNotifyCallback(this, &notify);
        }
    }
    /** Constructs a connection object from a slot object.
     * This is only useful if you create your own slot list.
     * @param sl The slot to operate on.
     */
    explicit QEXTConnection(QEXTSlotBase &slot);
    virtual ~QEXTConnection();

    /** Overrides this connection object copying another one.
     * @param other The connection object to make a copy from.
     */
    QEXTConnection& operator=(const QEXTConnection &other);

    /** Overrides this connection object with another slot list iterator.
     * @param iter The new slot list iterator to take the slot from.
     */
    template <typename T_slot>
    QEXTConnection& operator=(const QEXTSlotIterator<T_slot> &iter) {
        this->setSlot(&(*iter));
        return *this;
    }

    /** Returns whether the connection is still active.
     * @return @p false if the connection is still active.
     */
    bool isEmpty() const;
    /** Returns whether the connection is blocked.
     * @return @p true if the connection is blocked.
     */
    bool isBlocked() const;
    /** Sets or unsets the blocking state of this connection.
     * See QEXTSlotBase::block() for details.
     * @param should_block Indicates whether the blocking state should be set or unset.
     * @return @p true if the connection has been in blocking state before.
     */
    bool block(bool block = true);
    /** Unsets the blocking state of this connection.
     * @return @p true if the connection has been in blocking state before.
     */
    bool unblock();
    /** Returns whether the connection is still active.
     * @return @p true if the connection is still active.
     */
    bool isConnected() const;
    /** Disconnects the referred slot.
     */
    void disconnect();

    /** Returns whether the connection is still active.
     * @return @p true if the connection is still active.
     */
    operator bool();

    /** Callback that is executed when the referred slot is destroyed.
     * @param data The connection object notified (@p this).
     */
    static void* notify(void *data);

private:
    void setSlot(QEXTSlotBase *slot);

    /* Referred slot. Set to zero from notify().
     * A value of zero indicates an "empty" connection.
     */
    QEXTSlotBase *m_slot;
};

#endif // QEXTCONNECTION_H
