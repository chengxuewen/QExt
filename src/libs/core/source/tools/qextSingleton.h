#ifndef _QEXTSINGLETON_H
#define _QEXTSINGLETON_H

#include <qextOnceFlag.h>
#include <qextTypeTrait.h>

#include <QDebug>
#include <QObject>
#include <QScopedPointer>
#include <QCoreApplication>

#define QEXT_DECLARE_SINGLETON(CLASS) \
    private: \
        void deleteLater() { destroyLater(); }; \
        friend class QExtSingleton<CLASS>; \
        friend struct QExtSingletonScopedPointerDeleter<CLASS>;

QEXT_WARNING_PUSH
    QEXT_WARNING_DISABLE_GCC("-Wdeprecated-declarations")

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

    static inline void cleanupLater(T *pointer)
    {
        QObject *object = dynamic_cast<QObject *>(pointer);
        if (object)
        {
            object->deleteLater();
        }
        else
        {
            cleanup(pointer);
        }
    }
};


template <typename T>
class QExtSingleton
{
    typedef QExtSingletonScopedPointerDeleter<T> Deleter;
public:
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

public Q_SLOTS:
    void destroyLater()
    {
        this->onAboutToBeDestroyed();
        Deleter::cleanupLater(this->detachScoped());
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
    static void initSingleton()
    {
        mInstance = new T;
        QObject *object = dynamic_cast<QObject *>(mInstance);
        if (object)
        {
            if (qApp)
            {
                object->moveToThread(qApp->thread());
                object->setParent(qApp);
            }
            else
            {
                qWarning() << "WARN:init object singleton before qApp construct!";
            }
        }
        else
        {
            mScoped.reset(mInstance);
        }
    }

private:
    static T *mInstance;
    static QExtOnceFlag mOnceFlag;
    static QScopedPointer<T, Deleter> mScoped;
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtSingleton)
};

template <typename T> QExtOnceFlag QExtSingleton<T>::mOnceFlag;
template <typename T> T* QExtSingleton<T>::mInstance = QEXT_NULLPTR;
template <typename T> QScopedPointer<T, QExtSingletonScopedPointerDeleter<T> > QExtSingleton<T>::mScoped(QEXT_NULLPTR);

#define QEXT_DECLARE_OBJECT_SINGLETON() \
    private: \
        void setParent(QObject *parent) { QObject::setParent(parent); }

template <typename T>
class QExtObjectSingleton : public QObject, public QExtSingleton<T>
{
    QEXT_DECLARE_OBJECT_SINGLETON()
};

QEXT_WARNING_POP

#endif // _QEXTSINGLETON_H
