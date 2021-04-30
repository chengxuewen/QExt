#include "qextdiskinfoutils.h"
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

class QEXTDiskInfoUtilsPrivate
{
public:
    QEXTDiskInfoUtilsPrivate();
    ~QEXTDiskInfoUtilsPrivate();

private:
    QEXTDiskInfoUtils *q_ptr;
    Q_DECLARE_PUBLIC(QEXTDiskInfoUtils)

    QString m_strName;
    QString m_strUsedSize;
    QString m_strFreeSize;
    QString m_strAllSize;
    double m_dUsedPercent;
};

/**
 *@brief:
 *@param:
 *@return:
**/
QEXTDiskInfoUtilsPrivate::QEXTDiskInfoUtilsPrivate()
{
    m_strName = "";
    m_strUsedSize = "";
    m_strFreeSize = "";
    m_strAllSize = "";
    m_dUsedPercent = 0;
}

/**
 *@brief:
 *@param:
 *@return:
**/
QEXTDiskInfoUtilsPrivate::~QEXTDiskInfoUtilsPrivate()
{

}

/***************************************************************************************************
 *@Brief:
***************************************************************************************************/

/**
 *@brief:
 *@param:
 *@return:
**/
QEXTDiskInfoUtils::QEXTDiskInfoUtils(QObject *parent) : QObject(parent)
{
    d_ptr = new QEXTDiskInfoUtilsPrivate();
    d_ptr->q_ptr = this;
}

/**
 *@brief:
 *@param:
 *@return:
**/
QEXTDiskInfoUtils::QEXTDiskInfoUtils(const QEXTDiskInfoUtils &info, QObject *parent) : QObject(parent)
{
    d_ptr = new QEXTDiskInfoUtilsPrivate();
    d_ptr->q_ptr = this;
    this->copy(info);
}

/**
 *@brief:
 *@param:
 *@return:
**/
QEXTDiskInfoUtils::~QEXTDiskInfoUtils()
{
    delete d_ptr;
}

/**
 *@brief:
 *@param:
 *@return:
**/
QString QEXTDiskInfoUtils::getName() const
{
    return d_ptr->m_strName;
}

/**
 *@brief:
 *@param:
 *@return:
**/
QString QEXTDiskInfoUtils::getUsedSize() const
{
    return d_ptr->m_strUsedSize;
}

/**
 *@brief:
 *@param:
 *@return:
**/
QString QEXTDiskInfoUtils::getFreeSize() const
{
    return d_ptr->m_strFreeSize;
}

/**
 *@brief:
 *@param:
 *@return:
**/
QString QEXTDiskInfoUtils::getAllSize() const
{
    return d_ptr->m_strAllSize;
}

/**
 *@brief:
 *@param:
 *@return:
**/
double QEXTDiskInfoUtils::getUsedPercent() const
{
    return d_ptr->m_dUsedPercent;
}

/**
 *@brief:
 *@param:
 *@return:
**/
bool QEXTDiskInfoUtils::compare(const QEXTDiskInfoUtils &info) const
{
    if (info.getName() != d_ptr->m_strName) {
        return false;
    }
    if (info.getUsedSize() != d_ptr->m_strUsedSize) {
        return false;
    }
    if (info.getFreeSize() != d_ptr->m_strFreeSize) {
        return false;
    }
    if (info.getAllSize() != d_ptr->m_strAllSize) {
        return false;
    }
    if (info.getUsedPercent() != d_ptr->m_dUsedPercent) {
        return false;
    }
    return true;
}

/**
 *@brief:
 *@param:
 *@return:
**/
QEXTDiskInfoUtils &QEXTDiskInfoUtils::copy(const QEXTDiskInfoUtils &info)
{
    d_ptr->m_strName = info.getName();
    d_ptr->m_strUsedSize = info.getUsedSize();
    d_ptr->m_strFreeSize = info.getFreeSize();
    d_ptr->m_strAllSize = info.getAllSize();
    d_ptr->m_dUsedPercent = info.getUsedPercent();
    return *this;
}

/**
 *@brief:
 *@param:
 *@return:
**/
void QEXTDiskInfoUtils::setName(const QString &strName)
{
    d_ptr->m_strName = strName;
}

/**
 *@brief:
 *@param:
 *@return:
**/
void QEXTDiskInfoUtils::setUsedSize(const QString &strSize)
{
    d_ptr->m_strUsedSize = strSize;
}

/**
 *@brief:
 *@param:
 *@return:
**/
void QEXTDiskInfoUtils::setFreeSize(const QString &strSize)
{
    d_ptr->m_strFreeSize = strSize;
}

/**
 *@brief:
 *@param:
 *@return:
**/
void QEXTDiskInfoUtils::setAllSize(const QString &strSize)
{
    d_ptr->m_strAllSize = strSize;
}

/**
 *@brief:
 *@param:
 *@return:
**/
void QEXTDiskInfoUtils::setUsedPercent(const double &dSize)
{
    d_ptr->m_dUsedPercent = dSize;
}
