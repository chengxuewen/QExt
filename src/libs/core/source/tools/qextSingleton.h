#ifndef _QEXTSINGLETON_H
#define _QEXTSINGLETON_H

#include <qextOnceFlag.h>

#include <QScopedPointer>

template <typename T>
class QExtSingleton
{
public:
    typedef void(*InitFunc)(T *);

    static T *instance()
    {
        qextCallOnce(mOnceFlag, initSingleton);
        return mInstance.data();
    }

    template <InitFunc func = QEXT_NULLPTR>
    static T *instance()
    {
        if (mOnceFlag.enter())
        {
            initSingleton();
            if (func) func(mInstance.data());
            mOnceFlag.leave();
        }
        return mInstance.data();
    }

    static void initSingleton()
    {
        mInstance.reset(new T);
    }

protected:
    QExtSingleton() : mInstance(QEXT_NULLPTR) {}
    virtual ~QExtSingleton() {}

private:
    static QExtOnceFlag mOnceFlag;
    static QScopedPointer<T> mInstance;
    QEXT_DISABLE_COPY_MOVE(QExtSingleton)
};


template <typename T> QExtOnceFlag QExtSingleton<T>::mOnceFlag;
template <typename T> QScopedPointer<T> QExtSingleton<T>::mInstance(QEXT_NULLPTR);

#endif // _QEXTSINGLETON_H
