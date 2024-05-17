#ifndef _QEXTATOMIC_H
#define _QEXTATOMIC_H

#include <qextGlobal.h>

#include <QAtomicPointer>

class QExtAtomicDouble
{
public:
    QExtAtomicDouble() : m_atomic(0) { }
    QExtAtomicDouble(double value) : m_atomic(doubleToInt64Ptr(value)) {}
    virtual ~QExtAtomicDouble() {}

    static double doubleFromInt64Ptr(qint64 *intVal)
    {
        return doubleFromInt64(breinterpret_cast<qint64>(intVal));
    }
    static double doubleFromInt64(qint64 intVal)
    {
        double dblValue = 0;
        memcpy(&dblValue, &intVal, qMin(sizeof(dblValue), sizeof(intVal)));
        return dblValue;
    }

    static qint64 *doubleToInt64Ptr(double dblValue)
    {
        return reinterpret_cast<qint64 *>(doubleToInt64(dblValue));
    }
    static qint64 doubleToInt64(double dblValue)
    {
        qint64 intVal = 0;
        memcpy(&intVal, &dblValue, qMin(sizeof(intVal), sizeof(dblValue)));
        return intVal;
    }

private:
    QAtomicPointer<qint64> m_atomic;
};

#endif // _QEXTATOMIC_H
