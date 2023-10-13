#ifndef _QEXTDISKINFO_H
#define _QEXTDISKINFO_H

#include "qextUtilsGlobal.h"

#include <QObject>

class QEXT_UTILS_API QExtDiskInfo
{
public:
    QExtDiskInfo();
    QExtDiskInfo(const QExtDiskInfo &info);
    ~QExtDiskInfo();

    QString name() const { return m_name; }
    void setName(const QString &name) { m_name = name; }

    QString usedSize() const { return m_usedSize; }
    void setUsedSize(const QString &size) { m_usedSize = size; }

    QString freeSize() const { return m_freeSize; }
    void setFreeSize(const QString &size) { m_freeSize = size; }

    QString allSize() const { return m_allSize; }
    void setAllSize(const QString &size) { m_allSize = size; }

    double usedPercent() const { return m_usedPercent; }
    void setUsedPercent(double percent) { m_usedPercent = percent; }

    bool compare(const QExtDiskInfo &info) const;
    QExtDiskInfo &copy(const QExtDiskInfo &info);

    friend bool operator==(const QExtDiskInfo &info1, const QExtDiskInfo &info2) {
        return info1.compare(info2);
    }
    friend bool operator!=(const QExtDiskInfo &info1, const QExtDiskInfo &info2) {
        return !info1.compare(info2);
    }
    QExtDiskInfo &operator=(const QExtDiskInfo &info) {
        return this->copy(info);
    }

protected:
    QString m_name;
    QString m_usedSize;
    QString m_freeSize;
    QString m_allSize;
    double m_usedPercent;
};



#endif // _QEXTDISKINFO_H
