#ifndef _QEXTONCEFLAG_H
#define _QEXTONCEFLAG_H

#include <qextGlobal.h>

#include <QAtomicInt>

class QExtOnceFlag
{
public:
    enum
    {
        NeverCalled = 0,
        Inprocess,
        Done
    };

    QExtOnceFlag() : m_state(NeverCalled) {}
    virtual ~QExtOnceFlag() {}

    bool enter()
    {
        if (m_state.testAndSetOrdered(NeverCalled, Inprocess))
        {
            return true;
        }
        while (Done != m_state.fetchAndAddOrdered(0)) {}
        return false;
    }

    void leave()
    {
        m_state.fetchAndStoreOrdered(Done);
    }

private:
    QAtomicInt m_state;
    QEXT_DISABLE_COPY_MOVE(QExtOnceFlag)
};

template<typename Func>
void qextCallOnce(QExtOnceFlag &flag, Func func)
{
    if (flag.enter())
    {
        func();
        flag.leave();
    }
}
static QEXT_FORCE_INLINE void qextCallOnce(QExtOnceFlag &flag, void(*func)())
{
    qextCallOnce<void(*)()>(flag, func);
}
#ifdef QEXT_CXX_STANDARD11
static QEXT_FORCE_INLINE void qextCallOnce(QExtOnceFlag &flag, std::function<void()> func)
{
    qextCallOnce<std::function<void()>>(flag, func);
}
#endif


#endif // _QEXTONCEFLAG_H
