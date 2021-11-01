/****************************************************************************
** Library: QTK
**
** Copyright (c) German Cancer Research Center,
**     Division of Medical and Biological Informatics
** Copyright (c) chengxuewen <1398831004@qq.com>
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
** http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
****************************************************************************/

#include "qtkversion.h"

#include <QTKCore/QTKException>

#include <QStringListIterator>
#include <QDebug>

QTK_CORE_USE_NAMESPACE

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

const char *QTKVersion::SEPARATOR = ".";
const QRegExp QTKVersion::sm_regExp = QRegExp("[a-zA-Z0-9_\\-]*");

QTKVersion::QTKVersion(unsigned int uiMajorVersion, unsigned int uiMinorVersion, unsigned int uiMicroVersion)
    : m_uiMajorVersion(uiMajorVersion),
      m_uiMinorVersion(uiMinorVersion),
      m_uiMicroVersion(uiMicroVersion),
      m_strQualifier(""),
      m_bUndefined(false)
{

}

QTKVersion::QTKVersion(unsigned int uiMajorVersion, unsigned int uiMinorVersion, unsigned int uiMicroVersion,
                       const QString &strQualifier)
    : m_uiMajorVersion(uiMajorVersion),
      m_uiMinorVersion(uiMinorVersion),
      m_uiMicroVersion(uiMicroVersion),
      m_strQualifier(strQualifier),
      m_bUndefined(false)
{

}

QTKVersion::QTKVersion(const QString &strVersion)
    : m_uiMajorVersion(0),
      m_uiMinorVersion(0),
      m_uiMicroVersion(0),
      m_bUndefined(false)
{
    unsigned int uiMajor = 0;
    unsigned int uiMino = 0;
    unsigned int uiMicro = 0;
    QString strQual("");

    QStringList listSplit = strVersion.split(SEPARATOR);

    if (listSplit.empty()) {
        return;
    }

    QStringListIterator iter(listSplit);

    bool bOk = true;
    uiMajor = iter.next().toUInt(&bOk);

    if (iter.hasNext()) {
        uiMino = iter.next().toUInt(&bOk);
        if (iter.hasNext()) {
            uiMicro = iter.next().toUInt(&bOk);
            if (iter.hasNext()) {
                strQual = iter.next();
                if (iter.hasNext()) {
                    bOk = false;
                }
            }
        }
    }

    if (!bOk) {
        throw QTKInvalidArgumentException("invalid format");
    }

    m_uiMajorVersion = uiMajor;
    m_uiMinorVersion = uiMino;
    m_uiMicroVersion = uiMicro;
    m_strQualifier = strQual;
    this->validate();
}

QTKVersion::QTKVersion(const QTKVersion &version)
    : m_uiMajorVersion(version.m_uiMajorVersion),
      m_uiMinorVersion(version.m_uiMinorVersion),
      m_uiMicroVersion(version.m_uiMicroVersion),
      m_strQualifier(version.m_strQualifier),
      m_bUndefined(version.m_bUndefined)
{

}

QTKVersion QTKVersion::emptyVersion()
{
    static QTKVersion emptyV(false);
    return emptyV;
}

QTKVersion QTKVersion::undefinedVersion()
{
    static QTKVersion undefinedV(true);
    return undefinedV;
}

QTKVersion QTKVersion::parseVersion(const QString &strVersion)
{
    if (strVersion.isEmpty()) {
        return QTKVersion::emptyVersion();
    }

    QString strVersionTrimmed = strVersion.trimmed();
    if (strVersionTrimmed.isEmpty()) {
        return QTKVersion::emptyVersion();
    }

    return QTKVersion(strVersionTrimmed);
}

bool QTKVersion::isUndefined() const
{
    return m_bUndefined;
}

unsigned int QTKVersion::getMajor() const
{
    if (m_bUndefined) {
        throw QTKIllegalStateException("Version undefined");
    }
    return m_uiMajorVersion;
}

unsigned int QTKVersion::getMinor() const
{
    if (m_bUndefined) {
        throw QTKIllegalStateException("Version undefined");
    }
    return m_uiMinorVersion;
}

unsigned int QTKVersion::getMicro() const
{
    if (m_bUndefined) {
        throw QTKIllegalStateException("Version undefined");
    }
    return m_uiMicroVersion;
}

QString QTKVersion::getQualifier() const
{
    if (m_bUndefined) {
        throw QTKIllegalStateException("Version undefined");
    }
    return m_strQualifier;
}

QString QTKVersion::toString() const
{
    if (m_bUndefined) {
        return "undefined";
    }

    QString result;
    result += QString::number(m_uiMajorVersion) + SEPARATOR +
            QString::number(m_uiMinorVersion) + SEPARATOR +
            QString::number(m_uiMicroVersion);
    if (!m_strQualifier.isEmpty()) {
        result += SEPARATOR + m_strQualifier;
    }
    return result;
}

int QTKVersion::compare(const QTKVersion &other) const
{
    if (&other == this) { // quicktest
        return 0;
    }
    if (this->m_bUndefined || other.m_bUndefined) {
        throw QTKIllegalStateException("Cannot compare undefined version");
    }
    if (m_uiMajorVersion < other.m_uiMajorVersion) {
        return -1;
    }

    if (m_uiMajorVersion == other.m_uiMajorVersion) {
        if (m_uiMinorVersion < other.m_uiMinorVersion) {
            return -1;
        }

        if (m_uiMinorVersion == other.m_uiMinorVersion) {
            if (m_uiMicroVersion < other.m_uiMicroVersion) {
                return -1;
            }
            if (m_uiMicroVersion == other.m_uiMicroVersion) {
                return m_strQualifier.compare(other.m_strQualifier);
            }
        }
    }
    return 1;
}

bool QTKVersion::operator==(const QTKVersion &other) const
{
    if (&other == this) { // quicktest
        return true;
    }
    if (other.m_bUndefined && this->m_bUndefined) {
        return true;
    }
    if (this->m_bUndefined) {
        throw QTKIllegalStateException("Version undefined");
    }
    if (other.m_bUndefined) {
        return false;
    }

    return (m_uiMajorVersion == other.m_uiMajorVersion)
            && (m_uiMinorVersion == other.m_uiMinorVersion)
            && (m_uiMicroVersion == other.m_uiMicroVersion) &&
            m_strQualifier == other.m_strQualifier;
}

bool QTKVersion::operator<(const QTKVersion &other) const
{
    return this->compare(other) < 0;
}

void QTKVersion::validate()
{
    if (!sm_regExp.exactMatch(m_strQualifier)) {
        throw QTKInvalidArgumentException(QString("invalid qualifier: ") + m_strQualifier);
    }
    m_bUndefined = false;
}

QTKVersion::QTKVersion(bool bUndefined)
    : m_uiMajorVersion(0),
      m_uiMinorVersion(0),
      m_uiMicroVersion(0),
      m_strQualifier(""),
      m_bUndefined(bUndefined)
{

}

QTKVersion &QTKVersion::operator=(const QTKVersion &other)
{
    m_uiMajorVersion = other.m_uiMajorVersion;
    m_uiMinorVersion = other.m_uiMinorVersion;
    m_uiMicroVersion = other.m_uiMicroVersion;
    m_strQualifier = other.m_strQualifier;
    m_bUndefined = other.m_bUndefined;
    return *this;
}

QDebug operator<<(QDebug dbg, const QTKVersion &version)
{
    dbg << version.toString();
    return dbg.maybeSpace();
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
