#ifndef _QEXTSINGLETON_H
#define _QEXTSINGLETON_H

#include <qextOnceFlag.h>
#include <qextTypeTrait.h>

#include <QDebug>
#include <QObject>
#include <QScopedPointer>

#define QEXT_DECLARE_SINGLETON(CLASS) \
    void deleteLater() { destroyLater(); }; \
    friend class QExtSingleton<CLASS>; \
    friend struct QExtSingletonScopedPointerDeleter<CLASS>;


template <typename T>
struct QExtSingletonScopedPointerDeleter
{
    static inline void cleanup(T *pointer)
    {
        // Enforce a complete type.
        // If you get a compile error here, read the section on forward declared
        // classes in the QScopedPointer documentation.
        typedef char IsIncompleteType[ sizeof(T) ? 1 : -1 ];
        (void) sizeof(IsIncompleteType);

        delete pointer;
    }
    template <typename U>
    static inline void cleanupLater(U *pointer, QExtTrueType)
    {
        qobject_cast<QObject *>(pointer)->deleteLater();
    }
    template <typename U>
    static inline void cleanupLater(U *pointer, QExtFalseType)
    {
        cleanup(pointer);
    }
};


template <typename T>
class QExtSingleton
{
public:
    typedef QExtSingletonScopedPointerDeleter<T> Deleter;
    typedef void(*InitFunc)(T *);

    static T *instance()
    {
        qextCallOnce(mOnceFlag, initSingleton);
        return mInstance;
    }

    template <InitFunc func = QEXT_NULLPTR>
    static T *instance()
    {
        if (mOnceFlag.enter())
        {
            initSingleton();
            if (func) func(mInstance);
            mOnceFlag.leave();
        }
        return mInstance;
    }

    static void initSingleton()
    {
        mScoped.reset(new T);
        mInstance = mScoped.data();
    }

    void destroyLater()
    {
        this->onAboutToBeDestroyed();
        Deleter::cleanupLater(this->detachScoped(),
                              QExtIsQObjectBase<T>::Type());
    }

    void destroy()
    {
        this->onAboutToBeDestroyed();
        delete this->detachScoped();
    }

protected:
    QExtSingleton() {}
    virtual ~QExtSingleton() {}

    virtual void onAboutToBeDestroyed() {  }
    T *detachScoped() { mScoped.take(); return mInstance; }

private:
    static T *mInstance;
    static QExtOnceFlag mOnceFlag;
    static QScopedPointer<T, Deleter> mScoped;
    QEXT_DISABLE_COPY_MOVE(QExtSingleton)
};

template <typename T> QExtOnceFlag QExtSingleton<T>::mOnceFlag;
template <typename T> T* QExtSingleton<T>::mInstance = QEXT_NULLPTR;
template <typename T> QScopedPointer<T, QExtSingletonScopedPointerDeleter<T> > QExtSingleton<T>::mScoped(QEXT_NULLPTR);

#endif // _QEXTSINGLETON_H
