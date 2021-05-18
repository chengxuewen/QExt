#ifndef QEXTDISKINFO_H
#define QEXTDISKINFO_H

#include <qextobject.h>

#include <qextutilsglobal.h>

#include <QObject>



class QEXT_UTILS_API QEXTDiskInfo
{
public:
    QEXTDiskInfo();
    QEXTDiskInfo(const QEXTDiskInfo &info);
    ~QEXTDiskInfo();

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

    bool compare(const QEXTDiskInfo &info) const;
    QEXTDiskInfo &copy(const QEXTDiskInfo &info);

    friend bool operator==(const QEXTDiskInfo &info1, const QEXTDiskInfo &info2) {
        return info1.compare(info2);
    }
    friend bool operator!=(const QEXTDiskInfo &info1, const QEXTDiskInfo &info2) {
        return !info1.compare(info2);
    }
    QEXTDiskInfo &operator=(const QEXTDiskInfo &info) {
        return this->copy(info);
    }

protected:
    QString m_name;
    QString m_usedSize;
    QString m_freeSize;
    QString m_allSize;
    double m_usedPercent;
};



#endif // QEXTDISKINFO_H
