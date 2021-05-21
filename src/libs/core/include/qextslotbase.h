#ifndef QEXTSLOTBASE_H
#define QEXTSLOTBASE_H

#include <qextglobal.h>
#include <qextfunctortrait.h>
#include <qexttrackable.h>

namespace qextinternal {

typedef void* (*HookFunctionType)(void*);

struct QEXT_CORE_API QEXTSlotRepresentation : public QEXTTrackable
{
    QEXTSlotRepresentation(HookFunctionType call, HookFunctionType destroy, HookFunctionType deepCopy);
    ~QEXTSlotRepresentation();

    // only MSVC needs this to guarantee that all new/delete are executed from the DLL module
#ifdef Q_CC_MSVC
    void *operator new(size_t size);
    void operator delete(void *p);
#endif

    void destroy();
    QEXTSlotRepresentation *deepCopy() const;
    void setParent(void *parent, HookFunctionType cleanup);
    void disconnect();
    static void *notify(void *data);

    HookFunctionType m_call;
    HookFunctionType m_destroy;
    HookFunctionType m_deepCopy;
    HookFunctionType m_cleanup;
    void *m_parent;
};

struct QEXT_CORE_API QEXTSlotDoBind
{
    QEXTSlotDoBind(QEXTSlotRepresentation *rep) : m_slotRep(rep) {}

    void operator()(const QEXTTrackable *trackable) const {
        trackable->addDestroyNotifyCallback(m_slotRep, &QEXTSlotRepresentation::notify);
    }

    QEXTSlotRepresentation *m_slotRep;
};

struct QEXT_CORE_API QEXTSlotDoUnbind
{
    QEXTSlotDoUnbind(QEXTSlotRepresentation *rep) : m_slotRep(rep) {}

    void operator()(const QEXTTrackable *trackable) const {
        trackable->removeDestroyNotifyCallback(m_slotRep);
    }

    QEXTSlotRepresentation *m_slotRep;
};

} //namespace qextinternal



class QEXT_CORE_API QEXTSlotBase : public QEXTFunctorBase
{
    typedef qextinternal::QEXTSlotRepresentation SlotRepType;
public:
    typedef QEXTTrackable::DestroyNotifyFunc DestroyNotifyFunc;

    QEXTSlotBase();
    explicit QEXTSlotBase(SlotRepType *rep);
    QEXTSlotBase(const QEXTSlotBase &src);
    ~QEXTSlotBase();

    operator bool() const;
    QEXTSlotBase& operator=(const QEXTSlotBase &src);

    void setParent(void *parent, void*(*cleanup)(void*)) const;
    void addDestroyNotifyCallback(void *data, DestroyNotifyFunc func) const;
    void removeDestroyNotifyCallback(void *data) const;

    bool isEmpty() const;
    bool blocked() const;
    bool block(bool shouldBlock = true);
    bool unblock();
    void disconnect();

public:
    mutable SlotRepType *m_slotRep;
    bool m_blocked;
};


#endif // QEXTSLOTBASE_H
