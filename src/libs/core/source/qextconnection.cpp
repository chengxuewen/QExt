#include "qextconnection.h"

QEXTConnection::QEXTConnection()
    : m_slot(QEXT_NULLPTR)
{

}

QEXTConnection::QEXTConnection(const QEXTConnection &src)
    : m_slot(src.m_slot)
{
    //Let the connection forget about the signal handler when the handler object dies:
    if (m_slot) {
        m_slot->addDestroyNotifyCallback(this, &notify);
    }
}

QEXTConnection::QEXTConnection(QEXTSlotBase &slot)
    : m_slot(&slot)
{
    m_slot->addDestroyNotifyCallback(this, &notify);
}

QEXTConnection::~QEXTConnection()
{
    if (m_slot) {
        m_slot->removeDestroyNotifyCallback(this);
    }
}

QEXTConnection& QEXTConnection::operator=(const QEXTConnection &other)
{
    this->setSlot(other.m_slot);
    return *this;
}

bool QEXTConnection::isEmpty() const
{
    return (!m_slot || m_slot->isEmpty());
}

bool QEXTConnection::isBlocked() const
{
    return (m_slot ? m_slot->isBlocked() : false);
}

bool QEXTConnection::block(bool block)
{
    return (m_slot ? m_slot->setBlock(block) : false);
}

bool QEXTConnection::unblock()
{
    return (m_slot ? m_slot->unblock() : false);
}

bool QEXTConnection::connected() const
{
    return !this->isEmpty();
}

void QEXTConnection::disconnect()
{
    if (m_slot) {
        m_slot->disconnect(); // This notifies slot_'s parent.
    }
}

void *QEXTConnection::notify(void *data)
{
    QEXTConnection *self = reinterpret_cast<QEXTConnection*>(data);
    self->m_slot = QEXT_NULLPTR;
    return QEXT_NULLPTR;
}

void QEXTConnection::setSlot(QEXTSlotBase *slot)
{
    if (m_slot) {
        m_slot->removeDestroyNotifyCallback(this);
    }

    m_slot = slot;

    if (m_slot) {
        m_slot->addDestroyNotifyCallback(this, &notify);
    }
}

QEXTConnection::operator bool()
{
    return !this->isEmpty();
}
