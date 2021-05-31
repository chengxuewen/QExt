#ifndef QEXTCONNECTION_H
#define QEXTCONNECTION_H

#include <qextglobal.h>
#include <qextconnection.h>
#include <qextsignal.h>

class QEXT_CORE_API QEXTConnection
{
public:
    QEXTConnection();
    QEXTConnection(const QEXTConnection &src);
    template <typename T_slot>
    QEXTConnection(const QEXTSlotIterator<T_slot> &iter) : m_slot(&(*iter)) {
        if (m_slot) {
            m_slot->addDestroyNotifyCallback(this, &notify);
        }
    }
    explicit QEXTConnection(QEXTSlotBase &slot);
    virtual ~QEXTConnection();

    QEXTConnection& operator=(const QEXTConnection &other);

    template <typename T_slot>
    QEXTConnection& operator=(const QEXTSlotIterator<T_slot> &iter) {
        this->setSlot(&(*iter));
        return *this;
    }

    bool isEmpty() const;
    bool isBlocked() const;
    bool block(bool block = true);
    bool unblock();

    bool connected() const;
    void disconnect();

    operator bool();

    static void* notify(void *data);

private:
    void setSlot(QEXTSlotBase *slot);

    QEXTSlotBase *m_slot;
};

#endif // QEXTCONNECTION_H
