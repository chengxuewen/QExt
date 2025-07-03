#ifndef _QEXTMODIFIEDFLAG_H
#define _QEXTMODIFIEDFLAG_H

#include <QReadWriteLock>

class QExtModifiedFlag
{
public:
    typedef void(*Callback)(bool modified);

    QExtModifiedFlag(bool modified = false) : mModified(modified) {}
    virtual ~QExtModifiedFlag() {}

    void setModified(bool modified)
    {
        if (mModified.fetchAndStoreOrdered(modified) != modified)
        {
            this->onChanged(modified);
            QReadLocker locker(&mRWLock);
            foreach(const &callback, mCallbacks)
            {
                if (callback)
                {
                    callback(modified);
                }
            }
        }
    }
    bool isModified() const { return mModified.loadAcquire(); }

    void removeChangedCallback(Callback callback)
    {
        QWriteLocker locker(&mRWLock);
        mCallbacks.removeOne(callback);
    }
    void addChangedCallback(Callback callback)
    {
        QWriteLocker locker(&mRWLock);
        mCallbacks.append(callback);
    }
    void clearChangedCallback()
    {
        QWriteLocker locker(&mRWLock);
        mCallbacks.clear();
    }

protected:
    virtual void onChanged(bool modified) { Q_UNUSED(modified); }

private:
    QVector<Callback> mCallbacks;
    QReadWriteLock mRWLock;
    QAtomicInt mModified;
};

#endif // _QEXTMODIFIEDFLAG_H
