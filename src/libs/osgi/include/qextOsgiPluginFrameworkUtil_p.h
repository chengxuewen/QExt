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

#ifndef QTKPLUGINFRAMEWORKUTIL_H
#define QTKPLUGINFRAMEWORKUTIL_H

#include "qtkpluginframework_global.h"

#include <QSharedPointer>
#include <QStringList>
#include <QDir>
#include <QMap>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPlugin;
class QTKPluginFrameworkContext;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginFrameworkUtil class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginFrameworkUtil
{
public:
    /**
     * @brief parseEntries
     * Parse strings of format:
     *
     *   ENTRY (, ENTRY)*
     *   ENTRY = key (; key)* (; PARAM)*
     *   PARAM = attribute '=' value
     *   PARAM = directive ':=' value
     *
     * @param strAttribute Attribute being parsed
     * @param strText String to parse
     * @param bSingle If true, only allow one key per ENTRY
     * @param bUnique Only allow unique parameters for each ENTRY.
     * @param bSingleEntry If true, only allow one ENTRY is allowed.
     * @return QMap<QString, QString> mapping attributes to values.
     * @exception QTKInvalidArgumentException If syntax error in input string.
     */
    static QList<QMap<QString, QStringList> > parseEntries(const QString &strAttribute, const QString &strText,
                                                           bool bSingle, bool bUnique, bool bSingleEntry);

    static QString getFrameworkDir(QTKPluginFrameworkContext *pPFWContext);

    /**
     * @brief getFileStorage
     * Check for local file storage directory.
     *
     * @param strName local directory name.
     * @return A QDir object pointing to the directory. The directory is
     *         guaranteed to exist.
     * @throws QTKRuntimeException if there is no global framework storage
     *         directory or if the directory could not be created.
     */
    static QDir getFileStorage(QTKPluginFrameworkContext *pPFWContext, const QString &strName);

    /**
     * @brief filterMatch
     * Check wildcard filter matches the string
     *
     * @param strFilter
     * @param str
     * @return
     */
    static bool filterMatch(const QString &strFilter, const QString &str);

private:
    static bool patSubstr(const QString &str, int iSi, const QString &strPat, int iPi);
};

bool pluginIdLessThan(const QSharedPointer<QTKPlugin> &plugin1, const QSharedPointer<QTKPlugin> &plugin2);

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINFRAMEWORKUTIL_H
