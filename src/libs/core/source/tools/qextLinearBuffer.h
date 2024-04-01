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
    QExtLinearBuffer() : m_buf(QEXT_NULLPTR), m_len(0), m_first(QEXT_NULLPTR), m_capacity(0) { }
    virtual ~QExtLinearBuffer()
    {
        delete [] m_buf;
    }

    void clear()
    {
        m_len = 0;
        delete [] m_buf;
        m_buf = QEXT_NULLPTR;
        m_first = m_buf;
        m_capacity = 0;
    }
    qint64 size() const { return m_len; }
    bool isEmpty() const { return m_len == 0; }
    void skip(qint64 n)
    {
        if (n >= m_len)
        {
            this->clear();
        }
        else
        {
            m_len -= n;
            m_first += n;
        }
    }
    int getChar()
    {
        if (m_len == 0)
        {
            return -1;
        }
        int ch = uchar(*m_first);
        m_len--;
        m_first++;
        return ch;
    }
    qint64 read(char *target, qint64 size)
    {
        qint64 r = qMin(size, m_len);
        if (r)
        {
            memcpy(target, m_first, r);
            m_len -= r;
            m_first += r;
        }
        return r;
    }
    qint64 peek(char *target, qint64 size)
    {
        qint64 r = qMin(size, m_len);
        if (r)
        {
            memcpy(target, m_first, r);
        }
        return r;
    }
    char *reserve(qint64 size)
    {
        this->makeSpace(size + m_len, freeSpaceAtEnd);
        char *writePtr = m_first + m_len;
        m_len += size;
        return writePtr;
    }
    void chop(qint64 size)
    {
        if (size >= m_len)
        {
            this->clear();
        }
        else
        {
            m_len -= size;
        }
    }
    QByteArray readAll()
    {
        QByteArray retVal(m_first, m_len);
        this->clear();
        return retVal;
    }
    qint64 readLine(char *target, qint64 size)
    {
        qint64 r = qMin(size, m_len);
        char *eol = static_cast<char *>(memchr(m_first, '\n', r));
        if (eol)
        {
            r = 1 + (eol - m_first);
        }
        memcpy(target, m_first, r);
        m_len -= r;
        m_first += r;
        return r;
    }
    bool canReadLine() const
    {
        return m_first && memchr(m_first, '\n', m_len);
    }
    void ungetChar(char c)
    {
        if (m_first == m_buf)
        {
            // underflow, the existing valid data needs to move to the end of the (potentially bigger) buffer
            this->makeSpace(m_len+1, freeSpaceAtStart);
        }
        m_first--;
        m_len++;
        *m_first = c;
    }
    void ungetBlock(const char *block, qint64 size)
    {
        if ((m_first - m_buf) < size)
        {
            // underflow, the existing valid data needs to move to the end of the (potentially bigger) buffer
            this->makeSpace(m_len + size, freeSpaceAtStart);
        }
        m_first -= size;
        m_len += size;
        memcpy(m_first, block, size);
    }

private:
    enum FreeSpacePos {freeSpaceAtStart, freeSpaceAtEnd};
    void makeSpace(size_t required, FreeSpacePos where)
    {
        size_t newCapacity = qMax(m_capacity, size_t(QEXT_LINEAR_BUFFER_SIZE));
        while (newCapacity < required)
        {
            newCapacity *= 2;
        }
        const size_t moveOffset = (where == freeSpaceAtEnd) ? 0 : newCapacity - size_t(m_len);
        if (newCapacity > m_capacity)
        {
            // allocate more space
            char *newBuf = new char[newCapacity];
            if (m_first)
            {
                memmove(newBuf + moveOffset, m_first, m_len);
            }
            delete [] m_buf;
            m_buf = newBuf;
            m_capacity = newCapacity;
        }
        else
        {
            // shift any existing data to make space
            memmove(m_buf + moveOffset, m_first, m_len);
        }
        m_first = m_buf + moveOffset;
    }

private:
    // the allocated buffer
    char *m_buf;
    // length of the unread data
    qint64 m_len;
    // start of the unread data
    char* m_first;
    // allocated buffer size
    size_t m_capacity;
};

#endif // _QEXTLINEARBUFFER_H
