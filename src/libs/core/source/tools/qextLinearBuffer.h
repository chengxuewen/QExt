#ifndef _QEXTLINEARBUFFER_H
#define _QEXTLINEARBUFFER_H

#include <qextGlobal.h>

#ifndef QEXT_LINEAR_BUFFER_SIZE
#   define QEXT_LINEAR_BUFFER_SIZE Q_INT64_C(16384)
#endif

// This is QIODevice's read buffer, optimized for read(), isEmpty() and getChar()
class QEXT_CORE_API QExtLinearBuffer
{
public:
    QExtLinearBuffer() : mBuf(QEXT_NULLPTR), mLen(0), mFirst(QEXT_NULLPTR), mCapacity(0) { }
    virtual ~QExtLinearBuffer()
    {
        delete [] mBuf;
    }

    void clear()
    {
        mLen = 0;
        delete [] mBuf;
        mBuf = QEXT_NULLPTR;
        mFirst = mBuf;
        mCapacity = 0;
    }
    qint64 size() const { return mLen; }
    bool isEmpty() const { return mLen == 0; }
    void skip(qint64 n)
    {
        if (n >= mLen)
        {
            this->clear();
        }
        else
        {
            mLen -= n;
            mFirst += n;
        }
    }
    char getChar(bool *ok = QEXT_NULLPTR)
    {
        if (ok)
        {
            *ok = 0 != mLen;
        }
        if (mLen == 0)
        {
            return 0;
        }
        char ch = *mFirst;
        mLen--;
        mFirst++;
        return ch;
    }
    qint64 read(char *target, qint64 size)
    {
        qint64 r = qMin(size, mLen);
        if (r)
        {
            memcpy(target, mFirst, r);
            mLen -= r;
            mFirst += r;
        }
        return r;
    }
    qint64 peek(char *target, qint64 size)
    {
        qint64 r = qMin(size, mLen);
        if (r)
        {
            memcpy(target, mFirst, r);
        }
        return r;
    }
    char *reserve(qint64 size)
    {
        this->makeSpace(size + mLen, freeSpaceAtEnd);
        char *writePtr = mFirst + mLen;
        mLen += size;
        return writePtr;
    }
    void chop(qint64 size)
    {
        if (size >= mLen)
        {
            this->clear();
        }
        else
        {
            mLen -= size;
        }
    }
    QByteArray readAll()
    {
        QByteArray bytes(mFirst, mLen);
        this->clear();
        return bytes;
    }
    qint64 readLine(char *target, qint64 size)
    {
        qint64 r = qMin(size, mLen);
        char *eol = static_cast<char *>(memchr(mFirst, '\n', r));
        if (eol)
        {
            r = 1 + (eol - mFirst);
        }
        memcpy(target, mFirst, r);
        mLen -= r;
        mFirst += r;
        return r;
    }
    bool canReadLine() const
    {
        return mFirst && memchr(mFirst, '\n', mLen);
    }
    void ungetChar(char c)
    {
        if (mFirst == mBuf)
        {
            // underflow, the existing valid data needs to move to the end of the (potentially bigger) buffer
            this->makeSpace(mLen+1, freeSpaceAtStart);
        }
        mFirst--;
        mLen++;
        *mFirst = c;
    }
    void ungetBlock(const char *block, qint64 size)
    {
        if ((mFirst - mBuf) < size)
        {
            // underflow, the existing valid data needs to move to the end of the (potentially bigger) buffer
            this->makeSpace(mLen + size, freeSpaceAtStart);
        }
        mFirst -= size;
        mLen += size;
        memcpy(mFirst, block, size);
    }

private:
    enum FreeSpacePos {freeSpaceAtStart, freeSpaceAtEnd};
    void makeSpace(size_t required, FreeSpacePos where)
    {
        size_t newCapacity = qMax(mCapacity, size_t(QEXT_LINEAR_BUFFER_SIZE));
        while (newCapacity < required)
        {
            newCapacity *= 2;
        }
        const size_t moveOffset = (where == freeSpaceAtEnd) ? 0 : newCapacity - size_t(mLen);
        if (newCapacity > mCapacity)
        {
            // allocate more space
            char *newBuf = new char[newCapacity];
            if (mFirst)
            {
                memmove(newBuf + moveOffset, mFirst, mLen);
            }
            delete [] mBuf;
            mBuf = newBuf;
            mCapacity = newCapacity;
        }
        else
        {
            // shift any existing data to make space
            memmove(mBuf + moveOffset, mFirst, mLen);
        }
        mFirst = mBuf + moveOffset;
    }

private:
    // the allocated buffer
    char *mBuf;
    // length of the unread data
    qint64 mLen;
    // start of the unread data
    char* mFirst;
    // allocated buffer size
    size_t mCapacity;
};

#endif // _QEXTLINEARBUFFER_H
