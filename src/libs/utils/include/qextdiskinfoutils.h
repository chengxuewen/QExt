#ifndef QEXTDISKINFOUTILS_H
#define QEXTDISKINFOUTILS_H

#include <qextglobal.h>

#include <qextutilsglobal.h>

#include <QObject>

class QEXTDiskInfoUtilsPrivate;
class QEXT_UTILS_API QEXTDiskInfoUtils : public QObject
{
    Q_OBJECT

public:
    QEXTDiskInfoUtils(QObject *parent = QEXT_NULLPTR);
    QEXTDiskInfoUtils(const QEXTDiskInfoUtils &info, QObject *parent = QEXT_NULLPTR);
    ~QEXTDiskInfoUtils();

    QString getName() const;
    QString getUsedSize() const;
    QString getFreeSize() const;
    QString getAllSize() const;
    double getUsedPercent() const;

    bool compare(const QEXTDiskInfoUtils &info) const;
    QEXTDiskInfoUtils &copy(const QEXTDiskInfoUtils &info);

    friend bool operator==(const QEXTDiskInfoUtils &info1, const QEXTDiskInfoUtils &info2) {
        return info1.compare(info2);
    }
    friend bool operator!=(const QEXTDiskInfoUtils &info1, const QEXTDiskInfoUtils &info2) {
        return !info1.compare(info2);
    }
    QEXTDiskInfoUtils & operator=(const QEXTDiskInfoUtils &info) {
        return this->copy(info);
    }

public Q_SLOTS:
    void setName(const QString &strName);
    void setUsedSize(const QString &strSize);
    void setFreeSize(const QString &strSize);
    void setAllSize(const QString &strSize);
    void setUsedPercent(const double &dSize);

private:
    QEXTDiskInfoUtilsPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QEXTDiskInfoUtils)
};

#endif // QEXTDISKINFOUTILS_H
