#ifndef _QEXTONCEFLAG_H
#define _QEXTONCEFLAG_H

#include <qextGlobal.h>

#include <QAtomicInt>

class QEXT_CORE_API QExtOnceFlag
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

    static QExtOnceFlag *localOnceFlag();

private:
    QAtomicInt m_state;
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtOnceFlag)
};

template <typename Func>
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
#ifdef QEXT_CC_CPP11_OR_GREATER
static QEXT_FORCE_INLINE void qextCallOnce(QExtOnceFlag &flag, std::function<void()> func)
{
    qextCallOnce<std::function<void()>>(flag, func);
}
#endif

template <typename Func>
void qextCallOncePerThread(Func func)
{
    qextCallOnce(*QExtOnceFlag::localOnceFlag(), func);
}

#endif // _QEXTONCEFLAG_H
