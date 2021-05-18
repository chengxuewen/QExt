#include <qextdiskinfo.h>

#include <QDebug>
#include <QProcess>
#include <QFileInfo>
#include <QTimer>
#include <QDir>

#ifdef Q_OS_WIN
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x502
#endif
#include "windows.h"
#endif
#define GB (1024 * 1024 * 1024)
#define MB (1024 * 1024)
#define KB (1024)





QEXTDiskInfo::QEXTDiskInfo()
{
}

QEXTDiskInfo::QEXTDiskInfo(const QEXTDiskInfo &info)
{
    this->copy(info);
}

QEXTDiskInfo::~QEXTDiskInfo()
{

}

bool QEXTDiskInfo::compare(const QEXTDiskInfo &info) const
{
    if (info.name() != m_name) {
        return false;
    }
    if (info.usedSize() != m_usedSize) {
        return false;
    }
    if (info.freeSize() != m_freeSize) {
        return false;
    }
    if (info.allSize() != m_allSize) {
        return false;
    }
    if (info.usedPercent() != m_usedPercent) {
        return false;
    }
    return true;
}

QEXTDiskInfo &QEXTDiskInfo::copy(const QEXTDiskInfo &info)
{
    m_name = info.name();
    m_usedSize = info.usedSize();
    m_freeSize = info.freeSize();
    m_allSize = info.allSize();
    m_usedPercent = info.usedPercent();
    return *this;
}
