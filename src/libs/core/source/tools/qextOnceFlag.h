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


#endif // _QEXTONCEFLAG_H
